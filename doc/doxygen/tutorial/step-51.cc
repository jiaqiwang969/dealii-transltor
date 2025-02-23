/* ---------------------------------------------------------------------
 *
 * Copyright (C) 2013 - 2021 by the deal.II authors
 *
 * This file is part of the deal.II library.
 *
 * The deal.II library is free software; you can use it, redistribute
 * it, and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * The full text of the license can be found in the file LICENSE.md at
 * the top level directory of deal.II.
 *
 * ---------------------------------------------------------------------

 *
 * Author: Martin Kronbichler, Technische Universität München,
 *         Scott T. Miller, The Pennsylvania State University, 2013
 */

#include <deal.II/base/quadrature_lib.h>
#include <deal.II/base/function.h>
#include <deal.II/base/tensor_function.h>
#include <deal.II/base/exceptions.h>
#include <deal.II/base/logstream.h>
#include <deal.II/base/work_stream.h>
#include <deal.II/base/convergence_table.h>
#include <deal.II/lac/vector.h>
#include <deal.II/lac/affine_constraints.h>
#include <deal.II/lac/full_matrix.h>
#include <deal.II/lac/dynamic_sparsity_pattern.h>
#include <deal.II/lac/solver_bicgstab.h>
#include <deal.II/lac/precondition.h>
#include <deal.II/grid/tria.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_refinement.h>
#include <deal.II/dofs/dof_handler.h>
#include <deal.II/dofs/dof_renumbering.h>
#include <deal.II/dofs/dof_tools.h>
#include <deal.II/fe/fe_dgq.h>
#include <deal.II/fe/fe_system.h>
#include <deal.II/fe/fe_values.h>
#include <deal.II/numerics/vector_tools.h>
#include <deal.II/numerics/error_estimator.h>
#include <deal.II/numerics/matrix_tools.h>
#include <deal.II/numerics/data_out.h>

#include <deal.II/fe/fe_face.h>

#include <deal.II/lac/chunk_sparse_matrix.h>

#include <deal.II/numerics/data_out_faces.h>

#include <iostream>



namespace Step51
{
  using namespace dealii;

  template <int dim>
  class SolutionBase
  {
  protected:
    static const unsigned int n_source_centers = 3;
    static const Point<dim>   source_centers[n_source_centers];
    static const double       width;
  };


  template <>
  const Point<1>
    SolutionBase<1>::source_centers[SolutionBase<1>::n_source_centers] =
      {Point<1>(-1.0 / 3.0), Point<1>(0.0), Point<1>(+1.0 / 3.0)};


  template <>
  const Point<2>
    SolutionBase<2>::source_centers[SolutionBase<2>::n_source_centers] =
      {Point<2>(-0.5, +0.5), Point<2>(-0.5, -0.5), Point<2>(+0.5, -0.5)};

  template <>
  const Point<3>
    SolutionBase<3>::source_centers[SolutionBase<3>::n_source_centers] = {
      Point<3>(-0.5, +0.5, 0.25),
      Point<3>(-0.6, -0.5, -0.125),
      Point<3>(+0.5, -0.5, 0.5)};

  template <int dim>
  const double SolutionBase<dim>::width = 1. / 5.;


  template <int dim>
  class Solution : public Function<dim>, protected SolutionBase<dim>
  {
  public:
    virtual double value(const Point<dim> &p,
                         const unsigned int /*component*/ = 0) const override
    {
      double sum = 0;
      for (unsigned int i = 0; i < this->n_source_centers; ++i)
        {
          const Tensor<1, dim> x_minus_xi = p - this->source_centers[i];
          sum +=
            std::exp(-x_minus_xi.norm_square() / (this->width * this->width));
        }

      return sum /
             std::pow(2. * numbers::PI * this->width * this->width, dim / 2.);
    }

    virtual Tensor<1, dim>
    gradient(const Point<dim> &p,
             const unsigned int /*component*/ = 0) const override
    {
      Tensor<1, dim> sum;
      for (unsigned int i = 0; i < this->n_source_centers; ++i)
        {
          const Tensor<1, dim> x_minus_xi = p - this->source_centers[i];

          sum +=
            (-2 / (this->width * this->width) *
             std::exp(-x_minus_xi.norm_square() / (this->width * this->width)) *
             x_minus_xi);
        }

      return sum /
             std::pow(2. * numbers::PI * this->width * this->width, dim / 2.);
    }
  };



  template <int dim>
  class SolutionAndGradient : public Function<dim>, protected SolutionBase<dim>
  {
  public:
    SolutionAndGradient()
      : Function<dim>(dim + 1)
    {}

    virtual void vector_value(const Point<dim> &p,
                              Vector<double> &  v) const override
    {
      AssertDimension(v.size(), dim + 1);
      Solution<dim>  solution;
      Tensor<1, dim> grad = solution.gradient(p);
      for (unsigned int d = 0; d < dim; ++d)
        v[d] = -grad[d];
      v[dim] = solution.value(p);
    }
  };



