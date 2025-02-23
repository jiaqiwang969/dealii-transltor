//include/deal.II-translator/A-tutorial/step-74_0.txt
/**
  @page step_74 The step-74 tutorial program 
* 本教程依赖于  step-12  。
* @htmlonly
<table class="tutorial" width="50%">
<tr><th colspan="2"><b><small>Table of contents</small></b><b><small>Table of contents</small></b></th></tr>
<tr><td width="50%" valign="top">
<ol>
  <li> <a href="#Intro" class=bold>Introduction</a><a href="#Intro" class=bold>Introduction</a>
    <ul>
        <li><a href="#Overview">Overview</a><a href="#Overview">Overview</a>
        <li><a href="#Theequation">The equation</a><a href="#Theequation">The equation</a>
        <li><a href="#Thepenaltyparameter">The penalty parameter</a><a href="#Thepenaltyparameter">The penalty parameter</a>
        <li><a href="#Aposteriorierrorestimator">A posteriori error estimator</a><a href="#Aposteriorierrorestimator">A posteriori error estimator</a>
        <li><a href="#Thetestcase">The test case</a><a href="#Thetestcase">The test case</a>
    </ul>
  <li> <a href="#CommProg" class=bold>The commented program</a><a href="#CommProg" class=bold>The commented program</a>
    <ul>
        <li><a href="#Equationdata">Equation data</a><a href="#Equationdata">Equation data</a>
        <li><a href="#Auxiliaryfunctions">Auxiliary functions</a><a href="#Auxiliaryfunctions">Auxiliary functions</a>
        <li><a href="#TheCopyData">The CopyData</a><a href="#TheCopyData">The CopyData</a>
        <li><a href="#TheSIPGLaplaceclass">The SIPGLaplace class</a><a href="#TheSIPGLaplaceclass">The SIPGLaplace class</a>
        <li><a href="#Theassemble_systemfunction">The assemble_system function</a><a href="#Theassemble_systemfunction">The assemble_system function</a>
        <li><a href="#Thesolveandoutput_resultsfunction">The solve() and output_results() function</a><a href="#Thesolveandoutput_resultsfunction">The solve() and output_results() function</a>
        <li><a href="#Thecompute_error_estimatefunction">The compute_error_estimate() function</a><a href="#Thecompute_error_estimatefunction">The compute_error_estimate() function</a>
        <li><a href="#Thecompute_energy_norm_errorfunction">The compute_energy_norm_error() function</a><a href="#Thecompute_energy_norm_errorfunction">The compute_energy_norm_error() function</a>
        <li><a href="#Therefine_gridfunction">The refine_grid() function</a><a href="#Therefine_gridfunction">The refine_grid() function</a>
        <li><a href="#Thecompute_errorsfunction">The compute_errors() function</a><a href="#Thecompute_errorsfunction">The compute_errors() function</a>
        <li><a href="#Therunfunction">The run() function</a><a href="#Therunfunction">The run() function</a>
        <li><a href="#Themainfunction">The main() function</a><a href="#Themainfunction">The main() function</a>
      </ul>
</ol></td><td width="50%" valign="top"><ol>
  <li value="3"> <a href="#Results" class=bold>Results</a><a href="#Results" class=bold>Results</a>
    <ul>
    </ul>
  <li> <a href="#PlainProg" class=bold>The plain program</a><a href="#PlainProg" class=bold>The plain program</a>
</ol> </td> </tr> </table>
@endhtmlonly
*  <br> 
* <i>
This program was contributed by Timo Heister and Jiaqi Zhang.
<br>
This material is based upon work partly supported by the National
Science Foundation Award DMS-2028346, OAC-2015848, EAR-1925575, by the Computational
Infrastructure in Geodynamics initiative (CIG), through the NSF under Award
EAR-0949446 and EAR-1550901 and The University of California
* 
-- Davis.
</i>


*<a name="Intro"></a><a name="emSymmetricinteriorpenaltyGalerkinemSIPGmethodforPoissonsequation"></a><h1><em>Symmetric interior penalty Galerkin</em> (SIPG) method for Poisson's equation</h1>


* <a name="Overview"></a><h3>Overview</h3> 。
* 在本教程中，我们展示了FEInterfaceValues类的用法，该类是为集合不连续Galerkin（DG）方法产生的面项而设计的。FEInterfaceValues类提供了一种简单的方法来获得形状函数和跨单元面解的跳跃和平均。 <ol>   <li>  泊松方程的SIPG方法，在 step-39 和 step-59 中已经使用过。    <li>  使用FEInterfaceValues组装面项，使用 MeshWorker::mesh_loop(), 组装系统矩阵，这与 step-12 类似。    <li>  使用误差估计器进行自适应网格细化。    <li>  两个测试案例：平滑函数的收敛测试和奇异解的适应性网格细化测试。 </ol> 
*<a name="Theequation"></a><h3>The equation</h3>
* 在这个例子中，我们考虑泊松方程@f[
* 
- \nabla \cdot \left( \nu  \nabla u\right) = f  \qquad   \mbox{in } \Omega,
@f]受边界条件@f[
u = g_D \qquad \mbox{on } \partial \Omega.
@f]的影响。为了简单起见，我们假设扩散系数 $\nu$ 是常数。注意，如果 $\nu$ 是不连续的，我们在计算单元面上的跳跃项时需要考虑到这一点。
* 我们用 ${\mathbb T}_h$ 表示网格， $K\in{\mathbb T}_h$ 是一个网格单元。内部和边界面的集合分别用 ${\mathbb F}^i_h$ 和 ${\mathbb F}^b_h$ 表示。让 $K^0$ 和 $K^1$ 是共享一个面 $f\in F_h^i$ 的两个单元， $\mathbf n$ 是 $K^0$ 的外法向量。那么跳跃运算符由 "这里减去那里 "公式给出，@f[
\jump{v} = v^0
* 
- v^1
@f]和平均运算符分别为@f[
\average{v} = \frac{v^0 + v^1}{2}
@f]。请注意，当 $f\subset \partial \Omega$ 时，我们定义 $\jump{v} = v$ 和 $\average{v}=v$ 。使用SIPG的离散化由以下弱式给出（更多细节可以在 @cite di2011mathematical 和其中的参考文献中找到）。
* @f{align*}
&\sum_{K\in {\mathbb T}_h} (\nabla v_h, \nu \nabla u_h)_K\\
&-\sum_{F \in F_h^i} \left\{
    \left< \jump{v_h}, \nu\average{ \nabla u_h} \cdot  \mathbf n \right>_F
   +\left<\average{ \nabla v_h }\cdot \mathbf n,\nu\jump{u_h}\right>_F
* 


* 
* 


* 
* 


* 
* 
-\left<\jump{v_h},\nu \sigma \jump{u_h} \right>_F
  \right\}\\
&-\sum_{F \in F_h^b} \left\{
    \left<v_h, \nu  \nabla u_h\cdot \mathbf n \right>_F
  + \left< \nabla v_h \cdot \mathbf n , \nu u_h\right>_F
* 


* 
* 


* 
* 
- \left< v_h,\nu \sigma u_h\right>_F
  \right\}\\
&=(v_h, f)_\Omega
* 


* 
* 


* 
* 
- \sum_{F \in F_h^b} \left\{
    \left< \nabla v_h \cdot \mathbf n, \nu g_D\right>_F
* 
- \left<v_h,\nu \sigma g_D\right>_F
  \right\}.
@f}
*
*

* <a name="Thepenaltyparameter"></a><h3>The penalty parameter</h3> 。
* 惩罚参数定义为  $\sigma = \gamma/h_f$  ，其中  $h_f$  是与细胞面相关的局部长度尺度；这里我们选择细胞在面的法线方向上的长度近似值。 $\frac 1{h_f} = \frac 12 \left(\frac 1{h_K} + \frac 1{h_{K'}}\right)$  ，其中 $K,K'$ 是与面相邻的两个单元 $f$ ，我们计算出 $h_K = \frac{|K|}{|f|}$ 。
* 在上述公式中， $\gamma$ 是惩罚常数。为了确保离散矫捷性，惩罚常数必须足够大 @cite ainsworth2007posteriori 。人们对于应该使用文献中提出的哪个公式并没有真正的共识。(这与 step-47 的 "结果 "部分所讨论的情况相似。)人们可以直接选择一个大的常数，而其他选择可以是 $(p+1)^2$ 或 $p(p+1)$ 的倍数。在本代码中，我们遵循  step-39  并使用  $\gamma = p(p+1)$  。
*

*<a name="Aposteriorierrorestimator"></a><h3>A posteriori error estimator</h3>
* 在这个例子中，稍加修改，我们使用卡拉卡希安和帕斯卡尔的误差估计器 @cite karakashian2003posteriori @f[
\eta^2 = \sum_{K \in {\mathbb T}_h} \eta^2_{K} +  \sum_{f_i \in {\mathbb F}^i_h}  \eta^2_{f_i} + \sum_{f_b \in F^i_b}\eta^2_{f_b}
@f]，其中
* @f{align*}{
\eta^2_{K} &= h_K^2 \left\| f + \nu \Delta u_h \right\|_K^2,
\\
\eta^2_{f_i} &= \sigma \left\| \jump{u_h}  \right\|_f^2   +  h_f \left\|  \jump{\nu \nabla u_h} \cdot \mathbf n   \right\|_f^2,
\\
\eta_{f_b}^2 &=  \sigma \left\| u_h-g_D \right\|_f^2.
@f}
* 这里我们用 $\sigma = \gamma/h_f$ 代替 $\gamma^2/h_f$ 来表示 $u_h$ 的跳跃项（ $\eta^2_{f_i}$ 和 $\eta_{f_b}^2$ 的第一个项）。
*为了计算这个估计值，在每个单元格 $K$ 中我们计算
* @f{align*}{
\eta_{c}^2 &= h_K^2 \left\| f + \nu \Delta u_h \right\|_K^2,
\\
\eta_{f}^2 &= \sum_{f\in \partial K}\lbrace \sigma \left\| \jump{u_h}  \right\|_f^2   +  h_f \left\|  \jump{\nu \nabla u_h} \cdot \mathbf n  \right\|_f^2 \rbrace,
\\
\eta_{b}^2 &= \sum_{f\in \partial K \cap \partial \Omega}  \sigma \left\| (u_h
* 
-g_D)  \right\|_f^2.
@f}
* 然后每个单元的误差估计的平方是@f[
\eta_\text{local}^2 =\eta_{c}^2+0.5\eta_{f}^2+\eta_{b}^2.
@f]， $0.5$ 的系数是由于整体误差估计器只包括每个内部面一次，所以每个单元的估计器对相邻的两个单元都以一半的系数来计算。注意我们计算 $\eta_\text{local}^2$ 而不是 $\eta_\text{local}$ 以简化实现。然后每个单元的误差估计方被存储在一个全局向量中，其 $l_1$ 准则等于 $\eta^2$  。
*<a name="Thetestcase"></a><h3>The test case</h3> 。
* 在第一个测试问题中，我们使用二维的 $\nu =1$ 的平滑制造解进行收敛测试
* @f{align*}{
u&=\sin(2\pi x)\sin(2\pi y), &\qquad\qquad &(x,y)\in\Omega=(0,1)\times (0,1),
\\
u&=0,                        &\qquad\qquad &\text{on } \partial \Omega,
@f}
* 和  $f= 8\pi^2 u$  。我们针对制造的解决方案计算误差并评估收敛率。
* 在第二个测试中，我们在二维的L形域 (GridGenerator::hyper_L) 上选择了 Functions::LSingularityFunction 。该解在极坐标中由 $u(r,\phi) = r^{\frac{2}{3}}\sin \left(\frac{2}{3}\phi \right)$ 给出，它在原点有一个奇点。我们构建了一个误差估计器来检测有大误差的区域，根据这个估计器来自适应地细化网格。
*

* <a name="CommProg"></a> <h1> The commented program</h1>。
* 前面几个文件已经在前面的例子中讲过了，因此不再进一步评论。
*


* @code
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
*
* 这里定义了不连续的有限元和FEInterfaceValues。
*


* @code
 #include <deal.II/fe/fe_dgq.h>
 #include <deal.II/fe/fe_interface_values.h>
* 
 #include <deal.II/numerics/derivative_approximation.h>
 #include <deal.II/numerics/vector_tools.h>
 #include <deal.II/base/convergence_table.h>
* 
 #include <deal.II/meshworker/copy_data.h>
 #include <deal.II/meshworker/mesh_loop.h>
 #include <deal.II/meshworker/scratch_data.h>
* 
 namespace Step74
 {
   using namespace dealii;
* 
 @endcode
*
* <a name="Equationdata"></a> <h3>Equation data</h3> 这里我们定义了两个测试案例：平滑函数的收敛率和 Functions::LSingularityFunction.  的l_singularity。
*


* @code
   enum class TestCase
   {
     convergence_rate,
     l_singularity
   };
* 
 
* 
 @endcode
*
*收敛性测试的平滑解。
*


* @code
   template <int dim>
   class SmoothSolution : public Function<dim>
   {
   public:
     SmoothSolution()
       : Function<dim>()
     {}
* 
     virtual void value_list(const std::vector<Point<dim>> &points,
                             std::vector<double> &          values,
                             const unsigned int component = 0) const override;
* 
     virtual Tensor<1, dim>
     gradient(const Point<dim> & point,
              const unsigned int component = 0) const override;
   };
* 
 
* 
   template <int dim>
   void SmoothSolution<dim>::value_list(const std::vector<Point<dim>> &points,
                                        std::vector<double> &          values,
                                        const unsigned int  /*component*/ ) const
   {
     using numbers::PI;
     for (unsigned int i = 0; i < values.size(); ++i)
       values[i] =
         std::sin(2. PI points[i][0]) std::sin(2. PI points[i][1]);
   }
