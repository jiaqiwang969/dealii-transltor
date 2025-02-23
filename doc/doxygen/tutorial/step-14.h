//include/deal.II-translator/A-tutorial/step-14_0.txt
/**
  @page step_14 The step-14 tutorial program 
* 本教程依赖于  step-13  。
* @htmlonly
<table class="tutorial" width="50%">
<tr><th colspan="2"><b><small>Table of contents</small></b><b><small>Table of contents</small></b></th></tr>
<tr><td width="50%" valign="top">
<ol>
  <li> <a href="#Intro" class=bold>Introduction</a><a href="#Intro" class=bold>Introduction</a>
    <ul>
        <li><a href="#Themaths">The maths</a><a href="#Themaths">The maths</a>
        <li><a href="#Thesoftware">The software</a><a href="#Thesoftware">The software</a>
    </ul>
  <li> <a href="#CommProg" class=bold>The commented program</a><a href="#CommProg" class=bold>The commented program</a>
    <ul>
        <li><a href="#Evaluatingthesolution">Evaluating the solution</a><a href="#Evaluatingthesolution">Evaluating the solution</a>
      <ul>
        <li><a href="#TheEvaluationBaseclass">The EvaluationBase class</a><a href="#TheEvaluationBaseclass">The EvaluationBase class</a>
        <li><a href="#ThePointValueEvaluationclass">The PointValueEvaluation class</a><a href="#ThePointValueEvaluationclass">The PointValueEvaluation class</a>
        <li><a href="#ThePointXDerivativeEvaluationclass">The PointXDerivativeEvaluation class</a><a href="#ThePointXDerivativeEvaluationclass">The PointXDerivativeEvaluation class</a>
        <li><a href="#TheGridOutputclass">The GridOutput class</a><a href="#TheGridOutputclass">The GridOutput class</a>
      </ul>
        <li><a href="#TheLaplacesolverclasses">The Laplace solver classes</a><a href="#TheLaplacesolverclasses">The Laplace solver classes</a>
      <ul>
        <li><a href="#TheLaplacesolverbaseclass">The Laplace solver base class</a><a href="#TheLaplacesolverbaseclass">The Laplace solver base class</a>
        <li><a href="#TheLaplaceSolverclass">The Laplace Solver class</a><a href="#TheLaplaceSolverclass">The Laplace Solver class</a>
        <li><a href="#ThePrimalSolverclass">The PrimalSolver class</a><a href="#ThePrimalSolverclass">The PrimalSolver class</a>
        <li><a href="#TheRefinementGlobalandRefinementKellyclasses">The RefinementGlobal and RefinementKelly classes</a><a href="#TheRefinementGlobalandRefinementKellyclasses">The RefinementGlobal and RefinementKelly classes</a>
        <li><a href="#TheRefinementWeightedKellyclass">The RefinementWeightedKelly class</a><a href="#TheRefinementWeightedKellyclass">The RefinementWeightedKelly class</a>
      </ul>
        <li><a href="#Equationdata">Equation data</a><a href="#Equationdata">Equation data</a>
      <ul>
        <li><a href="#TheSetUpBaseandSetUpclasses">The SetUpBase and SetUp classes</a><a href="#TheSetUpBaseandSetUpclasses">The SetUpBase and SetUp classes</a>
        <li><a href="#TheCurvedRidgesclass">The CurvedRidges class</a><a href="#TheCurvedRidgesclass">The CurvedRidges class</a>
        <li><a href="#TheExercise_2_3class">The Exercise_2_3 class</a><a href="#TheExercise_2_3class">The Exercise_2_3 class</a>
        <li><a href="#Discussion">Discussion</a><a href="#Discussion">Discussion</a>
      </ul>
        <li><a href="#Dualfunctionals">Dual functionals</a><a href="#Dualfunctionals">Dual functionals</a>
      <ul>
        <li><a href="#TheDualFunctionalBaseclass">The DualFunctionalBase class</a><a href="#TheDualFunctionalBaseclass">The DualFunctionalBase class</a>
        <li><a href="#ThedualfunctionalPointValueEvaluationclass">The dual functional PointValueEvaluation class</a><a href="#ThedualfunctionalPointValueEvaluationclass">The dual functional PointValueEvaluation class</a>
        <li><a href="#ThedualfunctionalPointXDerivativeEvaluationclass">The dual functional PointXDerivativeEvaluation class</a><a href="#ThedualfunctionalPointXDerivativeEvaluationclass">The dual functional PointXDerivativeEvaluation class</a>
      </ul>
        <li><a href="#ExtendingtheLaplaceSolvernamespace">Extending the LaplaceSolver namespace</a><a href="#ExtendingtheLaplaceSolvernamespace">Extending the LaplaceSolver namespace</a>
      <ul>
        <li><a href="#TheDualSolverclass">The DualSolver class</a><a href="#TheDualSolverclass">The DualSolver class</a>
        <li><a href="#TheWeightedResidualclass">The WeightedResidual class</a><a href="#TheWeightedResidualclass">The WeightedResidual class</a>
      </ul>
        <li><a href="#Estimatingerrors">Estimating errors</a><a href="#Estimatingerrors">Estimating errors</a>
      <ul>
        <li><a href="#Errorestimationdriverfunctions">Error estimation driver functions</a><a href="#Errorestimationdriverfunctions">Error estimation driver functions</a>
        <li><a href="#Estimatingonasinglecell">Estimating on a single cell</a><a href="#Estimatingonasinglecell">Estimating on a single cell</a>
        <li><a href="#Computingcelltermerrorcontributions">Computing cell term error contributions</a><a href="#Computingcelltermerrorcontributions">Computing cell term error contributions</a>
        <li><a href="#Computingedgetermerrorcontributions1">Computing edge term error contributions &mdash; 1</a><a href="#Computingedgetermerrorcontributions1">Computing edge term error contributions &mdash; 1</a>
        <li><a href="#Computingedgetermerrorcontributions2">Computing edge term error contributions &mdash; 2</a><a href="#Computingedgetermerrorcontributions2">Computing edge term error contributions &mdash; 2</a>
      </ul>
        <li><a href="#Asimulationframework">A simulation framework</a><a href="#Asimulationframework">A simulation framework</a>
        <li><a href="#Themainfunction">The main function</a><a href="#Themainfunction">The main function</a>
      </ul>
</ol></td><td width="50%" valign="top"><ol>
  <li value="3"> <a href="#Results" class=bold>Results</a><a href="#Results" class=bold>Results</a>
    <ul>
        <li><a href="#Pointvalues">Point values</a><a href="#Pointvalues">Point values</a>
        <li><a href="#Comparingrefinementcriteria">Comparing refinement criteria</a><a href="#Comparingrefinementcriteria">Comparing refinement criteria</a>
        <li><a href="#Evaluationofpointstresses">Evaluation of point stresses</a><a href="#Evaluationofpointstresses">Evaluation of point stresses</a>
        <li><a href="#step13revisited">step-13 revisited</a><a href="#step13revisited">step-13 revisited</a>
        <li><a href="#Conclusionsandoutlook">Conclusions and outlook</a><a href="#Conclusionsandoutlook">Conclusions and outlook</a>
    </ul>
  <li> <a href="#PlainProg" class=bold>The plain program</a><a href="#PlainProg" class=bold>The plain program</a>
</ol> </td> </tr> </table>
@endhtmlonly
*<a name="Intro"></a><a name="Introduction"></a><h1>Introduction</h1> 。


*<a name="Themaths"></a><h3>The maths</h3> 。


* Rolf Rannacher教授的海德堡小组，deal.II库的三位初始作者在他们的博士期间属于该小组，后来也有部分人属于该小组，自1990年代中期以来一直从事有限元离散的适应性和误差估计工作。主要成就是开发了任意函数解的误差估计，以及用于其计算的最佳网格细化。
* 我们将不详细讨论这些概念的推导，而是在本例程序中实现其主要思想。对于一般概念的彻底介绍，我们可以参考Becker和Rannacher的开创性工作 @cite BR95 、 @cite BR96r ，以及Acta Numerica @cite BR01 中同一作者的概述文章；前者介绍了拉普拉斯方程一般函数输出的误差估计和适应性的概念，后者则给出了这些概念在大量其他更复杂方程中应用的许多例子。关于个别类型方程的应用，也可参见贝克尔 @cite Bec95 、 @cite Bec98 、坎沙特 @cite Kan96 、 @cite FK97 、苏特梅尔 @cite Sut96 的出版物。] ,  @cite RS97  ,  @cite RS98c  ,  @cite RS99  , Bangerth  @cite BR99b  ,  @cite Ban00w  ,  @cite BR01a  ,  @cite Ban02  , 和 Hartmann  @cite Har02  ,  @cite HH01  ,  @cite HH01b  。所有这些工作，从Becker和Rannacher的原始介绍到对特定方程的个别贡献，后来都在Bangerth和Rannacher的书中进行了总结，其中包括所有这些主题，见 @cite BR03 。
*

* 其基本思想如下：在应用中，人们通常对解本身不感兴趣，而是对它的某些方面感兴趣。例如，在模拟流动问题时，人们可能想知道浸在流体中的物体的升力或阻力；我们想知道的是这个数量的最佳精度，而描述方程的其余解是否得到很好的解决并不是主要的兴趣。同样，在弹性方面，人们可能想知道某些点的应力值，以猜测关节的最大负荷值是否安全，比如说。或者，在辐射转移问题中，平均通量强度是有意义的。
* 在刚才列举的所有情况中，我们感兴趣的是解的函数 $J(u)$ 的评估，而不是各地的 $u$ 的值。由于精确的解决方案 $u$ 是不可用的，只有它的数字近似值 $u_h$ ，所以问计算值 $J(u_h)$ 是否在精确值 $J(u)$ 的一定范围内是明智的，也就是说，我们希望约束与这个函数有关的误差， $J(u)-J(u_h)$ 。
* 为了简化论述，我们假设感兴趣的量 $J$ 以及方程都是线性的，我们将特别展示具有同质狄里奇边界条件的拉普拉斯方程的推导，尽管这一概念更为普遍。对于这种一般情况，我们参考上面列出的参考文献。  我们的目标是获得误差的界限， $J(e)=J(u)-J(u_h)$  。为此，让我们用 $z$ 表示对偶问题的解，定义如下：@f[
  a(\varphi,z) = J(\varphi) \qquad \forall \varphi,
@f]其中 $a(\cdot,\cdot)$ 是与微分方程相关的双线性形式，测试函数从相应的解空间中选择。然后，作为特殊的检验函数 $\varphi=e$ 的误差，我们有@f[
  J(e) = a(e,z)
@f]，通过Galerkin正交性，我们可以将其改写为@f[
  J(e) = a(e,z-\varphi_h)
@f]，其中 $\varphi_h$ 可以以我们认为方便的方式从离散检验空间选择。
* 具体来说，对于拉普拉斯方程，误差标识为@f[
  J(e) = (\nabla e, \nabla(z-\varphi_h)).
@f]，因为我们不仅要用这个公式来计算误差，还要细化网格，所以我们需要将上面的表达式改写为单元的总和，然后每个单元的贡献可以作为这个单元的误差指标。因此，我们将标量积分成每个单元的条款，并对每个条款进行分项积分：@f{eqnarray*}
  J(e)
  &=&
  \sum_K (\nabla (u-u_h), \nabla (z-\varphi_h))_K
  \\
  &=&
  \sum_K (-\Delta (u-u_h), z-\varphi_h)_K
  + (\partial_n (u-u_h), z-z_h)_{\partial K}.
@f} 。
* 接下来，我们利用 $-\Delta u=f$ ，对于拉普拉斯方程的解，其解足够平滑， $\partial_n u$ 几乎到处都是连续的。
*
* 因此，在单元格上涉及 $\partial_n u$ 的条款与相邻单元格上的条款相抵消，其中法向量具有相反的符号。(不过 $\partial_n u_h$ 的情况并非如此。)在域的边界，没有邻接单元可以抵消这个项，权重 $z-\varphi_h$ 可以选择为零，整个项就消失了。
* 因此，我们有@f{eqnarray*}
  J(e)
  &=&
  \sum_K (f+\Delta u_h, z-\varphi_h)_K
* 


* 
* 


* 
* 
- (\partial_n u_h, z-\varphi_h)_{\partial K\backslash \partial\Omega}.
@f}。
* 在最后一步，注意当取 $u_h$ 的法向导数时，我们是指从单元格的这一边取的这个量的值（对于通常的拉格朗日元素，导数在边上是不连续的）。然后我们通过将 $K$ 单元的一半边缘积分与相邻单元 $K'$ 交换来重写上述公式，得到@f{eqnarray*}
  J(e)
  &=&
  \sum_K (f+\Delta u_h, z-\varphi_h)_K
* 


* 
* 


* 
* 
- \frac 12 (\partial_n u_h|_K + \partial_{n'} u_h|_{K'},
              z-\varphi_h)_{\partial K\backslash \partial\Omega}.
@f} 。
* 对于相邻单元的法向量，我们有 $n'=-n$ ，我们通过@f[
  [\partial_n u_h] \dealcoloneq \partial_n u_h|_K + \partial_{n'} u_h|_{K'}
  =
  \partial_n u_h|_K
* 
- \partial_n u_h|_{K'},
@f]定义法向导数的跳跃，并在将离散函数 $\varphi_h$ （现在仍然是任意的）设定为对偶解的点插值后得到最终形式， $\varphi_h=I_h z$  ：@f{eqnarray*}
  J(e)
  &=&
  \sum_K (f+\Delta u_h, z-I_h z)_K
* 


* 
* 


* 
* 
- \frac 12 ([\partial_n u_h],
              z-I_h z)_{\partial K\backslash \partial\Omega}.
@f} 。
*
* 这样，我们就得到了关于任意（线性）函数的有限元离散化误差的精确表示  $J(\cdot)$  。它的结构是一个加权形式的残差估计，因为 $f+\Delta u_h$ 和 $[\partial_n u_h]$ 都是在精确解上消失的单元和边缘残差，而 $z-I_h z$ 是表示某个单元上的残差对给定函数的评估有多重要的权重。此外，它是一个单元的量，所以我们可以把它作为一个网格细化的标准。问题是：如何评价它？毕竟，评估需要了解对偶解 $z$ ，它带有我们想知道的最准确的量的信息。
* 在一些非常特殊的情况下，这个对偶解是已知的。例如，如果函数 $J(\cdot)$ 是点评价， $J(\varphi)=\varphi(x_0)$ ，那么对偶解必须满足@f[
* 


* 
* 


* 
* 
-\Delta z = \delta(x-x_0),
@f]，右边是狄拉克三角函数，而对偶解是关于点 $x_0$ 的格林函数。对于简单的几何形状，这个函数是分析上已知的，我们可以把它插入到误差表示公式中。
* 然而，我们不想把自己限制在这种特殊情况下。相反，我们将以数值方式计算对偶解，并以某种数值方式获得的 $\tilde z$ 近似 $z$ 。我们注意到，使用与初解 $u_h$ 相同的方法来计算这个近似值 $\tilde z$ 是不够的，因为这样 $\tilde z-I_h \tilde z=0$ 和整体误差估计将是零。相反，近似值 $\tilde z$ 必须来自比原始有限元空间更大的空间。有多种方法可以获得这样的近似值（见所引用的文献），我们将选择用高阶有限元空间来计算它。虽然这当然不是最有效的方法，但它很简单，因为我们已经有了所有需要做的事情，而且它还允许进行简单的实验。对于更有效的方法，请再次参考给定的文献，特别是  @cite BR95  ,  @cite BR03  。
* 至此，我们结束了对这个程序的数学方面的讨论，转而讨论实际的实现。
*


*  @note  如果你只关心计算误差的话，上面有两个步骤似乎没有必要：即(i)从 $z$ 中减去 $\phi_h$ ，以及(ii)将积分拆成单元格之和并对每个单元格进行积分。事实上，这两个步骤根本没有改变 $J(e)$ ，因为在用 $\tilde z$ 代替 $z$ 之前，我们只考虑上述的相同点。换句话说，如果你只关心<i>estimating the global error</i> $J(e)$ ，那么这些步骤是没有必要的。另一方面，如果你想将误差估计作为网格中每个单元的细化标准，那么就有必要(i)将估计值分解为单元的总和，(ii)以这样的方式按摩公式，使每个单元的贡献都与局部误差有关。(虽然上面的公式没有改变<i>sum</i> $J(e)$ 的值，但它们改变了我们为每个单元 $K$ 计算的值)。为此，我们希望以 "残差乘以双重权重 "的形式来写一切，其中 "残差 "是指随着近似度变得 $u_h$ 越来越好而归于零的东西。例如， $\partial_n
u_h$ 这个量不是残差，因为它只是收敛于精确解的梯度（法向分量）。另一方面， $[\partial_n u_h]$ 是一个残差，因为它收敛于 $[\partial_n
u]=0$  。我们在开发 $J(e)$ 的最终形式时采取的所有步骤，实际上都是为了将最终形式变成一种形式，在离散解 $u_h$ 收敛到 $u$ 时，每个项都收敛为零。这样就可以把每个单元的贡献看作是一个 "误差指标"，也会收敛为零。
*
* - 因为它应该随着网格的细化而细化。
*


*<a name="Thesoftware"></a><h3>The software</h3>


*  step-14 示例程序在很大程度上建立在 step-13 程序中已经使用的技术之上。它对上面解释的双重加权残差估算器的实现是通过派生出第二个类，正确地称为 <code>DualSolver</code>, from the <code>Solver</code> 基类，并有一个类（ <code>WeightedResidual</code> ）将两者再次连接起来，控制原始和双重问题的解决，然后使用两者来计算网格细化的误差指示器。
* 该程序延续了前面例子中的模块化概念，通过一个抽象的基类来实现对偶函数，描述兴趣量，并提供两个不同的函数来实现这个接口。因此，增加一个不同的兴趣量是很简单的。
* 一个更根本的区别是对数据的处理。一个常见的情况是，你开发了一个解决某个方程的程序，然后用不同的右手边、不同的域、不同的系数和边界值等来测试它。通常，这些必须匹配，以便知道确切的解决方案，或者它们的组合是有意义的。
* 我们展示了一种可以通过简单而又非常灵活的方式来实现的方法。我们将把属于某个设置的所有东西放到一个类中，并围绕它提供一个小小的C++砂浆，这样整个设置（域、系数、右手边等）就可以通过改变 <em> 中的某个 </em> 地方来交换。
* 再往前走一点，我们还将所有描述程序如何工作的其他参数集中在一个地方，如有限元的顺序、最大自由度数、应在计算出的解上执行的评价对象，以及很快。这使得程序的配置更加简单，我们将在后面的程序中展示如何使用一个库类来处理通过读取输入文件来设置这些参数。总的来说，我们的目的是减少程序中想要改变某个参数时需要查找的地方，因为在实践中，人们会在程序成长的过程中忘记它们的位置。此外，把所有描述程序在某次运行中所做的事情的选项放到一个文件中（可以和结果一起存储），比在程序中的某个地方设置各种标志更有助于结果的重复性，因为在下次改变这个地方后，它们的确切数值就会被遗忘。
* 不幸的是，这个程序已经变得相当长了。虽然这无疑降低了它作为一个示例程序的作用，但我们认为它是开发其他类型问题程序的一个很好的起点，涉及到比这里处理的拉普拉斯方程不同的方程。此外，它显示了我们可以向你展示的关于我们的后验误差估计方法的一切，其结构应该使你能够简单地调整这种方法，以适应其他问题、其他函数、其他几何、系数等等。
* 作者认为，本程序是他在示例程序中的杰作，涉及到数学的复杂性，以及添加扩展的简单性。如果你使用这个程序作为你自己程序的基础，我们希望你能说明这一事实，并在由此产生的出版物中注明示例程序的作者Wolfgang Bangerth的名字，你的程序有相当一部分是由示例程序组成的。
*

* <a name="CommProg"></a> <h1> The commented program</h1>。
*从众所周知的事情开始......



* @code
 #include <deal.II/base/quadrature_lib.h>
 #include <deal.II/base/function.h>
 #include <deal.II/base/logstream.h>
 #include <deal.II/base/thread_management.h>
 #include <deal.II/base/work_stream.h>
 #include <deal.II/lac/vector.h>
 #include <deal.II/lac/full_matrix.h>
 #include <deal.II/lac/sparse_matrix.h>
 #include <deal.II/lac/dynamic_sparsity_pattern.h>
 #include <deal.II/lac/solver_cg.h>
 #include <deal.II/lac/precondition.h>
 #include <deal.II/lac/affine_constraints.h>
 #include <deal.II/grid/tria.h>
 #include <deal.II/grid/grid_generator.h>
 #include <deal.II/grid/grid_out.h>
 #include <deal.II/grid/grid_refinement.h>
 #include <deal.II/dofs/dof_handler.h>
 #include <deal.II/dofs/dof_tools.h>
 #include <deal.II/fe/fe_q.h>
 #include <deal.II/fe/fe_values.h>
 #include <deal.II/fe/fe_tools.h>
 #include <deal.II/numerics/vector_tools.h>
 #include <deal.II/numerics/matrix_tools.h>
 #include <deal.II/numerics/data_out.h>
 #include <deal.II/numerics/error_estimator.h>
* 
 #include <algorithm>
 #include <fstream>
 #include <iostream>
 #include <list>
 #include <memory>
 #include <numeric>
* 
 @endcode

* 最后一步和以前的所有程序一样。
*


* @code
 namespace Step14
 {
   using namespace dealii;
* 
 @endcode
*
* <a name="Evaluatingthesolution"></a> <h3>Evaluating the solution</h3>。


*
* 正如介绍中提到的，该程序的重要部分只是从 step-13 的例子程序中拿过来的。因此，我们只对那些新的东西进行评论。   
* 首先，评估解决方案的框架没有改变，也就是说，基类是相同的，评估网格点上的解决方案的类也没有改变。
*


* @code
   namespace Evaluation
   {
 @endcode
*
* <a name="TheEvaluationBaseclass"></a> <h4>The EvaluationBase class</h4>。



* @code
     template <int dim>
     class EvaluationBase
     {
     public:
       virtual ~EvaluationBase() = default;
* 
       void set_refinement_cycle(const unsigned int refinement_cycle);
* 
       virtual void operator()(const DoFHandler<dim> &dof_handler,
                               const Vector<double> & solution) const = 0;
* 
     protected:
       unsigned int refinement_cycle;
     };
* 
 
* 
     template <int dim>
     void EvaluationBase<dim>::set_refinement_cycle(const unsigned int step)
     {
       refinement_cycle = step;
     }
* 
 
 @endcode
*
* <a name="ThePointValueEvaluationclass"></a> <h4>The PointValueEvaluation class</h4>。



* @code
     template <int dim>
     class PointValueEvaluation : public EvaluationBase<dim>
     {
     public:
       PointValueEvaluation(const Point<dim> &evaluation_point);
* 
       virtual void operator()(const DoFHandler<dim> &dof_handler,
                               const Vector<double> & solution) const override;
* 
       DeclException1(
         ExcEvaluationPointNotFound,
         Point<dim>,
         << "The evaluation point " << arg1
         << " was not found among the vertices of the present grid.");
* 
     private:
       const Point<dim> evaluation_point;
     };
* 
 
     template <int dim>
     PointValueEvaluation<dim>::PointValueEvaluation(
       const Point<dim> &evaluation_point)
       : evaluation_point(evaluation_point)
     {}
* 
 
* 
     template <int dim>
     void PointValueEvaluation<dim>::
          operator()(const DoFHandler<dim> &dof_handler,
                const Vector<double> & solution) const
     {
       double point_value = 1e20;
* 
       bool evaluation_point_found = false;
       for (const auto &cell : dof_handler.active_cell_iterators())
         if (!evaluation_point_found)
           for (const auto vertex : cell->vertex_indices())
             if (cell->vertex(vertex).distance(evaluation_point) <
                 cell->diameter() 1e-8)
               {
                 point_value = solution(cell->vertex_dof_index(vertex, 0));
* 
                 evaluation_point_found = true;
                 break;
               }
* 
       AssertThrow(evaluation_point_found,
                   ExcEvaluationPointNotFound(evaluation_point));
* 
       std::cout << "   Point value=" << point_value << std::endl;
     }
* 
 
 @endcode
*
* <a name="ThePointXDerivativeEvaluationclass"></a> <h4>The PointXDerivativeEvaluation class</h4>。


*
* 除了实现在一个点上求解的类，我们在这里提供了一个在网格点上求梯度的类。由于一般来说，有限元函数的梯度在一个顶点上是不连续的，所以我们在这里要更小心一点。我们所做的是在所有单元中循环，即使我们已经在一个单元中找到了点，并使用所有相邻单元的顶点梯度的平均值。     
* 鉴于 <code>PointValueEvaluation</code> 类的接口，这个类的声明没有提供什么惊喜，构造函数也没有。
*


* @code
     template <int dim>
     class PointXDerivativeEvaluation : public EvaluationBase<dim>
     {
     public:
       PointXDerivativeEvaluation(const Point<dim> &evaluation_point);
* 
       virtual void operator()(const DoFHandler<dim> &dof_handler,
                               const Vector<double> & solution) const;
* 
       DeclException1(
         ExcEvaluationPointNotFound,
         Point<dim>,
         << "The evaluation point " << arg1
         << " was not found among the vertices of the present grid.");
* 
     private:
       const Point<dim> evaluation_point;
     };
* 
 
     template <int dim>
     PointXDerivativeEvaluation<dim>::PointXDerivativeEvaluation(
       const Point<dim> &evaluation_point)
       : evaluation_point(evaluation_point)
     {}
* 
 
 @endcode
*
* 更有趣的事情发生在进行实际评估的函数中。
*


* @code
     template <int dim>
     void PointXDerivativeEvaluation<dim>::
          operator()(const DoFHandler<dim> &dof_handler,
                const Vector<double> & solution) const
     {
 @endcode
*
* 这一次用一些有用的东西来初始化返回值，因为我们将不得不把一些贡献加起来，之后再取平均值......
*


* @code
       double point_derivative = 0;
* 
 @endcode
*
* ......然后有一些对象，其含义将在下面变得清晰......
*


* @code
       QTrapezoid<dim>             vertex_quadrature;
       FEValues<dim>               fe_values(dof_handler.get_fe(),
                               vertex_quadrature,
                               update_gradients | update_quadrature_points);
       std::vector<Tensor<1, dim>> solution_gradients(vertex_quadrature.size());
* 
 @endcode
*
* ......接下来在所有单元格及其顶点上循环，并计算顶点被发现的频率。
*


* @code
       unsigned int evaluation_point_hits = 0;
       for (const auto &cell : dof_handler.active_cell_iterators())
         for (const auto vertex : cell->vertex_indices())
           if (cell->vertex(vertex) == evaluation_point)
             {
 @endcode
*
* 现在事情不再那么简单了，因为我们不能像以前那样得到有限元场的梯度，我们只需要在一个顶点挑选一个自由度。               
* 相反，我们必须评估这个单元上的有限元场，而且是在某一点。如你所知，在某一点上评估有限元场是通过 <code>FEValues</code> 类完成的，所以我们使用这个类。问题是： <code>FEValues</code> 对象需要给定一个正交公式，然后可以计算正交点的有限元量值。在这里，我们并不想做正交，我们只是想指定一些点!               
* 尽管如此，还是选择同样的方式：使用一个特殊的正交规则，点在顶点，因为这些是我们感兴趣的。适当的规则是梯形规则，所以这就是我们上面使用那个规则的原因。               
*这样：在这个单元上初始化 <code>FEValues</code> 对象。
*


* @code
               fe_values.reinit(cell);
 @endcode
*
* 并提取顶点的解向量梯度。
*


* @code
               fe_values.get_function_gradients(solution, solution_gradients);
* 
 @endcode
*
* 现在我们有所有顶点的梯度，所以挑出属于评估点的那一个（注意顶点的顺序不一定和正交点的顺序一样）。
*


* @code
               unsigned int q_point = 0;
               for (; q_point < solution_gradients.size(); ++q_point)
                 if (fe_values.quadrature_point(q_point) == evaluation_point)
                   break;
* 
 @endcode
*
* 检查是否确实找到了评估点。
*


* @code
               Assert(q_point < solution_gradients.size(), ExcInternalError());
 @endcode
*
* 如果是这样，就把那里的梯度的X导数作为我们感兴趣的值，并增加计数器，表明我们向该变量添加了多少次。
*


* @code
               point_derivative += solution_gradients[q_point][0];
               ++evaluation_point_hits;
* 
 @endcode
*
* 最后跳出最内层的循环，遍历当前单元格的顶点，因为如果我们在一个顶点找到了评估点，它不可能也在后面的顶点。
*


* @code
               break;
             }
* 
 @endcode
*
* 现在我们已经循环了所有的单元格和顶点，所以检查是否找到了这个点。
*


* @code
       AssertThrow(evaluation_point_hits > 0,
                   ExcEvaluationPointNotFound(evaluation_point));
* 
 @endcode
*
* 我们只是简单地将所有相邻单元的贡献相加，所以我们仍然要计算出平均值。一旦完成，报告状态。
*


* @code
       point_derivative /= evaluation_point_hits;
       std::cout << "   Point x-derivative=" << point_derivative << std::endl;
     }
* 
 
* 
 @endcode
*
* <a name="TheGridOutputclass"></a> <h4>The GridOutput class</h4>。


*
* 因为这个程序有一个更困难的结构（它除了计算一个原始解之外，还计算了一个对偶解），所以写出解不再由一个评估对象来完成，因为我们想把两个解同时写进一个文件，这需要一些比评估类可用的信息。     
* 然而，我们也想看看生成的网格。这也可以通过一个这样的类来完成。它的结构类似于前面例子程序中的 <code>SolutionOutput</code> 类，所以我们在这里不做更详细的讨论。此外，这里所使用的一切都已经在以前的例子程序中使用过了。
*


* @code
     template <int dim>
     class GridOutput : public EvaluationBase<dim>
     {
     public:
       GridOutput(const std::string &output_name_base);
* 
       virtual void operator()(const DoFHandler<dim> &dof_handler,
                               const Vector<double> & solution) const override;
* 
     private:
       const std::string output_name_base;
     };
* 
 
     template <int dim>
     GridOutput<dim>::GridOutput(const std::string &output_name_base)
       : output_name_base(output_name_base)
     {}
* 
 
     template <int dim>
     void GridOutput<dim>::operator()(const DoFHandler<dim> &dof_handler,
                                      const Vector<double> &  /*solution*/ ) const
     {
       std::ofstream out(output_name_base + "-" +
                         std::to_string(this->refinement_cycle) + ".svg");
       GridOut().write_svg(dof_handler.get_triangulation(), out);
     }
   } // namespace Evaluation