  template <int dim>
  class ConvectionVelocity : public TensorFunction<1, dim>
  {
  public:
    ConvectionVelocity()
      : TensorFunction<1, dim>()
    {}

    virtual Tensor<1, dim> value(const Point<dim> &p) const override
    {
      Tensor<1, dim> convection;
      switch (dim)
        {
          case 1:
            convection[0] = 1;
            break;
          case 2:
            convection[0] = p[1];
            convection[1] = -p[0];
            break;
          case 3:
            convection[0] = p[1];
            convection[1] = -p[0];
            convection[2] = 1;
            break;
          default:
            Assert(false, ExcNotImplemented());
        }
      return convection;
    }
  };



  template <int dim>
  class RightHandSide : public Function<dim>, protected SolutionBase<dim>
  {
  public:
    virtual double value(const Point<dim> &p,
                         const unsigned int /*component*/ = 0) const override
    {
      ConvectionVelocity<dim> convection_velocity;
      Tensor<1, dim>          convection = convection_velocity.value(p);
      double                  sum        = 0;
      for (unsigned int i = 0; i < this->n_source_centers; ++i)
        {
          const Tensor<1, dim> x_minus_xi = p - this->source_centers[i];

          sum +=
            ((2 * dim - 2 * convection * x_minus_xi -
              4 * x_minus_xi.norm_square() / (this->width * this->width)) /
             (this->width * this->width) *
             std::exp(-x_minus_xi.norm_square() / (this->width * this->width)));
        }

      return sum /
             std::pow(2. * numbers::PI * this->width * this->width, dim / 2.);
    }
  };




  template <int dim>
  class HDG
  {
  public:
    enum RefinementMode
    {
      global_refinement,
      adaptive_refinement
    };

    HDG(const unsigned int degree, const RefinementMode refinement_mode);
    void run();

  private:
    void setup_system();
    void assemble_system(const bool reconstruct_trace = false);
    void solve();
    void postprocess();
    void refine_grid(const unsigned int cycle);
    void output_results(const unsigned int cycle);

    struct PerTaskData;
    struct ScratchData;

    struct PostProcessScratchData;

    void assemble_system_one_cell(
      const typename DoFHandler<dim>::active_cell_iterator &cell,
      ScratchData &                                         scratch,
      PerTaskData &                                         task_data);

    void copy_local_to_global(const PerTaskData &data);

    void postprocess_one_cell(
      const typename DoFHandler<dim>::active_cell_iterator &cell,
      PostProcessScratchData &                              scratch,
      unsigned int &                                        empty_data);


    Triangulation<dim> triangulation;

    FESystem<dim>   fe_local;
    DoFHandler<dim> dof_handler_local;
    Vector<double>  solution_local;

    FE_FaceQ<dim>   fe;
    DoFHandler<dim> dof_handler;
    Vector<double>  solution;
    Vector<double>  system_rhs;

    FE_DGQ<dim>     fe_u_post;
    DoFHandler<dim> dof_handler_u_post;
    Vector<double>  solution_u_post;

    AffineConstraints<double> constraints;

    ChunkSparsityPattern      sparsity_pattern;
    ChunkSparseMatrix<double> system_matrix;

    const RefinementMode refinement_mode;
    ConvergenceTable     convergence_table;
  };


  template <int dim>
  HDG<dim>::HDG(const unsigned int degree, const RefinementMode refinement_mode)
    : fe_local(FE_DGQ<dim>(degree), dim, FE_DGQ<dim>(degree), 1)
    , dof_handler_local(triangulation)
    , fe(degree)
    , dof_handler(triangulation)
    , fe_u_post(degree + 1)
    , dof_handler_u_post(triangulation)
    , refinement_mode(refinement_mode)
  {}



  template <int dim>
  void HDG<dim>::setup_system()
  {
    dof_handler_local.distribute_dofs(fe_local);
    dof_handler.distribute_dofs(fe);
    dof_handler_u_post.distribute_dofs(fe_u_post);

    std::cout << "   Number of degrees of freedom: " << dof_handler.n_dofs()
              << std::endl;

    solution.reinit(dof_handler.n_dofs());
    system_rhs.reinit(dof_handler.n_dofs());

    solution_local.reinit(dof_handler_local.n_dofs());
    solution_u_post.reinit(dof_handler_u_post.n_dofs());

    constraints.clear();
    DoFTools::make_hanging_node_constraints(dof_handler, constraints);
    std::map<types::boundary_id, const Function<dim> *> boundary_functions;
    Solution<dim>                                       solution_function;
    boundary_functions[0] = &solution_function;
    VectorTools::project_boundary_values(dof_handler,
                                         boundary_functions,
                                         QGauss<dim - 1>(fe.degree + 1),
                                         constraints);
    constraints.close();

    {
      DynamicSparsityPattern dsp(dof_handler.n_dofs());
      DoFTools::make_sparsity_pattern(dof_handler, dsp, constraints, false);
      sparsity_pattern.copy_from(dsp, fe.n_dofs_per_face());
    }
    system_matrix.reinit(sparsity_pattern);
  }