* 
 
* 
   template <int dim>
   Tensor<1, dim>
   SmoothSolution<dim>::gradient(const Point<dim> &point,
                                 const unsigned int  /*component*/ ) const
   {
     Tensor<1, dim> return_value;
     using numbers::PI;
     return_value[0] =
       2. PI std::cos(2. PI point[0]) std::sin(2. PI point[1]);
     return_value[1] =
       2. PI std::sin(2. PI point[0]) std::cos(2. PI point[1]);
     return return_value;
   }
* 
 
* 
 @endcode
*
* 相应的平滑函数的右手边。
*


* @code
   template <int dim>
   class SmoothRightHandSide : public Function<dim>
   {
   public:
     SmoothRightHandSide()
       : Function<dim>()
     {}
* 
     virtual void value_list(const std::vector<Point<dim>> &points,
                             std::vector<double> &          values,
                             const unsigned int  /*component*/ ) const override;
   };
* 
 
* 
   template <int dim>
   void
   SmoothRightHandSide<dim>::value_list(const std::vector<Point<dim>> &points,
                                        std::vector<double> &          values,
                                        const unsigned int  /*component*/ ) const
   {
     using numbers::PI;
     for (unsigned int i = 0; i < values.size(); ++i)
       values[i] = 8. PI PI std::sin(2. PI points[i][0])
                   std::sin(2. PI points[i][1]);
   }