* 
 
 @endcode
*
* <a name="TheLaplacesolverclasses"></a> <h3>The Laplace solver classes</h3>。


*
* 接下来是实际的求解器类。同样，我们只讨论与之前程序的不同之处。
*


* @code
   namespace LaplaceSolver
   {
 @endcode
*
* <a name="TheLaplacesolverbaseclass"></a> <h4>The Laplace solver base class</h4>。


*
* 这个类几乎没有变化，只是多声明了两个函数。   <code>output_solution</code> 将用于从派生类计算的实际解决方案中生成输出文件，以及 <code>set_refinement_cycle</code> 函数，测试框架通过该函数将细化周期的编号设置为该类中的一个局部变量；该编号随后被用于生成解决方案输出的文件名。
*


* @code
     template <int dim>
     class Base
     {
     public:
       Base(Triangulation<dim> &coarse_grid);
       virtual ~Base() = default;
* 
       virtual void solve_problem() = 0;
       virtual void postprocess(
         const Evaluation::EvaluationBase<dim> &postprocessor) const = 0;
       virtual void         refine_grid()                            = 0;
       virtual unsigned int n_dofs() const                           = 0;
* 
       virtual void set_refinement_cycle(const unsigned int cycle);
* 
       virtual void output_solution() const = 0;
* 
     protected:
       const SmartPointer<Triangulation<dim>> triangulation;
* 
       unsigned int refinement_cycle;
     };
* 
 
     template <int dim>
     Base<dim>::Base(Triangulation<dim> &coarse_grid)
       : triangulation(&coarse_grid)
       , refinement_cycle(numbers::invalid_unsigned_int)
     {}
* 
 
* 
     template <int dim>
     void Base<dim>::set_refinement_cycle(const unsigned int cycle)
     {
       refinement_cycle = cycle;
     }
* 
 
 @endcode
*
* <a name="TheLaplaceSolverclass"></a> <h4>The Laplace Solver class</h4>。


*
* 同样， <code>Solver</code> 类也完全没有变化，因此将不进行讨论。
*


* @code
     template <int dim>
     class Solver : public virtual Base<dim>
     {
     public:
       Solver(Triangulation<dim> &       triangulation,
              const FiniteElement<dim> & fe,
              const Quadrature<dim> &    quadrature,
              const Quadrature<dim
* 
- 1> &face_quadrature,
              const Function<dim> &      boundary_values);
       virtual ~Solver() override;
* 
       virtual void solve_problem() override;
* 
       virtual void postprocess(
         const Evaluation::EvaluationBase<dim> &postprocessor) const override;
* 
       virtual unsigned int n_dofs() const override;
* 
     protected:
       const SmartPointer<const FiniteElement<dim>>  fe;
       const SmartPointer<const Quadrature<dim>>     quadrature;
       const SmartPointer<const Quadrature<dim
* 
- 1>> face_quadrature;
       DoFHandler<dim>                               dof_handler;
       Vector<double>                                solution;
       const SmartPointer<const Function<dim>>       boundary_values;
* 
       virtual void assemble_rhs(Vector<double> &rhs) const = 0;
* 
     private:
       struct LinearSystem
       {
         LinearSystem(const DoFHandler<dim> &dof_handler);
* 
         void solve(Vector<double> &solution) const;
* 
         AffineConstraints<double> hanging_node_constraints;
         SparsityPattern           sparsity_pattern;
         SparseMatrix<double>      matrix;
         Vector<double>            rhs;
       };
* 
 
 @endcode
*
* 该类的其余部分基本上也是 step-13 的副本，包括使用WorkStream框架并行计算线性系统所需的数据结构和函数。
*


* @code
       struct AssemblyScratchData
       {
         AssemblyScratchData(const FiniteElement<dim> &fe,
                             const Quadrature<dim> &   quadrature);
         AssemblyScratchData(const AssemblyScratchData &scratch_data);
* 
         FEValues<dim> fe_values;
       };
* 
       struct AssemblyCopyData
       {
         FullMatrix<double>                   cell_matrix;
         std::vector<types::global_dof_index> local_dof_indices;
       };
* 
 
       void assemble_linear_system(LinearSystem &linear_system);
* 
       void local_assemble_matrix(
         const typename DoFHandler<dim>::active_cell_iterator &cell,
         AssemblyScratchData &                                 scratch_data,
         AssemblyCopyData &                                    copy_data) const;
* 
 
       void copy_local_to_global(const AssemblyCopyData &copy_data,
                                 LinearSystem &          linear_system) const;
     };
* 
 
* 
     template <int dim>
     Solver<dim>::Solver(Triangulation<dim> &       triangulation,
                         const FiniteElement<dim> & fe,
                         const Quadrature<dim> &    quadrature,
                         const Quadrature<dim
* 
- 1> &face_quadrature,
                         const Function<dim> &      boundary_values)
       : Base<dim>(triangulation)
       , fe(&fe)
       , quadrature(&quadrature)
       , face_quadrature(&face_quadrature)
       , dof_handler(triangulation)
       , boundary_values(&boundary_values)
     {}
* 
 
     template <int dim>
     Solver<dim>::~Solver()
     {
       dof_handler.clear();
     }
* 
 
     template <int dim>
     void Solver<dim>::solve_problem()
     {
       dof_handler.distribute_dofs(*fe);
       solution.reinit(dof_handler.n_dofs());
* 
       LinearSystem linear_system(dof_handler);
       assemble_linear_system(linear_system);
       linear_system.solve(solution);
     }
* 
 
     template <int dim>
     void Solver<dim>::postprocess(
       const Evaluation::EvaluationBase<dim> &postprocessor) const
     {
       postprocessor(dof_handler, solution);
     }
* 
 
     template <int dim>
     unsigned int Solver<dim>::n_dofs() const
     {
       return dof_handler.n_dofs();
     }
* 
 
 @endcode
*
* 以下几个函数和构造函数是逐字复制自  step-13  。
*


* @code
     template <int dim>
     void Solver<dim>::assemble_linear_system(LinearSystem &linear_system)
     {
       Threads::Task<void> rhs_task =
         Threads::new_task(&Solver<dim>::assemble_rhs,this, linear_system.rhs);
* 
       auto worker =
         [this](const typename DoFHandler<dim>::active_cell_iterator &cell,
                AssemblyScratchData &scratch_data,
                AssemblyCopyData &   copy_data) {
           this->local_assemble_matrix(cell, scratch_data, copy_data);
         };
* 
       auto copier = [this, &linear_system](const AssemblyCopyData &copy_data) {
         this->copy_local_to_global(copy_data, linear_system);
       };
* 
       WorkStream::run(dof_handler.begin_active(),
                       dof_handler.end(),
                       worker,
                       copier,
                       AssemblyScratchData(*fe,quadrature),
                       AssemblyCopyData());
       linear_system.hanging_node_constraints.condense(linear_system.matrix);
* 
       std::map<types::global_dof_index, double> boundary_value_map;
       VectorTools::interpolate_boundary_values(dof_handler,
                                                0,
                                               boundary_values,
                                                boundary_value_map);
* 
       rhs_task.join();
       linear_system.hanging_node_constraints.condense(linear_system.rhs);
* 
       MatrixTools::apply_boundary_values(boundary_value_map,
                                          linear_system.matrix,
                                          solution,
                                          linear_system.rhs);
     }
* 
 
     template <int dim>
     Solver<dim>::AssemblyScratchData::AssemblyScratchData(
       const FiniteElement<dim> &fe,
       const Quadrature<dim> &   quadrature)
       : fe_values(fe, quadrature, update_gradients | update_JxW_values)
     {}
* 
 
     template <int dim>
     Solver<dim>::AssemblyScratchData::AssemblyScratchData(
       const AssemblyScratchData &scratch_data)
       : fe_values(scratch_data.fe_values.get_fe(),
                   scratch_data.fe_values.get_quadrature(),
                   update_gradients | update_JxW_values)
     {}
* 
 
     template <int dim>
     void Solver<dim>::local_assemble_matrix(
       const typename DoFHandler<dim>::active_cell_iterator &cell,
       AssemblyScratchData &                                 scratch_data,
       AssemblyCopyData &                                    copy_data) const
     {
       const unsigned int dofs_per_cell = fe->n_dofs_per_cell();
       const unsigned int n_q_points    = quadrature->size();
* 
       copy_data.cell_matrix.reinit(dofs_per_cell, dofs_per_cell);
* 
       copy_data.local_dof_indices.resize(dofs_per_cell);
* 
       scratch_data.fe_values.reinit(cell);
* 
       for (unsigned int q_point = 0; q_point < n_q_points; ++q_point)
         for (unsigned int i = 0; i < dofs_per_cell; ++i)
           for (unsigned int j = 0; j < dofs_per_cell; ++j)
             copy_data.cell_matrix(i, j) +=
               (scratch_data.fe_values.shape_grad(i, q_point)
                scratch_data.fe_values.shape_grad(j, q_point)
                scratch_data.fe_values.JxW(q_point));
* 
       cell->get_dof_indices(copy_data.local_dof_indices);
     }
* 
 
* 
     template <int dim>
     void Solver<dim>::copy_local_to_global(const AssemblyCopyData &copy_data,
                                            LinearSystem &linear_system) const
     {
       for (unsigned int i = 0; i < copy_data.local_dof_indices.size(); ++i)
         for (unsigned int j = 0; j < copy_data.local_dof_indices.size(); ++j)
           linear_system.matrix.add(copy_data.local_dof_indices[i],
                                    copy_data.local_dof_indices[j],
                                    copy_data.cell_matrix(i, j));
     }
* 
 
 @endcode
*
* 现在是实现线性系统类中动作的函数。首先，构造函数将所有的数据元素初始化为正确的大小，并设置了一些额外的数据结构，例如由于悬空节点而产生的约束。由于设置悬空节点和找出矩阵的非零元素是独立的，所以我们以并行方式进行（如果库被配置为使用并发，至少是这样；否则，这些动作是按顺序执行的）。注意，我们只启动一个线程，并在主线程中做第二个动作。由于只生成了一个线程，所以我们在这里不使用 <code>Threads::TaskGroup</code> 类，而是直接使用创建的一个任务对象来等待这个特定任务的退出。这个方法与我们在上面的 <code>Solver::assemble_linear_system()</code> 中使用的方法大致相同。     
* 注意，获取 <code>DoFTools::make_hanging_node_constraints</code> 函数的地址有点麻烦，因为实际上有三个这个名字的函数，每个支持的空间维度都有一个。在C++中，获取重载函数的地址有些复杂，因为在这种情况下，操作符 <code>&</code> 会返回一组值（所有具有该名称的函数的地址），然后选择正确的函数是下一步的事情。如果上下文决定采取哪一个（例如通过分配给一个已知类型的函数指针），那么编译器可以自己来做，但是如果这组指针应作为一个采取模板的函数的参数，编译器可以选择所有的，而不偏向于一个。因此，我们必须向编译器说明我们想要哪一个；为此，我们可以使用cast，但为了更清楚，我们把它分配给一个具有正确类型的临时 <code>mhnc_p</code> （简称<code>pointer to make_hanging_node_constraints</code>），并使用这个指针代替。
*


* @code
     template <int dim>
     Solver<dim>::LinearSystem::LinearSystem(const DoFHandler<dim> &dof_handler)
     {
       hanging_node_constraints.clear();
* 
       void (*mhnc_p)(const DoFHandler<dim> &, AffineConstraints<double> &) =
         &DoFTools::make_hanging_node_constraints;
* 
 @endcode
*
* 启动一个辅助任务，然后在主线程上继续进行
*


* @code
       Threads::Task<void> side_task =
         Threads::new_task(mhnc_p, dof_handler, hanging_node_constraints);
* 
       DynamicSparsityPattern dsp(dof_handler.n_dofs(), dof_handler.n_dofs());
       DoFTools::make_sparsity_pattern(dof_handler, dsp);
* 
 
* 
 @endcode
*
* 等到边上的任务完成后再进一步
*


* @code
       side_task.join();
* 
       hanging_node_constraints.close();
       hanging_node_constraints.condense(dsp);
       sparsity_pattern.copy_from(dsp);
* 
       matrix.reinit(sparsity_pattern);
       rhs.reinit(dof_handler.n_dofs());
     }
* 
 
* 
     template <int dim>
     void Solver<dim>::LinearSystem::solve(Vector<double> &solution) const
     {
       SolverControl            solver_control(5000, 1e-12);
       SolverCG<Vector<double>> cg(solver_control);
* 
       PreconditionSSOR<SparseMatrix<double>> preconditioner;
       preconditioner.initialize(matrix, 1.2);
* 
       cg.solve(matrix, solution, rhs, preconditioner);
* 
       hanging_node_constraints.distribute(solution);
     }
* 
 
* 
 @endcode
*
* <a name="ThePrimalSolverclass"></a> <h4>The PrimalSolver class</h4>。


*
* 除了实现 <code>output_solution</code> 函数， <code>PrimalSolver</code> 类也基本没有变化。我们在这个程序中保留了 <code>GlobalRefinement</code> and <code>RefinementKelly</code> 类，然后它们可以依赖这个函数的默认实现，它只是输出原始解。实现双重加权误差估计的类将自行重载这个函数，以同时输出双重解。
*


* @code
     template <int dim>
     class PrimalSolver : public Solver<dim>
     {
     public:
       PrimalSolver(Triangulation<dim> &       triangulation,
                    const FiniteElement<dim> & fe,
                    const Quadrature<dim> &    quadrature,
                    const Quadrature<dim
* 
- 1> &face_quadrature,
                    const Function<dim> &      rhs_function,
                    const Function<dim> &      boundary_values);
* 
       virtual void output_solution() const override;
* 
     protected:
       const SmartPointer<const Function<dim>> rhs_function;
       virtual void assemble_rhs(Vector<double> &rhs) const override;
     };
* 
 
     template <int dim>
     PrimalSolver<dim>::PrimalSolver(Triangulation<dim> &       triangulation,
                                     const FiniteElement<dim> & fe,
                                     const Quadrature<dim> &    quadrature,
                                     const Quadrature<dim
* 
- 1> &face_quadrature,
                                     const Function<dim> &      rhs_function,
                                     const Function<dim> &      boundary_values)
       : Base<dim>(triangulation)
       , Solver<dim>(triangulation,
                     fe,
                     quadrature,
                     face_quadrature,
                     boundary_values)
       , rhs_function(&rhs_function)
     {}
* 
 
* 
     template <int dim>
     void PrimalSolver<dim>::output_solution() const
     {
       DataOut<dim> data_out;
       data_out.attach_dof_handler(this->dof_handler);
       data_out.add_data_vector(this->solution, "solution");
       data_out.build_patches();
* 
       std::ofstream out("solution-" + std::to_string(this->refinement_cycle) +
                         ".vtu");
       data_out.write(out, DataOutBase::vtu);
     }
* 
 
* 
     template <int dim>
     void PrimalSolver<dim>::assemble_rhs(Vector<double> &rhs) const
     {
       FEValues<dim> fe_values(*this->fe,
                              this->quadrature,
                               update_values | update_quadrature_points |
                                 update_JxW_values);
* 
       const unsigned int dofs_per_cell = this->fe->n_dofs_per_cell();
       const unsigned int n_q_points    = this->quadrature->size();
* 
       Vector<double>                       cell_rhs(dofs_per_cell);
       std::vector<double>                  rhs_values(n_q_points);
       std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);
* 
       for (const auto &cell : this->dof_handler.active_cell_iterators())
         {
           cell_rhs = 0;
* 
           fe_values.reinit(cell);
* 
           rhs_function->value_list(fe_values.get_quadrature_points(),
                                    rhs_values);
* 
           for (unsigned int q_point = 0; q_point < n_q_points; ++q_point)
             for (unsigned int i = 0; i < dofs_per_cell; ++i)
               cell_rhs(i) += (fe_values.shape_value(i, q_point) // phi_i(x_q)
                               rhs_values[q_point]               // f((x_q)
                               fe_values.JxW(q_point));            // dx
* 
           cell->get_dof_indices(local_dof_indices);
           for (unsigned int i = 0; i < dofs_per_cell; ++i)
             rhs(local_dof_indices[i]) += cell_rhs(i);
         }
     }