  template <int dim>
  struct HDG<dim>::PerTaskData
  {
    FullMatrix<double>                   cell_matrix;
    Vector<double>                       cell_vector;
    std::vector<types::global_dof_index> dof_indices;

    bool trace_reconstruct;

    PerTaskData(const unsigned int n_dofs, const bool trace_reconstruct)
      : cell_matrix(n_dofs, n_dofs)
      , cell_vector(n_dofs)
      , dof_indices(n_dofs)
      , trace_reconstruct(trace_reconstruct)
    {}
  };



  template <int dim>
  struct HDG<dim>::ScratchData
  {
    FEValues<dim>     fe_values_local;
    FEFaceValues<dim> fe_face_values_local;
    FEFaceValues<dim> fe_face_values;

    FullMatrix<double> ll_matrix;
    FullMatrix<double> lf_matrix;
    FullMatrix<double> fl_matrix;
    FullMatrix<double> tmp_matrix;
    Vector<double>     l_rhs;
    Vector<double>     tmp_rhs;

    std::vector<Tensor<1, dim>> q_phi;
    std::vector<double>         q_phi_div;
    std::vector<double>         u_phi;
    std::vector<Tensor<1, dim>> u_phi_grad;
    std::vector<double>         tr_phi;
    std::vector<double>         trace_values;

    std::vector<std::vector<unsigned int>> fe_local_support_on_face;
    std::vector<std::vector<unsigned int>> fe_support_on_face;

    ConvectionVelocity<dim> convection_velocity;
    RightHandSide<dim>      right_hand_side;
    const Solution<dim>     exact_solution;

    ScratchData(const FiniteElement<dim> &fe,
                const FiniteElement<dim> &fe_local,
                const QGauss<dim> &       quadrature_formula,
                const QGauss<dim - 1> &   face_quadrature_formula,
                const UpdateFlags         local_flags,
                const UpdateFlags         local_face_flags,
                const UpdateFlags         flags)
      : fe_values_local(fe_local, quadrature_formula, local_flags)
      , fe_face_values_local(fe_local,
                             face_quadrature_formula,
                             local_face_flags)
      , fe_face_values(fe, face_quadrature_formula, flags)
      , ll_matrix(fe_local.n_dofs_per_cell(), fe_local.n_dofs_per_cell())
      , lf_matrix(fe_local.n_dofs_per_cell(), fe.n_dofs_per_cell())
      , fl_matrix(fe.n_dofs_per_cell(), fe_local.n_dofs_per_cell())
      , tmp_matrix(fe.n_dofs_per_cell(), fe_local.n_dofs_per_cell())
      , l_rhs(fe_local.n_dofs_per_cell())
      , tmp_rhs(fe_local.n_dofs_per_cell())
      , q_phi(fe_local.n_dofs_per_cell())
      , q_phi_div(fe_local.n_dofs_per_cell())
      , u_phi(fe_local.n_dofs_per_cell())
      , u_phi_grad(fe_local.n_dofs_per_cell())
      , tr_phi(fe.n_dofs_per_cell())
      , trace_values(face_quadrature_formula.size())
      , fe_local_support_on_face(GeometryInfo<dim>::faces_per_cell)
      , fe_support_on_face(GeometryInfo<dim>::faces_per_cell)
      , exact_solution()
    {
      for (unsigned int face_no : GeometryInfo<dim>::face_indices())
        for (unsigned int i = 0; i < fe_local.n_dofs_per_cell(); ++i)
          {
            if (fe_local.has_support_on_face(i, face_no))
              fe_local_support_on_face[face_no].push_back(i);
          }

      for (unsigned int face_no : GeometryInfo<dim>::face_indices())
        for (unsigned int i = 0; i < fe.n_dofs_per_cell(); ++i)
          {
            if (fe.has_support_on_face(i, face_no))
              fe_support_on_face[face_no].push_back(i);
          }
    }

    ScratchData(const ScratchData &sd)
      : fe_values_local(sd.fe_values_local.get_fe(),
                        sd.fe_values_local.get_quadrature(),
                        sd.fe_values_local.get_update_flags())
      , fe_face_values_local(sd.fe_face_values_local.get_fe(),
                             sd.fe_face_values_local.get_quadrature(),
                             sd.fe_face_values_local.get_update_flags())
      , fe_face_values(sd.fe_face_values.get_fe(),
                       sd.fe_face_values.get_quadrature(),
                       sd.fe_face_values.get_update_flags())
      , ll_matrix(sd.ll_matrix)
      , lf_matrix(sd.lf_matrix)
      , fl_matrix(sd.fl_matrix)
      , tmp_matrix(sd.tmp_matrix)
      , l_rhs(sd.l_rhs)
      , tmp_rhs(sd.tmp_rhs)
      , q_phi(sd.q_phi)
      , q_phi_div(sd.q_phi_div)
      , u_phi(sd.u_phi)
      , u_phi_grad(sd.u_phi_grad)
      , tr_phi(sd.tr_phi)
      , trace_values(sd.trace_values)
      , fe_local_support_on_face(sd.fe_local_support_on_face)
      , fe_support_on_face(sd.fe_support_on_face)
      , exact_solution()
    {}
  };