* 
 
* 
 @endcode
*
* 对应于函数 Functions::LSingularityFunction, 的右手边，我们假设扩散系数 $\nu = 1$  。
*


* @code
   template <int dim>
   class SingularRightHandSide : public Function<dim>
   {
   public:
     SingularRightHandSide()
       : Function<dim>()
     {}
* 
     virtual void value_list(const std::vector<Point<dim>> &points,
                             std::vector<double> &          values,
                             const unsigned int  /*component*/ ) const override;
* 
   private:
     const Functions::LSingularityFunction ref;
   };
* 
 
* 
   template <int dim>
   void
   SingularRightHandSide<dim>::value_list(const std::vector<Point<dim>> &points,
                                          std::vector<double> &          values,
                                          const unsigned int  /*component*/ ) const
   {
     for (unsigned int i = 0; i < values.size(); ++i)
       values[i] =
* 
-ref.laplacian(points[i]);
   }
* 
 
* 
 @endcode
*
* <a name="Auxiliaryfunctions"></a> <h3>Auxiliary functions</h3> 以下两个辅助函数分别用于计算一个面上的 $u_h$ 和 $\nabla u_h$ 的跳转项。
*


* @code
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
       jump[q] = face_values[0][q]
* 
- face_values[1][q];
   }
* 
 
* 
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
       gradient_jump[q] = face_gradients[0][q]
* 
- face_gradients[1][q];
   }
* 
 @endcode
*
* 这个函数计算惩罚  $\sigma$  。
*


* @code
   double get_penalty_factor(const unsigned int fe_degree,
                             const double       cell_extent_left,
                             const double       cell_extent_right)
   {
     const unsigned int degree = std::max(1U, fe_degree);
     return degree (degree + 1.) 0.5
            (1. / cell_extent_left + 1. / cell_extent_right);
   }
* 
 
 @endcode