* 
 
 @endcode
*
* <a name="TheRefinementGlobalandRefinementKellyclasses"></a> <h4>The RefinementGlobal and RefinementKelly classes</h4>。


*
* 对于以下两个班级，与上述大部分班级的情况相同：班级是按原样取自前面的例子。
*


* @code
     template <int dim>
     class RefinementGlobal : public PrimalSolver<dim>
     {
     public:
       RefinementGlobal(Triangulation<dim> &       coarse_grid,
                        const FiniteElement<dim> & fe,
                        const Quadrature<dim> &    quadrature,
                        const Quadrature<dim
* 
- 1> &face_quadrature,
                        const Function<dim> &      rhs_function,
                        const Function<dim> &      boundary_values);
* 
       virtual void refine_grid() override;
     };
* 
 
* 
     template <int dim>
     RefinementGlobal<dim>::RefinementGlobal(
       Triangulation<dim> &       coarse_grid,
       const FiniteElement<dim> & fe,
       const Quadrature<dim> &    quadrature,
       const Quadrature<dim
* 
- 1> &face_quadrature,
       const Function<dim> &      rhs_function,
       const Function<dim> &      boundary_values)
       : Base<dim>(coarse_grid)
       , PrimalSolver<dim>(coarse_grid,
                           fe,
                           quadrature,
                           face_quadrature,
                           rhs_function,
                           boundary_values)
     {}
* 
 
* 
     template <int dim>
     void RefinementGlobal<dim>::refine_grid()
     {
       this->triangulation->refine_global(1);
     }
* 
 
* 
     template <int dim>
     class RefinementKelly : public PrimalSolver<dim>
     {
     public:
       RefinementKelly(Triangulation<dim> &       coarse_grid,
                       const FiniteElement<dim> & fe,
                       const Quadrature<dim> &    quadrature,
                       const Quadrature<dim
* 
- 1> &face_quadrature,
                       const Function<dim> &      rhs_function,
                       const Function<dim> &      boundary_values);
* 
       virtual void refine_grid() override;
     };
* 
 
* 
     template <int dim>
     RefinementKelly<dim>::RefinementKelly(
       Triangulation<dim> &       coarse_grid,
       const FiniteElement<dim> & fe,
       const Quadrature<dim> &    quadrature,
       const Quadrature<dim
* 
- 1> &face_quadrature,
       const Function<dim> &      rhs_function,
       const Function<dim> &      boundary_values)
       : Base<dim>(coarse_grid)
       , PrimalSolver<dim>(coarse_grid,
                           fe,
                           quadrature,
                           face_quadrature,
                           rhs_function,
                           boundary_values)
     {}
* 
 
* 
     template <int dim>
     void RefinementKelly<dim>::refine_grid()
     {
       Vector<float> estimated_error_per_cell(
         this->triangulation->n_active_cells());
       KellyErrorEstimator<dim>::estimate(
         this->dof_handler,
         QGauss<dim
* 
- 1>(this->fe->degree + 1),
         std::map<types::boundary_id, const Function<dim>>(),
         this->solution,
         estimated_error_per_cell);
       GridRefinement::refine_and_coarsen_fixed_number(*this->triangulation,
                                                       estimated_error_per_cell,
                                                       0.3,
                                                       0.03);
       this->triangulation->execute_coarsening_and_refinement();
     }
* 
 
* 
 @endcode
*
* <a name="TheRefinementWeightedKellyclass"></a> <h4>The RefinementWeightedKelly class</h4>。


*
* 这个类是前一个类的变种，它允许用一些函数来加权我们从库的Kelly指标中得到的细化指标。我们包括这个类，因为这个例子程序的目标是展示自动细化标准，即使是复杂的输出量，如点值或应力。如果我们不解决对偶问题并计算其中的权重，我们可能会倾向于给指标一个手工制作的权重，以说明我们要评估这些数量。这个类接受这样一个加权函数作为其构造函数的参数。
*


* @code
     template <int dim>
     class RefinementWeightedKelly : public PrimalSolver<dim>
     {
     public:
       RefinementWeightedKelly(Triangulation<dim> &       coarse_grid,
                               const FiniteElement<dim> & fe,
                               const Quadrature<dim> &    quadrature,
                               const Quadrature<dim
* 
- 1> &face_quadrature,
                               const Function<dim> &      rhs_function,
                               const Function<dim> &      boundary_values,
                               const Function<dim> &      weighting_function);
* 
       virtual void refine_grid() override;
* 
     private:
       const SmartPointer<const Function<dim>> weighting_function;
     };
* 
 
* 
     template <int dim>
     RefinementWeightedKelly<dim>::RefinementWeightedKelly(
       Triangulation<dim> &       coarse_grid,
       const FiniteElement<dim> & fe,
       const Quadrature<dim> &    quadrature,
       const Quadrature<dim
* 
- 1> &face_quadrature,
       const Function<dim> &      rhs_function,
       const Function<dim> &      boundary_values,
       const Function<dim> &      weighting_function)
       : Base<dim>(coarse_grid)
       , PrimalSolver<dim>(coarse_grid,
                           fe,
                           quadrature,
                           face_quadrature,
                           rhs_function,
                           boundary_values)
       , weighting_function(&weighting_function)
     {}
* 
 
* 
 @endcode
*
* 现在，主要的功能来了，包括加权。
*


* @code
     template <int dim>
     void RefinementWeightedKelly<dim>::refine_grid()
     {
 @endcode
*
* 首先通过库中已经实现的方法为所有单元计算一些基于残差的误差指标。我们在这里计算的具体内容在该类的文档中有更详细的描述。
*


* @code
       Vector<float> estimated_error_per_cell(
         this->triangulation->n_active_cells());
       std::map<types::boundary_id, const Function<dim>> dummy_function_map;
       KellyErrorEstimator<dim>::estimate(this->dof_handler,
                                         this->face_quadrature,
                                          dummy_function_map,
                                          this->solution,
                                          estimated_error_per_cell);
* 
 @endcode
*
* 接下来用给构造函数的值来衡量指标向量中的每个条目，在单元格中心进行评估。我们需要将结果写入对应于当前单元的向量条目中，我们可以通过使用 CellAccessor::active_cell_index(). 询问单元在所有活动单元中的索引来获得这个结果（实际上，对于我们在循环中处理的第一个单元，这个索引是0，第二个单元是1，等等，我们也可以使用一个整数计数器来跟踪这个索引；但是使用 CellAccessor::active_cell_index() 使之更加明确）。
*


* @code
       for (const auto &cell : this->dof_handler.active_cell_iterators())
         estimated_error_per_cell(cell->active_cell_index())=
           weighting_function->value(cell->center());
* 
       GridRefinement::refine_and_coarsen_fixed_number(*this->triangulation,
                                                       estimated_error_per_cell,
                                                       0.3,
                                                       0.03);
       this->triangulation->execute_coarsening_and_refinement();
     }
* 
   } // namespace LaplaceSolver
* 
 
 @endcode