  template <int dim>
  struct HDG<dim>::PostProcessScratchData
  {
    FEValues<dim> fe_values_local;
    FEValues<dim> fe_values;

    std::vector<double>         u_values;
    std::vector<Tensor<1, dim>> u_gradients;
    FullMatrix<double>          cell_matrix;

    Vector<double> cell_rhs;
    Vector<double> cell_sol;

    PostProcessScratchData(const FiniteElement<dim> &fe,
                           const FiniteElement<dim> &fe_local,
                           const QGauss<dim> &       quadrature_formula,
                           const UpdateFlags         local_flags,
                           const UpdateFlags         flags)
      : fe_values_local(fe_local, quadrature_formula, local_flags)
      , fe_values(fe, quadrature_formula, flags)
      , u_values(quadrature_formula.size())
      , u_gradients(quadrature_formula.size())
      , cell_matrix(fe.n_dofs_per_cell(), fe.n_dofs_per_cell())
      , cell_rhs(fe.n_dofs_per_cell())
      , cell_sol(fe.n_dofs_per_cell())
    {}

    PostProcessScratchData(const PostProcessScratchData &sd)
      : fe_values_local(sd.fe_values_local.get_fe(),
                        sd.fe_values_local.get_quadrature(),
                        sd.fe_values_local.get_update_flags())
      , fe_values(sd.fe_values.get_fe(),
                  sd.fe_values.get_quadrature(),
                  sd.fe_values.get_update_flags())
      , u_values(sd.u_values)
      , u_gradients(sd.u_gradients)
      , cell_matrix(sd.cell_matrix)
      , cell_rhs(sd.cell_rhs)
      , cell_sol(sd.cell_sol)
    {}
  };



  template <int dim>
  void HDG<dim>::assemble_system(const bool trace_reconstruct)
  {
    const QGauss<dim>     quadrature_formula(fe.degree + 1);
    const QGauss<dim - 1> face_quadrature_formula(fe.degree + 1);

    const UpdateFlags local_flags(update_values | update_gradients |
                                  update_JxW_values | update_quadrature_points);

    const UpdateFlags local_face_flags(update_values);

    const UpdateFlags flags(update_values | update_normal_vectors |
                            update_quadrature_points | update_JxW_values);

    PerTaskData task_data(fe.n_dofs_per_cell(), trace_reconstruct);
    ScratchData scratch(fe,
                        fe_local,
                        quadrature_formula,
                        face_quadrature_formula,
                        local_flags,
                        local_face_flags,
                        flags);

    WorkStream::run(dof_handler.begin_active(),
                    dof_handler.end(),
                    *this,
                    &HDG<dim>::assemble_system_one_cell,
                    &HDG<dim>::copy_local_to_global,
                    scratch,
                    task_data);
  }