*
* <a name="TheCopyData"></a> <h3>The CopyData</h3> 在下文中，我们为  MeshWorker::mesh_loop(),  定义了 "复制 "对象，它与  step-12  基本上相同。注意，这里没有定义 "Scratch "对象，因为我们用 MeshWorker::ScratchData<dim> 代替。("复制 "和 "抓取 "对象的使用在WorkStream命名空间文档中有广泛的解释。
*


* @code
   struct CopyDataFace
   {
     FullMatrix<double>                   cell_matrix;
     std::vector<types::global_dof_index> joint_dof_indices;
     std::array<double, 2>                values;
     std::array<unsigned int, 2>          cell_indices;
   };
* 
 
* 
   struct CopyData
   {
     FullMatrix<double>                   cell_matrix;
     Vector<double>                       cell_rhs;
     std::vector<types::global_dof_index> local_dof_indices;
     std::vector<CopyDataFace>            face_data;
     double                               value;
     unsigned int                         cell_index;
* 
 
     template <class Iterator>
     void reinit(const Iterator &cell, const unsigned int dofs_per_cell)
     {
       cell_matrix.reinit(dofs_per_cell, dofs_per_cell);
       cell_rhs.reinit(dofs_per_cell);
       local_dof_indices.resize(dofs_per_cell);
       cell->get_dof_indices(local_dof_indices);
     }
   };
* 
 
* 
 @endcode
*
* <a name="TheSIPGLaplaceclass"></a> <h3>The SIPGLaplace class</h3> 在这些准备工作之后，我们进行本程序的主类，称为`SIPGLaplace`。该类的整体结构与其他许多教程程序一样。主要的区别只出现在集合函数的实现上，因为我们使用FEInterfaceValues来集合面的条件。
*


* @code
   template <int dim>
   class SIPGLaplace
   {
   public:
     SIPGLaplace(const TestCase &test_case);
     void run();
* 
   private:
     void setup_system();
     void assemble_system();
     void solve();
     void refine_grid();
     void output_results(const unsigned int cycle) const;
* 
     void   compute_errors();
     void   compute_error_estimate();
     double compute_energy_norm_error();
* 
     Triangulation<dim>    triangulation;
     const unsigned int    degree;
     const QGauss<dim>     quadrature;
     const QGauss<dim
* 
- 1> face_quadrature;
     const QGauss<dim>     quadrature_overintegration;
     const QGauss<dim
* 
- 1> face_quadrature_overintegration;
     const MappingQ1<dim>  mapping;
* 
     using ScratchData = MeshWorker::ScratchData<dim>;
* 
     const FE_DGQ<dim> fe;
     DoFHandler<dim>   dof_handler;
* 
     SparsityPattern      sparsity_pattern;
     SparseMatrix<double> system_matrix;
     Vector<double>       solution;
     Vector<double>       system_rhs;
* 
 @endcode
*
* 该类的其余成员用于以下方面。
*


*
* - 每个单元存储误差估计器平方和能量规范平方的矢量。
*


*
* - 在屏幕上打印收敛率和错误。
*


*
* - 扩散系数 $\nu$ 被设置为1。
*


*
* - 存储要计算的测试案例的信息的成员。
*


* @code
     Vector<double> estimated_error_square_per_cell;
     Vector<double> energy_norm_square_per_cell;
* 
     ConvergenceTable convergence_table;
* 
     const double diffusion_coefficient = 1.;
* 
     const TestCase                       test_case;
     std::unique_ptr<const Function<dim>> exact_solution;
     std::unique_ptr<const Function<dim>> rhs_function;
   };
* 
 @endcode
*
* 这里的构造函数将测试案例作为输入，然后确定正确的解决方案和右手边的类。其余的成员变量以明显的方式进行初始化。
*


* @code
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
* 
     else if (test_case == TestCase::l_singularity)
       {
         exact_solution =
           std::make_unique<const Functions::LSingularityFunction>();
         rhs_function = std::make_unique<const SingularRightHandSide<dim>>();
       }
     else
       AssertThrow(false, ExcNotImplemented());
   }
* 
 
* 
   template <int dim>
   void SIPGLaplace<dim>::setup_system()
   {
     dof_handler.distribute_dofs(fe);
     DynamicSparsityPattern dsp(dof_handler.n_dofs());
     DoFTools::make_flux_sparsity_pattern(dof_handler, dsp);
     sparsity_pattern.copy_from(dsp);
* 
     system_matrix.reinit(sparsity_pattern);
     solution.reinit(dof_handler.n_dofs());
     system_rhs.reinit(dof_handler.n_dofs());
   }
* 
 
* 
 @endcode
*
* <a name="Theassemble_systemfunction"></a> <h3>The assemble_system function</h3> 这里的装配功能与  step-12  和  step-47  中的相似。与手工装配不同的是，我们只需要专注于在每个单元格、每个边界面和每个内部面进行装配。单元和面的循环是由 MeshWorker::mesh_loop(). 自动处理的。
* 该函数首先定义了一个局部（lambda）函数，用于整合单元项。
*


* @code
   template <int dim>
   void SIPGLaplace<dim>::assemble_system()
   {
     const auto cell_worker =
       [&](const auto &cell, auto &scratch_data, auto &copy_data) {
         const FEValues<dim> &fe_v          = scratch_data.reinit(cell);
         const unsigned int   dofs_per_cell = fe_v.dofs_per_cell;
         copy_data.reinit(cell, dofs_per_cell);
* 
         const auto &       q_points    = scratch_data.get_quadrature_points();
         const unsigned int n_q_points  = q_points.size();
         const std::vector<double> &JxW = scratch_data.get_JxW_values();
* 
         std::vector<double> rhs(n_q_points);
         rhs_function->value_list(q_points, rhs);
* 
         for (unsigned int point = 0; point < n_q_points; ++point)
           for (unsigned int i = 0; i < fe_v.dofs_per_cell; ++i)
             {
               for (unsigned int j = 0; j < fe_v.dofs_per_cell; ++j)
                 copy_data.cell_matrix(i, j) +=
                   diffusion_coefficient     // nu
                   fe_v.shape_grad(i, point) // grad v_h
                   fe_v.shape_grad(j, point) // grad u_h
                   JxW[point];                 // dx
* 
               copy_data.cell_rhs(i) += fe_v.shape_value(i, point) // v_h
                                        rhs[point]                 // f
                                        JxW[point];                  // dx
             }
       };
* 
 @endcode
*
* 接下来，我们需要一个在边界上集合面积分的函数。
*


* @code
     const auto boundary_worker = [&](const auto &        cell,
                                      const unsigned int &face_no,
                                      auto &              scratch_data,
                                      auto &              copy_data) {
       const FEFaceValuesBase<dim> &fe_fv = scratch_data.reinit(cell, face_no);
* 
       const auto &       q_points      = scratch_data.get_quadrature_points();
       const unsigned int n_q_points    = q_points.size();
       const unsigned int dofs_per_cell = fe_fv.dofs_per_cell;
* 
       const std::vector<double> &        JxW = scratch_data.get_JxW_values();
       const std::vector<Tensor<1, dim>> &normals =
         scratch_data.get_normal_vectors();
* 
       std::vector<double> g(n_q_points);
       exact_solution->value_list(q_points, g);
* 
       const double extent1 = cell->measure() / cell->face(face_no)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent1);
* 
       for (unsigned int point = 0; point < n_q_points; ++point)
         {
           for (unsigned int i = 0; i < dofs_per_cell; ++i)
             for (unsigned int j = 0; j < dofs_per_cell; ++j)
               copy_data.cell_matrix(i, j) +=
                 (-diffusion_coefficient        //
* 
- nu
                    fe_fv.shape_value(i, point) // v_h
                    (fe_fv.shape_grad(j, point) // (grad u_h .
                     normals[point])              //  n)
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 
- diffusion_coefficient         //
* 
- nu
                      (fe_fv.shape_grad(i, point) // (grad v_h .
                       normals[point])            //  n)
                      fe_fv.shape_value(j, point)   // u_h
* 
                  + diffusion_coefficient penalty // + nu sigma
                      fe_fv.shape_value(i, point)   // v_h
                      fe_fv.shape_value(j, point)     // u_h
* 
                  )
                 JxW[point]; // dx
* 
           for (unsigned int i = 0; i < dofs_per_cell; ++i)
             copy_data.cell_rhs(i) +=
               (-diffusion_coefficient        //
* 
- nu
                  (fe_fv.shape_grad(i, point) // (grad v_h .
                   normals[point])            //  n)
                  g[point]                      // g
* 
 
                + diffusion_coefficient penalty        // + nu sigma
                    fe_fv.shape_value(i, point) g[point] // v_h g
* 
                )
               JxW[point]; // dx
         }
     };