*
* <a name="Equationdata"></a> <h3>Equation data</h3>。
* 在这个示例程序中，我们使用的数据集与前一个相同，但由于可能有人想用不同的边界值和右手函数或在不同的网格上运行程序，我们展示了一个简单的技术来做到这一点。为了更加清晰，我们进一步将所有与方程数据有关的东西都打包到一个自己的命名空间中。   
* 基本假设是这是一个研究项目，在那里我们经常有一些测试案例，由一个域、一个右手边、边界值、可能是一个指定的系数和一些其他参数组成。当从一个例子转移到另一个例子时，它们常常同时变化。使处理这种问题描述参数集变得简单是下面的目标。   
* 基本上，这个想法是这样的：让我们为每一组数据都有一个结构，在这个结构中，我们把描述一个测试案例的所有东西都打包：这里，这些是两个子类，一个叫 <code>BoundaryValues</code> ，用于精确解的边界值，一个叫 <code>RightHandSide</code>  ，然后是生成粗网格的方法。由于前面的例子程序的解看起来像弯曲的山脊，所以我们在这里用这个名字来表示包围的类。请注意，两个内层类的名称对于所有包围的测试案例类必须是相同的，同时我们将维度模板参数附加到包围类而不是内层类，以使进一步的处理更简单。  从语言的角度来看，用命名空间来封装这些内部类会比用结构来封装更好。然而，命名空间不能作为模板参数给出，所以我们使用一个结构来允许第二个对象从其给定的参数中选择。当然，这个封闭的结构除了它所声明的类之外，没有任何成员变量，还有一个静态函数来生成粗略的网格；一般来说，它永远不会被实例化）。)   
* 这个想法是这样的（现在是时候也简单看看下面的代码了）：我们可以为边界值和右手边生成对象，只需将外层类的名字作为模板参数给一个类，我们在这里称之为 <code>Data::SetUp</code> ，然后它就为内部类创建对象。在这种情况下，为了获得所有描述弧形山脊解决方案的特征，我们将简单地生成一个 <code>Data::SetUp@<Data::CurvedRidge@></code> 的实例，而我们需要知道的关于该解决方案的一切都将是该对象的静态成员变量和函数。   
* 在这种情况下，这种方法可能看起来是多余的，但是一旦某种设定不仅有迪里希特边界值和右手函数的特征，而且还有材料属性、诺伊曼值、不同的边界描述符等，就会变得非常方便。在这种情况下， <code>SetUp</code> 类可能由十几个对象组成，而每个描述符类（如下面的 <code>CurvedRidges</code> 类）都必须提供这些对象。然后，你会很高兴，只需在一个地方改变 <code>SetUp</code> 类的模板参数，而不是在许多地方改变，就能从一组数据改变到另一组。   
* 有了这个不同测试案例的框架，我们就快完成了，但还有一件事：到现在，我们可以通过改变一个模板参数，静态地选择要选择的数据集。为了能够动态地做到这一点，也就是说，在运行时，我们需要一个基类。我们以明显的方式提供这个基类，见下文，用虚拟抽象函数。这迫使我们引入第二个模板参数 <code>dim</code> ，我们需要这个基类（这可以通过一些模板魔法来避免，但我们省略），但这就是全部。   
* 添加新的测试用例现在很简单，你不需要接触框架类，只需要一个类似于 <code>CurvedRidges</code> 的结构。
*


* @code
   namespace Data
   {
 @endcode
*
* <a name="TheSetUpBaseandSetUpclasses"></a> <h4>The SetUpBase and SetUp classes</h4>。


*
* 基于上述描述， <code>SetUpBase</code> 类然后看起来如下。为了允许用这个类来使用 <code>SmartPointer</code> 类，我们从 <code>Subscriptor</code> 类派生出来。
*


* @code
     template <int dim>
     struct SetUpBase : public Subscriptor
     {
       virtual const Function<dim> &get_boundary_values() const = 0;
* 
       virtual const Function<dim> &get_right_hand_side() const = 0;
* 
       virtual void
       create_coarse_grid(Triangulation<dim> &coarse_grid) const = 0;
     };
* 
 
 @endcode
*
* 现在是派生类，按照上面的解释接受模板参数。     
* 这里我们把数据元素打包成私有变量，并允许通过基类的方法来访问它们。
*


* @code
     template <class Traits, int dim>
     struct SetUp : public SetUpBase<dim>
     {
       virtual const Function<dim> &get_boundary_values() const override;
* 
       virtual const Function<dim> &get_right_hand_side() const override;
* 
 
       virtual void
       create_coarse_grid(Triangulation<dim> &coarse_grid) const override;
* 
     private:
       static const typename Traits::BoundaryValues boundary_values;
       static const typename Traits::RightHandSide  right_hand_side;
     };
* 
 @endcode

* 我们必须为上述类的静态成员变量提供定义。
*


* @code
     template <class Traits, int dim>
     const typename Traits::BoundaryValues SetUp<Traits, dim>::boundary_values;
     template <class Traits, int dim>
     const typename Traits::RightHandSide SetUp<Traits, dim>::right_hand_side;
* 
 @endcode

* 还有成员函数的定义。



* @code
     template <class Traits, int dim>
     const Function<dim> &SetUp<Traits, dim>::get_boundary_values() const
     {
       return boundary_values;
     }
* 
 
     template <class Traits, int dim>
     const Function<dim> &SetUp<Traits, dim>::get_right_hand_side() const
     {
       return right_hand_side;
     }
* 
 
     template <class Traits, int dim>
     void SetUp<Traits, dim>::create_coarse_grid(
       Triangulation<dim> &coarse_grid) const
     {
       Traits::create_coarse_grid(coarse_grid);
     }
* 
 
 @endcode
*
* <a name="TheCurvedRidgesclass"></a> <h4>The CurvedRidges class</h4>。


*
* 用于描述 <code>curved ridge</code> 问题的边界值和右手边的类已经在 step-13 示例程序中使用，然后像这样。
*


* @code
     template <int dim>
     struct CurvedRidges
     {
       class BoundaryValues : public Function<dim>
       {
       public:
         virtual double value(const Point<dim> & p,
                              const unsigned int component) const;
       };
* 
 
       class RightHandSide : public Function<dim>
       {
       public:
         virtual double value(const Point<dim> & p,
                              const unsigned int component) const;
       };
* 
       static void create_coarse_grid(Triangulation<dim> &coarse_grid);
     };
* 
 
     template <int dim>
     double CurvedRidges<dim>::BoundaryValues::value(
       const Point<dim> &p,
       const unsigned int  /*component*/ ) const
     {
       double q = p(0);
       for (unsigned int i = 1; i < dim; ++i)
         q += std::sin(10 p(i) + 5 p(0) p(0));
       const double exponential = std::exp(q);
       return exponential;
     }
* 
 
* 
     template <int dim>
     double CurvedRidges<dim>::RightHandSide::value(
       const Point<dim> &p,
       const unsigned int  /*component*/ ) const
     {
       double q = p(0);
       for (unsigned int i = 1; i < dim; ++i)
         q += std::sin(10 p(i) + 5 p(0) p(0));
       const double u  = std::exp(q);
       double       t1 = 1, t2 = 0, t3 = 0;
       for (unsigned int i = 1; i < dim; ++i)
         {
           t1 += std::cos(10 p(i) + 5 p(0) p(0)) 10 p(0);
           t2 += 10 std::cos(10 p(i) + 5 p(0) p(0))
* 
-
                 100 std::sin(10 p(i) + 5 p(0) p(0)) p(0) p(0);
           t3 += 100 std::cos(10 p(i) + 5 p(0) p(0))
                   std::cos(10 p(i) + 5 p(0) p(0))
* 
-
                 100 std::sin(10 p(i) + 5 p(0) p(0));
         }
       t1 = t1 t1;
* 
       return
* 
-u (t1 + t2 + t3);
     }
* 
 
     template <int dim>
     void CurvedRidges<dim>::create_coarse_grid(Triangulation<dim> &coarse_grid)
     {
       GridGenerator::hyper_cube(coarse_grid,
* 
-1, 1);
       coarse_grid.refine_global(2);
     }
* 
 
 @endcode
*
* <a name="TheExercise_2_3class"></a> <h4>The Exercise_2_3 class</h4>。


*
* 这个例子程序是在为一个关于自适应有限元方法和基于对偶性的误差估计的讲座提供实践课程时写的。对于这些课程，我们有一个练习，要求在一个中心有方孔的正方形域上求解右方恒定的拉普拉斯方程，边界值为零。由于这个问题的属性在这里的实现特别简单，所以让我们来做。由于练习的编号是2.3，所以我们冒昧地把这个名字也保留下来，作为课的名称。
*


* @code
     template <int dim>
     struct Exercise_2_3
     {
 @endcode

* 我们需要一个类来表示问题的边界值。在这种情况下，这很简单：它是零函数，所以甚至不用声明一个类，只需要一个别名。
*


* @code
       using BoundaryValues = Functions::ZeroFunction<dim>;
* 
 @endcode

* 第二，一个表示右手的类。因为它们是常数，所以只要把库中相应的类子类化就可以了。
*


* @code
       class RightHandSide : public Functions::ConstantFunction<dim>
       {
       public:
         RightHandSide()
           : Functions::ConstantFunction<dim>(1.)
         {}
       };
* 
 @endcode
*
* 最后是一个生成粗略网格的函数。这在这里有些复杂，请看下面的内容。
*


* @code
       static void create_coarse_grid(Triangulation<dim> &coarse_grid);
     };
* 
 
 @endcode
*
* 如上所述，本例的网格是正方形[-1,1]^2，其中的正方形[-1/2,1/2]^2为孔。我们将粗略的网格创建为4乘以4的单元，中间的四个单元缺失。要了解网格的具体样子，最简单的方法可能是先看一下本教程程序的 "结果 "部分。一般来说，如果你想了解更多关于创建网格的信息，无论是像我们在这里所做的那样从头开始，还是使用其他技术，你都应该看一下  step-49  。     
* 当然，这个例子可以扩展到三维，但由于这个函数不能以独立于维度的方式编写，我们选择不在这里实现它，而只是对dim=2的模板进行专业化处理。如果你编译3d的程序，你会从链接器中得到一个信息：这个函数没有在3d中实现，需要提供。     
* 对于这个几何体的创建，库中没有预定义的方法。在这种情况下，几何体还是很简单的，可以用手来创建，而不是用网格发生器。
*


* @code
     template <>
     void Exercise_2_3<2>::create_coarse_grid(Triangulation<2> &coarse_grid)
     {
 @endcode

* 我们首先定义空间维度，以便让函数中那些实际上与维度无关的部分使用这个变量。如果你以后以这个为起点来实现这个网格的三维版本，那就更简单了。下一步是要有一个顶点的列表。这里，它们是24个（5乘以5，中间的省略）。最好的办法是在这里画一个草图。
*


* @code
       const unsigned int dim = 2;
* 
       const std::vector<Point<2>> vertices = {
         {-1.0,
* 
-1.0}, {-0.5,
* 
-1.0}, {+0.0,
* 
-1.0}, {+0.5,
* 
-1.0}, {+1.0,
* 
-1.0}, 
         {-1.0,
* 
-0.5}, {-0.5,
* 
-0.5}, {+0.0,
* 
-0.5}, {+0.5,
* 
-0.5}, {+1.0,
* 
-0.5}, 
         {-1.0, +0.0}, {-0.5, +0.0}, {+0.5, +0.0}, {+1.0, +0.0},               
         {-1.0, +0.5}, {-0.5, +0.5}, {+0.0, +0.5}, {+0.5, +0.5}, {+1.0, +0.5}, 
         {-1.0, +1.0}, {-0.5, +1.0}, {+0.0, +1.0}, {+0.5, +1.0}, {+1.0, +1.0}};
* 
 @endcode
*
* 接下来，我们要定义单元格和它们所包含的顶点。
*


* @code
       const std::vector<std::array<int, GeometryInfo<dim>::vertices_per_cell>>
         cell_vertices = {{{0, 1, 5, 6}},
                          {{1, 2, 6, 7}},
                          {{2, 3, 7, 8}},
                          {{3, 4, 8, 9}},
                          {{5, 6, 10, 11}},
                          {{8, 9, 12, 13}},
                          {{10, 11, 14, 15}},
                          {{12, 13, 17, 18}},
                          {{14, 15, 19, 20}},
                          {{15, 16, 20, 21}},
                          {{16, 17, 21, 22}},
                          {{17, 18, 22, 23}}};
* 
       const unsigned int n_cells = cell_vertices.size();
* 
 @endcode
*
* 再次，我们从中生成一个C++向量类型，但这次是通过在单元格上进行循环（是的，这很无聊）。此外，我们将所有单元格的材料指标设置为零。
*


* @code
       std::vector<CellData<dim>> cells(n_cells, CellData<dim>());
       for (unsigned int i = 0; i < n_cells; ++i)
         {
           for (unsigned int j = 0; j < cell_vertices[i].size(); ++j)
             cells[i].vertices[j] = cell_vertices[i][j];
           cells[i].material_id = 0;
         }
* 
 @endcode
*
* 最后将所有这些信息传递给库，以生成一个三角形图。最后一个参数可以用来将三角形的某些面的非零边界指标的信息传递给库，但是我们在这里并不希望这样，所以我们给出一个空对象。
*


* @code
       coarse_grid.create_triangulation(vertices, cells, SubCellData());
* 
 @endcode
*
* 因为我们希望本例中的评估点（3/4,3/4）是一个网格点，所以我们在全局上细化一次。
*


* @code
       coarse_grid.refine_global(1);
     }
   } // namespace Data
* 
 @endcode
*
* <a name="Discussion"></a> <h4>Discussion</h4>.
* 你现在已经读完了这个框架，你可能会想，为什么我们没有选择直接把实现某种设置的类（比如 <code>CurvedRidges</code> 类）作为派生自 <code>Data::SetUpBase</code> 的类来实现。事实上，我们可以很好地这样做。唯一的原因是，这样我们就必须在 <code>CurvedRidges</code> 类中为解决方案和右手边的类设置成员变量，以及重载基类的抽象函数来访问这些成员变量的成员函数。 <code>SetUp</code> 类的唯一原因是让我们不必再重申这些成员变量和函数，这些在所有这类中都是必要的。在某种程度上，这里的模板机制只是提供了一种方法，为一些依赖于外部量的函数提供默认的实现，因此不能使用正常的虚拟函数来提供，至少在没有模板的帮助下不能。   
* 然而，可能有很好的理由来实际实现从 <code>Data::SetUpBase</code> 派生的类，例如，如果解或右手边的类需要带参数的构造函数，而 <code>Data::SetUpBase</code> 类无法提供。在这种情况下，子类化是一个值得考虑的策略。对于特殊情况的其他可能性是派生自 <code>Data::SetUp@<SomeSetUp@></code> ，其中 <code>SomeSetUp</code> 表示一个类，甚至明确地专门化 <code>Data::SetUp@<SomeSetUp@></code>  。后者允许透明地使用 <code>SetUp</code> 类用于其他设置的方式，但对特殊参数采取特殊行动。   
* 赞成这里采取的方法的最后一个意见是：我们无数次发现，当开始一个项目时，参数的数量（通常是边界值，右侧，粗略的网格，就像这里一样）很小，测试案例的数量也很小。然后，人们一开始就把它们手工编码成一些 <code>switch</code> 的语句。随着时间的推移，项目的增长，测试用例的数量也在增长。 <code>switch</code> 语句的数量也随之增长，它们的长度也是如此，人们开始想办法考虑不可能的例子，其中域、边界值和右手边不再适合在一起，并且开始失去对整个结构的概述。事实证明，把属于某个测试用例的所有东西都封装到一个自己的结构中是值得的，因为它把属于一个测试用例的所有东西都放在一个地方。此外，它允许把这些东西都放在一个或多个文件中，这些文件只用于测试用例和它们的数据，而不需要把它们的实际实现与程序的其他部分联系起来。
*



*
* <a name="Dualfunctionals"></a> <h3>Dual functionals</h3>。



* 和程序的其他部分一样，我们把所有需要描述对偶函数的东西都放到一个自己的命名空间中，并定义一个抽象基类，提供解决对偶问题的类在工作中需要的接口。   
* 然后我们将实现两个这样的类，用于评估一个点的值和该点的解的导数。对于这些函数，我们已经有了相应的评估对象，所以它们是互补的。
*