  template <int dim>
  void HDG<dim>::assemble_system_one_cell(
    const typename DoFHandler<dim>::active_cell_iterator &cell,
    ScratchData &                                         scratch,
    PerTaskData &                                         task_data)
  {
    typename DoFHandler<dim>::active_cell_iterator loc_cell(&triangulation,
                                                            cell->level(),
                                                            cell->index(),
                                                            &dof_handler_local);

    const unsigned int n_q_points =
      scratch.fe_values_local.get_quadrature().size();
    const unsigned int n_face_q_points =
      scratch.fe_face_values_local.get_quadrature().size();

    const unsigned int loc_dofs_per_cell =
      scratch.fe_values_local.get_fe().n_dofs_per_cell();

    const FEValuesExtractors::Vector fluxes(0);
    const FEValuesExtractors::Scalar scalar(dim);

    scratch.ll_matrix = 0;
    scratch.l_rhs     = 0;
    if (!task_data.trace_reconstruct)
      {
        scratch.lf_matrix     = 0;
        scratch.fl_matrix     = 0;
        task_data.cell_matrix = 0;
        task_data.cell_vector = 0;
      }
    scratch.fe_values_local.reinit(loc_cell);

    for (unsigned int q = 0; q < n_q_points; ++q)
      {
        const double rhs_value = scratch.right_hand_side.value(
          scratch.fe_values_local.quadrature_point(q));
        const Tensor<1, dim> convection = scratch.convection_velocity.value(
          scratch.fe_values_local.quadrature_point(q));
        const double JxW = scratch.fe_values_local.JxW(q);
        for (unsigned int k = 0; k < loc_dofs_per_cell; ++k)
          {
            scratch.q_phi[k] = scratch.fe_values_local[fluxes].value(k, q);
            scratch.q_phi_div[k] =
              scratch.fe_values_local[fluxes].divergence(k, q);
            scratch.u_phi[k] = scratch.fe_values_local[scalar].value(k, q);
            scratch.u_phi_grad[k] =
              scratch.fe_values_local[scalar].gradient(k, q);
          }
        for (unsigned int i = 0; i < loc_dofs_per_cell; ++i)
          {
            for (unsigned int j = 0; j < loc_dofs_per_cell; ++j)
              scratch.ll_matrix(i, j) +=
                (scratch.q_phi[i] * scratch.q_phi[j] -
                 scratch.q_phi_div[i] * scratch.u_phi[j] +
                 scratch.u_phi[i] * scratch.q_phi_div[j] -
                 (scratch.u_phi_grad[i] * convection) * scratch.u_phi[j]) *
                JxW;
            scratch.l_rhs(i) += scratch.u_phi[i] * rhs_value * JxW;
          }
      }

    for (const auto face_no : cell->face_indices())
      {
        scratch.fe_face_values_local.reinit(loc_cell, face_no);
        scratch.fe_face_values.reinit(cell, face_no);

        if (task_data.trace_reconstruct)
          scratch.fe_face_values.get_function_values(solution,
                                                     scratch.trace_values);

        for (unsigned int q = 0; q < n_face_q_points; ++q)
          {
            const double     JxW = scratch.fe_face_values.JxW(q);
            const Point<dim> quadrature_point =
              scratch.fe_face_values.quadrature_point(q);
            const Tensor<1, dim> normal =
              scratch.fe_face_values.normal_vector(q);
            const Tensor<1, dim> convection =
              scratch.convection_velocity.value(quadrature_point);

            const double tau_stab = (5. + std::abs(convection * normal));

            for (unsigned int k = 0;
                 k < scratch.fe_local_support_on_face[face_no].size();
                 ++k)
              {
                const unsigned int kk =
                  scratch.fe_local_support_on_face[face_no][k];
                scratch.q_phi[k] =
                  scratch.fe_face_values_local[fluxes].value(kk, q);
                scratch.u_phi[k] =
                  scratch.fe_face_values_local[scalar].value(kk, q);
              }

            if (!task_data.trace_reconstruct)
              {
                for (unsigned int k = 0;
                     k < scratch.fe_support_on_face[face_no].size();
                     ++k)
                  scratch.tr_phi[k] = scratch.fe_face_values.shape_value(
                    scratch.fe_support_on_face[face_no][k], q);
                for (unsigned int i = 0;
                     i < scratch.fe_local_support_on_face[face_no].size();
                     ++i)
                  for (unsigned int j = 0;
                       j < scratch.fe_support_on_face[face_no].size();
                       ++j)
                    {
                      const unsigned int ii =
                        scratch.fe_local_support_on_face[face_no][i];
                      const unsigned int jj =
                        scratch.fe_support_on_face[face_no][j];
                      scratch.lf_matrix(ii, jj) +=
                        ((scratch.q_phi[i] * normal +
                          (convection * normal - tau_stab) * scratch.u_phi[i]) *
                         scratch.tr_phi[j]) *
                        JxW;

                      scratch.fl_matrix(jj, ii) -=
                        ((scratch.q_phi[i] * normal +
                          tau_stab * scratch.u_phi[i]) *
                         scratch.tr_phi[j]) *
                        JxW;
                    }

                for (unsigned int i = 0;
                     i < scratch.fe_support_on_face[face_no].size();
                     ++i)
                  for (unsigned int j = 0;
                       j < scratch.fe_support_on_face[face_no].size();
                       ++j)
                    {
                      const unsigned int ii =
                        scratch.fe_support_on_face[face_no][i];
                      const unsigned int jj =
                        scratch.fe_support_on_face[face_no][j];
                      task_data.cell_matrix(ii, jj) +=
                        ((convection * normal - tau_stab) * scratch.tr_phi[i] *
                         scratch.tr_phi[j]) *
                        JxW;
                    }

                if (cell->face(face_no)->at_boundary() &&
                    (cell->face(face_no)->boundary_id() == 1))
                  {
                    const double neumann_value =
                      -scratch.exact_solution.gradient(quadrature_point) *
                        normal +
                      convection * normal *
                        scratch.exact_solution.value(quadrature_point);
                    for (unsigned int i = 0;
                         i < scratch.fe_support_on_face[face_no].size();
                         ++i)
                      {
                        const unsigned int ii =
                          scratch.fe_support_on_face[face_no][i];
                        task_data.cell_vector(ii) +=
                          scratch.tr_phi[i] * neumann_value * JxW;
                      }
                  }
              }

            for (unsigned int i = 0;
                 i < scratch.fe_local_support_on_face[face_no].size();
                 ++i)
              for (unsigned int j = 0;
                   j < scratch.fe_local_support_on_face[face_no].size();
                   ++j)
                {
                  const unsigned int ii =
                    scratch.fe_local_support_on_face[face_no][i];
                  const unsigned int jj =
                    scratch.fe_local_support_on_face[face_no][j];
                  scratch.ll_matrix(ii, jj) +=
                    tau_stab * scratch.u_phi[i] * scratch.u_phi[j] * JxW;
                }

            if (task_data.trace_reconstruct)
              for (unsigned int i = 0;
                   i < scratch.fe_local_support_on_face[face_no].size();
                   ++i)
                {
                  const unsigned int ii =
                    scratch.fe_local_support_on_face[face_no][i];
                  scratch.l_rhs(ii) -=
                    (scratch.q_phi[i] * normal +
                     scratch.u_phi[i] * (convection * normal - tau_stab)) *
                    scratch.trace_values[q] * JxW;
                }
          }
      }

    scratch.ll_matrix.gauss_jordan();

    if (task_data.trace_reconstruct == false)
      {
        scratch.fl_matrix.mmult(scratch.tmp_matrix, scratch.ll_matrix);
        scratch.tmp_matrix.vmult_add(task_data.cell_vector, scratch.l_rhs);
        scratch.tmp_matrix.mmult(task_data.cell_matrix,
                                 scratch.lf_matrix,
                                 true);
        cell->get_dof_indices(task_data.dof_indices);
      }
    else
      {
        scratch.ll_matrix.vmult(scratch.tmp_rhs, scratch.l_rhs);
        loc_cell->set_dof_values(scratch.tmp_rhs, solution_local);
      }
  }