* 
 @endcode
*
* 最后，一个在内部面组装面积分的函数。为了重新初始化FEInterfaceValues，我们需要向FEInterfaceValues的reinit()函数传递单元格、面和子面指数（用于自适应细化）。
*


* @code
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
* 
       const auto &       q_points   = fe_iv.get_quadrature_points();
       const unsigned int n_q_points = q_points.size();
* 
       copy_data.face_data.emplace_back();
       CopyDataFace &     copy_data_face = copy_data.face_data.back();
       const unsigned int n_dofs_face    = fe_iv.n_current_interface_dofs();
       copy_data_face.joint_dof_indices  = fe_iv.get_interface_dof_indices();
       copy_data_face.cell_matrix.reinit(n_dofs_face, n_dofs_face);
* 
       const std::vector<double> &        JxW     = fe_iv.get_JxW_values();
       const std::vector<Tensor<1, dim>> &normals = fe_iv.get_normal_vectors();
* 
       const double extent1 = cell->measure() / cell->face(f)->measure();
       const double extent2 = ncell->measure() / ncell->face(nf)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent2);
* 
       for (unsigned int point = 0; point < n_q_points; ++point)
         {
           for (unsigned int i = 0; i < n_dofs_face; ++i)
             for (unsigned int j = 0; j < n_dofs_face; ++j)
               copy_data_face.cell_matrix(i, j) +=
                 (-diffusion_coefficient              //
* 
- nu
                    fe_iv.jump(i, point)              // [v_h]
                    (fe_iv.average_gradient(j, point) // ({grad u_h} .
                     normals[point])                    //  n)
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 


* 
* 
- diffusion_coefficient               //
* 
- nu
                      (fe_iv.average_gradient(i, point) // (grad v_h .
                       normals[point])                  //  n)
                      fe_iv.jump(j, point)                // [u_h]
* 
                  + diffusion_coefficient penalty // + nu sigma
                      fe_iv.jump(i, point)          // [v_h]
                      fe_iv.jump(j, point)            // [u_h]
* 
                  )
                 JxW[point]; // dx
         }
     };
* 
 @endcode

* 下面的lambda函数就会将数据复制到全局矩阵和右手边。  虽然DG离散化中没有悬空节点约束，但我们定义了一个空的AffineConstraints对象，使我们可以使用 AffineConstraints::distribute_local_to_global() 的功能。
*


* @code
     AffineConstraints<double> constraints;
     constraints.close();
     const auto copier = [&](const auto &c) {
       constraints.distribute_local_to_global(c.cell_matrix,
                                              c.cell_rhs,
                                              c.local_dof_indices,
                                              system_matrix,
                                              system_rhs);
* 
 @endcode
*
* 从内部面组件复制数据到全局矩阵。
*


* @code
       for (auto &cdf : c.face_data)
         {
           constraints.distribute_local_to_global(cdf.cell_matrix,
                                                  cdf.joint_dof_indices,
                                                  system_matrix);
         }
     };
* 
 
 @endcode
*
* 在定义了装配函数后，我们现在可以创建ScratchData和CopyData对象，并将它们与上面的lambda函数一起传递给 MeshWorker::mesh_loop(). 此外，我们需要指定我们要在内部面完全装配一次。
*


* @code
     const UpdateFlags cell_flags = update_values | update_gradients |
                                    update_quadrature_points | update_JxW_values;
     const UpdateFlags face_flags = update_values | update_gradients |
                                    update_quadrature_points |
                                    update_normal_vectors | update_JxW_values;
* 
     ScratchData scratch_data(
       mapping, fe, quadrature, cell_flags, face_quadrature, face_flags);
     CopyData copy_data;
* 
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
* 
 
* 
 @endcode
*
* <a name="Thesolveandoutput_resultsfunction"></a> <h3>The solve() and output_results() function</h3> 以下两个函数完全是标准的，没有难度。
*


* @code
   template <int dim>
   void SIPGLaplace<dim>::solve()
   {
     SparseDirectUMFPACK A_direct;
     A_direct.initialize(system_matrix);
     A_direct.vmult(solution, system_rhs);
   }
* 
 
* 
   template <int dim>
   void SIPGLaplace<dim>::output_results(const unsigned int cycle) const
   {
     const std::string filename = "sol_Q" + Utilities::int_to_string(degree, 1) +
                                  "-" + Utilities::int_to_string(cycle, 2) +
                                  ".vtu";
     std::ofstream output(filename);
* 
     DataOut<dim> data_out;
     data_out.attach_dof_handler(dof_handler);
     data_out.add_data_vector(solution, "u", DataOut<dim>::type_dof_data);
     data_out.build_patches(mapping);
     data_out.write_vtu(output);
   }
* 
 
 @endcode
*
* <a name="Thecompute_error_estimatefunction"></a> <h3>The compute_error_estimate() function</h3> 这里的误差估计器的装配与全局矩阵和右前侧的装配很相似，可以由 MeshWorker::mesh_loop() 框架处理。为了理解每个局部（lambda）函数的作用，首先回顾一下，局部单元残差的定义为  $h_K^2 \left\| f + \nu \Delta u_h \right\|_K^2$  。
*