* @code
   namespace DualFunctional
   {
 @endcode
*
* <a name="TheDualFunctionalBaseclass"></a> <h4>The DualFunctionalBase class</h4>。


*
* 首先从对偶函数的基类开始。因为对于线性问题来说，对偶问题的特征只在右手边起作用，所以我们只需要提供一个函数来组装给定离散化的右手边。
*


* @code
     template <int dim>
     class DualFunctionalBase : public Subscriptor
     {
     public:
       virtual void assemble_rhs(const DoFHandler<dim> &dof_handler,
                                 Vector<double> &       rhs) const = 0;
     };
* 
 
 @endcode
*
* <a name="ThedualfunctionalPointValueEvaluationclass"></a> <h4>The dual functional PointValueEvaluation class</h4>。


*
* 作为第一个应用，我们考虑对应于在一个给定的点上对解的值进行评估的函数，我们再次假设这个点是一个顶点。除了接受和存储评估点的构造函数之外，这个类只包括实现组装右手边的函数。
*


* @code
     template <int dim>
     class PointValueEvaluation : public DualFunctionalBase<dim>
     {
     public:
       PointValueEvaluation(const Point<dim> &evaluation_point);
* 
       virtual void assemble_rhs(const DoFHandler<dim> &dof_handler,
                                 Vector<double> &       rhs) const override;
* 
       DeclException1(
         ExcEvaluationPointNotFound,
         Point<dim>,
         << "The evaluation point " << arg1
         << " was not found among the vertices of the present grid.");
* 
     protected:
       const Point<dim> evaluation_point;
     };
* 
 
     template <int dim>
     PointValueEvaluation<dim>::PointValueEvaluation(
       const Point<dim> &evaluation_point)
       : evaluation_point(evaluation_point)
     {}
* 
 
 @endcode
*
* 至于做这门课的主要目的，组装右手边，让我们先考虑一下有什么必要。对偶问题的右手边是一个值的向量J(phi_i)，其中J是误差函数，phi_i是第i个形状函数。这里，J是在点x0处的评价，即J(phi_i)=phi_i(x0)。     
*现在，我们已经假定评价点是一个顶点。因此，对于我们在这个程序中可能使用的通常的有限元，我们可以想当然地认为在这样一个点上正好有一个形状函数是不为零的，特别是有一个值为1。因此，我们将右手边的向量设置为全零，然后寻找与该点相关的形状函数，并将右手边向量的相应值设置为1。
*


* @code
     template <int dim>
     void
     PointValueEvaluation<dim>::assemble_rhs(const DoFHandler<dim> &dof_handler,
                                             Vector<double> &       rhs) const
     {
 @endcode

* 所以，首先把所有东西都设为零......
*


* @code
       rhs.reinit(dof_handler.n_dofs());
* 
 @endcode
*
* ...然后在单元格上循环，在顶点中找到评估点（或者非常接近顶点，这可能是由于浮点舍入造成的）。
*


* @code
       for (const auto &cell : dof_handler.active_cell_iterators())
         for (const auto vertex : cell->vertex_indices())
           if (cell->vertex(vertex).distance(evaluation_point) <
               cell->diameter() 1e-8)
             {
 @endcode
*
* 好的，找到了，所以设置相应的条目，然后离开函数，因为我们已经完成了。
*


* @code
               rhs(cell->vertex_dof_index(vertex, 0)) = 1;
               return;
             }
* 
 @endcode
*
* 最后，一个理智的检查：如果我们以某种方式来到这里，那么我们一定是错过了评估点，所以无条件地引发一个异常。
*


* @code
       AssertThrow(false, ExcEvaluationPointNotFound(evaluation_point));
     }
* 
 
 @endcode
*
* <a name="ThedualfunctionalPointXDerivativeEvaluationclass"></a> <h4>The dual functional PointXDerivativeEvaluation class</h4>。


*
* 作为第二个应用，我们再次考虑在一个点上对解决方案的x-derivative进行评估。同样，这个类的声明和它的构造函数的实现也不是太有趣。
*


* @code
     template <int dim>
     class PointXDerivativeEvaluation : public DualFunctionalBase<dim>
     {
     public:
       PointXDerivativeEvaluation(const Point<dim> &evaluation_point);
* 
       virtual void assemble_rhs(const DoFHandler<dim> &dof_handler,
                                 Vector<double> &       rhs) const;
* 
       DeclException1(
         ExcEvaluationPointNotFound,
         Point<dim>,
         << "The evaluation point " << arg1
         << " was not found among the vertices of the present grid.");
* 
     protected:
       const Point<dim> evaluation_point;
     };
* 
 
     template <int dim>
     PointXDerivativeEvaluation<dim>::PointXDerivativeEvaluation(
       const Point<dim> &evaluation_point)
       : evaluation_point(evaluation_point)
     {}
* 
 
 @endcode
*
* 有趣的是这个函数的实现：这里，J(phi_i)=d/dx phi_i(x0)。     
* 我们可以像实现各自的评价对象那样，在这个评价点上取每个形状函数phi_i的梯度的平均值。然而，我们采取了一个略微不同的方法：我们简单地取该点周围所有单元格的平均值。哪些单元 <code>surrounds</code> 是评估点，这个问题取决于网格宽度，包括那些单元的中点到评估点的距离小于单元的直径的单元。     
* 在这些单元的面积/体积上取梯度的平均值，可以得到一个非常接近于梯度的点评估结果的二元解。从理论上讲，这并没有明显改变方法，这一点很容易证明。
*


* @code
     template <int dim>
     void PointXDerivativeEvaluation<dim>::assemble_rhs(
       const DoFHandler<dim> &dof_handler,
       Vector<double> &       rhs) const
     {
 @endcode

* 同样，首先将所有条目设置为零。
*


* @code
       rhs.reinit(dof_handler.n_dofs());
* 
 @endcode
*
* 用正交公式初始化一个 <code>FEValues</code> 对象，有正交点数量和形状函数的缩写......
*


* @code
       QGauss<dim>        quadrature(dof_handler.get_fe().degree + 1);
       FEValues<dim>      fe_values(dof_handler.get_fe(),
                               quadrature,
                               update_gradients | update_quadrature_points |
                                 update_JxW_values);
       const unsigned int n_q_points    = fe_values.n_quadrature_points;
       const unsigned int dofs_per_cell = dof_handler.get_fe().dofs_per_cell;
* 
 @endcode
*
* ...并有两个对象用于存储单元上自由度的全局指数，以及正交点上形状函数的梯度值。
*


* @code
       Vector<double>            cell_rhs(dofs_per_cell);
       std::vector<unsigned int> local_dof_indices(dofs_per_cell);
* 
 @endcode
*
* 最后有一个变量，我们将通过对这些单元上的单位函数进行积分，总结出这些单元的面积/体积。
*


* @code
       double total_volume = 0;
* 
 @endcode
*
* 然后在所有单元格上开始循环，并选择那些与评估点足够接近的单元格。
*


* @code
       for (const auto &cell : dof_handler.active_cell_iterators())
         if (cell->center().distance(evaluation_point) <= cell->diameter())
           {
 @endcode
*
* 如果我们找到了这样的单元，那么就初始化 <code>FEValues</code> 对象，并整合每个形状函数梯度的x分量，以及总面积/体积的单位函数。
*


* @code
             fe_values.reinit(cell);
             cell_rhs = 0;
* 
             for (unsigned int q = 0; q < n_q_points; ++q)
               {
                 for (unsigned int i = 0; i < dofs_per_cell; ++i)
                   cell_rhs(i) +=
                     fe_values.shape_grad(i, q)[0] // (d/dx phi_i(x_q))
                     fe_values.JxW(q);           // dx
                 total_volume += fe_values.JxW(q);
               }
* 
 @endcode
*
* 如果我们有本地贡献，就把它们分配到全局矢量。
*


* @code
             cell->get_dof_indices(local_dof_indices);
             for (unsigned int i = 0; i < dofs_per_cell; ++i)
               rhs(local_dof_indices[i]) += cell_rhs(i);
           }
* 
 @endcode
*
* 在我们对所有的单元格进行循环之后，检查我们是否找到了任何单元格，确保它们的体积不为零。如果不是，那么结果将是错误的，因为这时的右手边应该仍然是零，所以抛出一个异常。
*


* @code
       AssertThrow(total_volume > 0,
                   ExcEvaluationPointNotFound(evaluation_point));
* 
 @endcode
*
* 最后，我们现在只对形状函数的梯度进行了积分，而没有取其平均值。我们通过除以我们所整合的体积的尺度来解决这个问题。
*


* @code
       rhs /= total_volume;
     }
* 
 
   } // namespace DualFunctional
* 
 
 @endcode
*
* <a name="ExtendingtheLaplaceSolvernamespace"></a> <h3>Extending the LaplaceSolver namespace</h3>。