  template <int dim>
  void HDG<dim>::copy_local_to_global(const PerTaskData &data)
  {
    if (data.trace_reconstruct == false)
      constraints.distribute_local_to_global(data.cell_matrix,
                                             data.cell_vector,
                                             data.dof_indices,
                                             system_matrix,
                                             system_rhs);
  }



  template <int dim>
  void HDG<dim>::solve()
  {
    SolverControl                  solver_control(system_matrix.m() * 10,
                                 1e-11 * system_rhs.l2_norm());
    SolverBicgstab<Vector<double>> solver(solver_control);
    solver.solve(system_matrix, solution, system_rhs, PreconditionIdentity());

    std::cout << "   Number of BiCGStab iterations: "
              << solver_control.last_step() << std::endl;

    system_matrix.clear();
    sparsity_pattern.reinit(0, 0, 0, 1);

    constraints.distribute(solution);

    assemble_system(true);
  }




  template <int dim>
  void HDG<dim>::postprocess()
  {
    {
      const QGauss<dim> quadrature_formula(fe_u_post.degree + 1);
      const UpdateFlags local_flags(update_values);
      const UpdateFlags flags(update_values | update_gradients |
                              update_JxW_values);

      PostProcessScratchData scratch(
        fe_u_post, fe_local, quadrature_formula, local_flags, flags);

      WorkStream::run(
        dof_handler_u_post.begin_active(),
        dof_handler_u_post.end(),
        [this](const typename DoFHandler<dim>::active_cell_iterator &cell,
               PostProcessScratchData &                              scratch,
               unsigned int &                                        data) {
          this->postprocess_one_cell(cell, scratch, data);
        },
        std::function<void(const unsigned int &)>(),
        scratch,
        0U);
    }

    Vector<float> difference_per_cell(triangulation.n_active_cells());

    ComponentSelectFunction<dim> value_select(dim, dim + 1);
    VectorTools::integrate_difference(dof_handler_local,
                                      solution_local,
                                      SolutionAndGradient<dim>(),
                                      difference_per_cell,
                                      QGauss<dim>(fe.degree + 2),
                                      VectorTools::L2_norm,
                                      &value_select);
    const double L2_error =
      VectorTools::compute_global_error(triangulation,
                                        difference_per_cell,
                                        VectorTools::L2_norm);

    ComponentSelectFunction<dim> gradient_select(
      std::pair<unsigned int, unsigned int>(0, dim), dim + 1);
    VectorTools::integrate_difference(dof_handler_local,
                                      solution_local,
                                      SolutionAndGradient<dim>(),
                                      difference_per_cell,
                                      QGauss<dim>(fe.degree + 2),
                                      VectorTools::L2_norm,
                                      &gradient_select);
    const double grad_error =
      VectorTools::compute_global_error(triangulation,
                                        difference_per_cell,
                                        VectorTools::L2_norm);

    VectorTools::integrate_difference(dof_handler_u_post,
                                      solution_u_post,
                                      Solution<dim>(),
                                      difference_per_cell,
                                      QGauss<dim>(fe.degree + 3),
                                      VectorTools::L2_norm);
    const double post_error =
      VectorTools::compute_global_error(triangulation,
                                        difference_per_cell,
                                        VectorTools::L2_norm);

    convergence_table.add_value("cells", triangulation.n_active_cells());
    convergence_table.add_value("dofs", dof_handler.n_dofs());

    convergence_table.add_value("val L2", L2_error);
    convergence_table.set_scientific("val L2", true);
    convergence_table.set_precision("val L2", 3);

    convergence_table.add_value("grad L2", grad_error);
    convergence_table.set_scientific("grad L2", true);
    convergence_table.set_precision("grad L2", 3);

    convergence_table.add_value("val L2-post", post_error);
    convergence_table.set_scientific("val L2-post", true);
    convergence_table.set_precision("val L2-post", 3);
  }