* @code
   template <int dim>
   void SIPGLaplace<dim>::compute_error_estimate()
   {
     const auto cell_worker =
       [&](const auto &cell, auto &scratch_data, auto &copy_data) {
         const FEValues<dim> &fe_v = scratch_data.reinit(cell);
* 
         copy_data.cell_index = cell->active_cell_index();
* 
         const auto &               q_points   = fe_v.get_quadrature_points();
         const unsigned int         n_q_points = q_points.size();
         const std::vector<double> &JxW        = fe_v.get_JxW_values();
* 
         std::vector<Tensor<2, dim>> hessians(n_q_points);
         fe_v.get_function_hessians(solution, hessians);
* 
         std::vector<double> rhs(n_q_points);
         rhs_function->value_list(q_points, rhs);
* 
         const double hk                   = cell->diameter();
         double       residual_norm_square = 0;
* 
         for (unsigned int point = 0; point < n_q_points; ++point)
           {
             const double residual =
               rhs[point] + diffusion_coefficient trace(hessians[point]);
             residual_norm_square += residual residual JxW[point];
           }
         copy_data.value = hk hk residual_norm_square;
       };
* 
 @endcode
*
* 接下来计算边界项  $\sum_{f\in \partial K \cap \partial \Omega}
 \sigma \left\| [  u_h-g_D ]  \right\|_f^2  $  。
*


* @code
     const auto boundary_worker = [&](const auto &        cell,
                                      const unsigned int &face_no,
                                      auto &              scratch_data,
                                      auto &              copy_data) {
       const FEFaceValuesBase<dim> &fe_fv = scratch_data.reinit(cell, face_no);
* 
       const auto &   q_points   = fe_fv.get_quadrature_points();
       const unsigned n_q_points = q_points.size();
* 
       const std::vector<double> &JxW = fe_fv.get_JxW_values();
* 
       std::vector<double> g(n_q_points);
       exact_solution->value_list(q_points, g);
* 
       std::vector<double> sol_u(n_q_points);
       fe_fv.get_function_values(solution, sol_u);
* 
       const double extent1 = cell->measure() / cell->face(face_no)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent1);
* 
       double difference_norm_square = 0.;
       for (unsigned int point = 0; point < q_points.size(); ++point)
         {
           const double diff = (g[point]
* 
- sol_u[point]);
           difference_norm_square += diff diff JxW[point];
         }
       copy_data.value += penalty difference_norm_square;
     };
* 
 @endcode

* 最后是内部面孔条款 $\sum_{f\in \partial K}\lbrace \sigma
 \left\| [u_h]  \right\|_f^2   +  h_f \left\|  [\nu \nabla u_h \cdot
 \mathbf n ] \right\|_f^2 \rbrace$  。
*


* @code
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
* 
       copy_data.face_data.emplace_back();
       CopyDataFace &copy_data_face = copy_data.face_data.back();
* 
       copy_data_face.cell_indices[0] = cell->active_cell_index();
       copy_data_face.cell_indices[1] = ncell->active_cell_index();
* 
       const std::vector<double> &        JxW     = fe_iv.get_JxW_values();
       const std::vector<Tensor<1, dim>> &normals = fe_iv.get_normal_vectors();
* 
       const auto &       q_points   = fe_iv.get_quadrature_points();
       const unsigned int n_q_points = q_points.size();
* 
       std::vector<double> jump(n_q_points);
       get_function_jump(fe_iv, solution, jump);
* 
       std::vector<Tensor<1, dim>> grad_jump(n_q_points);
       get_function_gradient_jump(fe_iv, solution, grad_jump);
* 
       const double h = cell->face(f)->diameter();
* 
       const double extent1 = cell->measure() / cell->face(f)->measure();
       const double extent2 = ncell->measure() / ncell->face(nf)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent2);
* 
       double flux_jump_square = 0;
       double u_jump_square    = 0;
       for (unsigned int point = 0; point < n_q_points; ++point)
         {
           u_jump_square += jump[point] jump[point] JxW[point];
           const double flux_jump = grad_jump[point] normals[point];
           flux_jump_square +=
             diffusion_coefficient flux_jump flux_jump JxW[point];
         }
       copy_data_face.values[0] =
         0.5 h (flux_jump_square + penalty u_jump_square);
       copy_data_face.values[1] = copy_data_face.values[0];
     };
* 
 @endcode
*
* 在计算了每个单元的局部贡献后，我们仍然需要一种方法将这些贡献复制到全局向量中，该向量将容纳所有单元的误差估计值。
*


* @code
     const auto copier = [&](const auto &copy_data) {
       if (copy_data.cell_index != numbers::invalid_unsigned_int)
         estimated_error_square_per_cell[copy_data.cell_index] +=
           copy_data.value;
       for (auto &cdf : copy_data.face_data)
         for (unsigned int j = 0; j < 2; ++j)
           estimated_error_square_per_cell[cdf.cell_indices[j]] += cdf.values[j];
     };
* 
 @endcode
*
* 在所有这些设置之后，让我们来做实际的工作。我们调整向量的大小，将结果写入其中，然后用 MeshWorker::mesh_loop() 函数驱动整个过程。
*


* @code
     estimated_error_square_per_cell.reinit(triangulation.n_active_cells());
* 
     const UpdateFlags cell_flags =
       update_hessians | update_quadrature_points | update_JxW_values;
     const UpdateFlags face_flags = update_values | update_gradients |
                                    update_quadrature_points |
                                    update_JxW_values | update_normal_vectors;
* 
     ScratchData scratch_data(
       mapping, fe, quadrature, cell_flags, face_quadrature, face_flags);
* 
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
* 
 @endcode
*
* <a name="Thecompute_energy_norm_errorfunction"></a> <h3>The compute_energy_norm_error() function</h3> 接下来，我们用能量准则来评估准确性。这个功能类似于上面的误差估计器的集合。这里我们计算由@f[
 \|u \|_{1,h}^2 = \sum_{K \in \Gamma_h} \nu\|\nabla u \|_K^2 +
 \sum_{f \in F_i} \sigma \| [ u ] \|_f^2 +
 \sum_{f \in F_b} \sigma  \|u\|_f^2.
 @f]定义的能量准则的平方 因此，相应的误差是@f[
 \|u
* 
-u_h \|_{1,h}^2 = \sum_{K \in \Gamma_h} \nu\|\nabla (u_h
* 
- u)  \|_K^2
 + \sum_{f \in F_i} \sigma  \|[ u_h ] \|_f^2 + \sum_{f \in F_b}\sigma
 \|u_h-g_D\|_f^2.
 @f]
*