* @code
   namespace LaplaceSolver
   {
 @endcode
*
* <a name="TheDualSolverclass"></a> <h4>The DualSolver class</h4>。


*
* 与上面的 <code>PrimalSolver</code> 类相同，我们现在实现一个 <code>DualSolver</code>  。它具有所有相同的特征，唯一的区别是它不接受一个表示右侧对象的函数对象，而现在接受一个 <code>DualFunctionalBase</code> 对象，该对象将集合对偶问题的右侧向量。该类的其余部分是相当琐碎的。     
* 由于原始解算器和对偶解算器将使用相同的三角形，但不同的离散，现在很清楚为什么我们将 <code>Base</code> 类变成了虚拟类：因为最终类将从 <code>PrimalSolver</code> 以及 <code>DualSolver</code>, it would have two <code>Base</code> 实例中派生，我们是不是应该将继承标记为虚拟。因为在许多应用中，基类会存储更多的信息，而不仅仅是需要在原始和对偶求解器之间共享的三角关系，所以我们通常不希望使用两个这样的基类。
*


* @code
     template <int dim>
     class DualSolver : public Solver<dim>
     {
     public:
       DualSolver(
         Triangulation<dim> &                           triangulation,
         const FiniteElement<dim> &                     fe,
         const Quadrature<dim> &                        quadrature,
         const Quadrature<dim
* 
- 1> &                    face_quadrature,
         const DualFunctional::DualFunctionalBase<dim> &dual_functional);
* 
     protected:
       const SmartPointer<const DualFunctional::DualFunctionalBase<dim>>
                    dual_functional;
       virtual void assemble_rhs(Vector<double> &rhs) const override;
* 
       static const Functions::ZeroFunction<dim> boundary_values;
     };
* 
     template <int dim>
     const Functions::ZeroFunction<dim> DualSolver<dim>::boundary_values;
* 
     template <int dim>
     DualSolver<dim>::DualSolver(
       Triangulation<dim> &                           triangulation,
       const FiniteElement<dim> &                     fe,
       const Quadrature<dim> &                        quadrature,
       const Quadrature<dim
* 
- 1> &                    face_quadrature,
       const DualFunctional::DualFunctionalBase<dim> &dual_functional)
       : Base<dim>(triangulation)
       , Solver<dim>(triangulation,
                     fe,
                     quadrature,
                     face_quadrature,
                     boundary_values)
       , dual_functional(&dual_functional)
     {}
* 
 
* 
     template <int dim>
     void DualSolver<dim>::assemble_rhs(Vector<double> &rhs) const
     {
       dual_functional->assemble_rhs(this->dof_handler, rhs);
     }
* 
 
 @endcode
*
* <a name="TheWeightedResidualclass"></a> <h4>The WeightedResidual class</h4>。



* 这里终于出现了这个程序的主类，也就是实现对偶加权残差误差估计器的类。它连接了原始和对偶求解器类，用于计算原始和对偶解，并实现了误差表示公式，用于误差估计和网格细化。     
* 这个类的前几个函数大多是对基类各自函数的覆盖。
*


* @code
     template <int dim>
     class WeightedResidual : public PrimalSolver<dim>, public DualSolver<dim>
     {
     public:
       WeightedResidual(
         Triangulation<dim> &                           coarse_grid,
         const FiniteElement<dim> &                     primal_fe,
         const FiniteElement<dim> &                     dual_fe,
         const Quadrature<dim> &                        quadrature,
         const Quadrature<dim
* 
- 1> &                    face_quadrature,
         const Function<dim> &                          rhs_function,
         const Function<dim> &                          boundary_values,
         const DualFunctional::DualFunctionalBase<dim> &dual_functional);
* 
       virtual void solve_problem() override;
* 
       virtual void postprocess(
         const Evaluation::EvaluationBase<dim> &postprocessor) const override;
* 
       virtual unsigned int n_dofs() const override;
* 
       virtual void refine_grid() override;
* 
       virtual void output_solution() const override;
* 
     private:
 @endcode
*
* 在私有部分，我们有两个函数，用来调用原始类和双基类的 <code>solve_problem</code> 函数。这两个函数将被本类的 <code>solve_problem</code> 函数并行调用。
*


* @code
       void solve_primal_problem();
       void solve_dual_problem();
 @endcode
*
* 然后声明活动单元格迭代器的缩写，以避免我们不得不重复写这个冗长的名字。
*


*


* @code
       using active_cell_iterator =
         typename DoFHandler<dim>::active_cell_iterator;
* 
 @endcode
*
* 接下来，声明一个数据类型，我们将用它来存储面孔对误差估计器的贡献。我们的想法是，我们可以计算从两个单元格中的每一个到这个面的面项，因为从两边看时它们是一样的。我们要做的是，根据下面解释的一些规则，只计算一次，由相邻的两个单元负责计算。然后，我们将每个面的贡献存储在一个映射面与它们的值的地图中，并只通过在细胞上循环第二次并从地图上抓取值来收集每个细胞的贡献。       
* 这个地图的数据类型在此声明。
*


* @code
       using FaceIntegrals =
         typename std::map<typename DoFHandler<dim>::face_iterator, double>;
* 
 @endcode
*
* 在计算单元和面的误差估计时，我们需要一些辅助对象，如 <code>FEValues</code> 和 <code>FEFaceValues</code> 函数，但也需要一些临时对象来存储原始和对偶解的值和梯度，例如。这些字段在三个函数中都是需要的，这些函数分别在单元格、规则面和不规则面上做积分。       
* 有三种合理的方式来提供这些字段：第一，作为需要它们的函数中的局部变量；第二，作为本类的成员变量；第三，作为参数传递给该函数。       
* 这三种替代方法都有缺点：第三种是它们的数量不可忽略，会使调用这些函数成为一项冗长的事业。第二种方法的缺点是不允许并行化，因为计算误差估计值的线程必须各自拥有这些变量的副本，所以包围类的成员变量将不起作用。第一种方法虽然直接，但有一个微妙但重要的缺点：我们会反复调用这些函数，也许是成千上万次；现在证明，从堆中分配向量和其他需要内存的对象在运行时间上是昂贵的，因为当涉及几个线程时，内存分配是昂贵的。因此，只分配一次内存，并尽可能频繁地回收这些对象，是明显更好的做法。       
* 该怎么做呢？我们的答案是使用第三种策略的一个变种。事实上，这正是WorkStream概念所要做的（我们已经在上面介绍了它，但也请看 @ref threads ）。为了避免我们必须给这些函数十几个参数，我们将所有这些变量打包成两个结构，一个用于单元格的计算，另一个用于面的计算。然后，这两个结构被加入到WeightedResidualScratchData类中，该类将作为WorkStream概念的 "划痕数据 "类。
*


* @code
       struct CellData
       {
         FEValues<dim>                           fe_values;
         const SmartPointer<const Function<dim>> right_hand_side;
* 
         std::vector<double> cell_residual;
         std::vector<double> rhs_values;
         std::vector<double> dual_weights;
         std::vector<double> cell_laplacians;
         CellData(const FiniteElement<dim> &fe,
                  const Quadrature<dim> &   quadrature,
                  const Function<dim> &     right_hand_side);
         CellData(const CellData &cell_data);
       };
* 
       struct FaceData
       {
         FEFaceValues<dim>    fe_face_values_cell;
         FEFaceValues<dim>    fe_face_values_neighbor;
         FESubfaceValues<dim> fe_subface_values_cell;
* 
         std::vector<double>                  jump_residual;
         std::vector<double>                  dual_weights;
         typename std::vector<Tensor<1, dim>> cell_grads;
         typename std::vector<Tensor<1, dim>> neighbor_grads;
         FaceData(const FiniteElement<dim> & fe,
                  const Quadrature<dim
* 
- 1> &face_quadrature);
         FaceData(const FaceData &face_data);
       };
* 
       struct WeightedResidualScratchData
       {
         WeightedResidualScratchData(
           const FiniteElement<dim> & primal_fe,
           const Quadrature<dim> &    primal_quadrature,
           const Quadrature<dim
* 
- 1> &primal_face_quadrature,
           const Function<dim> &      rhs_function,
           const Vector<double> &     primal_solution,
           const Vector<double> &     dual_weights);
* 
         WeightedResidualScratchData(
           const WeightedResidualScratchData &scratch_data);
* 
         CellData       cell_data;
         FaceData       face_data;
         Vector<double> primal_solution;
         Vector<double> dual_weights;
       };
* 
 
 @endcode
*
*  WorkStream::run 一般都希望有一个抓取对象和一个复制对象。在这里，由于与我们在 step-9 中讨论计算梯度的近似值时类似的原因，我们实际上不需要一个 "拷贝数据 "结构。既然WorkStream坚持要有一个这样的结构，我们就声明一个空的结构，除了存在之外什么都不做。
*


* @code
       struct WeightedResidualCopyData
       {};
* 
 
* 
 @endcode
*
* 关于误差估计器的评估，我们有一个驱动函数，使用 WorkStream::run() 来调用每个单元格的第二个函数。
*


* @code
       void estimate_error(Vector<float> &error_indicators) const;
* 
       void estimate_on_one_cell(const active_cell_iterator & cell,
                                 WeightedResidualScratchData &scratch_data,
                                 WeightedResidualCopyData &   copy_data,
                                 Vector<float> &              error_indicators,
                                 FaceIntegrals &face_integrals) const;
* 
 @endcode
*
* 然后我们有函数对误差表示公式进行实际积分。它们将分别处理单元内部、没有悬挂节点的面和有悬挂节点的面的条款。
*


* @code
       void integrate_over_cell(const active_cell_iterator &cell,
                                const Vector<double> &      primal_solution,
                                const Vector<double> &      dual_weights,
                                CellData &                  cell_data,
                                Vector<float> &error_indicators) const;
* 
       void integrate_over_regular_face(const active_cell_iterator &cell,
                                        const unsigned int          face_no,
                                        const Vector<double> &primal_solution,
                                        const Vector<double> &dual_weights,
                                        FaceData &            face_data,
                                        FaceIntegrals &face_integrals) const;
       void integrate_over_irregular_face(const active_cell_iterator &cell,
                                          const unsigned int          face_no,
                                          const Vector<double> &primal_solution,
                                          const Vector<double> &dual_weights,
                                          FaceData &            face_data,
                                          FaceIntegrals &face_integrals) const;
     };
* 
 
* 
 @endcode
*
* 在这个类的实现中，我们首先有 <code>CellData</code> and <code>FaceData</code> 成员类的构造函数，以及 <code>WeightedResidual</code> 构造函数。它们只将字段初始化为正确的长度，所以我们不必过多地讨论它们。
*


* @code
     template <int dim>
     WeightedResidual<dim>::CellData::CellData(
       const FiniteElement<dim> &fe,
       const Quadrature<dim> &   quadrature,
       const Function<dim> &     right_hand_side)
       : fe_values(fe,
                   quadrature,
                   update_values | update_hessians | update_quadrature_points |
                     update_JxW_values)
       , right_hand_side(&right_hand_side)
       , cell_residual(quadrature.size())
       , rhs_values(quadrature.size())
       , dual_weights(quadrature.size())
       , cell_laplacians(quadrature.size())
     {}
* 
 
* 
     template <int dim>
     WeightedResidual<dim>::CellData::CellData(const CellData &cell_data)
       : fe_values(cell_data.fe_values.get_fe(),
                   cell_data.fe_values.get_quadrature(),
                   update_values | update_hessians | update_quadrature_points |
                     update_JxW_values)
       , right_hand_side(cell_data.right_hand_side)
       , cell_residual(cell_data.cell_residual)
       , rhs_values(cell_data.rhs_values)
       , dual_weights(cell_data.dual_weights)
       , cell_laplacians(cell_data.cell_laplacians)
     {}
* 
 
* 
     template <int dim>
     WeightedResidual<dim>::FaceData::FaceData(
       const FiniteElement<dim> & fe,
       const Quadrature<dim
* 
- 1> &face_quadrature)
       : fe_face_values_cell(fe,
                             face_quadrature,
                             update_values | update_gradients |
                               update_JxW_values | update_normal_vectors)
       , fe_face_values_neighbor(fe,
                                 face_quadrature,
                                 update_values | update_gradients |
                                   update_JxW_values | update_normal_vectors)
       , fe_subface_values_cell(fe, face_quadrature, update_gradients)
     {
       const unsigned int n_face_q_points = face_quadrature.size();
* 
       jump_residual.resize(n_face_q_points);
       dual_weights.resize(n_face_q_points);
       cell_grads.resize(n_face_q_points);
       neighbor_grads.resize(n_face_q_points);
     }
* 
 
* 
     template <int dim>
     WeightedResidual<dim>::FaceData::FaceData(const FaceData &face_data)
       : fe_face_values_cell(face_data.fe_face_values_cell.get_fe(),
                             face_data.fe_face_values_cell.get_quadrature(),
                             update_values | update_gradients |
                               update_JxW_values | update_normal_vectors)
       , fe_face_values_neighbor(
           face_data.fe_face_values_neighbor.get_fe(),
           face_data.fe_face_values_neighbor.get_quadrature(),
           update_values | update_gradients | update_JxW_values |
             update_normal_vectors)
       , fe_subface_values_cell(
           face_data.fe_subface_values_cell.get_fe(),
           face_data.fe_subface_values_cell.get_quadrature(),
           update_gradients)
       , jump_residual(face_data.jump_residual)
       , dual_weights(face_data.dual_weights)
       , cell_grads(face_data.cell_grads)
       , neighbor_grads(face_data.neighbor_grads)
     {}
* 
 
* 
     template <int dim>
     WeightedResidual<dim>::WeightedResidualScratchData::
       WeightedResidualScratchData(
         const FiniteElement<dim> & primal_fe,
         const Quadrature<dim> &    primal_quadrature,
         const Quadrature<dim
* 
- 1> &primal_face_quadrature,
         const Function<dim> &      rhs_function,
         const Vector<double> &     primal_solution,
         const Vector<double> &     dual_weights)
       : cell_data(primal_fe, primal_quadrature, rhs_function)
       , face_data(primal_fe, primal_face_quadrature)
       , primal_solution(primal_solution)
       , dual_weights(dual_weights)
     {}
* 
     template <int dim>
     WeightedResidual<dim>::WeightedResidualScratchData::
       WeightedResidualScratchData(
         const WeightedResidualScratchData &scratch_data)
       : cell_data(scratch_data.cell_data)
       , face_data(scratch_data.face_data)
       , primal_solution(scratch_data.primal_solution)
       , dual_weights(scratch_data.dual_weights)
     {}
* 
 
* 
     template <int dim>
     WeightedResidual<dim>::WeightedResidual(
       Triangulation<dim> &                           coarse_grid,
       const FiniteElement<dim> &                     primal_fe,
       const FiniteElement<dim> &                     dual_fe,
       const Quadrature<dim> &                        quadrature,
       const Quadrature<dim
* 
- 1> &                    face_quadrature,
       const Function<dim> &                          rhs_function,
       const Function<dim> &                          bv,
       const DualFunctional::DualFunctionalBase<dim> &dual_functional)
       : Base<dim>(coarse_grid)
       , PrimalSolver<dim>(coarse_grid,
                           primal_fe,
                           quadrature,
                           face_quadrature,
                           rhs_function,
                           bv)
       , DualSolver<dim>(coarse_grid,
                         dual_fe,
                         quadrature,
                         face_quadrature,
                         dual_functional)
     {}
* 
 
 @endcode
*
* 接下来的五个函数是很无聊的，因为它们只是简单地把它们的工作转交给基类。第一个函数并行地调用原始和对偶求解器，而解的后处理和检索自由度的数量则由原始类完成。
*


* @code
     template <int dim>
     void WeightedResidual<dim>::solve_problem()
     {
       Threads::TaskGroup<void> tasks;
       tasks +=
         Threads::new_task(&WeightedResidual<dim>::solve_primal_problem,this);
       tasks +=
         Threads::new_task(&WeightedResidual<dim>::solve_dual_problem,this);
       tasks.join_all();
     }
* 
 
     template <int dim>
     void WeightedResidual<dim>::solve_primal_problem()
     {
       PrimalSolver<dim>::solve_problem();
     }
* 
     template <int dim>
     void WeightedResidual<dim>::solve_dual_problem()
     {
       DualSolver<dim>::solve_problem();
     }
* 
 
     template <int dim>
     void WeightedResidual<dim>::postprocess(
       const Evaluation::EvaluationBase<dim> &postprocessor) const
     {
       PrimalSolver<dim>::postprocess(postprocessor);
     }
* 
 
     template <int dim>
     unsigned int WeightedResidual<dim>::n_dofs() const
     {
       return PrimalSolver<dim>::n_dofs();
     }
* 
 
* 
 @endcode
*
* 现在，它变得更加有趣了： <code>refine_grid()</code> 函数要求误差估计器计算单元格的误差指标，然后使用它们的绝对值进行网格细化。
*


* @code
     template <int dim>
     void WeightedResidual<dim>::refine_grid()
     {
 @endcode
*
*首先调用计算单元格和全局误差的函数。
*


* @code
       Vector<float> error_indicators(this->triangulation->n_active_cells());
       estimate_error(error_indicators);
* 
 @endcode
*
* 然后注意，只有当所有的指标都是正数时，为细化或粗化做标记的单元格才起作用，以便于它们的比较。因此，去掉所有这些指标上的符号。
*


* @code
       for (float &error_indicator : error_indicators)
         error_indicator = std::fabs(error_indicator);
* 
 @endcode
*
* 最后，我们可以选择不同的细化策略。这里默认的是细化那些误差指标最大、占总误差80%的单元，而我们则粗化那些指标最小、占总误差2%的单元。
*


* @code
       GridRefinement::refine_and_coarsen_fixed_fraction(*this->triangulation,
                                                         error_indicators,
                                                         0.8,
                                                         0.02);
       this->triangulation->execute_coarsening_and_refinement();
     }
* 
 
 @endcode
*
* 由于我们想同时输出原始解和对偶解，我们重载了 <code>output_solution</code> 函数。这个函数唯一有趣的特点是，原始解和对偶解是在不同的有限元空间上定义的，这不是 <code>DataOut</code> 类所期望的格式。因此，我们必须将它们转移到一个共同的有限元空间。由于我们只想从质量上看到这些解，所以我们要争夺将对偶解内插到（较小的）原始空间。对于插值，有一个库函数，它接收一个包括悬挂节点约束的AffineConstraints对象。其余的都是标准的。
*


* @code
     template <int dim>
     void WeightedResidual<dim>::output_solution() const
     {
       AffineConstraints<double> primal_hanging_node_constraints;
       DoFTools::make_hanging_node_constraints(PrimalSolver<dim>::dof_handler,
                                               primal_hanging_node_constraints);
       primal_hanging_node_constraints.close();
       Vector<double> dual_solution(PrimalSolver<dim>::dof_handler.n_dofs());
       FETools::interpolate(DualSolver<dim>::dof_handler,
                            DualSolver<dim>::solution,
                            PrimalSolver<dim>::dof_handler,
                            primal_hanging_node_constraints,
                            dual_solution);
* 
       DataOut<dim> data_out;
       data_out.attach_dof_handler(PrimalSolver<dim>::dof_handler);
* 
 @endcode
*
* 添加我们想要输出的数据向量。把它们都加进去， <code>DataOut</code> 函数可以处理你想写到输出的多少个数据向量。
*


* @code
       data_out.add_data_vector(PrimalSolver<dim>::solution, "primal_solution");
       data_out.add_data_vector(dual_solution, "dual_solution");
* 
       data_out.build_patches();
* 
       std::ofstream out("solution-" + std::to_string(this->refinement_cycle) +
                         ".vtu");
       data_out.write(out, DataOutBase::vtu);
     }
* 
 
 @endcode
*
* <a name="Estimatingerrors"></a> <h3>Estimating errors</h3>。



* <a name="Errorestimationdriverfunctions"></a> <h4>Error estimation driver functions</h4>。
* 至于误差估计的实际计算，让我们从驱动这一切的函数开始，即调用那些实际工作的函数，并最终收集结果。
*


* @code
     template <int dim>
     void
     WeightedResidual<dim>::estimate_error(Vector<float> &error_indicators) const
     {
 @endcode
*
* 计算误差的第一个任务是设置向量，表示原始解，以及权重(z-z_h)=(z-I_hz)，两者都在我们已经计算出对偶解的有限元空间。为此，我们必须将原始解内插到对偶有限元空间，并将计算出的对偶解内插到原始有限元空间。幸运的是，库中提供了插值到更大或更小的有限元空间的函数，所以这一点是很明显的。       
* 首先，让我们为原始解做这件事：它被单元内插到我们已经解决了对偶问题的有限元空间中：但是，还是像 <code>WeightedResidual::output_solution</code> 函数中那样，我们首先需要创建一个AffineConstraints对象，包括悬挂节点约束，但这次是对偶有限元空间。
*


* @code
       AffineConstraints<double> dual_hanging_node_constraints;
       DoFTools::make_hanging_node_constraints(DualSolver<dim>::dof_handler,
                                               dual_hanging_node_constraints);
       dual_hanging_node_constraints.close();
       Vector<double> primal_solution(DualSolver<dim>::dof_handler.n_dofs());
       FETools::interpolate(PrimalSolver<dim>::dof_handler,
                            PrimalSolver<dim>::solution,
                            DualSolver<dim>::dof_handler,
                            dual_hanging_node_constraints,
                            primal_solution);
* 
 @endcode

* 然后用于计算数值逼近的对偶解z插值到原始解的有限元空间并从z中减去：使用 <code>interpolate_difference</code> 函数，该函数在对偶解的元素空间中给出（z-I_hz）。
*


* @code
       AffineConstraints<double> primal_hanging_node_constraints;
       DoFTools::make_hanging_node_constraints(PrimalSolver<dim>::dof_handler,
                                               primal_hanging_node_constraints);
       primal_hanging_node_constraints.close();
       Vector<double> dual_weights(DualSolver<dim>::dof_handler.n_dofs());
       FETools::interpolation_difference(DualSolver<dim>::dof_handler,
                                         dual_hanging_node_constraints,
                                         DualSolver<dim>::solution,
                                         PrimalSolver<dim>::dof_handler,
                                         primal_hanging_node_constraints,
                                         dual_weights);
* 
 @endcode
*
* 请注意，这可能会更有效率，因为这些约束条件已经在之前为原始问题组装矩阵和右手边以及写出对偶解时使用过了。我们把这方面的程序优化作为一个练习。
*

*
* 在计算了对偶权重之后，我们现在开始计算原始解的单元和面的残差。首先，我们在面的迭代器和面的跳跃项对误差估计器的贡献之间建立一个映射。原因是我们只计算了一次跳跃项，从面的一侧开始，并且希望在第二次循环所有单元时才收集它们。       
* 我们已经用一个值来初始化这个地图，即
*
* e20，因为如果出了问题，我们因某种原因无法计算某个面的值，这个值会在结果中脱颖而出。其次，这个初始化已经使 std::map 对象分配了它可能需要的所有对象。这一点很重要，因为我们将从并行线程写进这个结构，如果地图需要分配内存，从而重塑其数据结构，那么这样做就不是线程安全的。换句话说，初始化使我们不必在线程每次写入（和修改）该地图的结构时通过互斥来同步。
*


* @code
       FaceIntegrals face_integrals;
       for (const auto &cell :
            DualSolver<dim>::dof_handler.active_cell_iterators())
         for (const auto &face : cell->face_iterators())
           face_integrals[face] =
* 
-1e20;
* 
       auto worker = [this,
                      &error_indicators,
                      &face_integrals](const active_cell_iterator & cell,
                                       WeightedResidualScratchData &scratch_data,
                                       WeightedResidualCopyData &   copy_data) {
         this->estimate_on_one_cell(
           cell, scratch_data, copy_data, error_indicators, face_integrals);
       };
* 
       auto do_nothing_copier =
         std::function<void(const WeightedResidualCopyData &)>();
* 
 @endcode
*
* 然后把它全部交给 WorkStream::run() ，以平行地计算所有单元的估计值。
*


* @code
       WorkStream::run(
         DualSolver<dim>::dof_handler.begin_active(),
         DualSolver<dim>::dof_handler.end(),
         worker,
         do_nothing_copier,
         WeightedResidualScratchData(*DualSolver<dim>::fe,
                                    DualSolver<dim>::quadrature,
                                    DualSolver<dim>::face_quadrature,
                                    this->rhs_function,
                                     primal_solution,
                                     dual_weights),
         WeightedResidualCopyData());
* 
 @endcode
*
* 一旦计算出误差贡献，就把它们加起来。对于这一点，请注意单元项已经设置好了，只需要收集边缘项。因此，在所有的单元和它们的面中循环，确保每个面的贡献都在那里，然后把它们加起来。只需要减去一半的跳跃项，因为另一半会被邻近的单元格拿走。
*


* @code
       unsigned int present_cell = 0;
       for (const auto &cell :
            DualSolver<dim>::dof_handler.active_cell_iterators())
         {
           for (const auto &face : cell->face_iterators())
             {
               Assert(face_integrals.find(face) != face_integrals.end(),
                      ExcInternalError());
               error_indicators(present_cell)
* 
-= 0.5 face_integrals[face];
             }
           ++present_cell;
         }
       std::cout << "   Estimated error="
                 << std::accumulate(error_indicators.begin(),
                                    error_indicators.end(),
                                    0.)
                 << std::endl;
     }
* 
 
 @endcode
*
* <a name="Estimatingonasinglecell"></a> <h4>Estimating on a single cell</h4>。


*
* 接下来我们有一个函数，它被调用来估计单个单元的误差。如果库被配置为使用多线程，该函数可以被多次调用。下面是它的内容。
*


* @code
     template <int dim>
     void WeightedResidual<dim>::estimate_on_one_cell(
       const active_cell_iterator & cell,
       WeightedResidualScratchData &scratch_data,
       WeightedResidualCopyData &   copy_data,
       Vector<float> &              error_indicators,
       FaceIntegrals &              face_integrals) const
     {
 @endcode
*
* 由于WorkStream的原因，估计_on_one_cell需要一个CopyData对象，即使它没有被使用。下一行对这个未使用的变量的警告保持沉默。
*


* @code
       (void)copy_data;
* 
 @endcode
*
*每个单元的第一个任务是计算这个单元的单元残差贡献，并把它们放入 <code>error_indicators</code> 变量中。
*


* @code
       integrate_over_cell(cell,
                           scratch_data.primal_solution,
                           scratch_data.dual_weights,
                           scratch_data.cell_data,
                           error_indicators);
* 
 @endcode
*
* 在计算完单元项之后，转向面项。为此，在当前单元格的所有面上进行循环，看看是否需要对其进行计算。
*


* @code
       for (const auto face_no : cell->face_indices())
         {
 @endcode

* 首先，如果这个面是边界的一部分，那么就没什么可做的。然而，为了在汇总单元格的面的贡献时使事情变得简单，我们把这个面输入对误差贡献为零的面的列表中。
*


* @code
           if (cell->face(face_no)->at_boundary())
             {
               face_integrals[cell->face(face_no)] = 0;
               continue;
             }
* 
 @endcode
*
* 接下来，请注意，由于我们想在每个面上只计算一次跳跃项，尽管我们访问它两次（如果它不在边界），我们必须定义一些规则，由谁负责在一个面上计算。
* 首先，如果相邻的单元格与这个单元格在同一层次上，也就是说，既不进一步细化，也不进一步粗化，那么这个层次中索引较低的单元格就负责计算。换句话说：如果另一个单元的指数较低，那么就跳过这个面的工作。
*


* @code
           if ((cell->neighbor(face_no)->has_children() == false) &&
               (cell->neighbor(face_no)->level() == cell->level()) &&
               (cell->neighbor(face_no)->index() < cell->index()))
             continue;
* 
 @endcode
*
* 同样，我们总是从较粗的单元开始工作，如果这个单元和它的邻居在细化程度上有所不同。因此，如果相邻的单元比现在的单元细化程度低，那么就什么都不做，因为我们在访问粗略的单元时对子表面进行整合。
*


* @code
           if (cell->at_boundary(face_no) == false)
             if (cell->neighbor(face_no)->level() < cell->level())
               continue;
* 
 
 @endcode

* 现在我们知道，我们在这里负责，所以实际上是计算面的跳跃项。如果这个面是一个规则的面，即另一边的单元格既不比这个单元格粗也不比这个单元格细，那么就调用一个函数，如果另一边的单元格进一步细化，那么就用另一个函数。请注意，另一边的单元格更粗的情况不可能发生，因为我们在上面已经决定，当我们传递到另一个单元格时，我们会处理这种情况。
*


* @code
           if (cell->face(face_no)->has_children() == false)
             integrate_over_regular_face(cell,
                                         face_no,
                                         scratch_data.primal_solution,
                                         scratch_data.dual_weights,
                                         scratch_data.face_data,
                                         face_integrals);
           else
             integrate_over_irregular_face(cell,
                                           face_no,
                                           scratch_data.primal_solution,
                                           scratch_data.dual_weights,
                                           scratch_data.face_data,
                                           face_integrals);
         }
     }
* 
 
 @endcode
*
* <a name="Computingcelltermerrorcontributions"></a> <h4>Computing cell term error contributions</h4>。


*
*至于误差贡献的实际计算，首先转向单元项。
*


* @code
     template <int dim>
     void WeightedResidual<dim>::integrate_over_cell(
       const active_cell_iterator &cell,
       const Vector<double> &      primal_solution,
       const Vector<double> &      dual_weights,
       CellData &                  cell_data,
       Vector<float> &             error_indicators) const
     {
 @endcode
*
* 需要完成的任务是看了误差估计公式后似乎很自然的事情：首先得到单元残差的正交点上的数值解的右手边和拉普拉斯。
*


* @code
       cell_data.fe_values.reinit(cell);
       cell_data.right_hand_side->value_list(
         cell_data.fe_values.get_quadrature_points(), cell_data.rhs_values);
       cell_data.fe_values.get_function_laplacians(primal_solution,
                                                   cell_data.cell_laplacians);
* 
 @endcode

* ......然后得到双重权重......
*


* @code
       cell_data.fe_values.get_function_values(dual_weights,
                                               cell_data.dual_weights);
* 
 @endcode
*
* ...最后建立所有正交点的总和，并将其与当前单元格一起存储。
*


* @code
       double sum = 0;
       for (unsigned int p = 0; p < cell_data.fe_values.n_quadrature_points; ++p)
         sum += ((cell_data.rhs_values[p] + cell_data.cell_laplacians[p])
                 cell_data.dual_weights[p] cell_data.fe_values.JxW(p));
       error_indicators(cell->active_cell_index()) += sum;
     }
* 
 
 @endcode
*
* <a name="Computingedgetermerrorcontributions1"></a> <h4>Computing edge term error contributions
* 
-- 1</h4>。


*
* 另一方面，误差估计的边缘项的计算并不那么简单。首先，我们必须区分有悬挂节点和无悬挂节点的面。因为它是简单的情况，我们首先考虑一个面上没有悬挂节点的情况（我们称之为 "常规 "情况）。
*


* @code
     template <int dim>
     void WeightedResidual<dim>::integrate_over_regular_face(
       const active_cell_iterator &cell,
       const unsigned int          face_no,
       const Vector<double> &      primal_solution,
       const Vector<double> &      dual_weights,
       FaceData &                  face_data,
       FaceIntegrals &             face_integrals) const
     {
       const unsigned int n_q_points =
         face_data.fe_face_values_cell.n_quadrature_points;
* 
 @endcode
*
* 第一步是获取本单元上有限元场的正交点的梯度值。为此，初始化 <code>FEFaceValues</code> 对象，对应于面的这一面，并使用该对象提取梯度。
*


* @code
       face_data.fe_face_values_cell.reinit(cell, face_no);
       face_data.fe_face_values_cell.get_function_gradients(
         primal_solution, face_data.cell_grads);
* 
 @endcode
*
* 第二步是提取面的另一边的正交点上的有限元解的梯度，即从邻近的单元中提取。       
* 为此，在之前做一个理智的检查：确保邻居确实存在（是的，如果邻居不存在，我们就不应该来这里，但是在复杂的软件中会有bug，所以最好检查一下），如果不是这样就会出现错误。
*


* @code
       Assert(cell->neighbor(face_no).state() == IteratorState::valid,
              ExcInternalError());
 @endcode
*
* 如果我们有了这个，那么我们需要找出相邻单元格的哪一个面，即 <code>how-many'th</code> 本单元格是本面后面的单元格的邻居。为此，有一个函数，我们将结果放入一个变量，名称为 <code>neighbor_neighbor</code>  。
*


* @code
       const unsigned int neighbor_neighbor =
         cell->neighbor_of_neighbor(face_no);
 @endcode
*
* 然后为邻近的单元格定义一个缩写，在该单元格上初始化 <code>FEFaceValues</code> 对象，并提取该单元格上的梯度。
*


* @code
       const active_cell_iterator neighbor = cell->neighbor(face_no);
       face_data.fe_face_values_neighbor.reinit(neighbor, neighbor_neighbor);
       face_data.fe_face_values_neighbor.get_function_gradients(
         primal_solution, face_data.neighbor_grads);
* 
 @endcode
*
* 现在我们有了这个单元和邻近单元的梯度，通过将梯度的跳跃与法向量相乘来计算跳跃的残差。
*


* @code
       for (unsigned int p = 0; p < n_q_points; ++p)
         face_data.jump_residual[p] =
           ((face_data.cell_grads[p]
* 
- face_data.neighbor_grads[p])
            face_data.fe_face_values_cell.normal_vector(p));
* 
 @endcode
*
* 接下来得到这个面的双重权重。
*


* @code
       face_data.fe_face_values_cell.get_function_values(dual_weights,
                                                         face_data.dual_weights);
* 
 @endcode
*
* 最后，我们要计算跳跃残差、对偶权重和正交权重的总和，以得到这个面的结果。
*


* @code
       double face_integral = 0;
       for (unsigned int p = 0; p < n_q_points; ++p)
         face_integral +=
           (face_data.jump_residual[p] face_data.dual_weights[p]
            face_data.fe_face_values_cell.JxW(p));
* 
 @endcode
*
* 仔细检查该元素是否已经存在，是否已经被写入...
*


* @code
       Assert(face_integrals.find(cell->face(face_no)) != face_integrals.end(),
              ExcInternalError());
       Assert(face_integrals[cell->face(face_no)] ==
* 
-1e20, ExcInternalError());
* 
 @endcode
*
* ...然后将计算值存储在指定的位置。请注意，存储的值并不包含错误表示中出现的因子1/2。原因是，如果我们在三角形的所有面上进行循环，这个项实际上没有这个因子，但只有当我们把它写成所有单元和每个单元的所有面的总和时才会出现；因此我们两次访问同一个面。我们通过使用这个因子来考虑到这一点
*
* - /2以后，当我们对每个单元的贡献进行单独求和时，就会考虑到这一点。
*


* @code
       face_integrals[cell->face(face_no)] = face_integral;
     }
* 
 
 @endcode
*
* <a name="Computingedgetermerrorcontributions2"></a> <h4>Computing edge term error contributions
* 
-- 2</h4>。



* 我们仍然缺少有悬空节点的面的情况。这就是这个函数中所涉及的内容。
*


* @code
     template <int dim>
     void WeightedResidual<dim>::integrate_over_irregular_face(
       const active_cell_iterator &cell,
       const unsigned int          face_no,
       const Vector<double> &      primal_solution,
       const Vector<double> &      dual_weights,
       FaceData &                  face_data,
       FaceIntegrals &             face_integrals) const
     {
 @endcode
*
* 首先还是两个缩写，以及一些一致性检查，以确定该函数是否只在它应该被调用的面上被调用。
*


* @code
       const unsigned int n_q_points =
         face_data.fe_face_values_cell.n_quadrature_points;
* 
       const typename DoFHandler<dim>::face_iterator face = cell->face(face_no);
       const typename DoFHandler<dim>::cell_iterator neighbor =
         cell->neighbor(face_no);
       Assert(neighbor.state() == IteratorState::valid, ExcInternalError());
       Assert(neighbor->has_children(), ExcInternalError());
       (void)neighbor;
* 
 @endcode

* 然后找出本单元是相邻单元的哪个邻居。注意，我们将对这个相邻单元的子女进行操作，但他们的方向与他们的母亲相同，也就是说，邻居的方向是相同的。
*


* @code
       const unsigned int neighbor_neighbor =
         cell->neighbor_of_neighbor(face_no);
* 
 @endcode
*
* 然后简单地做我们在前面的函数中为一个面所做的一切，现在为所有的子面。
*


* @code
       for (unsigned int subface_no = 0; subface_no < face->n_children();
            ++subface_no)
         {
 @endcode
*
* 再从一些检查开始：得到一个指向当前子面后面的单元格的迭代器，并检查其面是否是我们所考虑的子面。如果不是这样，那么上面调用的 <code>neighbor_neighbor</code> 函数就会有错误，或者是
*
* - 更糟糕
*


*
* - 库中的某些函数没有遵守关于单元格、它们的孩子和它们的面的一些基本假设。在任何情况下，尽管这个断言不应该被触发，但谨慎一点也无妨，在优化模式的计算中，这个断言还是会被删除。
*


* @code
           const active_cell_iterator neighbor_child =
             cell->neighbor_child_on_subface(face_no, subface_no);
           Assert(neighbor_child->face(neighbor_neighbor) ==
                    cell->face(face_no)->child(subface_no),
                  ExcInternalError());
* 
 @endcode
*
* 现在开始工作，首先在界面的这一侧再次得到解决方案的梯度。
*


* @code
           face_data.fe_subface_values_cell.reinit(cell, face_no, subface_no);
           face_data.fe_subface_values_cell.get_function_gradients(
             primal_solution, face_data.cell_grads);
 @endcode
*
*然后在另一边。
*


* @code
           face_data.fe_face_values_neighbor.reinit(neighbor_child,
                                                    neighbor_neighbor);
           face_data.fe_face_values_neighbor.get_function_gradients(
             primal_solution, face_data.neighbor_grads);
* 
 @endcode
*
*，最后建立跳跃残差。由于这次我们从另一个单元格中取法向量，所以与另一个函数相比，还原了第一项的符号。
*


* @code
           for (unsigned int p = 0; p < n_q_points; ++p)
             face_data.jump_residual[p] =
               ((face_data.neighbor_grads[p]
* 
- face_data.cell_grads[p])
                face_data.fe_face_values_neighbor.normal_vector(p));
* 
 @endcode

* 然后得到双重权重。
*


* @code
           face_data.fe_face_values_neighbor.get_function_values(
             dual_weights, face_data.dual_weights);
* 
 @endcode

* 最后，总结这个子面的贡献，并将其设置在全局图中。
*


* @code
           double face_integral = 0;
           for (unsigned int p = 0; p < n_q_points; ++p)
             face_integral +=
               (face_data.jump_residual[p] face_data.dual_weights[p]
                face_data.fe_face_values_neighbor.JxW(p));
           face_integrals[neighbor_child->face(neighbor_neighbor)] =
             face_integral;
         }
* 
 @endcode
*
* 一旦所有子面的贡献被计算出来，就循环收集所有子面，并将它们与母面一起存储起来，以便以后收集单元格的误差项时简单使用。再次进行安全检查，确保子面的条目已经被计算出来，并且不带有无效的值。
*


* @code
       double sum = 0;
       for (unsigned int subface_no = 0; subface_no < face->n_children();
            ++subface_no)
         {
           Assert(face_integrals.find(face->child(subface_no)) !=
                    face_integrals.end(),
                  ExcInternalError());
           Assert(face_integrals[face->child(subface_no)] !=
* 
-1e20,
                  ExcInternalError());
* 
           sum += face_integrals[face->child(subface_no)];
         }
 @endcode
*
* 最后将该值与父脸一起存储。
*


* @code
       face_integrals[face] = sum;
     }
* 
   } // namespace LaplaceSolver
