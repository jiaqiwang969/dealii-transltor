/**
@page step_74 The step-74 tutorial program
This tutorial depends on step-12.

@htmlonly
<table class="tutorial" width="50%">
<tr><th colspan="2"><b><small>Table of contents</small></b></th></tr>
<tr><td width="50%" valign="top">
<ol>
  <li> <a href="#Intro" class=bold>Introduction</a>
    <ul>
        <li><a href="#Overview">Overview</a>
        <li><a href="#Theequation">The equation</a>
        <li><a href="#Thepenaltyparameter">The penalty parameter</a>
        <li><a href="#Aposteriorierrorestimator">A posteriori error estimator</a>
        <li><a href="#Thetestcase">The test case</a>
    </ul>
  <li> <a href="#CommProg" class=bold>The commented program</a>
    <ul>
        <li><a href="#Equationdata">Equation data</a>
        <li><a href="#Auxiliaryfunctions">Auxiliary functions</a>
        <li><a href="#TheCopyData">The CopyData</a>
        <li><a href="#TheSIPGLaplaceclass">The SIPGLaplace class</a>
        <li><a href="#Theassemble_systemfunction">The assemble_system function</a>
        <li><a href="#Thesolveandoutput_resultsfunction">The solve() and output_results() function</a>
        <li><a href="#Thecompute_error_estimatefunction">The compute_error_estimate() function</a>
        <li><a href="#Thecompute_energy_norm_errorfunction">The compute_energy_norm_error() function</a>
        <li><a href="#Therefine_gridfunction">The refine_grid() function</a>
        <li><a href="#Thecompute_errorsfunction">The compute_errors() function</a>
        <li><a href="#Therunfunction">The run() function</a>
        <li><a href="#Themainfunction">The main() function</a>
      </ul>
</ol></td><td width="50%" valign="top"><ol>
  <li value="3"> <a href="#Results" class=bold>Results</a>
    <ul>
    </ul>
  <li> <a href="#PlainProg" class=bold>The plain program</a>
</ol> </td> </tr> </table>
@endhtmlonly
<br>

<i>
This program was contributed by Timo Heister and Jiaqi Zhang.
<br>
This material is based upon work partly supported by the National
Science Foundation Award DMS-2028346, OAC-2015848, EAR-1925575, by the Computational
Infrastructure in Geodynamics initiative (CIG), through the NSF under Award
EAR-0949446 and EAR-1550901 and The University of California -- Davis.
</i>


<a name="Intro"></a>
<a name="emSymmetricinteriorpenaltyGalerkinemSIPGmethodforPoissonsequation"></a><h1><em>Symmetric interior penalty Galerkin</em> (SIPG) method for Poisson's equation</h1>


<a name="Overview"></a><h3>Overview</h3>

In this tutorial, we display the usage of the FEInterfaceValues class,
which is designed for assembling face terms arising from discontinuous Galerkin (DG) methods.
The FEInterfaceValues class provides an easy way to obtain the jump
and the average of shape functions and of the solution across cell faces.
This tutorial includes the following topics.
<ol>
  <li> The SIPG method for Poisson's equation, which has already been used in step-39 and step-59.
  <li> Assembling of face terms using FEInterfaceValues and the system matrix using MeshWorker::mesh_loop(), which is similar to step-12.
  <li> Adaptive mesh refinement using an error estimator.
  <li> Two test cases: convergence test for a smooth function and adaptive mesh refinement test for a singular solution.
</ol>

<a name="Theequation"></a><h3>The equation</h3>

In this example, we consider Poisson's equation
@f[
- \nabla \cdot \left( \nu  \nabla u\right) = f  \qquad   \mbox{in } \Omega,
@f]
subject to the boundary condition
@f[
u = g_D \qquad \mbox{on } \partial \Omega.
@f]
For simplicity, we assume that the diffusion coefficient $\nu$ is constant here.
Note that if $\nu$ is discontinuous, we need to take this into account when computing jump terms
on cell faces.

We denote the mesh by ${\mathbb T}_h$, and $K\in{\mathbb T}_h$ is a mesh cell.
The sets of interior and boundary faces are denoted by ${\mathbb F}^i_h$ and ${\mathbb F}^b_h$
respectively. Let $K^0$ and $K^1$ be the two cells sharing a face $f\in F_h^i$,
and $\mathbf n$ be the outer normal vector of $K^0$. Then the jump
operator is given by the "here minus there" formula,
@f[
\jump{v} = v^0 - v^1
@f]
and the averaging operator as
@f[
\average{v} = \frac{v^0 + v^1}{2}
@f]
respectively. Note that when $f\subset \partial \Omega$, we define $\jump{v} = v$ and
$\average{v}=v$.
The discretization using the SIPG is given by the following weak formula
(more details can be found in @cite di2011mathematical and the references therein)
@f{align*}
&\sum_{K\in {\mathbb T}_h} (\nabla v_h, \nu \nabla u_h)_K\\
&-\sum_{F \in F_h^i} \left\{
    \left< \jump{v_h}, \nu\average{ \nabla u_h} \cdot  \mathbf n \right>_F
   +\left<\average{ \nabla v_h }\cdot \mathbf n,\nu\jump{u_h}\right>_F
   -\left<\jump{v_h},\nu \sigma \jump{u_h} \right>_F
  \right\}\\
&-\sum_{F \in F_h^b} \left\{
    \left<v_h, \nu  \nabla u_h\cdot \mathbf n \right>_F
  + \left< \nabla v_h \cdot \mathbf n , \nu u_h\right>_F
  - \left< v_h,\nu \sigma u_h\right>_F
  \right\}\\
&=(v_h, f)_\Omega
  - \sum_{F \in F_h^b} \left\{
    \left< \nabla v_h \cdot \mathbf n, \nu g_D\right>_F - \left<v_h,\nu \sigma g_D\right>_F
  \right\}.
@f}


<a name="Thepenaltyparameter"></a><h3>The penalty parameter</h3>

The penalty parameter is defined as $\sigma = \gamma/h_f$, where $h_f$ a local length scale associated
with the cell face; here we choose an approximation of the length of the cell in the direction normal to the face:
$\frac 1{h_f} = \frac 12 \left(\frac 1{h_K} + \frac 1{h_{K'}}\right)$,
where $K,K'$ are the two cells adjacent to the face $f$ and we we
compute $h_K = \frac{|K|}{|f|}$.

In the formula above, $\gamma$ is the penalization constant.
To ensure the discrete coercivity, the penalization constant has to be large enough @cite ainsworth2007posteriori.
People do not really have consensus on which of the formulas proposed
in the literature should be used. (This is similar to the situation
discussed in the "Results" section of step-47.)
One can just pick a large constant, while other options could be the multiples of $(p+1)^2$ or $p(p+1)$. In this code,
we follow step-39 and use $\gamma = p(p+1)$.


<a name="Aposteriorierrorestimator"></a><h3>A posteriori error estimator</h3>

In this example, with a slight modification, we use the error estimator by Karakashian and Pascal @cite karakashian2003posteriori
@f[
\eta^2 = \sum_{K \in {\mathbb T}_h} \eta^2_{K} +  \sum_{f_i \in {\mathbb F}^i_h}  \eta^2_{f_i} + \sum_{f_b \in F^i_b}\eta^2_{f_b}
@f]
where
@f{align*}{
\eta^2_{K} &= h_K^2 \left\| f + \nu \Delta u_h \right\|_K^2,
\\
\eta^2_{f_i} &= \sigma \left\| \jump{u_h}  \right\|_f^2   +  h_f \left\|  \jump{\nu \nabla u_h} \cdot \mathbf n   \right\|_f^2,
\\
\eta_{f_b}^2 &=  \sigma \left\| u_h-g_D \right\|_f^2.
@f}
Here we use $\sigma = \gamma/h_f$ instead of $\gamma^2/h_f$ for the jump terms of $u_h$ (the first term in $\eta^2_{f_i}$ and $\eta_{f_b}^2$).

In order to compute this estimator, in each cell $K$ we compute
@f{align*}{
\eta_{c}^2 &= h_K^2 \left\| f + \nu \Delta u_h \right\|_K^2,
\\
\eta_{f}^2 &= \sum_{f\in \partial K}\lbrace \sigma \left\| \jump{u_h}  \right\|_f^2   +  h_f \left\|  \jump{\nu \nabla u_h} \cdot \mathbf n  \right\|_f^2 \rbrace,
\\
\eta_{b}^2 &= \sum_{f\in \partial K \cap \partial \Omega}  \sigma \left\| (u_h -g_D)  \right\|_f^2.
@f}
Then the square of the error estimate per cell is
@f[
\eta_\text{local}^2 =\eta_{c}^2+0.5\eta_{f}^2+\eta_{b}^2.
@f]
The factor of $0.5$ results from the fact that the overall error
estimator includes each interior face only once, and so the estimators per cell
count it with a factor of one half for each of the two adjacent cells.
Note that we compute $\eta_\text{local}^2$ instead of $\eta_\text{local}$ to simplify the implementation.
The error estimate square per cell is then stored in a global vector, whose $l_1$ norm is equal to $\eta^2$.

<a name="Thetestcase"></a><h3>The test case</h3>

In the first test problem, we run a convergence test using a smooth manufactured solution with $\nu =1$ in 2D
@f{align*}{
u&=\sin(2\pi x)\sin(2\pi y), &\qquad\qquad &(x,y)\in\Omega=(0,1)\times (0,1),
\\
u&=0,                        &\qquad\qquad &\text{on } \partial \Omega,
@f}
and $f= 8\pi^2 u$. We compute errors against the manufactured solution and evaluate the convergence rate.

In the second test, we choose Functions::LSingularityFunction on a L-shaped domain (GridGenerator::hyper_L) in 2D.
The solution is given in the polar coordinates by $u(r,\phi) = r^{\frac{2}{3}}\sin \left(\frac{2}{3}\phi \right)$,
which has a singularity at the origin. An error estimator is constructed to detect the region with large errors,
according to which the mesh is refined adaptively.


 <a name="CommProg"></a>
 <h1> The commented program</h1>
 
 The first few files have already been covered in previous examples and will
 thus not be further commented on:
 
 @code
 #include <deal.II/base/quadrature_lib.h>
 #include <deal.II/base/function.h>
 #include <deal.II/base/function_lib.h>
 #include <deal.II/lac/vector.h>
 #include <deal.II/lac/dynamic_sparsity_pattern.h>
 #include <deal.II/lac/sparse_matrix.h>
 #include <deal.II/lac/sparse_direct.h>
 #include <deal.II/grid/tria.h>
 #include <deal.II/grid/grid_generator.h>
 #include <deal.II/grid/grid_out.h>
 #include <deal.II/grid/grid_refinement.h>
 #include <deal.II/fe/fe_values.h>
 #include <deal.II/dofs/dof_handler.h>
 #include <deal.II/dofs/dof_tools.h>
 #include <deal.II/numerics/data_out.h>
 #include <deal.II/fe/mapping_q1.h>
 @endcode
 
 Here the discontinuous finite elements and FEInterfaceValues are defined.
 
 @code
 #include <deal.II/fe/fe_dgq.h>
 #include <deal.II/fe/fe_interface_values.h>
 
 #include <deal.II/numerics/derivative_approximation.h>
 #include <deal.II/numerics/vector_tools.h>
 #include <deal.II/base/convergence_table.h>
 
 #include <deal.II/meshworker/copy_data.h>
 #include <deal.II/meshworker/mesh_loop.h>
 #include <deal.II/meshworker/scratch_data.h>
 
 namespace Step74
 {
   using namespace dealii;
 
 @endcode
 
 
 <a name="Equationdata"></a> 
 <h3>Equation data</h3>
 Here we define two test cases: convergence_rate for a smooth function
 and l_singularity for the Functions::LSingularityFunction.
 
 @code
   enum class TestCase
   {
     convergence_rate,
     l_singularity
   };
 
 
 
 @endcode
 
 A smooth solution for the convergence test:
 
 @code
   template <int dim>
   class SmoothSolution : public Function<dim>
   {
   public:
     SmoothSolution()
       : Function<dim>()
     {}
 
     virtual void value_list(const std::vector<Point<dim>> &points,
                             std::vector<double> &          values,
                             const unsigned int component = 0) const override;
 
     virtual Tensor<1, dim>
     gradient(const Point<dim> & point,
              const unsigned int component = 0) const override;
   };
 
 
 
   template <int dim>
   void SmoothSolution<dim>::value_list(const std::vector<Point<dim>> &points,
                                        std::vector<double> &          values,
                                        const unsigned int /*component*/) const
   {
     using numbers::PI;
     for (unsigned int i = 0; i < values.size(); ++i)
       values[i] =
         std::sin(2. * PI * points[i][0]) * std::sin(2. * PI * points[i][1]);
   }
 
 
 
   template <int dim>
   Tensor<1, dim>
   SmoothSolution<dim>::gradient(const Point<dim> &point,
                                 const unsigned int /*component*/) const
   {
     Tensor<1, dim> return_value;
     using numbers::PI;
     return_value[0] =
       2. * PI * std::cos(2. * PI * point[0]) * std::sin(2. * PI * point[1]);
     return_value[1] =
       2. * PI * std::sin(2. * PI * point[0]) * std::cos(2. * PI * point[1]);
     return return_value;
   }
 
 
 
 @endcode
 
 The corresponding right-hand side of the smooth function:
 
 @code
   template <int dim>
   class SmoothRightHandSide : public Function<dim>
   {
   public:
     SmoothRightHandSide()
       : Function<dim>()
     {}
 
     virtual void value_list(const std::vector<Point<dim>> &points,
                             std::vector<double> &          values,
                             const unsigned int /*component*/) const override;
   };
 
 
 
   template <int dim>
   void
   SmoothRightHandSide<dim>::value_list(const std::vector<Point<dim>> &points,
                                        std::vector<double> &          values,
                                        const unsigned int /*component*/) const
   {
     using numbers::PI;
     for (unsigned int i = 0; i < values.size(); ++i)
       values[i] = 8. * PI * PI * std::sin(2. * PI * points[i][0]) *
                   std::sin(2. * PI * points[i][1]);
   }
 
 
 
 @endcode
 
 The right-hand side that corresponds to the function
 Functions::LSingularityFunction, where we
 assume that the diffusion coefficient $\nu = 1$:
 
 @code
   template <int dim>
   class SingularRightHandSide : public Function<dim>
   {
   public:
     SingularRightHandSide()
       : Function<dim>()
     {}
 
     virtual void value_list(const std::vector<Point<dim>> &points,
                             std::vector<double> &          values,
                             const unsigned int /*component*/) const override;
 
   private:
     const Functions::LSingularityFunction ref;
   };
 
 
 
   template <int dim>
   void
   SingularRightHandSide<dim>::value_list(const std::vector<Point<dim>> &points,
                                          std::vector<double> &          values,
                                          const unsigned int /*component*/) const
   {
     for (unsigned int i = 0; i < values.size(); ++i)
       values[i] = -ref.laplacian(points[i]);
   }
 
 
 
 @endcode
 
 
 <a name="Auxiliaryfunctions"></a> 
 <h3>Auxiliary functions</h3>
 The following two auxiliary functions are used to compute
 jump terms for $u_h$ and $\nabla u_h$ on a face,
 respectively.
 
 @code
   template <int dim>
   void get_function_jump(const FEInterfaceValues<dim> &fe_iv,
                          const Vector<double> &        solution,
                          std::vector<double> &         jump)
   {
     const unsigned int                 n_q = fe_iv.n_quadrature_points;
     std::array<std::vector<double>, 2> face_values;
     jump.resize(n_q);
     for (unsigned int i = 0; i < 2; ++i)
       {
         face_values[i].resize(n_q);
         fe_iv.get_fe_face_values(i).get_function_values(solution,
                                                         face_values[i]);
       }
     for (unsigned int q = 0; q < n_q; ++q)
       jump[q] = face_values[0][q] - face_values[1][q];
   }
 
 
 
   template <int dim>
   void get_function_gradient_jump(const FEInterfaceValues<dim> &fe_iv,
                                   const Vector<double> &        solution,
                                   std::vector<Tensor<1, dim>> & gradient_jump)
   {
     const unsigned int          n_q = fe_iv.n_quadrature_points;
     std::vector<Tensor<1, dim>> face_gradients[2];
     gradient_jump.resize(n_q);
     for (unsigned int i = 0; i < 2; ++i)
       {
         face_gradients[i].resize(n_q);
         fe_iv.get_fe_face_values(i).get_function_gradients(solution,
                                                            face_gradients[i]);
       }
     for (unsigned int q = 0; q < n_q; ++q)
       gradient_jump[q] = face_gradients[0][q] - face_gradients[1][q];
   }
 
 @endcode
 
 This function computes the penalty $\sigma$.
 
 @code
   double get_penalty_factor(const unsigned int fe_degree,
                             const double       cell_extent_left,
                             const double       cell_extent_right)
   {
     const unsigned int degree = std::max(1U, fe_degree);
     return degree * (degree + 1.) * 0.5 *
            (1. / cell_extent_left + 1. / cell_extent_right);
   }
 
 
 @endcode
 
 
 <a name="TheCopyData"></a> 
 <h3>The CopyData</h3>
 In the following, we define "Copy" objects for the MeshWorker::mesh_loop(),
 which is essentially the same as step-12. Note that the
 "Scratch" object is not defined here because we use
 MeshWorker::ScratchData<dim> instead. (The use of "Copy" and "Scratch"
 objects is extensively explained in the WorkStream namespace documentation.
 
 @code
   struct CopyDataFace
   {
     FullMatrix<double>                   cell_matrix;
     std::vector<types::global_dof_index> joint_dof_indices;
     std::array<double, 2>                values;
     std::array<unsigned int, 2>          cell_indices;
   };
 
 
 
   struct CopyData
   {
     FullMatrix<double>                   cell_matrix;
     Vector<double>                       cell_rhs;
     std::vector<types::global_dof_index> local_dof_indices;
     std::vector<CopyDataFace>            face_data;
     double                               value;
     unsigned int                         cell_index;
 
 
     template <class Iterator>
     void reinit(const Iterator &cell, const unsigned int dofs_per_cell)
     {
       cell_matrix.reinit(dofs_per_cell, dofs_per_cell);
       cell_rhs.reinit(dofs_per_cell);
       local_dof_indices.resize(dofs_per_cell);
       cell->get_dof_indices(local_dof_indices);
     }
   };
 
 
 
 @endcode
 
 
 <a name="TheSIPGLaplaceclass"></a> 
 <h3>The SIPGLaplace class</h3>
 After these preparations, we proceed with the main class of this program,
 called `SIPGLaplace`. The overall structure of the class is as in many
 of the other tutorial programs. Major differences will only come up in the
 implementation of the assemble functions, since we use FEInterfaceValues to
 assemble face terms.
 
 @code
   template <int dim>
   class SIPGLaplace
   {
   public:
     SIPGLaplace(const TestCase &test_case);
     void run();
 
   private:
     void setup_system();
     void assemble_system();
     void solve();
     void refine_grid();
     void output_results(const unsigned int cycle) const;
 
     void   compute_errors();
     void   compute_error_estimate();
     double compute_energy_norm_error();
 
     Triangulation<dim>    triangulation;
     const unsigned int    degree;
     const QGauss<dim>     quadrature;
     const QGauss<dim - 1> face_quadrature;
     const QGauss<dim>     quadrature_overintegration;
     const QGauss<dim - 1> face_quadrature_overintegration;
     const MappingQ1<dim>  mapping;
 
     using ScratchData = MeshWorker::ScratchData<dim>;
 
     const FE_DGQ<dim> fe;
     DoFHandler<dim>   dof_handler;
 
     SparsityPattern      sparsity_pattern;
     SparseMatrix<double> system_matrix;
     Vector<double>       solution;
     Vector<double>       system_rhs;
 
 @endcode
 
 The remainder of the class's members are used for the following:
 - Vectors to store error estimator square and energy norm square per
 cell.
 - Print convergence rate and errors on the screen.
 - The fiffusion coefficient $\nu$ is set to 1.
 - Members that store information about the test case to be computed.
 
 @code
     Vector<double> estimated_error_square_per_cell;
     Vector<double> energy_norm_square_per_cell;
 
     ConvergenceTable convergence_table;
 
     const double diffusion_coefficient = 1.;
 
     const TestCase                       test_case;
     std::unique_ptr<const Function<dim>> exact_solution;
     std::unique_ptr<const Function<dim>> rhs_function;
   };
 
 @endcode
 
 The constructor here takes the test case as input and then
 determines the correct solution and right-hand side classes. The
 remaining member variables are initialized in the obvious way.
 
 @code
   template <int dim>
   SIPGLaplace<dim>::SIPGLaplace(const TestCase &test_case)
     : degree(3)
     , quadrature(degree + 1)
     , face_quadrature(degree + 1)
     , quadrature_overintegration(degree + 2)
     , face_quadrature_overintegration(degree + 2)
     , mapping()
     , fe(degree)
     , dof_handler(triangulation)
     , test_case(test_case)
   {
     if (test_case == TestCase::convergence_rate)
       {
         exact_solution = std::make_unique<const SmoothSolution<dim>>();
         rhs_function   = std::make_unique<const SmoothRightHandSide<dim>>();
       }
 
     else if (test_case == TestCase::l_singularity)
       {
         exact_solution =
           std::make_unique<const Functions::LSingularityFunction>();
         rhs_function = std::make_unique<const SingularRightHandSide<dim>>();
       }
     else
       AssertThrow(false, ExcNotImplemented());
   }
 
 
 
   template <int dim>
   void SIPGLaplace<dim>::setup_system()
   {
     dof_handler.distribute_dofs(fe);
     DynamicSparsityPattern dsp(dof_handler.n_dofs());
     DoFTools::make_flux_sparsity_pattern(dof_handler, dsp);
     sparsity_pattern.copy_from(dsp);
 
     system_matrix.reinit(sparsity_pattern);
     solution.reinit(dof_handler.n_dofs());
     system_rhs.reinit(dof_handler.n_dofs());
   }
 
 
 
 @endcode
 
 
 <a name="Theassemble_systemfunction"></a> 
 <h3>The assemble_system function</h3>
 The assemble function here is similar to that in step-12 and step-47.
 Different from assembling by hand, we just need to focus
 on assembling on each cell, each boundary face, and each
 interior face. The loops over cells and faces are handled
 automatically by MeshWorker::mesh_loop().
   

 
 The function starts by defining a local (lambda) function that is
 used to integrate the cell terms:
 
 @code
   template <int dim>
   void SIPGLaplace<dim>::assemble_system()
   {
     const auto cell_worker =
       [&](const auto &cell, auto &scratch_data, auto &copy_data) {
         const FEValues<dim> &fe_v          = scratch_data.reinit(cell);
         const unsigned int   dofs_per_cell = fe_v.dofs_per_cell;
         copy_data.reinit(cell, dofs_per_cell);
 
         const auto &       q_points    = scratch_data.get_quadrature_points();
         const unsigned int n_q_points  = q_points.size();
         const std::vector<double> &JxW = scratch_data.get_JxW_values();
 
         std::vector<double> rhs(n_q_points);
         rhs_function->value_list(q_points, rhs);
 
         for (unsigned int point = 0; point < n_q_points; ++point)
           for (unsigned int i = 0; i < fe_v.dofs_per_cell; ++i)
             {
               for (unsigned int j = 0; j < fe_v.dofs_per_cell; ++j)
                 copy_data.cell_matrix(i, j) +=
                   diffusion_coefficient *     // nu
                   fe_v.shape_grad(i, point) * // grad v_h
                   fe_v.shape_grad(j, point) * // grad u_h
                   JxW[point];                 // dx
 
               copy_data.cell_rhs(i) += fe_v.shape_value(i, point) * // v_h
                                        rhs[point] *                 // f
                                        JxW[point];                  // dx
             }
       };
 
 @endcode
 
 Next, we need a function that assembles face integrals on the boundary:
 
 @code
     const auto boundary_worker = [&](const auto &        cell,
                                      const unsigned int &face_no,
                                      auto &              scratch_data,
                                      auto &              copy_data) {
       const FEFaceValuesBase<dim> &fe_fv = scratch_data.reinit(cell, face_no);
 
       const auto &       q_points      = scratch_data.get_quadrature_points();
       const unsigned int n_q_points    = q_points.size();
       const unsigned int dofs_per_cell = fe_fv.dofs_per_cell;
 
       const std::vector<double> &        JxW = scratch_data.get_JxW_values();
       const std::vector<Tensor<1, dim>> &normals =
         scratch_data.get_normal_vectors();
 
       std::vector<double> g(n_q_points);
       exact_solution->value_list(q_points, g);
 
       const double extent1 = cell->measure() / cell->face(face_no)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent1);
 
       for (unsigned int point = 0; point < n_q_points; ++point)
         {
           for (unsigned int i = 0; i < dofs_per_cell; ++i)
             for (unsigned int j = 0; j < dofs_per_cell; ++j)
               copy_data.cell_matrix(i, j) +=
                 (-diffusion_coefficient *        // - nu
                    fe_fv.shape_value(i, point) * // v_h
                    (fe_fv.shape_grad(j, point) * // (grad u_h .
                     normals[point])              //  n)
 
                  - diffusion_coefficient *         // - nu
                      (fe_fv.shape_grad(i, point) * // (grad v_h .
                       normals[point]) *            //  n)
                      fe_fv.shape_value(j, point)   // u_h
 
                  + diffusion_coefficient * penalty * // + nu sigma
                      fe_fv.shape_value(i, point) *   // v_h
                      fe_fv.shape_value(j, point)     // u_h
 
                  ) *
                 JxW[point]; // dx
 
           for (unsigned int i = 0; i < dofs_per_cell; ++i)
             copy_data.cell_rhs(i) +=
               (-diffusion_coefficient *        // - nu
                  (fe_fv.shape_grad(i, point) * // (grad v_h .
                   normals[point]) *            //  n)
                  g[point]                      // g
 
 
                + diffusion_coefficient * penalty *        // + nu sigma
                    fe_fv.shape_value(i, point) * g[point] // v_h g
 
                ) *
               JxW[point]; // dx
         }
     };
 
 @endcode
 
 Finally, a function that assembles face integrals on interior
 faces. To reinitialize FEInterfaceValues, we need to pass
 cells, face and subface indices (for adaptive refinement) to
 the reinit() function of FEInterfaceValues:
 
 @code
     const auto face_worker = [&](const auto &        cell,
                                  const unsigned int &f,
                                  const unsigned int &sf,
                                  const auto &        ncell,
                                  const unsigned int &nf,
                                  const unsigned int &nsf,
                                  auto &              scratch_data,
                                  auto &              copy_data) {
       const FEInterfaceValues<dim> &fe_iv =
         scratch_data.reinit(cell, f, sf, ncell, nf, nsf);
 
       const auto &       q_points   = fe_iv.get_quadrature_points();
       const unsigned int n_q_points = q_points.size();
 
       copy_data.face_data.emplace_back();
       CopyDataFace &     copy_data_face = copy_data.face_data.back();
       const unsigned int n_dofs_face    = fe_iv.n_current_interface_dofs();
       copy_data_face.joint_dof_indices  = fe_iv.get_interface_dof_indices();
       copy_data_face.cell_matrix.reinit(n_dofs_face, n_dofs_face);
 
       const std::vector<double> &        JxW     = fe_iv.get_JxW_values();
       const std::vector<Tensor<1, dim>> &normals = fe_iv.get_normal_vectors();
 
       const double extent1 = cell->measure() / cell->face(f)->measure();
       const double extent2 = ncell->measure() / ncell->face(nf)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent2);
 
       for (unsigned int point = 0; point < n_q_points; ++point)
         {
           for (unsigned int i = 0; i < n_dofs_face; ++i)
             for (unsigned int j = 0; j < n_dofs_face; ++j)
               copy_data_face.cell_matrix(i, j) +=
                 (-diffusion_coefficient *              // - nu
                    fe_iv.jump(i, point) *              // [v_h]
                    (fe_iv.average_gradient(j, point) * // ({grad u_h} .
                     normals[point])                    //  n)
 
                  - diffusion_coefficient *               // - nu
                      (fe_iv.average_gradient(i, point) * // (grad v_h .
                       normals[point]) *                  //  n)
                      fe_iv.jump(j, point)                // [u_h]
 
                  + diffusion_coefficient * penalty * // + nu sigma
                      fe_iv.jump(i, point) *          // [v_h]
                      fe_iv.jump(j, point)            // [u_h]
 
                  ) *
                 JxW[point]; // dx
         }
     };
 
 @endcode
 
 The following lambda function will then copy data into the
 global matrix and right-hand side.  Though there are no hanging
 node constraints in DG discretization, we define an empty
 AffineConstraints object that allows us to use the
 AffineConstraints::distribute_local_to_global() functionality.
 
 @code
     AffineConstraints<double> constraints;
     constraints.close();
     const auto copier = [&](const auto &c) {
       constraints.distribute_local_to_global(c.cell_matrix,
                                              c.cell_rhs,
                                              c.local_dof_indices,
                                              system_matrix,
                                              system_rhs);
 
 @endcode
 
 Copy data from interior face assembly to the global matrix.
 
 @code
       for (auto &cdf : c.face_data)
         {
           constraints.distribute_local_to_global(cdf.cell_matrix,
                                                  cdf.joint_dof_indices,
                                                  system_matrix);
         }
     };
 
 
 @endcode
 
 With the assembly functions defined, we can now create
 ScratchData and CopyData objects, and pass them together with
 the lambda functions above to MeshWorker::mesh_loop(). In
 addition, we need to specify that we want to assemble on
 interior faces exactly once.
 
 @code
     const UpdateFlags cell_flags = update_values | update_gradients |
                                    update_quadrature_points | update_JxW_values;
     const UpdateFlags face_flags = update_values | update_gradients |
                                    update_quadrature_points |
                                    update_normal_vectors | update_JxW_values;
 
     ScratchData scratch_data(
       mapping, fe, quadrature, cell_flags, face_quadrature, face_flags);
     CopyData copy_data;
 
     MeshWorker::mesh_loop(dof_handler.begin_active(),
                           dof_handler.end(),
                           cell_worker,
                           copier,
                           scratch_data,
                           copy_data,
                           MeshWorker::assemble_own_cells |
                             MeshWorker::assemble_boundary_faces |
                             MeshWorker::assemble_own_interior_faces_once,
                           boundary_worker,
                           face_worker);
   }
 
 
 
 @endcode
 
 
 <a name="Thesolveandoutput_resultsfunction"></a> 
 <h3>The solve() and output_results() function</h3>
 The following two functions are entirely standard and without difficulty.
 
 @code
   template <int dim>
   void SIPGLaplace<dim>::solve()
   {
     SparseDirectUMFPACK A_direct;
     A_direct.initialize(system_matrix);
     A_direct.vmult(solution, system_rhs);
   }
 
 
 
   template <int dim>
   void SIPGLaplace<dim>::output_results(const unsigned int cycle) const
   {
     const std::string filename = "sol_Q" + Utilities::int_to_string(degree, 1) +
                                  "-" + Utilities::int_to_string(cycle, 2) +
                                  ".vtu";
     std::ofstream output(filename);
 
     DataOut<dim> data_out;
     data_out.attach_dof_handler(dof_handler);
     data_out.add_data_vector(solution, "u", DataOut<dim>::type_dof_data);
     data_out.build_patches(mapping);
     data_out.write_vtu(output);
   }
 
 
 @endcode
 
 
 <a name="Thecompute_error_estimatefunction"></a> 
 <h3>The compute_error_estimate() function</h3>
 The assembly of the error estimator here is quite similar to
 that of the global matrix and right-had side and can be handled
 by the MeshWorker::mesh_loop() framework. To understand what
 each of the local (lambda) functions is doing, recall first that
 the local cell residual is defined as
 $h_K^2 \left\| f + \nu \Delta u_h \right\|_K^2$:
 
 @code
   template <int dim>
   void SIPGLaplace<dim>::compute_error_estimate()
   {
     const auto cell_worker =
       [&](const auto &cell, auto &scratch_data, auto &copy_data) {
         const FEValues<dim> &fe_v = scratch_data.reinit(cell);
 
         copy_data.cell_index = cell->active_cell_index();
 
         const auto &               q_points   = fe_v.get_quadrature_points();
         const unsigned int         n_q_points = q_points.size();
         const std::vector<double> &JxW        = fe_v.get_JxW_values();
 
         std::vector<Tensor<2, dim>> hessians(n_q_points);
         fe_v.get_function_hessians(solution, hessians);
 
         std::vector<double> rhs(n_q_points);
         rhs_function->value_list(q_points, rhs);
 
         const double hk                   = cell->diameter();
         double       residual_norm_square = 0;
 
         for (unsigned int point = 0; point < n_q_points; ++point)
           {
             const double residual =
               rhs[point] + diffusion_coefficient * trace(hessians[point]);
             residual_norm_square += residual * residual * JxW[point];
           }
         copy_data.value = hk * hk * residual_norm_square;
       };
 
 @endcode
 
 Next compute boundary terms $\sum_{f\in \partial K \cap \partial \Omega}
 \sigma \left\| [  u_h-g_D ]  \right\|_f^2  $:
 
 @code
     const auto boundary_worker = [&](const auto &        cell,
                                      const unsigned int &face_no,
                                      auto &              scratch_data,
                                      auto &              copy_data) {
       const FEFaceValuesBase<dim> &fe_fv = scratch_data.reinit(cell, face_no);
 
       const auto &   q_points   = fe_fv.get_quadrature_points();
       const unsigned n_q_points = q_points.size();
 
       const std::vector<double> &JxW = fe_fv.get_JxW_values();
 
       std::vector<double> g(n_q_points);
       exact_solution->value_list(q_points, g);
 
       std::vector<double> sol_u(n_q_points);
       fe_fv.get_function_values(solution, sol_u);
 
       const double extent1 = cell->measure() / cell->face(face_no)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent1);
 
       double difference_norm_square = 0.;
       for (unsigned int point = 0; point < q_points.size(); ++point)
         {
           const double diff = (g[point] - sol_u[point]);
           difference_norm_square += diff * diff * JxW[point];
         }
       copy_data.value += penalty * difference_norm_square;
     };
 
 @endcode
 
 And finally interior face terms $\sum_{f\in \partial K}\lbrace \sigma
 \left\| [u_h]  \right\|_f^2   +  h_f \left\|  [\nu \nabla u_h \cdot
 \mathbf n ] \right\|_f^2 \rbrace$:
 
 @code
     const auto face_worker = [&](const auto &        cell,
                                  const unsigned int &f,
                                  const unsigned int &sf,
                                  const auto &        ncell,
                                  const unsigned int &nf,
                                  const unsigned int &nsf,
                                  auto &              scratch_data,
                                  auto &              copy_data) {
       const FEInterfaceValues<dim> &fe_iv =
         scratch_data.reinit(cell, f, sf, ncell, nf, nsf);
 
       copy_data.face_data.emplace_back();
       CopyDataFace &copy_data_face = copy_data.face_data.back();
 
       copy_data_face.cell_indices[0] = cell->active_cell_index();
       copy_data_face.cell_indices[1] = ncell->active_cell_index();
 
       const std::vector<double> &        JxW     = fe_iv.get_JxW_values();
       const std::vector<Tensor<1, dim>> &normals = fe_iv.get_normal_vectors();
 
       const auto &       q_points   = fe_iv.get_quadrature_points();
       const unsigned int n_q_points = q_points.size();
 
       std::vector<double> jump(n_q_points);
       get_function_jump(fe_iv, solution, jump);
 
       std::vector<Tensor<1, dim>> grad_jump(n_q_points);
       get_function_gradient_jump(fe_iv, solution, grad_jump);
 
       const double h = cell->face(f)->diameter();
 
       const double extent1 = cell->measure() / cell->face(f)->measure();
       const double extent2 = ncell->measure() / ncell->face(nf)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent2);
 
       double flux_jump_square = 0;
       double u_jump_square    = 0;
       for (unsigned int point = 0; point < n_q_points; ++point)
         {
           u_jump_square += jump[point] * jump[point] * JxW[point];
           const double flux_jump = grad_jump[point] * normals[point];
           flux_jump_square +=
             diffusion_coefficient * flux_jump * flux_jump * JxW[point];
         }
       copy_data_face.values[0] =
         0.5 * h * (flux_jump_square + penalty * u_jump_square);
       copy_data_face.values[1] = copy_data_face.values[0];
     };
 
 @endcode
 
 Having computed local contributions for each cell, we still
 need a way to copy these into the global vector that will hold
 the error estimators for all cells:
 
 @code
     const auto copier = [&](const auto &copy_data) {
       if (copy_data.cell_index != numbers::invalid_unsigned_int)
         estimated_error_square_per_cell[copy_data.cell_index] +=
           copy_data.value;
       for (auto &cdf : copy_data.face_data)
         for (unsigned int j = 0; j < 2; ++j)
           estimated_error_square_per_cell[cdf.cell_indices[j]] += cdf.values[j];
     };
 
 @endcode
 
 After all of this set-up, let's do the actual work: We resize
 the vector into which the results will be written, and then
 drive the whole process using the MeshWorker::mesh_loop()
 function.
 
 @code
     estimated_error_square_per_cell.reinit(triangulation.n_active_cells());
 
     const UpdateFlags cell_flags =
       update_hessians | update_quadrature_points | update_JxW_values;
     const UpdateFlags face_flags = update_values | update_gradients |
                                    update_quadrature_points |
                                    update_JxW_values | update_normal_vectors;
 
     ScratchData scratch_data(
       mapping, fe, quadrature, cell_flags, face_quadrature, face_flags);
 
     CopyData copy_data;
     MeshWorker::mesh_loop(dof_handler.begin_active(),
                           dof_handler.end(),
                           cell_worker,
                           copier,
                           scratch_data,
                           copy_data,
                           MeshWorker::assemble_own_cells |
                             MeshWorker::assemble_own_interior_faces_once |
                             MeshWorker::assemble_boundary_faces,
                           boundary_worker,
                           face_worker);
   }
 
 @endcode
 
 
 <a name="Thecompute_energy_norm_errorfunction"></a> 
 <h3>The compute_energy_norm_error() function</h3>
 Next, we evaluate the accuracy in terms of the energy norm.
 This function is similar to the assembling of the error estimator above.
 Here we compute the square of the energy norm defined by
 @f[
 \|u \|_{1,h}^2 = \sum_{K \in \Gamma_h} \nu\|\nabla u \|_K^2 +
 \sum_{f \in F_i} \sigma \| [ u ] \|_f^2 +
 \sum_{f \in F_b} \sigma  \|u\|_f^2.
 @f]
 Therefore the corresponding error is
 @f[
 \|u -u_h \|_{1,h}^2 = \sum_{K \in \Gamma_h} \nu\|\nabla (u_h - u)  \|_K^2
 + \sum_{f \in F_i} \sigma  \|[ u_h ] \|_f^2 + \sum_{f \in F_b}\sigma
 \|u_h-g_D\|_f^2.
 @f]
 
 @code
   template <int dim>
   double SIPGLaplace<dim>::compute_energy_norm_error()
   {
     energy_norm_square_per_cell.reinit(triangulation.n_active_cells());
 
 @endcode
 
 Assemble $\sum_{K \in \Gamma_h} \nu\|\nabla (u_h - u)  \|_K^2 $.
 
 @code
     const auto cell_worker =
       [&](const auto &cell, auto &scratch_data, auto &copy_data) {
         const FEValues<dim> &fe_v = scratch_data.reinit(cell);
 
         copy_data.cell_index = cell->active_cell_index();
 
         const auto &               q_points   = fe_v.get_quadrature_points();
         const unsigned int         n_q_points = q_points.size();
         const std::vector<double> &JxW        = fe_v.get_JxW_values();
 
         std::vector<Tensor<1, dim>> grad_u(n_q_points);
         fe_v.get_function_gradients(solution, grad_u);
 
         std::vector<Tensor<1, dim>> grad_exact(n_q_points);
         exact_solution->gradient_list(q_points, grad_exact);
 
         double norm_square = 0;
         for (unsigned int point = 0; point < n_q_points; ++point)
           {
             norm_square +=
               (grad_u[point] - grad_exact[point]).norm_square() * JxW[point];
           }
         copy_data.value = diffusion_coefficient * norm_square;
       };
 
 @endcode
 
 Assemble $\sum_{f \in F_b}\sigma  \|u_h-g_D\|_f^2$.
 
 @code
     const auto boundary_worker = [&](const auto &        cell,
                                      const unsigned int &face_no,
                                      auto &              scratch_data,
                                      auto &              copy_data) {
       const FEFaceValuesBase<dim> &fe_fv = scratch_data.reinit(cell, face_no);
 
       const auto &   q_points   = fe_fv.get_quadrature_points();
       const unsigned n_q_points = q_points.size();
 
       const std::vector<double> &JxW = fe_fv.get_JxW_values();
 
       std::vector<double> g(n_q_points);
       exact_solution->value_list(q_points, g);
 
       std::vector<double> sol_u(n_q_points);
       fe_fv.get_function_values(solution, sol_u);
 
       const double extent1 = cell->measure() / cell->face(face_no)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent1);
 
       double difference_norm_square = 0.;
       for (unsigned int point = 0; point < q_points.size(); ++point)
         {
           const double diff = (g[point] - sol_u[point]);
           difference_norm_square += diff * diff * JxW[point];
         }
       copy_data.value += penalty * difference_norm_square;
     };
 
 @endcode
 
 Assemble $\sum_{f \in F_i} \sigma  \| [ u_h ] \|_f^2$.
 
 @code
     const auto face_worker = [&](const auto &        cell,
                                  const unsigned int &f,
                                  const unsigned int &sf,
                                  const auto &        ncell,
                                  const unsigned int &nf,
                                  const unsigned int &nsf,
                                  auto &              scratch_data,
                                  auto &              copy_data) {
       const FEInterfaceValues<dim> &fe_iv =
         scratch_data.reinit(cell, f, sf, ncell, nf, nsf);
 
       copy_data.face_data.emplace_back();
       CopyDataFace &copy_data_face = copy_data.face_data.back();
 
       copy_data_face.cell_indices[0] = cell->active_cell_index();
       copy_data_face.cell_indices[1] = ncell->active_cell_index();
 
       const std::vector<double> &JxW = fe_iv.get_JxW_values();
 
       const auto &       q_points   = fe_iv.get_quadrature_points();
       const unsigned int n_q_points = q_points.size();
 
       std::vector<double> jump(n_q_points);
       get_function_jump(fe_iv, solution, jump);
 
       const double extent1 = cell->measure() / cell->face(f)->measure();
       const double extent2 = ncell->measure() / ncell->face(nf)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent2);
 
       double u_jump_square = 0;
       for (unsigned int point = 0; point < n_q_points; ++point)
         {
           u_jump_square += jump[point] * jump[point] * JxW[point];
         }
       copy_data_face.values[0] = 0.5 * penalty * u_jump_square;
       copy_data_face.values[1] = copy_data_face.values[0];
     };
 
     const auto copier = [&](const auto &copy_data) {
       if (copy_data.cell_index != numbers::invalid_unsigned_int)
         energy_norm_square_per_cell[copy_data.cell_index] += copy_data.value;
       for (auto &cdf : copy_data.face_data)
         for (unsigned int j = 0; j < 2; ++j)
           energy_norm_square_per_cell[cdf.cell_indices[j]] += cdf.values[j];
     };
 
     const UpdateFlags cell_flags =
       update_gradients | update_quadrature_points | update_JxW_values;
     UpdateFlags face_flags =
       update_values | update_quadrature_points | update_JxW_values;
 
     const ScratchData scratch_data(mapping,
                                    fe,
                                    quadrature_overintegration,
                                    cell_flags,
                                    face_quadrature_overintegration,
                                    face_flags);
 
     CopyData copy_data;
     MeshWorker::mesh_loop(dof_handler.begin_active(),
                           dof_handler.end(),
                           cell_worker,
                           copier,
                           scratch_data,
                           copy_data,
                           MeshWorker::assemble_own_cells |
                             MeshWorker::assemble_own_interior_faces_once |
                             MeshWorker::assemble_boundary_faces,
                           boundary_worker,
                           face_worker);
     const double energy_error =
       std::sqrt(energy_norm_square_per_cell.l1_norm());
     return energy_error;
   }
 
 
 
 @endcode
 
 
 <a name="Therefine_gridfunction"></a> 
 <h3>The refine_grid() function</h3>
 
 @code
   template <int dim>
   void SIPGLaplace<dim>::refine_grid()
   {
     const double refinement_fraction = 0.1;
 
     GridRefinement::refine_and_coarsen_fixed_number(
       triangulation, estimated_error_square_per_cell, refinement_fraction, 0.);
 
     triangulation.execute_coarsening_and_refinement();
   }
 
 
 
 @endcode
 
 
 <a name="Thecompute_errorsfunction"></a> 
 <h3>The compute_errors() function</h3>
 We compute three errors in the $L_2$ norm, $H_1$ seminorm, and
 the energy norm, respectively. These are then printed to screen,
 but also stored in a table that records how these errors decay
 with mesh refinement and which can be output in one step at the
 end of the program.
 
 @code
   template <int dim>
   void SIPGLaplace<dim>::compute_errors()
   {
     double L2_error, H1_error, energy_error;
 
     {
       Vector<float> difference_per_cell(triangulation.n_active_cells());
       VectorTools::integrate_difference(mapping,
                                         dof_handler,
                                         solution,
                                         *(exact_solution.get()),
                                         difference_per_cell,
                                         quadrature_overintegration,
                                         VectorTools::L2_norm);
 
       L2_error = VectorTools::compute_global_error(triangulation,
                                                    difference_per_cell,
                                                    VectorTools::L2_norm);
       convergence_table.add_value("L2", L2_error);
     }
 
     {
       Vector<float> difference_per_cell(triangulation.n_active_cells());
       VectorTools::integrate_difference(mapping,
                                         dof_handler,
                                         solution,
                                         *(exact_solution.get()),
                                         difference_per_cell,
                                         quadrature_overintegration,
                                         VectorTools::H1_seminorm);
 
       H1_error = VectorTools::compute_global_error(triangulation,
                                                    difference_per_cell,
                                                    VectorTools::H1_seminorm);
       convergence_table.add_value("H1", H1_error);
     }
 
     {
       energy_error = compute_energy_norm_error();
       convergence_table.add_value("Energy", energy_error);
     }
 
     std::cout << "  Error in the L2 norm         : " << L2_error << std::endl
               << "  Error in the H1 seminorm     : " << H1_error << std::endl
               << "  Error in the energy norm     : " << energy_error
               << std::endl;
   }
 
 
 
 @endcode
 
 
 <a name="Therunfunction"></a> 
 <h3>The run() function</h3>
 
 @code
   template <int dim>
   void SIPGLaplace<dim>::run()
   {
     const unsigned int max_cycle =
       (test_case == TestCase::convergence_rate ? 6 : 20);
     for (unsigned int cycle = 0; cycle < max_cycle; ++cycle)
       {
         std::cout << "Cycle " << cycle << std::endl;
 
         switch (test_case)
           {
             case TestCase::convergence_rate:
               {
                 if (cycle == 0)
                   {
                     GridGenerator::hyper_cube(triangulation);
 
                     triangulation.refine_global(2);
                   }
                 else
                   {
                     triangulation.refine_global(1);
                   }
                 break;
               }
 
             case TestCase::l_singularity:
               {
                 if (cycle == 0)
                   {
                     GridGenerator::hyper_L(triangulation);
                     triangulation.refine_global(3);
                   }
                 else
                   {
                     refine_grid();
                   }
                 break;
               }
 
             default:
               {
                 Assert(false, ExcNotImplemented());
               }
           }
 
         std::cout << "  Number of active cells       : "
                   << triangulation.n_active_cells() << std::endl;
         setup_system();
 
         std::cout << "  Number of degrees of freedom : " << dof_handler.n_dofs()
                   << std::endl;
 
         assemble_system();
         solve();
         output_results(cycle);
         {
           convergence_table.add_value("cycle", cycle);
           convergence_table.add_value("cells", triangulation.n_active_cells());
           convergence_table.add_value("dofs", dof_handler.n_dofs());
         }
         compute_errors();
 
         if (test_case == TestCase::l_singularity)
           {
             compute_error_estimate();
             std::cout << "  Estimated error              : "
                       << std::sqrt(estimated_error_square_per_cell.l1_norm())
                       << std::endl;
 
             convergence_table.add_value(
               "Estimator",
               std::sqrt(estimated_error_square_per_cell.l1_norm()));
           }
         std::cout << std::endl;
       }
 
 @endcode
 
 Having run all of our computations, let us tell the convergence
 table how to format its data and output it to screen:
 
 @code
     convergence_table.set_precision("L2", 3);
     convergence_table.set_precision("H1", 3);
     convergence_table.set_precision("Energy", 3);
 
     convergence_table.set_scientific("L2", true);
     convergence_table.set_scientific("H1", true);
     convergence_table.set_scientific("Energy", true);
 
     if (test_case == TestCase::convergence_rate)
       {
         convergence_table.evaluate_convergence_rates(
           "L2", ConvergenceTable::reduction_rate_log2);
         convergence_table.evaluate_convergence_rates(
           "H1", ConvergenceTable::reduction_rate_log2);
       }
     if (test_case == TestCase::l_singularity)
       {
         convergence_table.set_precision("Estimator", 3);
         convergence_table.set_scientific("Estimator", true);
       }
 
     std::cout << "degree = " << degree << std::endl;
     convergence_table.write_text(
       std::cout, TableHandler::TextOutputFormat::org_mode_table);
   }
 } // namespace Step74
 
 
 
 @endcode
 
 
 <a name="Themainfunction"></a> 
 <h3>The main() function</h3>
 The following <code>main</code> function is similar to previous examples as
 well, and need not be commented on.
 
 @code
 int main()
 {
   try
     {
       using namespace dealii;
       using namespace Step74;
 
       const TestCase test_case = TestCase::l_singularity;
 
       SIPGLaplace<2> problem(test_case);
       problem.run();
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
     };
 
   return 0;
 }
 @endcode