* @code
   template <int dim>
   double SIPGLaplace<dim>::compute_energy_norm_error()
   {
     energy_norm_square_per_cell.reinit(triangulation.n_active_cells());
* 
 @endcode
*
* 组装  $\sum_{K \in \Gamma_h} \nu\|\nabla (u_h
* 
- u)  \|_K^2 $  。
*


* @code
     const auto cell_worker =
       [&](const auto &cell, auto &scratch_data, auto &copy_data) {
         const FEValues<dim> &fe_v = scratch_data.reinit(cell);
* 
         copy_data.cell_index = cell->active_cell_index();
* 
         const auto &               q_points   = fe_v.get_quadrature_points();
         const unsigned int         n_q_points = q_points.size();
         const std::vector<double> &JxW        = fe_v.get_JxW_values();
* 
         std::vector<Tensor<1, dim>> grad_u(n_q_points);
         fe_v.get_function_gradients(solution, grad_u);
* 
         std::vector<Tensor<1, dim>> grad_exact(n_q_points);
         exact_solution->gradient_list(q_points, grad_exact);
* 
         double norm_square = 0;
         for (unsigned int point = 0; point < n_q_points; ++point)
           {
             norm_square +=
               (grad_u[point]
* 
- grad_exact[point]).norm_square() JxW[point];
           }
         copy_data.value = diffusion_coefficient norm_square;
       };
* 
 @endcode
*
* 组装  $\sum_{f \in F_b}\sigma  \|u_h-g_D\|_f^2$  。
*


* @code
     const auto boundary_worker = [&](const auto &        cell,
                                      const unsigned int &face_no,
                                      auto &              scratch_data,
                                      auto &              copy_data) {
       const FEFaceValuesBase<dim> &fe_fv = scratch_data.reinit(cell, face_no);
* 
       const auto &   q_points   = fe_fv.get_quadrature_points();
       const unsigned n_q_points = q_points.size();
* 
       const std::vector<double> &JxW = fe_fv.get_JxW_values();
* 
       std::vector<double> g(n_q_points);
       exact_solution->value_list(q_points, g);
* 
       std::vector<double> sol_u(n_q_points);
       fe_fv.get_function_values(solution, sol_u);
* 
       const double extent1 = cell->measure() / cell->face(face_no)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent1);
* 
       double difference_norm_square = 0.;
       for (unsigned int point = 0; point < q_points.size(); ++point)
         {
           const double diff = (g[point]
* 
- sol_u[point]);
           difference_norm_square += diff diff JxW[point];
         }
       copy_data.value += penalty difference_norm_square;
     };
* 
 @endcode
*
* 组装  $\sum_{f \in F_i} \sigma  \| [ u_h ] \|_f^2$  。
*


* @code
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
* 
       copy_data.face_data.emplace_back();
       CopyDataFace &copy_data_face = copy_data.face_data.back();
* 
       copy_data_face.cell_indices[0] = cell->active_cell_index();
       copy_data_face.cell_indices[1] = ncell->active_cell_index();
* 
       const std::vector<double> &JxW = fe_iv.get_JxW_values();
* 
       const auto &       q_points   = fe_iv.get_quadrature_points();
       const unsigned int n_q_points = q_points.size();
* 
       std::vector<double> jump(n_q_points);
       get_function_jump(fe_iv, solution, jump);
* 
       const double extent1 = cell->measure() / cell->face(f)->measure();
       const double extent2 = ncell->measure() / ncell->face(nf)->measure();
       const double penalty = get_penalty_factor(degree, extent1, extent2);
* 
       double u_jump_square = 0;
       for (unsigned int point = 0; point < n_q_points; ++point)
         {
           u_jump_square += jump[point] jump[point] JxW[point];
         }
       copy_data_face.values[0] = 0.5 penalty u_jump_square;
       copy_data_face.values[1] = copy_data_face.values[0];
     };
* 
     const auto copier = [&](const auto &copy_data) {
       if (copy_data.cell_index != numbers::invalid_unsigned_int)
         energy_norm_square_per_cell[copy_data.cell_index] += copy_data.value;
       for (auto &cdf : copy_data.face_data)
         for (unsigned int j = 0; j < 2; ++j)
           energy_norm_square_per_cell[cdf.cell_indices[j]] += cdf.values[j];
     };
* 
     const UpdateFlags cell_flags =
       update_gradients | update_quadrature_points | update_JxW_values;
     UpdateFlags face_flags =
       update_values | update_quadrature_points | update_JxW_values;
* 
     const ScratchData scratch_data(mapping,
                                    fe,
                                    quadrature_overintegration,
                                    cell_flags,
                                    face_quadrature_overintegration,
                                    face_flags);
* 
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
* 
 
* 
 @endcode
*
* <a name="Therefine_gridfunction"></a> <h3>The refine_grid() function</h3>。



* @code
   template <int dim>
   void SIPGLaplace<dim>::refine_grid()
   {
     const double refinement_fraction = 0.1;
* 
     GridRefinement::refine_and_coarsen_fixed_number(
       triangulation, estimated_error_square_per_cell, refinement_fraction, 0.);
* 
     triangulation.execute_coarsening_and_refinement();
   }
* 
 
* 
 @endcode
*
* <a name="Thecompute_errorsfunction"></a> <h3>The compute_errors() function</h3> 我们分别计算 $L_2$ 规范、 $H_1$ 半规范和能量规范中的三个误差。这些误差将被打印到屏幕上，同时也被存储在一个表格中，该表格记录了这些误差是如何随着网格细化而衰减的，并且可以在程序的最后一步输出。
*


* @code
   template <int dim>
   void SIPGLaplace<dim>::compute_errors()
   {
     double L2_error, H1_error, energy_error;
* 
     {
       Vector<float> difference_per_cell(triangulation.n_active_cells());
       VectorTools::integrate_difference(mapping,
                                         dof_handler,
                                         solution,
                                        (exact_solution.get()),
                                         difference_per_cell,
                                         quadrature_overintegration,
                                         VectorTools::L2_norm);
* 
       L2_error = VectorTools::compute_global_error(triangulation,
                                                    difference_per_cell,
                                                    VectorTools::L2_norm);
       convergence_table.add_value("L2", L2_error);
     }
* 
     {
       Vector<float> difference_per_cell(triangulation.n_active_cells());
       VectorTools::integrate_difference(mapping,
                                         dof_handler,
                                         solution,
                                        (exact_solution.get()),
                                         difference_per_cell,
                                         quadrature_overintegration,
                                         VectorTools::H1_seminorm);
* 
       H1_error = VectorTools::compute_global_error(triangulation,
                                                    difference_per_cell,
                                                    VectorTools::H1_seminorm);
       convergence_table.add_value("H1", H1_error);
     }
* 
     {
       energy_error = compute_energy_norm_error();
       convergence_table.add_value("Energy", energy_error);
     }
* 
     std::cout << "  Error in the L2 norm         : " << L2_error << std::endl
               << "  Error in the H1 seminorm     : " << H1_error << std::endl
               << "  Error in the energy norm     : " << energy_error
               << std::endl;
   }