  template <int dim>
  void HDG<dim>::postprocess_one_cell(
    const typename DoFHandler<dim>::active_cell_iterator &cell,
    PostProcessScratchData &                              scratch,
    unsigned int &)
  {
    typename DoFHandler<dim>::active_cell_iterator loc_cell(&triangulation,
                                                            cell->level(),
                                                            cell->index(),
                                                            &dof_handler_local);

    scratch.fe_values_local.reinit(loc_cell);
    scratch.fe_values.reinit(cell);

    FEValuesExtractors::Vector fluxes(0);
    FEValuesExtractors::Scalar scalar(dim);

    const unsigned int n_q_points = scratch.fe_values.get_quadrature().size();
    const unsigned int dofs_per_cell = scratch.fe_values.dofs_per_cell;

    scratch.fe_values_local[scalar].get_function_values(solution_local,
                                                        scratch.u_values);
    scratch.fe_values_local[fluxes].get_function_values(solution_local,
                                                        scratch.u_gradients);

    double sum = 0;
    for (unsigned int i = 1; i < dofs_per_cell; ++i)
      {
        for (unsigned int j = 0; j < dofs_per_cell; ++j)
          {
            sum = 0;
            for (unsigned int q = 0; q < n_q_points; ++q)
              sum += (scratch.fe_values.shape_grad(i, q) *
                      scratch.fe_values.shape_grad(j, q)) *
                     scratch.fe_values.JxW(q);
            scratch.cell_matrix(i, j) = sum;
          }

        sum = 0;
        for (unsigned int q = 0; q < n_q_points; ++q)
          sum -= (scratch.fe_values.shape_grad(i, q) * scratch.u_gradients[q]) *
                 scratch.fe_values.JxW(q);
        scratch.cell_rhs(i) = sum;
      }
    for (unsigned int j = 0; j < dofs_per_cell; ++j)
      {
        sum = 0;
        for (unsigned int q = 0; q < n_q_points; ++q)
          sum += scratch.fe_values.shape_value(j, q) * scratch.fe_values.JxW(q);
        scratch.cell_matrix(0, j) = sum;
      }
    {
      sum = 0;
      for (unsigned int q = 0; q < n_q_points; ++q)
        sum += scratch.u_values[q] * scratch.fe_values.JxW(q);
      scratch.cell_rhs(0) = sum;
    }

    scratch.cell_matrix.gauss_jordan();
    scratch.cell_matrix.vmult(scratch.cell_sol, scratch.cell_rhs);
    cell->distribute_local_to_global(scratch.cell_sol, solution_u_post);
  }



  template <int dim>
  void HDG<dim>::output_results(const unsigned int cycle)
  {
    std::string filename;
    switch (refinement_mode)
      {
        case global_refinement:
          filename = "solution-global";
          break;
        case adaptive_refinement:
          filename = "solution-adaptive";
          break;
        default:
          Assert(false, ExcNotImplemented());
      }

    std::string face_out(filename);
    face_out += "-face";

    filename += "-q" + Utilities::int_to_string(fe.degree, 1);
    filename += "-" + Utilities::int_to_string(cycle, 2);
    filename += ".vtk";
    std::ofstream output(filename);

    DataOut<dim> data_out;

    std::vector<std::string> names(dim, "gradient");
    names.emplace_back("solution");
    std::vector<DataComponentInterpretation::DataComponentInterpretation>
      component_interpretation(
        dim + 1, DataComponentInterpretation::component_is_part_of_vector);
    component_interpretation[dim] =
      DataComponentInterpretation::component_is_scalar;
    data_out.add_data_vector(dof_handler_local,
                             solution_local,
                             names,
                             component_interpretation);

    std::vector<std::string> post_name(1, "u_post");
    std::vector<DataComponentInterpretation::DataComponentInterpretation>
      post_comp_type(1, DataComponentInterpretation::component_is_scalar);
    data_out.add_data_vector(dof_handler_u_post,
                             solution_u_post,
                             post_name,
                             post_comp_type);

    data_out.build_patches(fe.degree);
    data_out.write_vtk(output);

    face_out += "-q" + Utilities::int_to_string(fe.degree, 1);
    face_out += "-" + Utilities::int_to_string(cycle, 2);
    face_out += ".vtk";
    std::ofstream face_output(face_out);

    DataOutFaces<dim>        data_out_face(false);
    std::vector<std::string> face_name(1, "u_hat");
    std::vector<DataComponentInterpretation::DataComponentInterpretation>
      face_component_type(1, DataComponentInterpretation::component_is_scalar);

    data_out_face.add_data_vector(dof_handler,
                                  solution,
                                  face_name,
                                  face_component_type);

    data_out_face.build_patches(fe.degree);
    data_out_face.write_vtk(face_output);
  }