<a name="Results"></a><h1>Results</h1>


The output of this program consist of the console output and
solutions in vtu format.

In the first test case, when you run the program, the screen output should look like the following:
@code
Cycle 0
  Number of active cells       : 16
  Number of degrees of freedom : 256
  Error in the L2 norm         : 0.00193285
  Error in the H1 seminorm     : 0.106087
  Error in the energy norm     : 0.150625

Cycle 1
  Number of active cells       : 64
  Number of degrees of freedom : 1024
  Error in the L2 norm         : 9.60497e-05
  Error in the H1 seminorm     : 0.0089954
  Error in the energy norm     : 0.0113265

Cycle 2
.
.
.
@endcode

When using the smooth case with polynomial degree 3, the convergence
table will look like this:
<table align="center" class="doxtable">
  <tr>
    <th>cycle</th>
    <th>n_cellss</th>
    <th>n_dofs</th>
    <th>L2 </th>
    <th>rate</th>
    <th>H1</th>
    <th>rate</th>
    <th>Energy</th>
  </tr>
  <tr>
    <td align="center">0</td>
    <td align="right">16</td>
    <td align="right">256</td>
    <td align="center">1.933e-03</td>
    <td>&nbsp;</td>
    <td align="center">1.061e-01</td>
    <td>&nbsp;</td>
    <td align="center">1.506e-01</td>
  </tr>
  <tr>
    <td align="center">1</td>
    <td align="right">64</td>
    <td align="right">1024</td>
    <td align="center">9.605e-05</td>
    <td align="center">4.33</td>
    <td align="center">8.995e-03</td>
    <td align="center">3.56</td>
    <td align="center">1.133e-02</td>
  </tr>
  <tr>
    <td align="center">2</td>
    <td align="right">256</td>
    <td align="right">4096</td>
    <td align="center">5.606e-06</td>
    <td align="center">4.10</td>
    <td align="center">9.018e-04</td>
    <td align="center">3.32</td>
    <td align="center">9.736e-04</td>
  </tr>
  <tr>
    <td align="center">3</td>
    <td align="right">1024</td>
    <td align="right">16384</td>
    <td align="center">3.484e-07</td>
    <td align="center">4.01</td>
    <td align="center">1.071e-04</td>
    <td align="center">3.07</td>
    <td align="center">1.088e-04</td>
  </tr>
  <tr>
    <td align="center">4</td>
    <td align="right">4096</td>
    <td align="right">65536</td>
    <td align="center">2.179e-08</td>
    <td align="center">4.00</td>
    <td align="center">1.327e-05</td>
    <td align="center">3.01</td>
    <td align="center">1.331e-05</td>
  </tr>
  <tr>
    <td align="center">5</td>
    <td align="right">16384</td>
    <td align="right">262144</td>
    <td align="center">1.363e-09</td>
    <td align="center">4.00</td>
    <td align="center">1.656e-06</td>
    <td align="center">3.00</td>
    <td align="center">1.657e-06</td>
  </tr>