* 
 
 @endcode
*
* <a name="Asimulationframework"></a> <h3>A simulation framework</h3>。


*
* 在前面的例子程序中，我们有两个函数，用来驱动在随后的更细的网格上求解的过程。我们在这里进行了扩展，允许向这些函数传递一些参数，并将这些参数全部放入框架类。   
* 你会注意到，这个程序是由许多小部分组成的（评估函数、实现各种细化方法的求解器类、不同的对偶函数、不同的问题和数据描述），这使得程序的扩展相对简单，但也允许通过用一个部分替换另一个部分来解决大量不同的问题。我们通过在下面的框架类中声明一个结构来反映这种灵活性，该结构持有一些参数，可以设置这些参数来测试这个程序的各个部分的组合，并且可以用简单的方法在各种问题和离散度上进行测试。
*


* @code
   template <int dim>
   struct Framework
   {
   public:
 @endcode
*
* 首先，我们声明两个缩写，用于简单使用各自的数据类型。
*


* @code
     using Evaluator     = Evaluation::EvaluationBase<dim>;
     using EvaluatorList = std::list<Evaluator>;
* 
 
 @endcode

* 然后我们有一个结构，它声明了所有可能被设置的参数。在该结构的默认构造函数中，这些值都被设置为默认值，以供简单使用。
*


* @code
     struct ProblemDescription
     {
 @endcode
*
* 首先，允许输入分片多项式的度数，原始问题和对偶问题将被离散化。对于原始问题，它们默认为（双，三）线性分解函数，对于对偶问题，默认为（双，三）二次函数。如果选择了一个不需要解决对偶问题的细化准则，对偶有限元度的值当然会被忽略。
*


* @code
       unsigned int primal_fe_degree;
       unsigned int dual_fe_degree;
* 
 @endcode
*
* 然后有一个描述问题类型的对象，即右手边、领域、边界值等。这里需要的指针默认为Null指针，也就是说，你必须在这个对象的实际实例中设置它，才能使它发挥作用。
*


* @code
       std::unique_ptr<const Data::SetUpBase<dim>> data;
* 
 @endcode
*
* 因为我们允许使用不同的细化标准（全局细化，通过凯利误差指标细化，可能有一个权重，以及使用对偶估计器），定义一些枚举值，并随后定义一个该类型的变量。它将默认为 <code>dual_weighted_error_estimator</code>  。
*


* @code
       enum RefinementCriterion
       {
         dual_weighted_error_estimator,
         global_refinement,
         kelly_indicator,
         weighted_kelly_indicator
       };
* 
       RefinementCriterion refinement_criterion;
* 
 @endcode
*
* 接下来是一个描述双重函数的对象。只有在选择双重加权残差细化时才需要它，并且默认为一个空指针。
*


* @code
       std::unique_ptr<const DualFunctional::DualFunctionalBase<dim>>
         dual_functional;
* 
 @endcode

* 然后是一个评价对象的列表。其默认值为空，即没有评价对象。
*


* @code
       EvaluatorList evaluator_list;
* 
 @endcode
*
* 接下来是一个函数，它被用作 <code>RefinementWeightedKelly</code> 类的权重。这个指针的默认值是零，但是如果你想使用 <code>weighted_kelly_indicator</code> 细化标准，你必须把它设置为其他的值。
*


* @code
       std::unique_ptr<const Function<dim>> kelly_weight;
* 
 @endcode

* 最后，我们有一个变量，表示我们允许（原始）离散化的最大自由度数。如果超过这个数值，我们将停止解算和间歇性的网格细化过程。其默认值为20,000。
*


* @code
       unsigned int max_degrees_of_freedom;
* 
 @endcode
*
* 最后是这个类的默认构造函数。
*


* @code
       ProblemDescription();
     };
* 
 @endcode
*
* 驱动程序框架类只有一个方法，它断断续续地调用求解器和网格细化，并在中间做一些其他的小任务。由于它不需要除了给它的参数之外的数据，我们把它变成静态的。
*


* @code
     static void run(const ProblemDescription &descriptor);
   };
* 
 
 @endcode
*
* 至于实现，首先是参数对象的构造函数，将所有的值设置为默认值。
*


* @code
   template <int dim>
   Framework<dim>::ProblemDescription::ProblemDescription()
     : primal_fe_degree(1)
     , dual_fe_degree(2)
     , refinement_criterion(dual_weighted_error_estimator)
     , max_degrees_of_freedom(20000)
   {}
* 
 
* 
 @endcode
*
* 然后是驱动整个过程的函数。
*


* @code
   template <int dim>
   void Framework<dim>::run(const ProblemDescription &descriptor)
   {
 @endcode
*
*首先从给定的数据对象中创建一个三角测量。
*


* @code
     Triangulation<dim> triangulation(
       Triangulation<dim>::smoothing_on_refinement);
     descriptor.data->create_coarse_grid(triangulation);
* 
 @endcode

*然后是一组有限元和适当的正交公式。
*


* @code
     const FE_Q<dim>       primal_fe(descriptor.primal_fe_degree);
     const FE_Q<dim>       dual_fe(descriptor.dual_fe_degree);
     const QGauss<dim>     quadrature(descriptor.dual_fe_degree + 1);
     const QGauss<dim
* 
- 1> face_quadrature(descriptor.dual_fe_degree + 1);
* 
 @endcode
*
* 接下来，从实现不同细化标准的类中选择一个。
*


* @code
     std::unique_ptr<LaplaceSolver::Base<dim>> solver;
     switch (descriptor.refinement_criterion)
       {
         case ProblemDescription::dual_weighted_error_estimator:
           {
             solver = std::make_unique<LaplaceSolver::WeightedResidual<dim>>(
               triangulation,
               primal_fe,
               dual_fe,
               quadrature,
               face_quadrature,
               descriptor.data->get_right_hand_side(),
               descriptor.data->get_boundary_values(),
              descriptor.dual_functional);
             break;
           }
* 
         case ProblemDescription::global_refinement:
           {
             solver = std::make_unique<LaplaceSolver::RefinementGlobal<dim>>(
               triangulation,
               primal_fe,
               quadrature,
               face_quadrature,
               descriptor.data->get_right_hand_side(),
               descriptor.data->get_boundary_values());
             break;
           }
* 
         case ProblemDescription::kelly_indicator:
           {
             solver = std::make_unique<LaplaceSolver::RefinementKelly<dim>>(
               triangulation,
               primal_fe,
               quadrature,
               face_quadrature,
               descriptor.data->get_right_hand_side(),
               descriptor.data->get_boundary_values());
             break;
           }
* 
         case ProblemDescription::weighted_kelly_indicator:
           {
             solver =
               std::make_unique<LaplaceSolver::RefinementWeightedKelly<dim>>(
                 triangulation,
                 primal_fe,
                 quadrature,
                 face_quadrature,
                 descriptor.data->get_right_hand_side(),
                 descriptor.data->get_boundary_values(),
                descriptor.kelly_weight);
             break;
           }
* 
         default:
           AssertThrow(false, ExcInternalError());
       }
* 
 @endcode
*
* 现在所有的对象都到位了，运行主循环。停止的标准在循环的底部实现。     
* 在这个循环中，首先设置新的循环数，然后解决问题，输出它的解，对它应用评估对象，然后决定我们是否要进一步细化网格并在这个网格上再次求解，或者跳出循环。
*


* @code
     for (unsigned int step = 0; true; ++step)
       {
         std::cout << "Refinement cycle: " << step << std::endl;
* 
         solver->set_refinement_cycle(step);
         solver->solve_problem();
         solver->output_solution();
* 
         std::cout << "   Number of degrees of freedom=" << solver->n_dofs()
                   << std::endl;
* 
         for (const auto &evaluator : descriptor.evaluator_list)
           {
             evaluator->set_refinement_cycle(step);
             solver->postprocess(*evaluator);
           }
* 
 
         if (solver->n_dofs() < descriptor.max_degrees_of_freedom)
           solver->refine_grid();
         else
           break;
       }
* 
 @endcode
*
* 循环运行后清理屏幕。
*


* @code
     std::cout << std::endl;
   }