  template <int dim>
  void HDG<dim>::refine_grid(const unsigned int cycle)
  {
    if (cycle == 0)
      {
        GridGenerator::subdivided_hyper_cube(triangulation, 2, -1, 1);
        triangulation.refine_global(3 - dim);
      }
    else
      switch (refinement_mode)
        {
          case global_refinement:
            {
              triangulation.clear();
              GridGenerator::subdivided_hyper_cube(triangulation,
                                                   2 + (cycle % 2),
                                                   -1,
                                                   1);
              triangulation.refine_global(3 - dim + cycle / 2);
              break;
            }

          case adaptive_refinement:
            {
              Vector<float> estimated_error_per_cell(
                triangulation.n_active_cells());

              FEValuesExtractors::Scalar scalar(dim);
              std::map<types::boundary_id, const Function<dim> *>
                neumann_boundary;
              KellyErrorEstimator<dim>::estimate(dof_handler_local,
                                                 QGauss<dim - 1>(fe.degree + 1),
                                                 neumann_boundary,
                                                 solution_local,
                                                 estimated_error_per_cell,
                                                 fe_local.component_mask(
                                                   scalar));

              GridRefinement::refine_and_coarsen_fixed_number(
                triangulation, estimated_error_per_cell, 0.3, 0.);

              triangulation.execute_coarsening_and_refinement();

              break;
            }

          default:
            {
              Assert(false, ExcNotImplemented());
            }
        }

    for (const auto &cell : triangulation.cell_iterators())
      for (const auto &face : cell->face_iterators())
        if (face->at_boundary())
          if ((std::fabs(face->center()(0) - (-1)) < 1e-12) ||
              (std::fabs(face->center()(1) - (-1)) < 1e-12))
            face->set_boundary_id(1);
  }

  template <int dim>
  void HDG<dim>::run()
  {
    for (unsigned int cycle = 0; cycle < 10; ++cycle)
      {
        std::cout << "Cycle " << cycle << ':' << std::endl;

        refine_grid(cycle);
        setup_system();
        assemble_system(false);
        solve();
        postprocess();
        output_results(cycle);
      }

    if (refinement_mode == global_refinement)
      {
        convergence_table.evaluate_convergence_rates(
          "val L2", "cells", ConvergenceTable::reduction_rate_log2, dim);
        convergence_table.evaluate_convergence_rates(
          "grad L2", "cells", ConvergenceTable::reduction_rate_log2, dim);
        convergence_table.evaluate_convergence_rates(
          "val L2-post", "cells", ConvergenceTable::reduction_rate_log2, dim);
      }
    convergence_table.write_text(std::cout);
  }

} // end of namespace Step51



int main()
{
  const unsigned int dim = 2;

  try
    {
      {
        std::cout << "Solving with Q1 elements, adaptive refinement"
                  << std::endl
                  << "============================================="
                  << std::endl
                  << std::endl;

        Step51::HDG<dim> hdg_problem(1, Step51::HDG<dim>::adaptive_refinement);
        hdg_problem.run();

        std::cout << std::endl;
      }

      {
        std::cout << "Solving with Q1 elements, global refinement" << std::endl
                  << "===========================================" << std::endl
                  << std::endl;

        Step51::HDG<dim> hdg_problem(1, Step51::HDG<dim>::global_refinement);
        hdg_problem.run();

        std::cout << std::endl;
      }

      {
        std::cout << "Solving with Q3 elements, global refinement" << std::endl
                  << "===========================================" << std::endl
                  << std::endl;

        Step51::HDG<dim> hdg_problem(3, Step51::HDG<dim>::global_refinement);
        hdg_problem.run();

        std::cout << std::endl;
      }
    }
  catch (std::exception &exc)
    {
      std::cerr << std::endl
                << std::endl
                << "----------------------------------------------------"
                << std::endl;
      std::cerr << "Exception on processing: " << std::endl
                << exc.what() << std::endl
                << "Aborting!" << std::endl
                << "----------------------------------------------------"
                << std::endl;
      return 1;
    }
  catch (...)
    {
      std::cerr << std::endl
                << std::endl
                << "----------------------------------------------------"
                << std::endl;
      std::cerr << "Unknown exception!" << std::endl
                << "Aborting!" << std::endl
                << "----------------------------------------------------"
                << std::endl;
      return 1;
    }

  return 0;
}