* 
 
* 
 @endcode
*
* <a name="Therunfunction"></a> <h3>The run() function</h3>。



* @code
   template <int dim>
   void SIPGLaplace<dim>::run()
   {
     const unsigned int max_cycle =
       (test_case == TestCase::convergence_rate ? 6 : 20);
     for (unsigned int cycle = 0; cycle < max_cycle; ++cycle)
       {
         std::cout << "Cycle " << cycle << std::endl;
* 
         switch (test_case)
           {
             case TestCase::convergence_rate:
               {
                 if (cycle == 0)
                   {
                     GridGenerator::hyper_cube(triangulation);
* 
                     triangulation.refine_global(2);
                   }
                 else
                   {
                     triangulation.refine_global(1);
                   }
                 break;
               }
* 
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
* 
             default:
               {
                 Assert(false, ExcNotImplemented());
               }
           }
* 
         std::cout << "  Number of active cells       : "
                   << triangulation.n_active_cells() << std::endl;
         setup_system();
* 
         std::cout << "  Number of degrees of freedom : " << dof_handler.n_dofs()
                   << std::endl;
* 
         assemble_system();
         solve();
         output_results(cycle);
         {
           convergence_table.add_value("cycle", cycle);
           convergence_table.add_value("cells", triangulation.n_active_cells());
           convergence_table.add_value("dofs", dof_handler.n_dofs());
         }
         compute_errors();
* 
         if (test_case == TestCase::l_singularity)
           {
             compute_error_estimate();
             std::cout << "  Estimated error              : "
                       << std::sqrt(estimated_error_square_per_cell.l1_norm())
                       << std::endl;
* 
             convergence_table.add_value(
               "Estimator",
               std::sqrt(estimated_error_square_per_cell.l1_norm()));
           }
         std::cout << std::endl;
       }
* 
 @endcode
*
* 在运行了我们所有的计算之后，让我们告诉收敛表如何格式化它的数据并将其输出到屏幕。
*


* @code
     convergence_table.set_precision("L2", 3);
     convergence_table.set_precision("H1", 3);
     convergence_table.set_precision("Energy", 3);
* 
     convergence_table.set_scientific("L2", true);
     convergence_table.set_scientific("H1", true);
     convergence_table.set_scientific("Energy", true);
* 
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
* 
     std::cout << "degree = " << degree << std::endl;
     convergence_table.write_text(
       std::cout, TableHandler::TextOutputFormat::org_mode_table);
   }
 } // namespace Step74
* 
 
* 
 @endcode
*
* <a name="Themainfunction"></a> <h3>The main() function</h3> 下面的 <code>main</code> 函数与前面的例子也类似，不需要注释。
*


* @code
 int main()
 {
   try
     {
       using namespace dealii;
       using namespace Step74;
* 
       const TestCase test_case = TestCase::l_singularity;
* 
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
* 
   return 0;
 }
 @endcode
* <a name="Results"></a><h1>Results</h1> 。


* 这个程序的输出包括控制台输出和vtu格式的解决方案。
* 在第一个测试案例中，当你运行该程序时，屏幕输出应该是以下样子。
* @code
Cycle 0
  Number of active cells       : 16
  Number of degrees of freedom : 256
  Error in the L2 norm         : 0.00193285
  Error in the H1 seminorm     : 0.106087
  Error in the energy norm     : 0.150625
* 
Cycle 1
  Number of active cells       : 64
  Number of degrees of freedom : 1024
  Error in the L2 norm         : 9.60497e-05
  Error in the H1 seminorm     : 0.0089954
  Error in the energy norm     : 0.0113265
* 
Cycle 2
.
.
.
@endcode
*
* 当使用多项式度数为3的光滑情况时，收敛表将看起来像这样。 <table align="center" class="doxtable">
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
* 理论上，对于多项式度数 $p$ ，在 $L_2$ 规范和 $H^1$ 半规范中的收敛顺序应该是 $p+1$ 和 $p$ ，分别。我们的数值结果与理论有很好的一致性。
* 在第二个测试案例中，当你运行程序时，屏幕输出应该是以下样子。
* @code
Cycle 0
  Number of active cells       : 192
  Number of degrees of freedom : 3072
  Error in the L2 norm         : 0.000323585
  Error in the H1 seminorm     : 0.0296202
  Error in the energy norm     : 0.0420478
  Estimated error              : 0.136067
* 
Cycle 1
  Number of active cells       : 249
  Number of degrees of freedom : 3984
  Error in the L2 norm         : 0.000114739
  Error in the H1 seminorm     : 0.0186571
  Error in the energy norm     : 0.0264879
  Estimated error              : 0.0857186
* 
Cycle 2
.
.
.
@endcode
*
* 下图提供了一个L型域上这个测试案例的误差与自由度数的对数图。为了解释它，让 $n$ 为自由度数，那么在均匀细化的网格上， $h$ 是二维的 $1/\sqrt{n}$ 阶。结合前面的理论结果，我们可以看到，如果解足够光滑，我们可以预期 $L_2$ 准则的误差为 $O(n^{-\frac{p+1}{2}})$ 阶， $H^1$ 半准则的误差为 $O(n^{-\frac{p}{2}})$ 。在自适应细化的网格上，如我们在第二个测试案例中使用的网格，会不会得到与 $n$ 函数相同的行为，这不是一个先验的说法，但人们当然可以希望。事实上，从图中我们可以看出，带有自适应网格细化的SIPG产生了渐进式的那种希望的结果。
*  <img width="600px" src="https://www.dealii.org/images/steps/developer/step-74.log-log-plot.png" alt=""> 
* 此外，我们观察到误差估计值的下降速度几乎与能量准则和 $H^1$ 半准则的误差相同，并且比 $L_2$ 的误差低一阶。这表明它有能力预测具有较大误差的区域。
* 虽然本教程侧重于实现，但 step-59 教程程序以无矩阵求解技术在计算时间上实现了一个高效的大规模求解器。注意， step-59 教程目前不能与含有悬空节点的网格一起工作，因为多网格界面矩阵不那么容易确定，但这只是deal.II中缺少一些界面，没有什么根本原因。
*

* <a name="PlainProg"></a><h1> The plain program</h1> @include "step-74.cc" 
* */