</table>

Theoretically, for polynomial degree $p$, the order of convergence in $L_2$
norm and $H^1$ seminorm should be $p+1$ and $p$, respectively. Our numerical
results are in good agreement with theory.

In the second test case, when you run the program, the screen output should look like the following:
@code
Cycle 0
  Number of active cells       : 192
  Number of degrees of freedom : 3072
  Error in the L2 norm         : 0.000323585
  Error in the H1 seminorm     : 0.0296202
  Error in the energy norm     : 0.0420478
  Estimated error              : 0.136067

Cycle 1
  Number of active cells       : 249
  Number of degrees of freedom : 3984
  Error in the L2 norm         : 0.000114739
  Error in the H1 seminorm     : 0.0186571
  Error in the energy norm     : 0.0264879
  Estimated error              : 0.0857186

Cycle 2
.
.
.
@endcode

The following figure provides a log-log plot of the errors versus
the number of degrees of freedom for this test case on the L-shaped
domain. In order to interpret it, let $n$ be the number of degrees of
freedom, then on uniformly refined meshes, $h$ is of order
$1/\sqrt{n}$ in 2D. Combining the theoretical results in the previous case,
we see that if the solution is sufficiently smooth,
we can expect the error in the $L_2$ norm to be of order $O(n^{-\frac{p+1}{2}})$
and in $H^1$ seminorm to be $O(n^{-\frac{p}{2}})$. It is not a priori
clear that one would get the same kind of behavior as a function of
$n$ on adaptively refined meshes like the ones we use for this second
test case, but one can certainly hope. Indeed, from the figure, we see
that the SIPG with adaptive mesh refinement produces asymptotically
the kinds of hoped-for results:

<img width="600px" src="https://www.dealii.org/images/steps/developer/step-74.log-log-plot.png" alt="">

In addition, we observe that the error estimator decreases
at almost the same rate as the errors in the energy norm and $H^1$ seminorm,
and one order lower than the $L_2$ error. This suggests
its ability to predict regions with large errors.

While this tutorial is focused on the implementation, the step-59 tutorial program achieves an efficient
large-scale solver in terms of computing time with matrix-free solution techniques.
Note that the step-59 tutorial does not work with meshes containing hanging nodes at this moment,
because the multigrid interface matrices are not as easily determined,
but that is merely the lack of some interfaces in deal.II, nothing fundamental.


<a name="PlainProg"></a>
<h1> The plain program</h1>
@include "step-74.cc"
*/