* 
 } // namespace Step14
* 
 
* 
 @endcode
*
* <a name="Themainfunction"></a> <h3>The main function</h3>。


*
* 最后是主函数。它通过指定一组用于模拟的参数（多项式度数、评估和对偶函数等）来驱动整个过程，并将它们打包成一个结构传递给上面的框架工作类。
*


* @code
 int main()
 {
   try
     {
       using namespace Step14;
* 
 @endcode
*
* 在这里描述一下我们要解决的问题，将一个描述符对象传递给做其他工作的函数。
*


* @code
       const unsigned int                 dim = 2;
       Framework<dim>::ProblemDescription descriptor;
* 
 @endcode
*
* 首先设置我们希望使用的细化标准。
*


* @code
       descriptor.refinement_criterion =
         Framework<dim>::ProblemDescription::dual_weighted_error_estimator;
 @endcode
*
* 这里，我们也可以使用 <code>global_refinement</code> 或 <code>weighted_kelly_indicator</code>  。请注意，所给出的关于对偶有限元、对偶函数等信息只对给定的细化准则选择很重要，否则就会被忽略。
*

*
* 然后设置原始问题和对偶问题的多项式度数。我们在这里选择双线性和双二次方的。
*


* @code
       descriptor.primal_fe_degree = 1;
       descriptor.dual_fe_degree   = 2;
* 
 @endcode

* 然后设置测试案例的描述，即域、边界值和右手边。这些都是预先打包在类中的。我们在这里采取  <code>Exercise_2_3</code>  的描述，但你也可以使用  <code>CurvedRidges@<dim@></code>  。
*


* @code
       descriptor.data =
         std::make_unique<Data::SetUp<Data::Exercise_2_3<dim>, dim>>();
* 
 @endcode
*
* 接下来首先设置一个二元函数，然后是一个评价对象的列表。我们默认选择在一个评价点上对数值进行评价，由评价和二元函数类命名空间中的 <code>PointValueEvaluation</code> 类代表。你也可以设置 <code>PointXDerivativeEvaluation</code> 类来代替评价点的值的x-derivative。       
* 请注意，双功能和评价对象应该匹配。然而，你可以给你想要的评价函数，所以你可以在每一步之后让点值和导数都得到评价。  一个这样的附加评价是在每一步中输出网格。
*


* @code
       const Point<dim> evaluation_point(0.75, 0.75);
       descriptor.dual_functional =
         std::make_unique<DualFunctional::PointValueEvaluation<dim>>(
           evaluation_point);
* 
       Evaluation::PointValueEvaluation<dim> postprocessor1(evaluation_point);
       Evaluation::GridOutput<dim>           postprocessor2("grid");
* 
       descriptor.evaluator_list.push_back(&postprocessor1);
       descriptor.evaluator_list.push_back(&postprocessor2);
* 
 @endcode
*
* 设置最大的自由度数，之后我们希望程序停止进一步细化网格。
*


* @code
       descriptor.max_degrees_of_freedom = 20000;
* 
 @endcode
*
* 最后将描述符对象传递给一个函数，用它来运行整个解决方案。
*


* @code
       Framework<dim>::run(descriptor);
     }
* 
 @endcode
*
* 捕获异常以提供有关失败的信息。
*


* @code
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
* 
   return 0;
 }
 @endcode
* <a name="Results"></a><h1>Results</h1> 。


*<a name="Pointvalues"></a><h3>Point values</h3> 。



* 这个程序提供了大量的可能性来玩。因此，我们只能展示所有可能的结果中的一小部分，在这个程序的帮助下可以获得。然而，我们鼓励你通过改变主程序中的设置来尝试。在这里，我们先简单地让它运行，不做任何修改。
* @code
Refinement cycle: 0
   Number of degrees of freedom=72
   Point value=0.03243
   Estimated error=0.000702385
Refinement cycle: 1
   Number of degrees of freedom=67
   Point value=0.0324827
   Estimated error=0.000888953
Refinement cycle: 2
   Number of degrees of freedom=130
   Point value=0.0329619
   Estimated error=0.000454606
Refinement cycle: 3
   Number of degrees of freedom=307
   Point value=0.0331934
   Estimated error=0.000241254
Refinement cycle: 4
   Number of degrees of freedom=718
   Point value=0.0333675
   Estimated error=7.4912e-05
Refinement cycle: 5
   Number of degrees of freedom=1665
   Point value=0.0334083
   Estimated error=3.69111e-05
Refinement cycle: 6
   Number of degrees of freedom=3975
   Point value=0.033431
   Estimated error=1.54218e-05
Refinement cycle: 7
   Number of degrees of freedom=8934
   Point value=0.0334406
   Estimated error=6.28359e-06
Refinement cycle: 8
   Number of degrees of freedom=21799
   Point value=0.0334444
@endcode

*

*首先让我们看看这个程序的实际计算结果。在第七个网格上，原始和双重数值解看起来是这样的（使用的颜色方案旨在唤起科罗拉多州白雪皑皑的山峰，这个程序的原作者现在称它为家）。 <table align="center">
  <tr>
    <td width="50%">
      <img src="https://www.dealii.org/images/steps/developer/step-14.point-value.solution-7.9.2.png" alt="">
    </td>
    <td width="50%">
      <img src="https://www.dealii.org/images/steps/developer/step-14.point-value.solution-7-dual.9.2.png" alt="">
    </td>
  </tr>
</table> 显然，左下角的区域对于右上角的点值评估是如此不重要，以至于网格在那里完全没有被细化，尽管解决方案在该单元的内角有奇异点由于右手边和领域的对称性，解决方案实际上应该像右上角的所有四个角一样，但是涉及到对偶解决方案的网格细化标准选择了不同的细化方式
*
* - 因为我们说过，我们真正关心的只是右上方某处的一个函数值。
*

*
* 下面是一些在细化周期0,2,4（顶行）和5,7,8（底行）产生的网格。
*  <table width="80%" align="center">
  <tr>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-value.grid-0.9.2.png" alt="" width="100%"></td>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-value.grid-2.9.2.png" alt="" width="100%"></td>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-value.grid-4.9.2.png" alt="" width="100%"></td>
  </tr>
  <tr>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-value.grid-5.9.2.png" alt="" width="100%"></td>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-value.grid-7.9.2.png" alt="" width="100%"></td>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-value.grid-8.9.2.png" alt="" width="100%"></td>
  </tr>
</table> 
* 注意解决角部奇异点和解决评估点周围的微妙的相互作用。手工生成这样的网格将是相当困难的，因为这将涉及到定量地判断四个角奇点中的哪一个应该被解决，并设置与评估点附近的权重。
*

*
*程序打印出这个数量的点值和估计误差。通过推断，我们可以猜测精确的数值是接近0.0334473，正负0.0000001（注意，我们从只有22000（原始）自由度中得到几乎6个有效数字。这个数字不能单独从函数的值中得到，但我使用了一个假设，即误差估计器大部分是精确的，并将计算值与估计的误差进行推算，以得到真实值的近似值。用更多自由度的计算表明，这个假设确实是有效的。
*

*
* 从计算结果中，我们可以生成两个图表：一个显示点值中误差 $J(u)-J(u_h)$ （将外推值视为正确）的收敛性，以及我们将计算值 $J(u_h)$ 和估计误差eta相加得到的值（如果误差估计器 $eta$ 是精确的，那么值 $J(u_h)+\eta$ 将等于精确的点值，这个量的误差将始终为零；但是，由于误差估计器只是一个
*
* - 好
*
* - 对真实误差的近似值，我们只能通过这个方法来减少误差的大小）。)在这张图中，我们还指出了复杂度 ${\cal O}(1/N)$ ，以表明在这种情况下，网格细化器是最优的。第二张图比较了真实误差和估计误差，显示两者实际上非常接近，即使对于点值这样一个复杂的量。
*

*  <table width="80%" align="center">
  <tr>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-value.error.png" alt="" width="100%"></td>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-value.error-estimation.png" alt="" width="100%"></td>
  </tr>
</table> 


*<a name="Comparingrefinementcriteria"></a><h3>Comparing refinement criteria</h3>


*
* 由于我们在使用由对偶加权误差估计器驱动的网格细化时接受了相当多的努力（用于解决对偶问题，以及评估误差表示），因此值得询问这种努力是否成功。为此，我们首先比较了不同网格细化标准下的误差水平。要产生这些数据，只需改变主程序中网格细化准则变量的值。结果如下（对于Kelly指标中的权重，我们选择了函数 $1/(r^2+0.1^2)$ ，其中 $r$ 是到评估点的距离；可以证明，如果我们忽略边界的影响，这是最佳的权重）。
*  <img src="https://www.dealii.org/images/steps/developer/step-14.point-value.error-comparison.png" alt=""> 
*

*
* 检查这些数字，我们看到对于全局细化，误差与 $O(1/(sqrt(N) log(N)))$ 成正比，而对于双重估计器 $O(1/N)$ 。一般来说，我们看到双重加权误差估计器比其他细化指标更好，至少在与那些具有类似规则行为的指标相比时是如此。凯利指标产生的误差较小，但在画面上的跳动相当不规则，误差的符号有时也会改变。因此，它的行为不允许将结果外推到更大的N值。此外，如果信任双重加权误差估计器的误差估计，可以通过将估计的误差加入计算值来改进结果。就可靠性而言，加权估计器因此比凯利指标更好，尽管后者有时会产生更小的误差。
*


*<a name="Evaluationofpointstresses"></a><h3>Evaluation of point stresses</h3>


*
* 除了评估某一点上的解的值之外，该程序还提供了评估某一点上的X-导数的可能性，并且还可以为此定制网格细化。要让程序计算这些数量，只需将主函数中出现的两个 <code>PointValueEvaluation</code> 替换为 <code>PointXDerivativeEvaluation</code> ，然后让程序运行。
* @code
Refinement cycle: 0
   Number of degrees of freedom=72
   Point x-derivative=-0.0719397
   Estimated error=-0.0126173
Refinement cycle: 1
   Number of degrees of freedom=61
   Point x-derivative=-0.0707956
   Estimated error=-0.00774316
Refinement cycle: 2
   Number of degrees of freedom=131
   Point x-derivative=-0.0568671
   Estimated error=-0.00313426
Refinement cycle: 3
   Number of degrees of freedom=247
   Point x-derivative=-0.053033
   Estimated error=-0.00136114
Refinement cycle: 4
   Number of degrees of freedom=532
   Point x-derivative=-0.0526429
   Estimated error=-0.000558868
Refinement cycle: 5
   Number of degrees of freedom=1267
   Point x-derivative=-0.0526955
   Estimated error=-0.000220116
Refinement cycle: 6
   Number of degrees of freedom=2864
   Point x-derivative=-0.0527495
   Estimated error=-9.46731e-05
Refinement cycle: 7
   Number of degrees of freedom=6409
   Point x-derivative=-0.052785
   Estimated error=-4.21543e-05
Refinement cycle: 8
   Number of degrees of freedom=14183
   Point x-derivative=-0.0528028
   Estimated error=-2.04241e-05
Refinement cycle: 9
   Number of degrees of freedom=29902
   Point x-derivative=-0.052814
@endcode
*
*

*
* 解决方案看起来与以前大致相同（确切的解决方案当然是 <em> 是 </em> 相同，只是网格发生了一些变化），但现在的双解是不同的。评估点周围的特写显示了这一点。 <table align="center">
  <tr>
    <td width="50%">
      <img src="https://www.dealii.org/images/steps/developer/step-14.point-derivative.solution-7-dual.png" alt="">
    </td>
    <td width="50%">
      <img src="https://www.dealii.org/images/steps/developer/step-14.point-derivative.solution-7-dual-close-up.png" alt="">
    </td>
</table>  这一次，细化周期0、5、6、7、8和9的网格看起来像这样。
*  <table align="center" width="80%">
  <tr>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-derivative.grid-0.9.2.png" alt="" width="100%"></td>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-derivative.grid-5.9.2.png" alt="" width="100%"></td>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-derivative.grid-6.9.2.png" alt="" width="100%"></td>
  </tr>
  <tr>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-derivative.grid-7.9.2.png" alt="" width="100%"></td>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-derivative.grid-8.9.2.png" alt="" width="100%"></td>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-derivative.grid-9.9.2.png" alt="" width="100%"></td>
  </tr>
</table> 
* 注意与我们在点评估中获得的网格相比，这些网格是不对称的。这是由于域和初解可能是围绕对角线对称的，但 $x$ 的导数不是，后者进入了细化准则。
*

*
* 然后，将感兴趣的数量的实际计算值（即解决方案在某一点上的X衍生物）与一个参考值进行比较是很有趣的。
*
* - .0528223...正负0.0000005。我们通过在更细的网格上计算得到这个参考值，大约有13万个单元。回顾一下，如果在最佳情况下，误差是 $O(1/N)$ ，采用多十倍的单元网格，我们的结果就多了一个数字。
*

*
*在下图的左边部分，你再次看到了误差向这个外推值的收敛，而在右边你看到了真实和估计误差的比较。
*  <table width="80%" align="center">
  <tr>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-derivative.error.png" alt="" width="100%"></td>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.point-derivative.error-estimation.png" alt="" width="100%"></td>
  </tr>
</table> 
* 在初始阶段，真实误差改变了它的符号，估计误差再次与它相当匹配。还请注意，当使用估计误差来修正 $J(u_h)$ 的计算值时，误差有了很大的改善。
*


*<a name="step13revisited"></a><h3>step-13 revisited</h3>。


*
* 如果我们不选择 <code>Exercise_2_3</code> 的数据集，而是在主函数中选择 <code>CurvedRidges</code> ，并选择 $(0.5,0.5)$ 作为评估点，那么我们就可以重新进行前面例子程序的计算，以比较在双重加权误差估计器的帮助下获得的结果是否比我们之前的结果更好。
*

*
* 首先，经过9个自适应细化周期后，分别用点评估和导数评估细化标准得到的网格，看起来像这样。
*  <table width="80%" align="center">
  <tr>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.step-13.point-value.png" alt="" width="100%"></td>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.step-13.point-derivative.png" alt="" width="100%"></td>
  </tr>
</table> 
* 在网格中仍然可以看到解的特征，但是由于解是光滑的，对偶解的奇异性完全支配了网格细化准则，并导致强烈集中的网格。第七次细化步骤后的解看起来像下面这样。
*  <table width="40%" align="center">
  <tr>
    <td><img src="https://www.dealii.org/images/steps/developer/step-14.step-13.solution-7.9.2.png" alt="" width="100%"></td>
  </tr>
</table> 
* 显然，在某些地方的解更差，但是网格细化过程中应该注意到这些地方对计算点值并不重要。
*


*

* 下一步是将新的（基于二元性的）网格细化标准与旧的进行比较。这些是结果。
*  <img src="https://www.dealii.org/images/steps/developer/step-14.step-13.error-comparison.png" alt=""> 
*

*
* 结果是，嗯，有点混合。首先，Kelly指示器因其不稳定的行为而不合格，多次改变了误差的符号，并且在网格细化下的误差越来越大。双重加权误差估计器的误差呈单调下降，比加权凯利和全局精简要好，但幅度没有预期的那么大。这是因为全局细化可以利用评估点周围网格的规则结构，这导致了点误差的更好收敛顺序。然而，如果我们的网格不是局部矩形的，例如因为我们必须接近弯曲的边界，或者如果系数不是恒定的，那么全局细化网格的这种优势就会消失，而基于对偶性的估计器的良好性能就会保持。
*


*

*<a name="Conclusionsandoutlook"></a><h3>Conclusions and outlook</h3> 。


*
* 这里的结果并没有太清楚地表明加权误差估计方法在网格细化方面比其他网格细化标准（如Kelly指标）的优越性。这是由于所显示的应用相对简单。如果你还不相信这种方法确实有优势，请你浏览一下引言中提到的文献，其中提供了大量的例子，双加权方法可以将必要的数值工作减少几个数量级，使之成为计算某些数量的合理精度的唯一方法。
*

*
* 除了你可能提出的反对其作为网格细化标准的反对意见外，考虑到对一个人可能想要计算的量的误差的准确认识是非常有用的，因为我们可以在对精度满意时停止计算。使用更传统的方法，很难得到任意量的精确估计，也许除了能量规范的误差，我们将不能保证我们计算的结果满足对其精度的任何要求。另外，正如对点值和导数的评价所显示的那样，误差估计可以用来推断结果，从而在我们想知道的数量上产生更高的精度。
*

*
* 抛开这些数学上的考虑，我们试图以模块化的方式来编写程序，这样，实现另一个测试案例，或另一个评估和双重功能就很简单。我们鼓励你把这个程序作为你自己实验的基础，并稍加发挥。
*

* <a name="PlainProg"></a><h1> The plain program</h1>  @include "step-14.cc"  。
* */


