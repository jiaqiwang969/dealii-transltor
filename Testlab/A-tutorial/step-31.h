//include/deal.II-translator/A-tutorial/step-31_0.txt
/**
  @page step_31 The step-31 tutorial program  
* 本教程依赖于  step-22  。
* @htmlonly
<table class="tutorial" width="50%">
<tr><th colspan="2"><b><small>Table of contents</small></b><b><small>Table of contents</small></b></th></tr>
<tr><td width="50%" valign="top">
<ol>
  <li> <a href="#Intro" class=bold>Introduction</a><a href="#Intro" class=bold>Introduction</a>
    <ul>
        <li><a href="#TheBoussinesqequations">The Boussinesq equations</a><a href="#TheBoussinesqequations">The Boussinesq equations</a>
        <li><a href="#Boundaryandinitialconditions">Boundary and initial conditions</a><a href="#Boundaryandinitialconditions">Boundary and initial conditions</a>
        <li><a href="#Solutionapproach">Solution approach</a><a href="#Solutionapproach">Solution approach</a>
      <ul>
        <li><a href="#Timestepping">Time stepping</a><a href="#Timestepping">Time stepping</a>
        <li><a href="#WeakformandspacediscretizationfortheStokespart">Weak form and space discretization for the Stokes part</a><a href="#WeakformandspacediscretizationfortheStokespart">Weak form and space discretization for the Stokes part</a>
        <li><a href="#Stabilizationweakformandspacediscretizationforthetemperatureequation">Stabilization, weak form and space discretization for the temperature equation</a><a href="#Stabilizationweakformandspacediscretizationforthetemperatureequation">Stabilization, weak form and space discretization for the temperature equation</a>
        <li><a href="#Linearsolvers">Linear solvers</a><a href="#Linearsolvers">Linear solvers</a>
      <ul>
        <li><a href="#LinearsolversfortheStokesproblem">Linear solvers for the Stokes problem</a><a href="#LinearsolversfortheStokesproblem">Linear solvers for the Stokes problem</a>
        <li><a href="#Linearsolversforthetemperatureequation">Linear solvers for the temperature equation</a><a href="#Linearsolversforthetemperatureequation">Linear solvers for the temperature equation</a>
      </ul>
      </ul>
        <li><a href="#Implementationdetails">Implementation details</a><a href="#Implementationdetails">Implementation details</a>
      <ul>
        <li><a href="#UsingdifferentDoFHandlerobjects">Using different DoFHandler objects</a><a href="#UsingdifferentDoFHandlerobjects">Using different DoFHandler objects</a>
        <li><a href="#UsingTrilinos">Using Trilinos</a><a href="#UsingTrilinos">Using Trilinos</a>
      </ul>
        <li><a href="#Thetestcase">The testcase</a><a href="#Thetestcase">The testcase</a>
    </ul>
  <li> <a href="#CommProg" class=bold>The commented program</a><a href="#CommProg" class=bold>The commented program</a>
    <ul>
        <li><a href="#Includefiles">Include files</a><a href="#Includefiles">Include files</a>
        <li><a href="#Equationdata">Equation data</a><a href="#Equationdata">Equation data</a>
        <li><a href="#Linearsolversandpreconditioners">Linear solvers and preconditioners</a><a href="#Linearsolversandpreconditioners">Linear solvers and preconditioners</a>
      <ul>
        <li><a href="#ThecodeInverseMatrixcodeclasstemplate">The <code>InverseMatrix</code> class template</a><a href="#ThecodeInverseMatrixcodeclasstemplate">The <code>InverseMatrix</code> class template</a>
        <li><a href="#Schurcomplementpreconditioner">Schur complement preconditioner</a><a href="#Schurcomplementpreconditioner">Schur complement preconditioner</a>
      </ul>
        <li><a href="#ThecodeBoussinesqFlowProblemcodeclasstemplate">The <code>BoussinesqFlowProblem</code> class template</a><a href="#ThecodeBoussinesqFlowProblemcodeclasstemplate">The <code>BoussinesqFlowProblem</code> class template</a>
        <li><a href="#BoussinesqFlowProblemclassimplementation">BoussinesqFlowProblem class implementation</a><a href="#BoussinesqFlowProblemclassimplementation">BoussinesqFlowProblem class implementation</a>
      <ul>
        <li><a href="#BoussinesqFlowProblemBoussinesqFlowProblem">BoussinesqFlowProblem::BoussinesqFlowProblem</a><a href="#BoussinesqFlowProblemBoussinesqFlowProblem">BoussinesqFlowProblem::BoussinesqFlowProblem</a>
        <li><a href="#BoussinesqFlowProblemget_maximal_velocity">BoussinesqFlowProblem::get_maximal_velocity</a><a href="#BoussinesqFlowProblemget_maximal_velocity">BoussinesqFlowProblem::get_maximal_velocity</a>
        <li><a href="#BoussinesqFlowProblemget_extrapolated_temperature_range">BoussinesqFlowProblem::get_extrapolated_temperature_range</a> ]<a href="#BoussinesqFlowProblemget_extrapolated_temperature_range">BoussinesqFlowProblem::get_extrapolated_temperature_range</a>
        <li><a href="#BoussinesqFlowProblemcompute_viscosity">BoussinesqFlowProblem::compute_viscosity</a><a href="#BoussinesqFlowProblemcompute_viscosity">BoussinesqFlowProblem::compute_viscosity</a>
        <li><a href="#BoussinesqFlowProblemsetup_dofs">BoussinesqFlowProblem::setup_dofs</a><a href="#BoussinesqFlowProblemsetup_dofs">BoussinesqFlowProblem::setup_dofs</a>
        <li><a href="#BoussinesqFlowProblemassemble_stokes_preconditioner">BoussinesqFlowProblem::assemble_stokes_preconditioner</a><a href="#BoussinesqFlowProblemassemble_stokes_preconditioner">BoussinesqFlowProblem::assemble_stokes_preconditioner</a>
        <li><a href="#BoussinesqFlowProblembuild_stokes_preconditioner">BoussinesqFlowProblem::build_stokes_preconditioner</a><a href="#BoussinesqFlowProblembuild_stokes_preconditioner">BoussinesqFlowProblem::build_stokes_preconditioner</a>
        <li><a href="#BoussinesqFlowProblemassemble_stokes_system">BoussinesqFlowProblem::assemble_stokes_system</a><a href="#BoussinesqFlowProblemassemble_stokes_system">BoussinesqFlowProblem::assemble_stokes_system</a>
        <li><a href="#BoussinesqFlowProblemassemble_temperature_matrix">BoussinesqFlowProblem::assemble_temperature_matrix</a><a href="#BoussinesqFlowProblemassemble_temperature_matrix">BoussinesqFlowProblem::assemble_temperature_matrix</a>
        <li><a href="#BoussinesqFlowProblemassemble_temperature_system">BoussinesqFlowProblem::assemble_temperature_system</a><a href="#BoussinesqFlowProblemassemble_temperature_system">BoussinesqFlowProblem::assemble_temperature_system</a>
        <li><a href="#BoussinesqFlowProblemsolve">BoussinesqFlowProblem::solve</a><a href="#BoussinesqFlowProblemsolve">BoussinesqFlowProblem::solve</a>
        <li><a href="#BoussinesqFlowProblemoutput_results">BoussinesqFlowProblem::output_results</a><a href="#BoussinesqFlowProblemoutput_results">BoussinesqFlowProblem::output_results</a>
        <li><a href="#BoussinesqFlowProblemrefine_mesh">BoussinesqFlowProblem::refine_mesh</a><a href="#BoussinesqFlowProblemrefine_mesh">BoussinesqFlowProblem::refine_mesh</a>
        <li><a href="#BoussinesqFlowProblemrun">BoussinesqFlowProblem::run</a><a href="#BoussinesqFlowProblemrun">BoussinesqFlowProblem::run</a>
      </ul>
        <li><a href="#Thecodemaincodefunction">The <code>main</code> function</a> ]<a href="#Thecodemaincodefunction">The <code>main</code> function</a>
      </ul>
</ol></td><td width="50%" valign="top"><ol>
  <li value="3"> <a href="#Results" class=bold>Results</a><a href="#Results" class=bold>Results</a>
    <ul>
        <li><a href="#Resultsin2d"> Results in 2d </a><a href="#Resultsin2d"> Results in 2d </a>
        <li><a href="#Resultsin3d"> Results in 3d </a><a href="#Resultsin3d"> Results in 3d </a>
        <li><a href="#Numericalexperimentstodetermineoptimalparameters"> Numerical experiments to determine optimal parameters </a><a href="#Numericalexperimentstodetermineoptimalparameters"> Numerical experiments to determine optimal parameters </a>
      <ul>
        <li><a href="#Choosingicsubksubiandbeta"> Choosing <i>c<sub>k</sub></i><a href="#Choosingicsubksubiandbeta"> Choosing <i>c<sub>k</sub></i> and beta </a><i>c<sub>k</sub></i> and beta </a>
      <ul>
        <li><a href="#ResultsforQsub1subelements">Results for Q<sub>1</sub> elements</a><a href="#ResultsforQsub1subelements">Results for Q<sub>1</sub> elements</a>
        <li><a href="#ResultsforQsub2subelements">Results for Q<sub>2</sub> elements</a><a href="#ResultsforQsub2subelements">Results for Q<sub>2</sub> elements</a>
        <li><a href="#Resultsfor3d">Results for 3d</a><a href="#Resultsfor3d">Results for 3d</a>
        <li><a href="#Conclusions">Conclusions</a><a href="#Conclusions">Conclusions</a>
      </ul>
      </ul>
        <li><a href="#Possibilitiesforextensions"> Possibilities for extensions </a><a href="#Possibilitiesforextensions"> Possibilities for extensions </a>
    </ul>
  <li> <a href="#PlainProg" class=bold>The plain program</a><a href="#PlainProg" class=bold>The plain program</a>
</ol> </td> </tr> </table>
@endhtmlonly
*  <br>  
* <i>This program was contributed by Martin Kronbichler and Wolfgang
Bangerth.
<br>
This material is based upon work partly supported by the National
Science Foundation under Award No. EAR-0426271 and The California Institute of
Technology. Any opinions, findings, and conclusions or recommendations
expressed in this publication are those of the author and do not
necessarily reflect the views of the National Science Foundation or of The
California Institute of Technology.
</i>
 

* <a name="Intro"></a><a name="Introduction"></a><h1>Introduction</h1> 。
* 

*<a name="TheBoussinesqequations"></a><h3>The Boussinesq equations</h3>
* 

* 这个程序处理一个有趣的物理问题：如果流体（即液体或气体）遇到由温差引起的浮力差异，它是如何表现的？很明显，流体中温度较高（因此较轻）的部分会上升，而温度较低（密度较大）的部分会在重力作用下下沉。
* 在流体运动缓慢到可以忽略惯性效应的情况下，描述这种行为的方程是Boussinesq方程，其内容如下：@f{eqnarray*}
* 


* 
* 


* 
* 
-\nabla \cdot (2 \eta \varepsilon ({\mathbf u})) + \nabla p &=&
* 


* 
* 


* 
* 
-\rho\; \beta \; T\; \mathbf{g},
  \\
  \nabla \cdot {\mathbf u} &=& 0,
  \\
  \frac{\partial T}{\partial t}
  +
  {\mathbf u} \cdot \nabla T
* 


* 
* 


* 
* 
-
  \nabla \cdot \kappa \nabla T &=& \gamma.
@f} 。
* 这些方程属于矢量值问题的范畴（对这一主题的概述可在 @ref vector_valued 模块中找到）。这里， $\mathbf u$ 是速度场， $p$ 是压力， $T$ 是流体的温度。  $\varepsilon ({\mathbf u}) = \frac 12
[(\nabla{\mathbf u}) + (\nabla {\mathbf u})^T]$ 是速度的对称梯度。可以看出，速度和压力解决了描述不可压缩流体运动的斯托克斯方程，这个方程我们以前在 step-22 中考虑过；我们将广泛借鉴在该程序中获得的经验，特别是关于高效线性斯托克斯求解器的经验。
* 流体运动的强制项是流体的浮力，表示为密度 $\rho$ 、热膨胀系数 $\beta$ 、温度 $T$ 和指向下方的重力矢量 $\mathbf{g}$ 的积。(在 step-32 的介绍中给出了右手边的推导。)前两个方程描述了流体如何通过运动对温差做出反应，第三个方程说明了流体运动如何影响温度场：它是一个平流扩散方程，即温度附着在流体颗粒上，在流场中平流，还有一个额外的扩散（热传导）项。在许多应用中，扩散系数相当小，温度方程实际上是传输的，而不是扩散主导的，因此在性质上更像是双曲而不是椭圆；我们在开发一个稳定的微分时必须考虑到这一点。
* 在上述方程中，右侧的 $\gamma$ 项表示热源，可能是一个空间和时间上的变化函数。  $\eta$ 和 $\kappa$ 表示粘度和扩散系数，在本教程中我们假定它们是恒定的。当 $\eta$ 取决于温度时，更普遍的情况是物理应用中的一个重要因素。大多数材料随着温度的升高而变得更加流动（即 $\eta$ 随着 $T$ 的降低而降低）；有时，如在温度接近熔点的岩石矿物的情况下， $\eta$ 可能在典型的温度范围内发生数量级的变化。
* 我们注意到，上述斯托克斯方程可以通过引入<a target="_top"
href="http://en.wikipedia.org/wiki/Rayleigh_number">Rayleigh
number</a> $\mathrm{Ra}=\frac{\|\mathbf{g}\| \beta \rho}{\eta \kappa} \delta T L^3$ 的非典型长度尺度 $L$ 、典型温差 $\delta T$ 、密度 $\rho$ 、热扩散率 $\eta$ 和热导率 $\kappa$ 进行非维化。 $\mathrm{Ra}$ 是一个无量纲数字，它描述了由温差引起的浮力变化所导致的对流的热传输和由热扩散导致的热传输的比率。一个小的瑞利数意味着浮力相对于粘度来说并不强，流体运动 $\mathbf{u}$ 足够慢，以至于热扩散 $\kappa\nabla T$ 是主要的热传输方式。另一方面，具有高雷利数的流体将显示出主导热传导的强烈对流。
* 对于我们感兴趣的计算热对流的大多数流体来说，瑞利数是非常大的，通常是 $10^6$ 或更大。从方程的结构中，我们看到这将导致大的压力差和大的速度。因此， $T$ 的对流扩散方程中的对流项也会非常大，要准确解决这个方程，就需要我们选择小的时间步长。因此，具有大雷利数的问题很难用数值来解决，原因类似于当<a
href="http://en.wikipedia.org/wiki/Reynolds_number">Reynolds number
$\mathrm{Re}$</a>很大时，解决<a
href="http://en.wikipedia.org/wiki/Navier-stokes_equations">Navier-Stokes
equations</a>很难。
* 请注意，大的瑞利数不一定涉及大的绝对密度。例如，地幔中的雷利数大于 $10^6$ 。然而，密度很小：该材料实际上是固体岩石，但它的温度和压力很高，它可以非常缓慢地流动，每年最多只有几厘米的速度。然而，这可能会导致在几百万年的时间尺度上的混合，这个时间尺度比相同数量的热量通过热传导分布的时间尺度要短得多，而且这个时间尺度与影响地球内部和表面结构的演变有关。
*  @note  如果你有兴趣使用该程序作为你自己实验的基础，你也会想看看它在 step-32 中的续篇。此外， step-32 后来被开发成更大的开源代码ASPECT（见https://aspect.geodynamics.org/），它可以解决现实的问题，在试图将 step-31 改造成可以解决任何你想解决的问题之前，你可能想要调查一下。
* 

*<a name="Boundaryandinitialconditions"></a><h3>Boundary and initial conditions</h3>
* 

* 由于Boussinesq方程是在流体运动的惯性不起作用的假设下推导出来的，所以流场在每个时间都完全由当时的浮力差决定，而不是由以前的流场决定。这反映在上面的前两个方程是稳态的斯托克斯方程，不包含时间导数的事实。因此，我们不需要初始条件，也不需要初始条件，因为温度和压力都是如此。另一方面，温度场确实满足有时间导数的方程，所以我们需要初始条件 $T$ 。
* 至于边界条件：如果 $\kappa>0$ ，那么温度满足一个二阶微分方程，需要边界周围所有时间的边界数据。这些可以是规定的边界温度 $T|_{\partial\Omega}=T_b$ （Dirichlet边界条件），或规定的热通量 $\mathbf{n}\cdot\kappa\nabla
T|_{\partial\Omega}=\phi$ ；在本程序中，我们将使用绝缘边界条件，即规定没有热通量。  $\phi=0$  .
* 同样，速度场要求我们提出边界条件。如果流体粘在边界上，可以是 $\partial\Omega$ 上的无滑移无通量条件 $\mathbf{u}=0$ ；如果流体可以沿边界流动但不能穿过边界，可以是无正常通量条件 $\mathbf n \cdot \mathbf
u = 0$ ，或者是其他任何数量的物理上合理的条件。在这个程序中，我们将使用无正常通量条件。
* 

* <a name="Solutionapproach"></a><h3>Solution approach</h3> 。
 

* 与 step-21 中解决的方程一样，我们这里有一个微分代数方程（DAE）系统：就时间变量而言，只有温度方程是微分方程，而 $\mathbf{u}$ 和 $p$ 的斯托克斯系统没有时间导数，因此属于代数约束，必须在每个时间点上保持。与 step-21 的主要区别是，那里的代数约束是形式为@f{eqnarray*}
  \mathbf u + {\mathbf K}\lambda \nabla p &=& 0, \\
  \nabla\cdot \mathbf u &=& f,
@f}的混合拉普拉斯系统。
* 而现在我们有一个斯托克斯系统@f{eqnarray*}
* 


* 
* 


* 
* 
-\nabla \cdot (2 \eta \varepsilon ({\mathbf u})) + \nabla p &=& f, \\
  \nabla\cdot \mathbf u &=& 0,
@f}。
* 其中 $\nabla \cdot \eta \varepsilon (\cdot)$ 是一个类似于拉普拉斯系 $\Delta$ 的算子，应用于一个矢量场。
* 鉴于与我们在 step-21 中所做的相似，我们选择类似的方法可能并不奇怪，尽管我们将不得不对微分算子左上角的算子变化进行调整。
* 

*<a name="Timestepping"></a><h4>Time stepping</h4>
* 

* 作为DAE的问题结构允许我们使用与我们已经在 step-21 中使用的相同策略，即我们使用一个时间滞后方案：我们首先解决温度方程（使用外推的速度场），然后将新的温度解插入速度方程的右侧。不过，我们在代码中实现这一点的方式是从一个稍微不同的角度来看问题的。我们首先使用前一个时间步长的温度场来求解速度和压力的斯托克斯方程，这意味着我们得到前一个时间步长的速度。换句话说，我们首先将时间步骤 $n
* 
- 1$ 的斯托克斯系统解为@f{eqnarray*}
* 


* 
* 


* 
* 
-\nabla \cdot (2\eta \varepsilon ({\mathbf u}^{n-1})) + \nabla p^{n-1} &=&
* 


* 
* 


* 
* 
-\rho\; \beta \; T^{n-1} \mathbf{g},
  \\
  \nabla \cdot {\mathbf u}^{n-1} &=& 0,
@f}。
* 然后用外推的速度场解温度方程，直到时间 $n$ 。
* 与 step-21 相反，我们在这里使用一个高阶的时间步进方案，即用（单边）差分商 $\frac{\frac 32 T^{n}-2T^{n-1}+\frac 12 T^{n-2}}{k}$ 取代时间导数 $\frac{\partial T}{\partial t}$ ， $k$ 为时间步长。这就得到了离散化的时间温度方程@f{eqnarray*}
  \frac 32 T^n
* 


* 
* 


* 
* 
-
  k\nabla \cdot \kappa \nabla T^n
  &=&
  2 T^{n-1}
* 


* 
* 


* 
* 
-
  \frac 12 T^{n-2}
* 


* 
* 


* 
* 
-
  k(2{\mathbf u}^{n-1}
* 
- {\mathbf u}^{n-2} ) \cdot \nabla (2T^{n-1}-T^{n-2})
  +
  k\gamma.
@f} 。
* 注意温度方程是如何以半显式方式求解的：扩散是隐式处理的，而平流是显式处理的，采用温度和速度的外推法（或前推法），包括刚刚计算的速度 ${\mathbf u}^{n-1}$ 。对当前时间层的正向投影 $n$ 来自泰勒扩展 $T^n
\approx T^{n-1} + k_n \frac{\partial T}{\partial t} \approx T^{n-1} + k_n
\frac{T^{n-1}-T^{n-2}}{k_n} = 2T^{n-1}-T^{n-2}$ 。我们需要这个投影来保持BDF-2方案的精度等级。换句话说，我们在显式右手边使用的温度场是当前温度场的二阶近似值&mdash；不完全是显式时间步进方案，但从特征上看也不是太远。
* 温度外推的引入限制了时间步长<a href="http://en.wikipedia.org/wiki/Courant–Friedrichs–Lewy_condition">
Courant-Friedrichs-Lewy (CFL) condition</a>，就像在 @ref step_21 " step-21 "中一样。（如果我们隐式处理对流项，就不会有这个稳定条件，因为BDF-2方案是A级稳定的，代价是我们需要在每个时间步长建立一个新的温度矩阵）。我们将在<a href="#Results">results
section</a>中讨论时间步长的确切选择，但目前重要的是，这个CFL条件意味着时间步长 $k$ 可能会从时间步长中改变，我们必须稍微修改上述公式。如果 $k_n,k_{n-1}$ 是当前和前一时间段的时间步长，那么我们使用近似值
* @f{align*}{
\frac{\partial T}{\partial t} \approx
 \frac 1{k_n}
 \left(
       \frac{2k_n+k_{n-1}}{k_n+k_{n-1}} T^{n}
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
-
       \frac{k_n+k_{n-1}}{k_{n-1}}T^{n-1}
       +
       \frac{k_n^2}{k_{n-1}(k_n+k_{n-1})} T^{n-2}
 \right)
 @f}
*和
* @f{align*}{
T^n \approx
   T^{n-1} + k_n \frac{\partial T}{\partial t}
   \approx
   T^{n-1} + k_n
   \frac{T^{n-1}-T^{n-2}}{k_{n-1}}
   =
   \left(1+\frac{k_n}{k_{n-1}}\right)T^{n-1}-\frac{k_n}{k_{n-1}}T^{n-2},
@f}
*上述方程被概括为：@f{eqnarray*}
  \frac{2k_n+k_{n-1}}{k_n+k_{n-1}} T^n
* 


* 
* 


* 
* 
-
  k_n\nabla \cdot \kappa \nabla T^n
  &=&
  \frac{k_n+k_{n-1}}{k_{n-1}} T^{n-1}
* 


* 
* 


* 
* 
-
  \frac{k_n^2}{k_{n-1}(k_n+k_{n-1})} T^{n-2}
* 


* 
* 


* 
* 
-
  k_n{\mathbf u}^{*,n} \cdot \nabla T^{*,n}
  +
  k_n\gamma,
@f} 。
* 
* 其中 ${(\cdot)}^{*,n} = \left(1+\frac{k_n}{k_{n-1}}\right)(\cdot)^{n-1}
* 
-
\frac{k_n}{k_{n-1}}(\cdot)^{n-2}$ 表示速度 $\mathbf u$ 和温度 $T$ 外推到时间水平 $n$ ，使用前两个时间步骤的数值。这不是一个容易读懂的方程，但可以为我们提供所需的高阶精度。作为一致性检查，很容易验证，如果 $k_n=k_{n-1}$ ，它可以还原成与上面相同的方程。
* 最后，我们注意到，选择高阶时隙方案当然会迫使我们在内存中保留更多的时隙；特别是，我们在这里需要保留 $T^{n-2}$ ，一个我们以前可以抛弃的向量。这似乎是个麻烦事，我们以前只用一阶分步方案就能避免，但正如我们在下面讨论稳定化问题时看到的，我们无论如何都需要这个向量，所以保留它进行时间离散化基本上是免费的，并使我们有机会使用高阶方案。
* 

*<a name="WeakformandspacediscretizationfortheStokespart"></a><h4>Weak form and space discretization for the Stokes part</h4>
* 

* 与解决混合拉普拉斯方程一样，解决斯托克斯方程需要我们为密度和压力变量选择特定的有限元对。因为在 step-22 中已经讨论过这个问题，所以我们只简单介绍一下这个话题：在这里，我们使用稳定的对 $Q_{p+1}^d \times Q_p, p\ge 1$ 。这些都是连续元素，所以我们可以通过部分积分和用离散函数替代连续函数来形成斯托克斯方程的弱形式，而不存在问题：@f{eqnarray*}
  (\nabla {\mathbf v}_h, 2\eta \varepsilon ({\mathbf u}^{n-1}_h))
* 


* 
* 


* 
* 
-
  (\nabla \cdot {\mathbf v}_h, p^{n-1}_h)
  &=&
* 


* 
* 


* 
* 
-({\mathbf v}_h, \rho\; \beta \; T^{n-1}_h \mathbf{g}),
  \\
  (q_h, \nabla \cdot {\mathbf u}^{n-1}_h) &=& 0,
@f} 。
*为所有测试函数 $\mathbf v_h, q_h$  。第一个方程的第一项被认为是张量之间的内积，即 $(\nabla {\mathbf v}_h, \eta \varepsilon ({\mathbf u}^{n-1}_h))_\Omega
 = \int_\Omega \sum_{i,j=1}^d [\nabla {\mathbf v}_h]_{ij}
           \eta [\varepsilon ({\mathbf u}^{n-1}_h)]_{ij}\, dx$ .因为这个积中的第二个张量是对称的， $\nabla {\mathbf v}_h$ 的反对称成分不起作用，如果我们用 $\mathbf v_h$ 的对称梯度代替，它导致完全相同的形式。因此，我们考虑并实施的表述是@f{eqnarray*}
  (\varepsilon({\mathbf v}_h), 2\eta \varepsilon ({\mathbf u}^{n-1}_h))
* 


* 
* 


* 
* 
-
  (\nabla \cdot {\mathbf v}_h, p^{n-1}_h)
  &=&
* 


* 
* 


* 
* 
-({\mathbf v}_h, \rho\; \beta \; T^{n-1}_h \mathbf{g}),
  \\
  (q_h, \nabla \cdot {\mathbf u}^{n-1}_h) &=& 0.
@f} 。
* 
* 这与我们在 step-22 中已经讨论过的完全一样，这里没有什么可说的了。
* 

* <a name="Stabilizationweakformandspacediscretizationforthetemperatureequation"></a><h4>Stabilization, weak form and space discretization for the temperature equation</h4> 。
* 

* 更有趣的问题是如何处理温度对流-扩散方程。默认情况下，并非所有的离散化方程都是同样稳定的，除非我们做一些像上卷、稳定化或所有这些的事情。实现这一目标的方法之一是使用不连续元素（即我们在 step-12 中离散传输方程时使用的FE_DGQ类，或者在 step-20 和 step-21 中离散压力时使用的FE_DGQ类），并在单元间的界面上定义一个考虑到上绕的流速。如果我们有一个纯粹的平流问题，这可能是最简单的方法。然而，在这里我们也有一些扩散，用不连续元素对拉普拉斯算子进行离散化是很麻烦的，因为有大量的附加项需要在细胞间的每个面上进行积分。不连续元素还有一个缺点，即使用数值通量会带来额外的数值扩散，这种扩散无处不在，而我们真正希望把数值扩散的影响降到最低，只在需要稳定方案的地方应用它。
* 因此，一个更好的选择是在模型中加入一些非线性粘性。从本质上讲，这样做的目的是将温度方程从@f{eqnarray*}
  \frac{\partial T}{\partial t}
  +
  {\mathbf u} \cdot \nabla T
* 


* 
* 


* 
* 
-
  \nabla \cdot \kappa \nabla T &=& \gamma
@f}的形式转变为@f{eqnarray*}
  \frac{\partial T}{\partial t}
  +
  {\mathbf u} \cdot \nabla T
* 


* 
* 


* 
* 
-
  \nabla \cdot \kappa \nabla T &=& \gamma
@f}的形式。
*变成类似@f{eqnarray*}
  \frac{\partial T}{\partial t}
  +
  {\mathbf u} \cdot \nabla T
* 


* 
* 


* 
* 
-
  \nabla \cdot (\kappa+\nu(T)) \nabla T &=& \gamma,
@f}的形式。
*其中 $\nu(T)$ 是一个额外的粘度（扩散）项，只在冲击和其他不连续的附近起作用。  $\nu(T)$ 的选择方式是，如果 $T$ 满足原始方程，额外的粘度为零。
* 为了实现这一点，文献中包含了许多方法。我们在此将采用Guermond和Popov开发的一种方法，它建立在一个适当定义的残差和额外粘度的极限程序之上。为此，让我们定义一个残差 $R_\alpha(T)$ 如下：@f{eqnarray*}
  R_\alpha(T)
  =
  \left(
  \frac{\partial T}{\partial t}
  +
  {\mathbf u} \cdot \nabla T
* 


* 
* 


* 
* 
-
  \nabla \cdot \kappa \nabla T
* 
- \gamma
  \right)
  T^{\alpha-1}
@f} 。
*在这里，我们以后将从 $[1,2]$ 的范围内选择稳定指数 $\alpha$ 。请注意，如果 $T$ 满足温度方程， $R_\alpha(T)$ 将为零，因为此时括号内的项将为零。将条款相乘，我们得到以下完全等同的形式：@f{eqnarray*}
  R_\alpha(T)
  =
  \frac 1\alpha
  \frac{\partial (T^\alpha)}{\partial t}
  +
  \frac 1\alpha
  {\mathbf u} \cdot \nabla (T^\alpha)
* 


* 
* 


* 
* 
-
  \frac 1\alpha
  \nabla \cdot \kappa \nabla (T^\alpha)
  +
  \kappa(\alpha-1)
  T^{\alpha-2} |\nabla T|^2
* 


* 
* 


* 
* 
-
  \gamma
  T^{\alpha-1}
@f} 。
* 
* 有了这个残差，我们现在可以把人工黏度定义为一个分片常数函数，分别定义在直径为 $h_K$ 的每个单元上，如下所示：@f{eqnarray*}
  \nu_\alpha(T)|_K
  =
  \beta
  \|\mathbf{u}\|_{L^\infty(K)}
  \min\left\{
    h_K,
    h_K^\alpha
    \frac{\|R_\alpha(T)\|_{L^\infty(K)}}{c(\mathbf{u},T)}
  \right\}
@f} 。
* 
* 这里， $\beta$ 是一个稳定常数（维度分析表明它是无单位的，因此与比例无关；我们将在<a href="#Results">results section</a>中讨论它的选择）， $c(\mathbf{u},T)$ 是一个归一化常数，必须有单位 $\frac{m^{\alpha-1}K^\alpha}{s}$ 。我们将选择它作为 $c(\mathbf{u},T) =
 c_R\ \|\mathbf{u}\|_{L^\infty(\Omega)} \ \mathrm{var}(T)
 \ |\mathrm{diam}(\Omega)|^{\alpha-2}$ ，其中 $\mathrm{var}(T)=\max_\Omega T
* 
- \min_\Omega T$ 是现有温度值的范围（记住，浮力是由温度变化驱动的，而不是绝对温度）， $c_R$ 是一个无量纲常数。为了理解为什么这种方法有效，请考虑一下。如果在一个特定的单元 $K$ 上，温度场是平滑的，那么我们希望那里的残差很小（事实上是在 ${\cal O}(h_K)$ 的数量级上），注入人工扩散的稳定项在那里将是大小为 $h_K^{\alpha+1}$ &mdash；也就是说，相当小，就像我们希望它在没有必要的额外扩散时一样。另一方面，如果我们处于或接近温度场的不连续状态，那么它将是大的； $\nu_\alpha(T)$ 定义中的最小操作将确保稳定化具有大小 $h_K$ &mdash；确保方案稳定性的最佳人工粘性量。
* Guermond和Popov的计算表明，这种形式的稳定化实际上比周围的大多数其他稳定化方案（例如流线型扩散，仅举最简单的一种）表现得更好。此外，对于 $\alpha\in
[1,2)$ ，他们甚至可以证明它比流线型扩散产生更好的线性传输方程收敛顺序。对于 $\alpha=2$ ，目前还没有理论结果，但数值测试表明，其结果比 $\alpha=1$ 好得多。
* 一个更实际的问题是如何将这种人工扩散引入我们想解决的方程中。请注意，当时的粘度 $\nu(T)$ 是随温度变化的，所以我们要解决的方程在 $T$ 中是非线性的&mdash; 不是人们所希望的稳定方程的简单方法，如果我们意识到 $\nu(T)$ 在 $T$ 中是不可微分的，那就更不是了。然而，我们没有理由感到绝望：我们仍然必须进行时间离散，而且我们不能明确地处理这个术语。
* 在稳定参数的定义中，我们用 $\frac{\partial T}{\partial t} \approx
\frac{T^{n-1}-T^{n-2}}{k^{n-1}}$ 对时间导数进行近似。这种近似只利用了可用的时间数据，这也是我们需要存储前两个时间步骤的数据的原因（这使我们能够使用BDF-2方案而不需要额外的存储成本）。我们现在可以简单地在 $t_{n-1}$ 处评估其余的项，但这样一来，离散残差就只是一个向后的欧拉近似值，而这只是一阶精确。因此，如果是平滑解，尽管外部BDF-2方案和空间FE离散化的时间精度为二阶，但残差仍为 $h$ 阶。这当然不是我们想要的（事实上，我们希望在解决方案表现良好的区域有较小的残差），所以需要更谨慎一些。这个问题的关键是观察我们构建的第一导数实际上是以 $t_{n-\frac{3}{2}}$ 为中心的。如果我们通过使用近似值 $\frac 12 T^{n-1}+\frac 12 T^{n-2}$ 来评估 $t_{n-\frac{3}{2}}$ 处的所有空间项，我们就可以得到所需的二阶精确的剩余计算，这意味着我们将非线性粘度作为这个中间温度的函数来计算， $\nu_\alpha =
\nu_\alpha\left(\frac 12 T^{n-1}+\frac 12 T^{n-2}\right)$  。请注意，这种对残余物的评估不外乎是Crank-Nicholson方案，所以我们可以肯定，现在一切都很好。人们可能会想，现在的数值粘度没有在 $n$ 的时候被评估（相对于方程的其余部分），这是否是一个问题。然而，这种抵消是不严谨的。对于平滑解， $\nu_\alpha$ 将连续变化，所以时间偏移的误差比非线性粘度本身要小 $k$ 倍，也就是说，它是一个被遗漏的小的高阶贡献。这很好，因为该术语本身已经达到了平滑区域的分化误差水平。
* 使用上面介绍的BDF-2方案，对于较简单的均匀时间步长为 $k$ 的情况，可以得出：@f{eqnarray*}
  \frac 32 T^n
* 


* 
* 


* 
* 
-
  k\nabla \cdot \kappa \nabla T^n
  &=&
  2 T^{n-1}
* 


* 
* 


* 
* 
-
  \frac 12 T^{n-2}
  \\
  &&
  +
  k\nabla \cdot
  \left[
    \nu_\alpha\left(\frac 12 T^{n-1}+\frac 12 T^{n-2}\right)
    \ \nabla (2T^{n-1}-T^{n-2})
  \right]
  \\
  &&
* 


* 
* 


* 
* 
-
  k(2{\mathbf u}^{n-1}-{\mathbf u}^{n-2}) \cdot \nabla (2T^{n-1}-T^{n-2})
  \\
  &&
  +
  k\gamma.
@f} 。
* 在这个方程的左边，仍然是来自时间导数和原始（物理）扩散的项，我们以隐式处理（这实际上是一个很好的项：从左边产生的矩阵是质量矩阵和拉普拉斯矩阵的倍数&mdash；两者都是正定的，如果时间步长 $k$ 很小，和很容易反演）。在右手边，第一行的条款是时间导数的结果；第二行是时间 $t_{n-\frac
32}$ 的人工扩散；第三行包含对流条款，第四行是来源。请注意，人工扩散对当前时间的外推温度的作用，与我们在时间步进一节中讨论的平流作用相同。
* 我们在现实中必须使用的非均匀时间步长的形式有点复杂（这就是为什么我们首先展示了较简单的形式），内容是：@f{eqnarray*}
  \frac{2k_n+k_{n-1}}{k_n+k_{n-1}} T^n
* 


* 
* 


* 
* 
-
  k_n\nabla \cdot \kappa \nabla T^n
  &=&
  \frac{k_n+k_{n-1}}{k_{n-1}} T^{n-1}
* 


* 
* 


* 
* 
-
  \frac{k_n^2}{k_{n-1}(k_n+k_{n-1})} T^{n-2}
  \\
  &&
  +
  k_n\nabla \cdot
  \left[
    \nu_\alpha\left(\frac 12 T^{n-1}+\frac 12 T^{n-2}\right)
    \ \nabla  \left[
    \left(1+\frac{k_n}{k_{n-1}}\right)T^{n-1}-\frac{k_n}{k_{n-1}}T^{n-2}
  \right]
  \right]
  \\
  &&
* 


* 
* 


* 
* 
-
  k_n
  \left[
    \left(1+\frac{k_n}{k_{n-1}}\right){\mathbf u}^{n-1}
* 
-
    \frac{k_n}{k_{n-1}}{\mathbf u}^{n-2}
  \right]
  \cdot \nabla
  \left[
    \left(1+\frac{k_n}{k_{n-1}}\right)T^{n-1}-\frac{k_n}{k_{n-1}}T^{n-2}
  \right]
  \\
  &&
  +
  k_n\gamma.
@f} 。
* 
* 在解决了所有这些问题之后，弱形式自然而然地从最后一个方程中显示的强形式中产生，我们立即得出了离散化方程的弱形式：@f{eqnarray*}
  \frac{2k_n+k_{n-1}}{k_n+k_{n-1}} (\tau_h,T_h^n)
  +
  k_n (\nabla \tau_h, \kappa \nabla T_h^n)
  &=&
  \biggl(\tau_h,
  \frac{k_n+k_{n-1}}{k_{n-1}} T_h^{n-1}
* 


* 
* 


* 
* 
-
  \frac{k_n^2}{k_{n-1}(k_n+k_{n-1})} T_h^{n-2}
  \\
  &&\qquad
* 


* 
* 


* 
* 
-
  k_n
  \left[
    \left(1+\frac{k_n}{k_{n-1}}\right){\mathbf u}^{n-1}
* 
-
    \frac{k_n}{k_{n-1}}{\mathbf u}^{n-2}
  \right]
  \cdot \nabla
  \left[
    \left(1+\frac{k_n}{k_{n-1}}\right)T^{n-1}-\frac{k_n}{k_{n-1}}T^{n-2}
  \right]
  +
  k_n\gamma \biggr)
  \\
  &&
* 


* 
* 


* 
* 
-
  k_n \left(\nabla \tau_h,
    \nu_\alpha\left(\frac 12 T_h^{n-1}+\frac 12 T_h^{n-2}\right)
    \ \nabla \left[
    \left(1+\frac{k_n}{k_{n-1}}\right)T^{n-1}-\frac{k_n}{k_{n-1}}T^{n-2}
  \right]
  \right)
@f} 。
*对于所有离散测试函数  $\tau_h$  。在这里，扩散项已经被部分整合，而且我们已经使用了我们将不施加热通量，  $\mathbf{n}\cdot\kappa\nabla T|_{\partial\Omega}=0$  。
* 这就导致了矩阵方程的形式@f{eqnarray*}
  \left( \frac{2k_n+k_{n-1}}{k_n+k_{n-1}} M+k_n A_T\right) T_h^n
  = F(U_h^{n-1}, U_h^{n-2},T_h^{n-1},T_h^{n-2}),
@f} 。
* 考虑到左边的矩阵结构（两个正定矩阵之和），可以用共轭梯度法轻松求解。
* 

* 
* <a name="Linearsolvers"></a><h4>Linear solvers</h4>。
* 

* 如上所述，我们解决速度/压力联合系统和温度联合系统的方法是使用运算器分割，首先用旧的温度场解决速度和压力的斯托克斯系统，然后用刚刚计算的速度场解决新的温度场。关于算子分割方法的更广泛的讨论可以在  step-58  中找到）。
* 

* <a name="LinearsolversfortheStokesproblem"></a><h5>Linear solvers for the Stokes problem</h5> 。
* 

* 解决来自斯托克斯系统的线性方程在 step-22 中得到了详细的讨论。特别是，在该方案的结果部分，我们讨论了一些替代性的线性求解策略，结果发现这些策略比原来的方法更有效。在那里，我们发现最好的替代方法是使用GMRES求解器，以涉及Schur补数的块矩阵为前提条件。具体来说，斯托克斯算子导致了一个块状结构矩阵@f{eqnarray*}
  \left(\begin{array}{cc}
    A & B^T \\ B & 0
  \end{array}\right)
@f} 。
*正如那里所讨论的，一个好的预处理程序是@f{eqnarray*}
  P
  =
  \left(\begin{array}{cc}
    A & 0 \\ B &
* 
-S
  \end{array}\right),
  \qquad
  \text{or equivalently}
  \qquad
  P^{-1}
  =
  \left(\begin{array}{cc}
    A^{-1} & 0 \\ S^{-1} B A^{-1} &
* 
-S^{-1}
  \end{array}\right)
@f} 。
*其中 $S$ 是斯托克斯算子的舒尔补码 $S=B^TA^{-1}B$ 。当然，这个预处理程序是没有用的，因为我们不能形成矩阵的各种倒数，但我们可以用下面的方法作为预处理程序：@f{eqnarray*}
  \tilde P^{-1}
  =
  \left(\begin{array}{cc}
    \tilde A^{-1} & 0 \\ \tilde S^{-1} B \tilde A^{-1} &
* 
-\tilde S^{-1}
  \end{array}\right)
@f} 。
*其中 $\tilde A^{-1},\tilde S^{-1}$ 是对逆矩阵的近似值。特别是，事实证明 $S$ 在频谱上等同于质量矩阵，因此用适用于压力空间上的质量矩阵的CG求解器取代 $\tilde
S^{-1}$ 是一个不错的选择。与 step-22 略有不同的是，我们在动量方程中有一个系数 $\eta$ ，通过与那里相同的推导，我们应该得出结论，我们应该使用的是有条目 $\tilde S_{ij}=(\eta^{-1}\varphi_i,\varphi_j)$ 的加权质量矩阵。
* 在 step-22 中，我们使用了 $A$ 的稀疏LU分解（使用SparseDirectUMFPACK类）。 ]的 $\tilde A^{-1}$ &mdash；perfect preconditioner&mdash；在2D中，但对于3D来说，内存和计算时间通常不足以实际计算这个分解；因此，我们在3D中只使用不完全LU分解（ILU，使用SparseILU类）。
* 对于这个程序，我们希望能走得更远一些。为此，请注意，矢量场上的对称化双线性形式 $(\varepsilon {\mathbf v}_i, 2 \eta \varepsilon ({\mathbf v}_j))$ 与非对称化版本 $(\nabla {\mathbf v}_i, \eta \nabla {\mathbf v}_j)
= \sum_{k,l=1}^d
  (\partial_k ({\mathbf v}_i)_l, \eta \partial_k ({\mathbf v}_j)_l)
$ 相差不大（注意，在这种形式中，因子2已经消失了）。然而，后者的优点是测试函数的 <code>dim</code> 矢量分量没有耦合（好吧，几乎没有，见下文），也就是说，得到的矩阵是块对角线的：每个矢量分量有一个块，这些块中的每个都等于这个矢量分量的拉普拉斯矩阵。因此，假设我们以这样的方式排列自由度，即首先对速度的所有 $x$ -分量进行编号，然后是 $y$ -分量，然后是 $z$ -分量，那么与这种稍有不同的双线性形式相关的矩阵 $\hat A$ 具有@f{eqnarray*}
  \hat A =
  \left(\begin{array}{ccc}
    A_s & 0 & 0 \\ 0 & A_s & 0 \\ 0 & 0 & A_s
  \end{array}\right)
@f}形式
* 其中 $A_s$ 是一个拉普拉斯矩阵，其大小等于与矢量值速度的每个分量相关的形状函数的数量。有了这个矩阵，我们就可以将速度矩阵 $A$ 的预处理定义如下：@f{eqnarray*}
  \tilde A^{-1} =
  \left(\begin{array}{ccc}
    \tilde A_s^{-1} & 0 & 0 \\
    0 & \tilde A_s^{-1} & 0 \\
    0 & 0 & \tilde A_s^{-1}
  \end{array}\right),
@f} 。
* 其中 $\tilde A_s^{-1}$ 是拉普拉斯矩阵的预处理程序&mdash;我们非常清楚如何建立良好的预处理程序!
* 在现实中，故事并不那么简单。为了使矩阵 $\tilde A$ 明确，我们需要通过应用边界条件使各个块 $\tilde
A_s$ 明确。我们可以尝试通过在边界周围施加迪里希特边界条件来做到这一点，如果后者的矩阵是由斯托克斯问题产生的，我们在域的周围也有迪里希特边界条件，也就是说，如果我们执行 $\mathbf{u} =
0$ ，那么如此定义的预处理程序 $\tilde A^{-1}$ 就会变成 $A$ 的良好预处理。
* 不幸的是，这个 "如果 "是一个 "如果和唯一的如果"：在下面的程序中，我们希望使用 $\mathbf u
\cdot \mathbf n = 0$ 形式的无流量边界条件（即允许平行于边界的流量%，但没有通过边界的流量）。在这种情况下，事实证明，上面定义的块状对角线矩阵并不是一个好的预处理条件，因为它忽略了边界上的分量的耦合。因此，更好的方法是如果我们把矩阵 $\hat A$ 建立为矢量拉普拉斯矩阵 $\hat A_{ij} = (\nabla {\mathbf v}_i,
\eta \nabla {\mathbf v}_j)$ ，然后应用与我们应用于 $A$ 相同的边界条件。如果这是一个围绕领域的迪里希特边界条件， $\hat A$ 将像上面那样解耦为三个对角线块，如果边界条件是 $\mathbf u
\cdot \mathbf n = 0$ 的形式，那么这将在边界引入自由度的耦合，但只是在那里。事实上，这比上面介绍的那个预处理程序要好得多，而且几乎具有我们希望得到的所有好处。
* 

* 总结这整个故事，我们可以看到。 <ul>   <li>  与我们在 step-22 中从对称梯度产生的原始矩阵 $A$ 中建立一个预处理器相比，我们不得不期待基于拉普拉斯双线性形式的预处理器表现更差，因为它没有考虑到矢量成分之间的耦合。
*  <li>  另一方面，拉普拉斯矩阵的预处理程序通常更成熟，比矢量问题的预处理程序性能更好。例如，在写这篇文章的时候，代数%多重网格（AMG）算法对于标量问题已经非常成熟，但对于矢量问题却不是这样。
*  <li>  在建立这个预处理程序时，我们将不得不建立起矩阵 $\hat A$ 及其预处理程序。虽然这意味着我们必须存储一个之前不需要的额外矩阵，但与存储耦合矩阵 $A$ 的预处理程序相比，预处理程序 $\tilde A_s^{-1}$ 可能需要更少的内存。这是因为矩阵 $A_s$ 在所有对应于内部自由度的行中每行只有三分之一的条目，并且只在边界条件引入耦合的部分包含矢量成分间的耦合。因此，存储该矩阵是比较便宜的，我们可以预期，计算和存储预处理程序 $\tilde A_s$ 也将比为完全耦合的矩阵做这些事情便宜得多。 </ul>  
* 

* 
* <a name="Linearsolversforthetemperatureequation"></a><h5>Linear solvers for the temperature equation</h5> 。
* 

* 这是最简单的部分。温度方程的矩阵具有 $\alpha M + \beta A$ 的形式，其中 $M,A$ 是温度空间的质量和刚度矩阵， $\alpha,\beta$ 是与时间步长和当前及前一个时间步长有关的常数。这是不对称正定和对称正半定矩阵之和，其结果也是对称正定的。此外， $\frac\beta\alpha$ 是一个与时间步长成正比的数字，因此只要网格很细，就会变得很小，从而减弱当时条件不良的刚度矩阵的影响。
* 因此，用共轭梯度算法反演这个矩阵，使用一个简单的预处理程序，与反演斯托克斯矩阵相比，是微不足道和非常便宜的。
* 

* 
* <a name="Implementationdetails"></a><h3>Implementation details</h3> 。
* 

* <a name="UsingdifferentDoFHandlerobjects"></a><h4>Using different DoFHandler objects</h4> * <a name="UsingdifferentDoFHandlerobjects"></a><h4>Using different DoFHandler objects</h4>。
* 

* 下面的程序中，有一件事值得事先解释，那就是使用了两个不同的DoFHandler对象。如果我们看一下上述方程的结构和它们的求解方案，我们就会意识到，几乎没有什么共同点使斯托克斯部分和温度部分保持一致。在以前所有讨论 @ref
vector_valued "矢量值问题 "的教程程序中，我们总是只使用一个有几个矢量分量的单一无限元素和一个DoFHandler对象。有时，我们将得到的矩阵分解成块，以方便特定的求解方案；例如，在目前程序所基于的斯托克斯方程的 step-22 程序中就是如此。
* 当然，我们在这里也可以这样做。我们将得到的线性系统看起来像这样：@f{eqnarray*}
  \left(\begin{array}{ccc}
    A & B^T & 0 \\ B & 0 &0 \\ C & 0 & K
  \end{array}\right)
  \left(\begin{array}{ccc}
    U^{n-1} \\ P^{n-1} \\ T^n
  \end{array}\right)
  =
  \left(\begin{array}{ccc}
    F_U(T^{n-1}) \\ 0 \\ F_T(U^{n-1},U^{n-2},T^{n-1},T^{n-2})
  \end{array}\right).
@f} 。
* 这方面的问题是。我们从未同时使用整个矩阵。事实上，它从未真正存在于同一时间。如上所述， $K$ 和 $F_T$ 依赖于已经计算出的解决方案 $U^n$ ，在第一种情况下，通过时间步骤（依赖于 $U^n$ ，因为它必须满足一个CFL条件）。因此，我们只有在已经解决了左上角 $2\times 2$ 块斯托克斯系统后才能组装它，而一旦我们转向温度方程，我们就不再需要斯托克斯部分了；为一个在任何特定时间都不会以整体存在于内存中的矩阵建立网络对象的事实导致我们在 step-21 中跳过一些圈套，所以我们不要重复这类错误。此外，我们并不直接建立矩阵 $C$ ：因为当我们进入温度方程时，我们已经知道了 $U^n$ ，而且因为我们必须在这个时候组装右手边的 $F_T$ ，我们只是将项 $CU^n$ 移到右手边并与所有其他项一起组装。这意味着矩阵中不存在温度变量和斯托克斯变量耦合的部分，因此所有自由度的全局列举不再重要：如果我们有所有斯托克斯自由度的列举，以及所有温度自由度的独立列举就足够了。
* 从本质上讲，将<i>everything</i>放入一个块状矩阵中没有什么用处（当然对于 $2\times 2$ 斯托克斯部分也有同样好的理由这样做），或者说，将所有东西放入同一个DoFHandler对象中。
* 但这样做是否有<i>downsides</i>的好处？这些问题是存在的，尽管它们一开始可能并不明显。主要的问题是，如果我们需要创建一个包含速度、压力和温度变形函数的全局无限元素，并使用它来初始化DoFHandler。但是我们也用这个无限元素对象来初始化我们使用的所有FEValues或FEFaceValues对象。这可能看起来不是什么大问题，但是想象一下，例如，当我们评估我们需要用来计算人工粘度 $\nu_\alpha(T)|_K$ 的残差 $
  R_\alpha(T)
  =
  \left(
  \frac{\partial T}{\partial t}
  +
  {\mathbf u} \cdot \nabla T
* 


* 
* 


* 
* 
-
  \nabla \cdot \kappa \nabla T
* 
- \gamma
  \right)
  T^{\alpha-1}
$ 时会发生什么。 为此，我们需要温度的拉普拉斯，我们用形状函数的二阶导数（Hessians）张量来计算（我们必须给FEValues对象加上 <code>update_hessians</code> 标志）。现在，如果我们有一个包含速度、压力和温度的形状函数的有限性，这意味着我们必须计算<i>all</i>形状函数的Hessians，包括速度的许多高阶形状函数。这是我们不需要的大量计算，事实上，如果要这样做（正如我们在程序的早期版本中所做的那样），组装右手边需要大约四分之一的整体计算时间。
* 所以我们要做的是使用两个不同的有限元对象，一个用于斯托克斯成分，一个用于温度。这样就有了两个不同的DoFHandlers，两个稀疏模式和两个用于斯托克斯和温度部分的矩阵，等等。每当我们要组装包含温度和斯托克斯形状函数的东西时（特别是斯托克斯和温度方程的右侧），我们就使用两个FEValues对象，用两个单元格迭代器进行初始化，我们通过与同一个三角形对象相关的两个DoFHandler对象进行%的平行移动。对于这两个FEValues对象，我们当然使用相同的正交对象，以便我们可以在同一组正交点上进行迭代，但是每个FEValues对象将只根据它实际需要计算的内容获得更新标志。特别是，当我们像上面那样计算残差时，我们只要求得到斯托克斯形状函数的值，但也要求得到温度形状函数的Hessians &mdash；确实便宜得多，而且事实证明：组装温度方程的右侧现在是程序的一个组成部分，几乎无法测量。
* 有了这些变化，对程序进行计时的结果是，只有以下操作与整个运行时间相关。 <ul>   <li>  解决斯托克斯系统：占运行时间的72%。   <li>  使用Trilinos ML软件包组装斯托克斯预处理程序和计算代数多网格层次：占运行时间的11%。   <li>  函数 <code>BoussinesqFlowProblem::setup_dofs</code>  ：占总体运行时间的7%。   <li>  组装斯托克斯和温度右侧向量以及组装矩阵。7%.  </ul>  实质上这意味着除了代数多重网格外，所有的瓶颈都已被消除。
* 

* 
* <a name="UsingTrilinos"></a><h4>Using Trilinos</h4> 。
* 

* 与我们在 step-17 和 step-18 中使用PETSc来支持我们的线性代数需求一样，我们在这个程序中使用了<a
href="http://trilinos.org">Trilinos</a>库的接口（安装说明见thedeal.II README文件）。Trilinosis是一个非常大的集合，包含了所有与线性和非线性代数有关的东西，以及围绕这些东西的各种工具（看起来它在未来也会在许多其他方向上发展）。
* 使用Trilinos的主要原因，与我们探索PETSc类似，是它是一个非常强大的库，比deal.II自己的线性代数库提供更多的工具。这尤其包括在一个集群上使用MPI进行并行工作的能力，以及更多种类的预处理程序。在后一类中，最有趣的能力之一是Trilinos ML包的存在，它实现了代数多栅（AMG）方法。我们将使用这个预处理程序来预处理动量方程的二阶运算器部分。在 step-32 中，我们将利用这里讨论的相同问题，探讨以%并行方式解决问题的能力。
* 我们在 step-17 和 step-18 中使用的PETSc无疑是一个强大的库，它提供了大量处理矩阵、向量、迭代求解器和预处理器的函数，还有很多其他的东西，其中大部分在%并行中运行得很好。然而，它比Trilinos晚了几年，是用C语言编写的，通常不像其他一些库那样容易使用。因此，deal.II也获得了与Trilinos的接口，Trilinos与PETSc有很多相同的功能。然而，它是一个年轻了几年的项目，是用C++编写的，并且是由那些通常非常重视软体设计的人编写的。
* 

* <a name="Thetestcase"></a><h3>The testcase</h3>。
* 

* 我们在这里要解决的情况如下：我们用 $\kappa=10^{-6}, \eta=1, \rho=1, \beta=10$ 来解决上述的Boussinesq方程，即一个相对缓慢运动的流体，几乎没有热扩散传导性，主要通过对流来传输热量。在边界上，我们将要求速度（ $\mathrm{n}\cdot\mathrm{u}=0$ ）和温度（ $\mathrm{n}\cdot\nabla T=0$ ）没有正态流量。这是 step-22 导言中讨论的情况之一，它固定了速度的一个分量，同时允许流动与边界平行%。还有 <code>dim-1</code> 分量需要固定，即法向应力的切向分量；对于这些分量，我们选择同质条件，这意味着我们不需要任何特殊条件。初始条件只对温度场是必要的，我们选择它为恒定的零。
* 然后，问题的演变完全由温度方程的右侧 $\gamma(\mathrm{x},t)$ 驱动，即由热源和热汇驱动。在这里，我们选择了一个在圣诞节讲座前发明的设置：美国的教室里当然禁止使用真实的蜡烛，但允许使用虚拟的蜡烛。因此，我们选择了三个球形的热源，不等距地靠近领域的底部，模仿三个蜡烛。位于这些热源处的流体，最初处于静止状态，然后被加热，随着温度的升高，获得浮力，上升；更多的流体被拖上来，穿过热源，导致三个热羽上升，直到它们被外面下沉的流体循环所捕获，取代了因加热而上升的空气。
* 

* <a name="CommProg"></a> <h1> The commented program</h1>。
* <a name="Includefiles"></a> <h3>Include files</h3>。
* 

* 
* 第一步，像往常一样，包括这些著名的deal.II库文件和一些C++头文件的功能。
* 

* 
* @code
 #include <deal.II/base/quadrature_lib.h>
 #include <deal.II/base/logstream.h>
 #include <deal.II/base/utilities.h>
* 
 #include <deal.II/lac/full_matrix.h>
 #include <deal.II/lac/solver_gmres.h>
 #include <deal.II/lac/solver_cg.h>
 #include <deal.II/lac/block_sparsity_pattern.h>
 #include <deal.II/lac/affine_constraints.h>
* 
 #include <deal.II/grid/tria.h>
 #include <deal.II/grid/grid_generator.h>
 #include <deal.II/grid/grid_tools.h>
 #include <deal.II/grid/grid_refinement.h>
* 
 #include <deal.II/dofs/dof_handler.h>
 #include <deal.II/dofs/dof_renumbering.h>
 #include <deal.II/dofs/dof_tools.h>
* 
 #include <deal.II/fe/fe_q.h>
 #include <deal.II/fe/fe_system.h>
 #include <deal.II/fe/fe_values.h>
* 
 #include <deal.II/numerics/vector_tools.h>
 #include <deal.II/numerics/data_out.h>
 #include <deal.II/numerics/error_estimator.h>
 #include <deal.II/numerics/solution_transfer.h>
* 
 @endcode
 
* 然后我们需要包括一些头文件，这些头文件提供了矢量、矩阵和预处理类，这些类实现了各自Trilinos类的接口。特别是，我们将需要基于Trilinos的矩阵和向量类的接口，以及Trilinos预处理程序。
* 

* 
* @code
 #include <deal.II/base/index_set.h>
 #include <deal.II/lac/trilinos_sparse_matrix.h>
 #include <deal.II/lac/trilinos_block_sparse_matrix.h>
 #include <deal.II/lac/trilinos_vector.h>
 #include <deal.II/lac/trilinos_parallel_block_vector.h>
 #include <deal.II/lac/trilinos_precondition.h>
* 
 @endcode
 
* 最后，这里有几个C++头文件还没有被上述头文件之一所包含。
 

* 
* @code
 #include <iostream>
 #include <fstream>
 #include <memory>
 #include <limits>
* 
 
 @endcode
 
* 在这个头文件的最后，我们将所有deal.II的名字导入全局命名空间。
* 

* 
* @code
 namespace Step31
 {
   using namespace dealii;
* 
 
 @endcode
* 
* <a name="Equationdata"></a> <h3>Equation data</h3>。
* 

* 
* 同样，程序的下一阶段是定义方程数据，即各种边界条件、右手边和初始条件（记住，我们要解决的是一个时间依赖的系统）。这个定义的基本策略与  step-22  中的相同。不过关于细节，还是有一些区别。
* 

* 
* 首先是我们没有对速度设置任何不均匀的边界条件，因为正如介绍中所解释的，我们将使用无流条件  $\mathbf{n}\cdot\mathbf{u}=0$  。所以剩下的是 <code>dim-1</code> 对应力张量法线分量的切向部分的条件， $\textbf{n} \cdot [p \textbf{1}
* 
-
 \eta\varepsilon(\textbf{u})]$ ；我们假定这些分量的值是同质的，即一个自然的边界条件，不需要具体的动作（它作为零项出现在弱形式的右边）。  
* 对于温度 $T$ ，我们假设没有热能通量，即 $\mathbf{n} \cdot \kappa \nabla T=0$ 。这也是一个边界条件，不需要我们做任何特别的事情。  
* 其次，我们必须设置温度的初始条件（速度和压力不需要初始条件，因为我们在这里考虑的准稳态情况下的斯托克斯方程没有速度或压力的时间导数）。在这里，我们选择了一个非常简单的测试案例，即初始温度为零，所有动力学都由温度的右手边驱动。  
* 第三，我们需要定义温度方程的右手边。我们选择它在域的底部某处的三个圆（或三维球体）内是恒定的，正如介绍中所解释的那样，而在域外是零。  
* 最后，或者说首先，在这个命名空间的顶部，我们定义我们需要的各种材料常数（  $\eta,\kappa$  ，密度  $\rho$  和热膨胀系数  $\beta$  ）。
* 

* 
* @code
   namespace EquationData
   {
     constexpr double eta     = 1;
     constexpr double kappa   = 1e-6;
     constexpr double beta    = 10;
     constexpr double density = 1;
* 
 
     template <int dim>
     class TemperatureInitialValues : public Function<dim>
     {
     public:
       TemperatureInitialValues()
         : Function<dim>(1)
       {}
* 
       virtual double value(const Point<dim> &  /*p*/ ,
                            const unsigned int  /*component*/  = 0) const override
       {
         return 0;
       }
* 
       virtual void vector_value(const Point<dim> &p,
                                 Vector<double> &  value) const override
       {
         for (unsigned int c = 0; c < this->n_components; ++c)
           value(c) = TemperatureInitialValues<dim>::value(p, c);
       }
     };
* 
 
* 
     template <int dim>
     class TemperatureRightHandSide : public Function<dim>
     {
     public:
       TemperatureRightHandSide()
         : Function<dim>(1)
       {}
* 
       virtual double value(const Point<dim> & p,
                            const unsigned int component = 0) const override
       {
         (void)component;
         Assert(component == 0,
                ExcMessage("Invalid operation for a scalar function."));
* 
         Assert((dim == 2) || (dim == 3), ExcNotImplemented());
* 
         static const Point<dim> source_centers[3] = {
           (dim == 2 ? Point<dim>(.3, .1) : Point<dim>(.3, .5, .1)),
           (dim == 2 ? Point<dim>(.45, .1) : Point<dim>(.45, .5, .1)),
           (dim == 2 ? Point<dim>(.75, .1) : Point<dim>(.75, .5, .1))};
         static const double source_radius = (dim == 2 ? 1. / 32 : 1. / 8);
* 
         return ((source_centers[0].distance(p) < source_radius) ||
                     (source_centers[1].distance(p) < source_radius) ||
                     (source_centers[2].distance(p) < source_radius) ?
                   1 :
                   0);
       }
* 
       virtual void vector_value(const Point<dim> &p,
                                 Vector<double> &  value) const override
       {
         for (unsigned int c = 0; c < this->n_components; ++c)
           value(c) = TemperatureRightHandSide<dim>::value(p, c);
       }
     };
   } // namespace EquationData
* 
 
* 
 @endcode
* 
* <a name="Linearsolversandpreconditioners"></a> <h3>Linear solvers and preconditioners</h3>。
 

* 
* 本节介绍了一些用于求解斯托克斯系统线性方程的对象，我们需要在每个时间步长中求解。这里使用的许多想法与 step-20 相同，其中介绍了基于Schur补的预处理和求解器，实际接口来自 step-22 （特别是 step-22 的 "结果 "部分的讨论，其中我们介绍了直接Schur补方法的替代方法）。然而，请注意，在这里我们不使用Schur补数来解决Stokes方程，尽管预处理程序中出现了一个近似的Schur补数（压力空间的质量矩阵）。
* 

* 
* @code
   namespace LinearSolvers
   {
 @endcode
* 
* <a name="ThecodeInverseMatrixcodeclasstemplate"></a> <h4>The <code>InverseMatrix</code> class template</h4>
 

* 
* 该类是一个接口，用于计算 "倒置 "矩阵对向量的作用（使用 <code>vmult</code> 操作），其方式与 step-22 中的相应类相同：当请求该类对象的乘积时，我们使用CG方法解决与该矩阵的线性方程组，通过（模板化）类 <code>PreconditionerType</code> 的预处理器加速。    
* 与 step-22 中同一类别的实现略有不同，我们让 <code>vmult</code> 函数接受任何类型的向量（但是，如果矩阵不允许与这种向量进行矩阵-向量乘积，它将产生编译器错误）。    
* 其次，我们捕捉解算器可能抛出的任何异常。原因如下。在调试这样的程序时，偶尔会犯一个错误，即把一个不确定或不对称的矩阵或预处理程序传递给当前的类。在这种情况下，求解器将不能收敛并抛出一个运行时异常。如果在这里没有被捕捉到，它将在调用堆栈中传播，并可能最终在 <code>main()</code> 中被发现，在那里我们将输出一条错误信息，说CG求解器失败了。那么问题来了。哪个CG求解器？倒置质量矩阵的那个？用拉普拉斯算子反转左上角块的那个？还是在当前代码中我们使用线性求解器的其他几个嵌套位置中的一个CG求解器？在运行时异常中没有这方面的指示，因为它没有存储调用堆栈，我们通过它到达了产生异常的地方。    
* 因此，与其让异常自由传播到 <code>main()</code> ，不如让我们意识到，如果内部求解器失败了，外部函数能做的很少，不如将运行时异常转换为一个断言，该断言失败后会触发对 <code>abort()</code> 的调用，使我们能够在调试器中追溯我们是如何到达当前位置的。
* 

* 
* @code
     template <class MatrixType, class PreconditionerType>
     class InverseMatrix : public Subscriptor
     {
     public:
       InverseMatrix(const MatrixType &        m,
                     const PreconditionerType &preconditioner);
* 
 
       template <typename VectorType>
       void vmult(VectorType &dst, const VectorType &src) const;
* 
     private:
       const SmartPointer<const MatrixType> matrix;
       const PreconditionerType &           preconditioner;
     };
* 
 
     template <class MatrixType, class PreconditionerType>
     InverseMatrix<MatrixType, PreconditionerType>::InverseMatrix(
       const MatrixType &        m,
       const PreconditionerType &preconditioner)
       : matrix(&m)
       , preconditioner(preconditioner)
     {}
* 
 
* 
     template <class MatrixType, class PreconditionerType>
     template <typename VectorType>
     void InverseMatrix<MatrixType, PreconditionerType>::vmult(
       VectorType &      dst,
       const VectorType &src) const
     {
       SolverControl        solver_control(src.size(), 1e-7 src.l2_norm());
       SolverCG<VectorType> cg(solver_control);
* 
       dst = 0;
* 
       try
         {
           cg.solve(*matrix, dst, src, preconditioner);
         }
       catch (std::exception &e)
         {
           Assert(false, ExcMessage(e.what()));
         }
     }
* 
 @endcode
* 
* <a name="Schurcomplementpreconditioner"></a> <h4>Schur complement preconditioner</h4>.
 

* 
* 这是在介绍中详细描述的舒尔补码预处理的实现。与 step-20 和 step-22 相反，我们使用GMRES一次性解决块系统，并使用块结构矩阵的Schur补码来建立一个良好的预处理程序。    
* 让我们看一下介绍中描述的理想的预处理矩阵 $P=\left(\begin{array}{cc} A & 0 \\ B &
* 
-S \end{array}\right)$ 。如果我们在线性系统的求解中应用这个矩阵，迭代式GMRES求解器的收敛性将受矩阵@f{eqnarray*} P^{-1}\left(\begin{array}{cc} A &
 B^T \\ B & 0 \end{array}\right) = \left(\begin{array}{cc} I & A^{-1}
 B^T \\ 0 & I \end{array}\right), @f}的制约，这确实非常简单。基于精确矩阵的GMRES求解器将在一次迭代中收敛，因为所有的特征值都是相等的（任何Krylov方法最多需要多少次迭代就有多少个不同的特征值）。Silvester和Wathen提出了这样一个用于受阻斯托克斯系统的预处理程序（"稳定的斯托克斯系统的快速迭代解第二部分。 Using general block preconditioners", SIAM J. Numer. Anal., 31 (1994), pp. 1352-1367)。    
* 用 $\tilde{P}$ 代替 $P$ 可以保持这种精神：乘积 $P^{-1} A$ 仍将接近于特征值为1的矩阵，其分布不取决于问题的大小。这让我们希望能够得到一个与问题规模无关的GMRES迭代次数。    
*已经通过 step-20 和 step-22 教程的deal.II用户当然可以想象我们将如何实现这一点。 我们用一些由InverseMatrix类构建的近似逆矩阵来代替 $P^{-1}$ 中的精确逆矩阵，而逆舒尔补码将由压力质量矩阵 $M_p$ 来近似（如介绍中提到的由 $\eta^{-1}$ 加权）。正如在 step-22 的结果部分所指出的，我们可以通过应用一个预处理程序来取代 $A$ 的精确逆，在这种情况下，如介绍中所解释的那样，在一个矢量拉普拉斯矩阵上。这确实增加了（外部）GMRES的迭代次数，但仍然比精确的逆运算便宜得多，因为 <em> 的每个 </em> 外部求解器步骤（使用AMG预处理程序）需要20到35次CG迭代。    
* 考虑到上述解释，我们定义了一个具有 <code>vmult</code> 功能的预处理类，这就是我们在程序代码中进一步与通常的求解器函数进行交互所需要的一切。    
* 首先是声明。这与 step-20 中Schur补码的定义相似，不同的是我们在构造函数中需要更多的预处理程序，而且我们在这里使用的矩阵是建立在Trilinos之上的。
* 

* 
* @code
     template <class PreconditionerTypeA, class PreconditionerTypeMp>
     class BlockSchurPreconditioner : public Subscriptor
     {
     public:
       BlockSchurPreconditioner(
         const TrilinosWrappers::BlockSparseMatrix &S,
         const InverseMatrix<TrilinosWrappers::SparseMatrix,
                             PreconditionerTypeMp> &Mpinv,
         const PreconditionerTypeA &                Apreconditioner);
* 
       void vmult(TrilinosWrappers::MPI::BlockVector &      dst,
                  const TrilinosWrappers::MPI::BlockVector &src) const;
* 
     private:
       const SmartPointer<const TrilinosWrappers::BlockSparseMatrix>
         stokes_matrix;
       const SmartPointer<const InverseMatrix<TrilinosWrappers::SparseMatrix,
                                              PreconditionerTypeMp>>
                                  m_inverse;
       const PreconditionerTypeA &a_preconditioner;
* 
       mutable TrilinosWrappers::MPI::Vector tmp;
     };
* 
 
* 
 @endcode
* 
* 当使用 TrilinosWrappers::MPI::Vector 或 TrilinosWrappers::MPI::BlockVector, 时，Vector是使用IndexSet初始化的。IndexSet不仅用于调整 TrilinosWrappers::MPI::Vector 的大小，而且还将 TrilinosWrappers::MPI::Vector 中的一个索引与一个自由度联系起来（更详细的解释见 step-40 ）。函数complete_index_set()创建了一个IndexSet，每个有效的索引都是这个集合的一部分。请注意，这个程序只能按顺序运行，如果并行使用，将抛出一个异常。
* 

* 
* @code
     template <class PreconditionerTypeA, class PreconditionerTypeMp>
     BlockSchurPreconditioner<PreconditionerTypeA, PreconditionerTypeMp>::
       BlockSchurPreconditioner(
         const TrilinosWrappers::BlockSparseMatrix &S,
         const InverseMatrix<TrilinosWrappers::SparseMatrix,
                             PreconditionerTypeMp> &Mpinv,
         const PreconditionerTypeA &                Apreconditioner)
       : stokes_matrix(&S)
       , m_inverse(&Mpinv)
       , a_preconditioner(Apreconditioner)
       , tmp(complete_index_set(stokes_matrix->block(1, 1).m()))
     {}
* 
 
 @endcode
* 
* 接下来是 <code>vmult</code> 函数。我们以三个连续的步骤实现上述 $P^{-1}$ 的动作。 在公式中，我们要计算 $Y=P^{-1}X$ ，其中 $X,Y$ 都是有两个块分量的向量。    
* 第一步用矩阵 $A$ 的预处理乘以矢量的速度部分，即我们计算 $Y_0={\tilde
 A}^{-1}X_0$  。 然后将得到的速度矢量乘以 $B$ 并减去压力，即我们要计算 $X_1-BY_0$  。这第二步只作用于压力向量，由我们矩阵类的残差函数完成，只是符号不对。因此，我们改变临时压力向量中的符号，最后乘以反压力质量矩阵，得到最终的压力向量，完成我们对斯托克斯预处理的工作。
* 

* 
* @code
     template <class PreconditionerTypeA, class PreconditionerTypeMp>
     void
     BlockSchurPreconditioner<PreconditionerTypeA, PreconditionerTypeMp>::vmult(
       TrilinosWrappers::MPI::BlockVector &      dst,
       const TrilinosWrappers::MPI::BlockVector &src) const
     {
       a_preconditioner.vmult(dst.block(0), src.block(0));
       stokes_matrix->block(1, 0).residual(tmp, dst.block(0), src.block(1));
       tmp=
* 
-1;
       m_inverse->vmult(dst.block(1), tmp);
     }
   } // namespace LinearSolvers
* 
 
* 
 @endcode
* 
* <a name="ThecodeBoussinesqFlowProblemcodeclasstemplate"></a> <h3>The <code>BoussinesqFlowProblem</code> class template</h3> * <h3>The <code>BoussinesqFlowProblem</code> class template</h3>.
 

* 
* 定义了解决时间相关的Boussinesq问题的顶层逻辑的类，主要是基于 step-22 的教程程序。主要的区别在于，现在我们还必须求解温度方程，这就迫使我们为温度变量准备第二个DoFHandler对象，以及当前和之前时间步骤的矩阵、右手边和求解向量。正如介绍中提到的，所有的线性代数对象都要使用相应的Trilinos功能的包装器。  
* 这个类的成员函数让人想起 step-21 ，在那里我们也使用了一个交错的方案，首先解决流动方程（这里是斯托克斯方程，在 step-21 中是达西流动），然后更新平流量（这里是温度，那里是饱和度）。新的函数主要涉及到确定时间步长，以及人工粘性稳定的适当大小。  
* 最后三个变量表示在下一次调用相应的建立函数时，是否需要重新建立各种矩阵或预处理程序。这使得我们可以将相应的 <code>if</code> 移到相应的函数中，从而保持我们的主 <code>run()</code> 函数的简洁和易读。
* 

* 
* @code
   template <int dim>
   class BoussinesqFlowProblem
   {
   public:
     BoussinesqFlowProblem();
     void run();
* 
   private:
     void   setup_dofs();
     void   assemble_stokes_preconditioner();
     void   build_stokes_preconditioner();
     void   assemble_stokes_system();
     void   assemble_temperature_system(const double maximal_velocity);
     void   assemble_temperature_matrix();
     double get_maximal_velocity() const;
     std::pair<double, double> get_extrapolated_temperature_range() const;
     void                      solve();
     void                      output_results() const;
     void                      refine_mesh(const unsigned int max_grid_level);
* 
     double compute_viscosity(
       const std::vector<double> &        old_temperature,
       const std::vector<double> &        old_old_temperature,
       const std::vector<Tensor<1, dim>> &old_temperature_grads,
       const std::vector<Tensor<1, dim>> &old_old_temperature_grads,
       const std::vector<double> &        old_temperature_laplacians,
       const std::vector<double> &        old_old_temperature_laplacians,
       const std::vector<Tensor<1, dim>> &old_velocity_values,
       const std::vector<Tensor<1, dim>> &old_old_velocity_values,
       const std::vector<double> &        gamma_values,
       const double                       global_u_infty,
       const double                       global_T_variation,
       const double                       cell_diameter) const;
* 
 
     Triangulation<dim> triangulation;
     double             global_Omega_diameter;
* 
     const unsigned int        stokes_degree;
     FESystem<dim>             stokes_fe;
     DoFHandler<dim>           stokes_dof_handler;
     AffineConstraints<double> stokes_constraints;
* 
     std::vector<IndexSet>               stokes_partitioning;
     TrilinosWrappers::BlockSparseMatrix stokes_matrix;
     TrilinosWrappers::BlockSparseMatrix stokes_preconditioner_matrix;
* 
     TrilinosWrappers::MPI::BlockVector stokes_solution;
     TrilinosWrappers::MPI::BlockVector old_stokes_solution;
     TrilinosWrappers::MPI::BlockVector stokes_rhs;
* 
 
     const unsigned int        temperature_degree;
     FE_Q<dim>                 temperature_fe;
     DoFHandler<dim>           temperature_dof_handler;
     AffineConstraints<double> temperature_constraints;
* 
     TrilinosWrappers::SparseMatrix temperature_mass_matrix;
     TrilinosWrappers::SparseMatrix temperature_stiffness_matrix;
     TrilinosWrappers::SparseMatrix temperature_matrix;
* 
     TrilinosWrappers::MPI::Vector temperature_solution;
     TrilinosWrappers::MPI::Vector old_temperature_solution;
     TrilinosWrappers::MPI::Vector old_old_temperature_solution;
     TrilinosWrappers::MPI::Vector temperature_rhs;
* 
 
     double       time_step;
     double       old_time_step;
     unsigned int timestep_number;
* 
     std::shared_ptr<TrilinosWrappers::PreconditionAMG> Amg_preconditioner;
     std::shared_ptr<TrilinosWrappers::PreconditionIC>  Mp_preconditioner;
* 
     bool rebuild_stokes_matrix;
     bool rebuild_temperature_matrices;
     bool rebuild_stokes_preconditioner;
   };
* 
 
 @endcode
* 
* <a name="BoussinesqFlowProblemclassimplementation"></a> <h3>BoussinesqFlowProblem class implementation</h3>.
 

* 
* <a name="BoussinesqFlowProblemBoussinesqFlowProblem"></a> <h4>BoussinesqFlowProblem::BoussinesqFlowProblem</h4>   
* 该类的构造函数是对  step-22  中的构造函数的扩展。我们需要添加涉及温度的各种变量。正如介绍中所讨论的，我们将再次使用 $Q_2\times Q_1$ （Taylor-Hood）元素来表示斯托克斯部分，并使用 $Q_2$ 元素表示温度。然而，通过使用存储斯托克斯和温度有限元的多项式程度的变量，可以很容易地持续修改这些元素的程度，以及下游使用的所有正交公式。此外，我们还初始化了时间步长，以及矩阵组合和预处理的选项。
* 

* 
* @code
   template <int dim>
   BoussinesqFlowProblem<dim>::BoussinesqFlowProblem()
     : triangulation(Triangulation<dim>::maximum_smoothing)
     , global_Omega_diameter(std::numeric_limits<double>::quiet_NaN())
     , stokes_degree(1)
     , stokes_fe(FE_Q<dim>(stokes_degree + 1), dim, FE_Q<dim>(stokes_degree), 1)
     , stokes_dof_handler(triangulation)
     ,
* 
     temperature_degree(2)
     , temperature_fe(temperature_degree)
     , temperature_dof_handler(triangulation)
     ,
* 
     time_step(0)
     , old_time_step(0)
     , timestep_number(0)
     , rebuild_stokes_matrix(true)
     , rebuild_temperature_matrices(true)
     , rebuild_stokes_preconditioner(true)
   {}
* 
 
* 
 @endcode
* 
* <a name="BoussinesqFlowProblemget_maximal_velocity"></a> <h4>BoussinesqFlowProblem::get_maximal_velocity</h4>
 

* 
* 开始这个类的真正功能是一个辅助函数，它确定域中（实际上是正交点处）的最大（ $L_\infty$ ）速度。它是如何工作的，对所有已经达到本教程这一点的人来说应该是比较明显的。请注意，由于我们只对速度感兴趣，我们不使用 <code>stokes_fe_values.get_function_values</code> 来获取整个斯托克斯解的值（速度和压力），而是使用 <code>stokes_fe_values[velocities].get_function_values</code> 来提取速度部分。这有一个额外的好处，即我们得到的是一个张量<1,dim>，而不是向量<double>中的一些分量，使我们能够立即使用 <code>norm()</code> 函数来处理它，以得到速度的大小。  
*唯一值得思考一下的是如何选择我们在这里使用的正交点。因为这个函数的目标是通过查看每个单元上的正交点来找到域上的最大速度。所以我们应该问，我们应该如何最好地选择每个单元上的这些正交点。为此，回顾一下，如果我们有一个单一的 $Q_1$ 场（而不是高阶的矢量值场），那么最大值将在网格的一个顶点达到。换句话说，我们应该使用QTrapezoid类，它的正交点只在单元的顶点。  
* 对于高阶形状函数，情况更为复杂：最大值和最小值可能在形状函数的支持点之间的点上达到（对于通常的 $Q_p$ 元素，支持点是等距的Lagrange插值点）；此外，由于我们正在寻找一个矢量值量的最大幅度，我们更不能肯定地说潜在的最大点集合在哪里。尽管如此，从直觉上看，如果不能证明，拉格朗日插值点似乎比高斯点更好。  
* 现在有不同的方法来产生一个正交公式，其正交点等于有限元的插值点。一种选择是使用 FiniteElement::get_unit_support_points() 函数，将输出减少到一组唯一的点以避免重复的函数评估，并使用这些点创建一个正交对象。另一个选择，这里选择的是使用QTrapezoid类，并将其与QIterated类相结合，该类在每个坐标方向的若干子单元上重复QTrapezoid公式。为了覆盖所有的支持点，我们需要将其迭代 <code>stokes_degree+1</code> 次，因为这是使用中的斯托克斯元素的多项式程度。
* 

* 
* @code
   template <int dim>
   double BoussinesqFlowProblem<dim>::get_maximal_velocity() const
   {
     const QIterated<dim> quadrature_formula(QTrapezoid<1>(), stokes_degree + 1);
     const unsigned int   n_q_points = quadrature_formula.size();
* 
     FEValues<dim> fe_values(stokes_fe, quadrature_formula, update_values);
     std::vector<Tensor<1, dim>> velocity_values(n_q_points);
     double                      max_velocity = 0;
* 
     const FEValuesExtractors::Vector velocities(0);
* 
     for (const auto &cell : stokes_dof_handler.active_cell_iterators())
       {
         fe_values.reinit(cell);
         fe_values[velocities].get_function_values(stokes_solution,
                                                   velocity_values);
* 
         for (unsigned int q = 0; q < n_q_points; ++q)
           max_velocity = std::max(max_velocity, velocity_values[q].norm());
       }
* 
     return max_velocity;
   }
* 
 
* 
 @endcode
* 
* <a name="BoussinesqFlowProblemget_extrapolated_temperature_range"></a> <h4>BoussinesqFlowProblem::get_extrapolated_temperature_range</h4>。
 

* 
* 接下来是一个函数，确定从前两个时间步长推算到当前步长时， $\Omega$ 内正交点的最低和最高温度。我们在计算人工粘性参数 $\nu$ 时需要这个信息，正如在介绍中讨论的那样。  
* 外推温度的公式是  $\left(1+\frac{k_n}{k_{n-1}} \right)T^{n-1} + \frac{k_n}{k_{n-1}}
 T^{n-2}$  。计算它的方法是在所有正交点上循环，如果当前值比前一个值大/小，则更新最大和最小值。在对所有正交点进行循环之前，我们将存储最大和最小值的变量初始化为最小和最大的可表示为双数的数字。然后我们就知道它比最小/最大值大/小，并且所有正交点的循环最终会用正确的值更新初始值。  
* 这里唯一值得一提的其他复杂情况是，在第一个时间步骤中， $T^{k-2}$ 当然还不能使用。在这种情况下，我们只能使用 $T^{k-1}$ ，这是我们从初始温度得到的。作为正交点，我们使用与前一个函数相同的选择，但不同的是，现在重复的数量由温度场的多项式程度决定。
* 

* 
* @code
   template <int dim>
   std::pair<double, double>
   BoussinesqFlowProblem<dim>::get_extrapolated_temperature_range() const
   {
     const QIterated<dim> quadrature_formula(QTrapezoid<1>(),
                                             temperature_degree);
     const unsigned int   n_q_points = quadrature_formula.size();
* 
     FEValues<dim> fe_values(temperature_fe, quadrature_formula, update_values);
     std::vector<double> old_temperature_values(n_q_points);
     std::vector<double> old_old_temperature_values(n_q_points);
* 
     if (timestep_number != 0)
       {
         double min_temperature = std::numeric_limits<double>::max(),
                max_temperature =
* 
-std::numeric_limits<double>::max();
* 
         for (const auto &cell : temperature_dof_handler.active_cell_iterators())
           {
             fe_values.reinit(cell);
             fe_values.get_function_values(old_temperature_solution,
                                           old_temperature_values);
             fe_values.get_function_values(old_old_temperature_solution,
                                           old_old_temperature_values);
* 
             for (unsigned int q = 0; q < n_q_points; ++q)
               {
                 const double temperature =
                   (1. + time_step / old_time_step) old_temperature_values[q]
* 
-
                   time_step / old_time_step old_old_temperature_values[q];
* 
                 min_temperature = std::min(min_temperature, temperature);
                 max_temperature = std::max(max_temperature, temperature);
               }
           }
* 
         return std::make_pair(min_temperature, max_temperature);
       }
     else
       {
         double min_temperature = std::numeric_limits<double>::max(),
                max_temperature =
* 
-std::numeric_limits<double>::max();
* 
         for (const auto &cell : temperature_dof_handler.active_cell_iterators())
           {
             fe_values.reinit(cell);
             fe_values.get_function_values(old_temperature_solution,
                                           old_temperature_values);
* 
             for (unsigned int q = 0; q < n_q_points; ++q)
               {
                 const double temperature = old_temperature_values[q];
* 
                 min_temperature = std::min(min_temperature, temperature);
                 max_temperature = std::max(max_temperature, temperature);
               }
           }
* 
         return std::make_pair(min_temperature, max_temperature);
       }
   }
* 
 
* 
 @endcode
* 
* <a name="BoussinesqFlowProblemcompute_viscosity"></a> <h4>BoussinesqFlowProblem::compute_viscosity</h4>
 

* 
* 最后一个工具函数计算单元 $\nu|_K$ 上的人工粘度参数 $K$ ，作为外推温度、其梯度和Hessian（二阶导数）、速度的函数，右手 $\gamma$ 都在当前单元的正交点上，以及在介绍中详细描述的各种其他参数。  
* 这里有一些值得一提的通用常数。首先，我们需要固定 $\beta$ ；我们选择 $\beta=0.017\cdot dim$ ，这个选择在本教程程序的结果部分有详细讨论。其次是指数 $\alpha$ ； $\alpha=1$ 似乎对目前的程序来说工作正常，尽管选择 $\alpha = 2$ 可能会有一些额外的好处。最后，有一件事需要特别说明。在第一个时间步骤中，速度等于零， $\nu|_K$ 的公式没有定义。在这种情况下，我们返回 $\nu|_K=5\cdot 10^3
 \cdot h_K$ ，这个选择无疑更多的是出于启发式的考虑（不过，它与第二个时间步骤中大多数单元的返回值处于同一数量级）。  
* 根据介绍中讨论的材料，该函数的其余部分应该是很明显的。
* 

* 
* @code
   template <int dim>
   double BoussinesqFlowProblem<dim>::compute_viscosity(
     const std::vector<double> &        old_temperature,
     const std::vector<double> &        old_old_temperature,
     const std::vector<Tensor<1, dim>> &old_temperature_grads,
     const std::vector<Tensor<1, dim>> &old_old_temperature_grads,
     const std::vector<double> &        old_temperature_laplacians,
     const std::vector<double> &        old_old_temperature_laplacians,
     const std::vector<Tensor<1, dim>> &old_velocity_values,
     const std::vector<Tensor<1, dim>> &old_old_velocity_values,
     const std::vector<double> &        gamma_values,
     const double                       global_u_infty,
     const double                       global_T_variation,
     const double                       cell_diameter) const
   {
     constexpr double beta  = 0.017 dim;
     constexpr double alpha = 1.0;
* 
     if (global_u_infty == 0)
       return 5e-3 cell_diameter;
* 
     const unsigned int n_q_points = old_temperature.size();
* 
     double max_residual = 0;
     double max_velocity = 0;
* 
     for (unsigned int q = 0; q < n_q_points; ++q)
       {
         const Tensor<1, dim> u =
           (old_velocity_values[q] + old_old_velocity_values[q]) / 2;
* 
         const double dT_dt =
           (old_temperature[q]
* 
- old_old_temperature[q]) / old_time_step;
         const double u_grad_T =
           u (old_temperature_grads[q] + old_old_temperature_grads[q]) / 2;
* 
         const double kappa_Delta_T =
           EquationData::kappa
           (old_temperature_laplacians[q] + old_old_temperature_laplacians[q]) /
           2;
* 
         const double residual =
           std::abs((dT_dt + u_grad_T
* 
- kappa_Delta_T
* 
- gamma_values[q])
                    std::pow((old_temperature[q] + old_old_temperature[q]) / 2,
                             alpha
* 
- 1.));
* 
         max_residual = std::max(residual, max_residual);
         max_velocity = std::max(std::sqrt(u u), max_velocity);
       }
* 
     const double c_R            = std::pow(2., (4.
* 
- 2 alpha) / dim);
     const double global_scaling = c_R global_u_infty global_T_variation
                                   std::pow(global_Omega_diameter, alpha
* 
- 2.);
* 
     return (
       beta max_velocity
       std::min(cell_diameter,
                std::pow(cell_diameter, alpha) max_residual / global_scaling));
   }
* 
 
* 
 @endcode
* 
* <a name="BoussinesqFlowProblemsetup_dofs"></a> <h4>BoussinesqFlowProblem::setup_dofs</h4>   
* 这是一个函数，用来设置我们这里的DoFHandler对象（一个用于斯托克斯部分，一个用于温度部分），以及将本程序中线性代数所需的各种对象设置为正确的尺寸。它的基本操作与我们在  step-22  中的操作相似。  
* 该函数的主体首先列举了斯托克斯和温度系统的所有自由度。对于斯托克斯部分，自由度被排序以确保速度优先于压力自由度，这样我们就可以将斯托克斯矩阵划分为 $2\times 2$ 矩阵。作为与 step-22 的区别，我们不进行任何额外的DoF重新编号。在那个程序中，它得到了回报，因为我们的求解器严重依赖ILU，而我们在这里使用AMG，它对DoF编号不敏感。用于反演压力质量矩阵的IC预处理程序当然会利用类似Cuthill-McKee的重新编号，但是与速度部分相比，它的成本很低，所以额外的工作并没有得到回报。  
* 然后，我们继续生成悬挂节点约束，这些约束来自于两个DoFHandler对象的自适应网格细化。对于速度，我们通过向已经存储了悬挂节点约束矩阵的对象添加约束来施加无流边界条件 $\mathbf{u}\cdot
 \mathbf{n}=0$ 。函数中的第二个参数描述了总dof向量中的第一个速度分量，这里是零。变量 <code>no_normal_flux_boundaries</code> 表示要设置无通量边界条件的边界指标；这里是边界指标0。  
* 做完这些后，我们计算各块中的自由度数量。
* 

* 
* @code
   template <int dim>
   void BoussinesqFlowProblem<dim>::setup_dofs()
   {
     std::vector<unsigned int> stokes_sub_blocks(dim + 1, 0);
     stokes_sub_blocks[dim] = 1;
* 
     {
       stokes_dof_handler.distribute_dofs(stokes_fe);
       DoFRenumbering::component_wise(stokes_dof_handler, stokes_sub_blocks);
* 
       stokes_constraints.clear();
       DoFTools::make_hanging_node_constraints(stokes_dof_handler,
                                               stokes_constraints);
       std::set<types::boundary_id> no_normal_flux_boundaries;
       no_normal_flux_boundaries.insert(0);
       VectorTools::compute_no_normal_flux_constraints(stokes_dof_handler,
                                                       0,
                                                       no_normal_flux_boundaries,
                                                       stokes_constraints);
       stokes_constraints.close();
     }
     {
       temperature_dof_handler.distribute_dofs(temperature_fe);
* 
       temperature_constraints.clear();
       DoFTools::make_hanging_node_constraints(temperature_dof_handler,
                                               temperature_constraints);
       temperature_constraints.close();
     }
* 
     const std::vector<types::global_dof_index> stokes_dofs_per_block =
       DoFTools::count_dofs_per_fe_block(stokes_dof_handler, stokes_sub_blocks);
* 
     const unsigned int n_u = stokes_dofs_per_block[0],
                        n_p = stokes_dofs_per_block[1],
                        n_T = temperature_dof_handler.n_dofs();
* 
     std::cout << "Number of active cells: " << triangulation.n_active_cells()
               << " (on " << triangulation.n_levels() << " levels)" << std::endl
               << "Number of degrees of freedom: " << n_u + n_p + n_T << " ("
               << n_u << '+' << n_p << '+' << n_T << ')' << std::endl
               << std::endl;
* 
 @endcode
 
* 下一步是为斯托克斯和温度系统矩阵以及预处理矩阵创建稀疏模式，我们从这些矩阵中建立斯托克斯预处理程序。如同在 step-22 中，我们选择使用DynamicSparsityPattern的封锁版本来创建模式。    
* 因此，我们首先释放存储在矩阵中的内存，然后设置一个BlockDynamicSparsityPattern类型的对象，该对象由 $2\times 2$ 块（用于斯托克斯系统矩阵和前置条件器）或DynamicSparsityPattern（用于温度部分）组成。然后我们用非零模式填充这些对象，考虑到对于斯托克斯系统矩阵，在压力-压力块中没有条目（但所有速度矢量分量相互耦合并与压力耦合）。同样，在斯托克斯预处理矩阵中，只有对角线块是非零的，因为我们使用了介绍中讨论的矢量拉普拉斯。这个算子只把拉普拉斯的每个矢量分量与它自己联系起来，而不是与其他矢量分量联系起来。然而，应用无流量边界条件产生的约束条件将在边界处再次耦合向量分量）。    
* 当生成稀疏模式时，我们直接应用悬挂节点和无流边界条件的约束。这种方法在 step-27 中已经使用过了，但与早期教程中的方法不同，在早期教程中，我们先建立原始的稀疏模式，然后才加入约束条件产生的条目。这样做的原因是，在以后的装配过程中，我们要在将本地道夫转移到全局道夫时立即分配约束。因此，在受限自由度的位置不会有数据写入，所以我们可以通过将最后一个布尔标志设置为 <code>false</code> ，让 DoFTools::make_sparsity_pattern 函数省略这些条目。一旦疏散模式准备好了，我们就可以用它来初始化特里诺斯矩阵。由于Trilinos矩阵在内部存储了稀疏模式，所以在初始化矩阵之后，没有必要再保留稀疏模式。
* 

* 
* @code
     stokes_partitioning.resize(2);
     stokes_partitioning[0] = complete_index_set(n_u);
     stokes_partitioning[1] = complete_index_set(n_p);
     {
       stokes_matrix.clear();
* 
       BlockDynamicSparsityPattern dsp(2, 2);
* 
       dsp.block(0, 0).reinit(n_u, n_u);
       dsp.block(0, 1).reinit(n_u, n_p);
       dsp.block(1, 0).reinit(n_p, n_u);
       dsp.block(1, 1).reinit(n_p, n_p);
* 
       dsp.collect_sizes();
* 
       Table<2, DoFTools::Coupling> coupling(dim + 1, dim + 1);
* 
       for (unsigned int c = 0; c < dim + 1; ++c)
         for (unsigned int d = 0; d < dim + 1; ++d)
           if (!((c == dim) && (d == dim)))
             coupling[c][d] = DoFTools::always;
           else
             coupling[c][d] = DoFTools::none;
* 
       DoFTools::make_sparsity_pattern(
         stokes_dof_handler, coupling, dsp, stokes_constraints, false);
* 
       stokes_matrix.reinit(dsp);
     }
* 
     {
       Amg_preconditioner.reset();
       Mp_preconditioner.reset();
       stokes_preconditioner_matrix.clear();
* 
       BlockDynamicSparsityPattern dsp(2, 2);
* 
       dsp.block(0, 0).reinit(n_u, n_u);
       dsp.block(0, 1).reinit(n_u, n_p);
       dsp.block(1, 0).reinit(n_p, n_u);
       dsp.block(1, 1).reinit(n_p, n_p);
* 
       dsp.collect_sizes();
* 
       Table<2, DoFTools::Coupling> coupling(dim + 1, dim + 1);
       for (unsigned int c = 0; c < dim + 1; ++c)
         for (unsigned int d = 0; d < dim + 1; ++d)
           if (c == d)
             coupling[c][d] = DoFTools::always;
           else
             coupling[c][d] = DoFTools::none;
* 
       DoFTools::make_sparsity_pattern(
         stokes_dof_handler, coupling, dsp, stokes_constraints, false);
* 
       stokes_preconditioner_matrix.reinit(dsp);
     }
* 
 @endcode
 
* 温度矩阵（或者说是矩阵，因为我们提供了一个温度质量矩阵和一个温度刚度矩阵，它们将在时间离散化中被加在一起）的创建与斯托克斯矩阵的生成相同；只是这里要简单得多，因为我们不需要照顾任何块或组件之间的耦合。注意我们是如何初始化三个温度矩阵的。我们只使用稀疏模式对第一个矩阵进行再初始化，而对其余两个再初始化则使用先前生成的矩阵。这样做的原因是，从一个已经生成的矩阵进行重新初始化，可以让Trilinos重新使用稀疏模式，而不是为每个副本生成一个新的模式。这可以节省一些时间和内存。
* 

* 
* @code
     {
       temperature_mass_matrix.clear();
       temperature_stiffness_matrix.clear();
       temperature_matrix.clear();
* 
       DynamicSparsityPattern dsp(n_T, n_T);
       DoFTools::make_sparsity_pattern(temperature_dof_handler,
                                       dsp,
                                       temperature_constraints,
                                       false);
* 
       temperature_matrix.reinit(dsp);
       temperature_mass_matrix.reinit(temperature_matrix);
       temperature_stiffness_matrix.reinit(temperature_matrix);
     }
* 
 @endcode
 
* 最后，我们为斯托克斯解 $\mathbf u^{n-1}$ 和 $\mathbf u^{n-2}$ 以及温度 $T^{n}$ 、 $T^{n-1}$ 和 $T^{n-2}$ （时间步进所需）设置向量，并将所有系统的右侧设置为正确的大小和块结构。
* 

* 
* @code
     IndexSet temperature_partitioning = complete_index_set(n_T);
     stokes_solution.reinit(stokes_partitioning, MPI_COMM_WORLD);
     old_stokes_solution.reinit(stokes_partitioning, MPI_COMM_WORLD);
     stokes_rhs.reinit(stokes_partitioning, MPI_COMM_WORLD);
* 
     temperature_solution.reinit(temperature_partitioning, MPI_COMM_WORLD);
     old_temperature_solution.reinit(temperature_partitioning, MPI_COMM_WORLD);
     old_old_temperature_solution.reinit(temperature_partitioning,
                                         MPI_COMM_WORLD);
* 
     temperature_rhs.reinit(temperature_partitioning, MPI_COMM_WORLD);
   }
* 
 
* 
 @endcode
* 
* <a name="BoussinesqFlowProblemassemble_stokes_preconditioner"></a> <h4>BoussinesqFlowProblem::assemble_stokes_preconditioner</h4>。  
* 这个函数集合了我们用于预处理斯托克斯系统的矩阵。我们需要的是速度分量上的矢量拉普拉斯矩阵和压力分量上的质量矩阵，并以 $\eta^{-1}$ 加权。我们首先生成一个适当阶数的正交对象，即FEValues对象，它可以给出正交点的值和梯度（连同正交权重）。接下来我们为单元格矩阵和局部与全局DoF之间的关系创建数据结构。向量 <code>grad_phi_u</code> and <code>phi_p</code> 将保存基础函数的值，以便更快地建立局部矩阵，正如在 step-22 中已经完成的那样。在我们开始对所有活动单元进行循环之前，我们必须指定哪些成分是压力，哪些是速度。
* 

* 
* @code
   template <int dim>
   void BoussinesqFlowProblem<dim>::assemble_stokes_preconditioner()
   {
     stokes_preconditioner_matrix = 0;
* 
     const QGauss<dim> quadrature_formula(stokes_degree + 2);
     FEValues<dim>     stokes_fe_values(stokes_fe,
                                    quadrature_formula,
                                    update_JxW_values | update_values |
                                      update_gradients);
* 
     const unsigned int dofs_per_cell = stokes_fe.n_dofs_per_cell();
     const unsigned int n_q_points    = quadrature_formula.size();
* 
     FullMatrix<double> local_matrix(dofs_per_cell, dofs_per_cell);
     std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);
* 
     std::vector<Tensor<2, dim>> grad_phi_u(dofs_per_cell);
     std::vector<double>         phi_p(dofs_per_cell);
* 
     const FEValuesExtractors::Vector velocities(0);
     const FEValuesExtractors::Scalar pressure(dim);
* 
     for (const auto &cell : stokes_dof_handler.active_cell_iterators())
       {
         stokes_fe_values.reinit(cell);
         local_matrix = 0;
* 
 @endcode
 
* 本地矩阵的建立相当简单。只有一个拉普拉斯项（关于速度）和一个由 $\eta^{-1}$ 加权的质量矩阵需要生成，所以本地矩阵的创建在两行完成。一旦本地矩阵准备好了（在每个正交点上循环查看本地矩阵的行和列），我们就可以得到本地DoF指数，并将本地信息写入全局矩阵。我们像在 step-27 中那样做，也就是说，我们直接应用本地悬挂节点的约束。这样做，我们就不必事后再做，也不会在消除约束时把实际上会再次设置为零的条目写进矩阵中。
* 

* 
* @code
         for (unsigned int q = 0; q < n_q_points; ++q)
           {
             for (unsigned int k = 0; k < dofs_per_cell; ++k)
               {
                 grad_phi_u[k] = stokes_fe_values[velocities].gradient(k, q);
                 phi_p[k]      = stokes_fe_values[pressure].value(k, q);
               }
* 
             for (unsigned int i = 0; i < dofs_per_cell; ++i)
               for (unsigned int j = 0; j < dofs_per_cell; ++j)
                 local_matrix(i, j) +=
                   (EquationData::eta
                      scalar_product(grad_phi_u[i], grad_phi_u[j]) +
                    (1. / EquationData::eta) phi_p[i] phi_p[j])
                   stokes_fe_values.JxW(q);
           }
* 
         cell->get_dof_indices(local_dof_indices);
         stokes_constraints.distribute_local_to_global(
           local_matrix, local_dof_indices, stokes_preconditioner_matrix);
       }
   }
* 
 
* 
 @endcode
* 
* <a name="BoussinesqFlowProblembuild_stokes_preconditioner"></a> <h4>BoussinesqFlowProblem::build_stokes_preconditioner</h4>   
* 该函数生成将用于舒尔补码预处理器的内部预处理器。由于只有当矩阵发生变化时才需要重新生成预处理程序，因此在矩阵没有变化的情况下，该函数不需要做任何事情（即标志 <code>rebuild_stokes_preconditioner</code> 的值为 <code>false</code> ）。否则它的第一个任务是调用 <code>assemble_stokes_preconditioner</code> 来生成预处理矩阵。  
* 接下来，我们为速度-速度矩阵 $A$ 设置预处理器。正如介绍中所解释的，我们将使用基于矢量拉普拉斯矩阵 $\hat{A}$ 的AMG预处理器（它在频谱上与斯托克斯矩阵 $A$ 接近）。通常， TrilinosWrappers::PreconditionAMG 类可以被看作是一个好的黑箱预处理器，不需要任何特殊的知识。然而，在这种情况下，我们必须小心：由于我们为一个矢量问题建立了一个AMG，我们必须告诉预处理程序设置哪些道夫属于哪个矢量分量。我们使用函数 DoFTools::extract_constant_modes, 来做这件事，该函数生成一组 <code>dim</code> 向量，其中每个向量在向量问题的相应分量中为1，在其他地方为0。因此，这些是每个分量上的常数模式，这解释了变量的名称。
* 

* 
* @code
   template <int dim>
   void BoussinesqFlowProblem<dim>::build_stokes_preconditioner()
   {
     if (rebuild_stokes_preconditioner == false)
       return;
* 
     std::cout << "   Rebuilding Stokes preconditioner..." << std::flush;
* 
     assemble_stokes_preconditioner();
* 
     Amg_preconditioner = std::make_shared<TrilinosWrappers::PreconditionAMG>();
* 
     std::vector<std::vector<bool>> constant_modes;
     FEValuesExtractors::Vector     velocity_components(0);
     DoFTools::extract_constant_modes(stokes_dof_handler,
                                      stokes_fe.component_mask(
                                        velocity_components),
                                      constant_modes);
     TrilinosWrappers::PreconditionAMG::AdditionalData amg_data;
     amg_data.constant_modes = constant_modes;
* 
 @endcode
* 
* 接下来，我们再设置一些AMG预处理程序的选项。特别是，我们需要告诉AMG设置，我们对速度矩阵使用二次基函数（这意味着矩阵中有更多的非零元素，因此需要在内部选择一个更稳健的算法）。此外，我们希望能够控制粗化结构的建立方式。Trilinos平滑聚合AMG的方法是寻找哪些矩阵条目与对角线条目大小相似，以便代数式地建立一个粗网格结构。通过将参数 <code>aggregation_threshold</code> 设置为0.02，我们指定所有尺寸超过该行中一些对角线枢轴的百分之二的条目应该形成一个粗网格点。这个参数是比较特别的，对它进行一些微调会影响预处理程序的性能。根据经验，较大的 <code>aggregation_threshold</code> 值会减少迭代次数，但增加每次迭代的成本。看一下Trilinos的文档会提供更多关于这些参数的信息。有了这个数据集，我们就用我们想要的矩阵来初始化预处理程序。    
* 最后，我们也初始化预处理程序，用于反转压力质量矩阵。这个矩阵是对称的，表现良好，所以我们可以选择一个简单的预处理程序。我们坚持使用不完全Cholesky（IC）因子化预处理器，它是为对称矩阵设计的。我们也可以选择SSOR预处理器，其松弛系数约为1.2，但IC对我们的例子来说更便宜。我们把预处理程序包成一个 <code>std::shared_ptr</code> 指针，这使得下次重新创建预处理程序更加容易，因为我们不必关心破坏以前使用的对象。
* 

* 
* @code
     amg_data.elliptic              = true;
     amg_data.higher_order_elements = true;
     amg_data.smoother_sweeps       = 2;
     amg_data.aggregation_threshold = 0.02;
     Amg_preconditioner->initialize(stokes_preconditioner_matrix.block(0, 0),
                                    amg_data);
* 
     Mp_preconditioner = std::make_shared<TrilinosWrappers::PreconditionIC>();
     Mp_preconditioner->initialize(stokes_preconditioner_matrix.block(1, 1));
* 
     std::cout << std::endl;
* 
     rebuild_stokes_preconditioner = false;
   }
* 
 
* 
 @endcode
* 
* <a name="BoussinesqFlowProblemassemble_stokes_system"></a> <h4>BoussinesqFlowProblem::assemble_stokes_system</h4>   
* 我们用于推进耦合的斯托克斯-温度系统的时间滞后方案迫使我们将装配（以及线性系统的求解）分成两步。第一步是创建斯托克斯系统的矩阵和右手边，第二步是创建温度道夫的矩阵和右手边，这取决于速度的线性系统的结果。  
*这个函数在每个时间步的开始被调用。在第一个时间步骤中，或者如果网格已经改变，由 <code>rebuild_stokes_matrix</code> 表示，我们需要组装斯托克斯矩阵；另一方面，如果网格没有改变，矩阵已经可用，这就没有必要了，我们需要做的是组装在每个时间步骤中改变的右手向量。  
* 关于实施的技术细节，与 step-22 相比没有太大变化。我们重置矩阵和向量，在单元格上创建正交公式，然后创建相应的FEValues对象。对于更新标志，我们只在完全装配的情况下需要基函数导数，因为右手边不需要它们；像往常一样，根据当前需要选择最小的标志集，使程序中进一步调用 FEValues::reinit 的效率更高。  
* 有一件事需要评论&ndash；因为我们有一个单独的有限元和DoFHandler来处理温度问题，所以我们需要生成第二个FEValues对象来正确评估温度解决方案。要实现这一点并不复杂：只需使用温度结构，并为我们需要用于评估温度解决方案的基函数值设置一个更新标志。这里唯一需要记住的是，两个FEValues对象使用相同的正交公式，以确保我们在两个对象的正交点上循环时得到匹配的信息。  
* 声明的过程中，对数组的大小、本地矩阵和右手的创建以及与全局系统相比，本地道夫的指数的向量都有一些捷径。
* 

* 
* @code
   template <int dim>
   void BoussinesqFlowProblem<dim>::assemble_stokes_system()
   {
     std::cout << "   Assembling..." << std::flush;
* 
     if (rebuild_stokes_matrix == true)
       stokes_matrix = 0;
* 
     stokes_rhs = 0;
* 
     const QGauss<dim> quadrature_formula(stokes_degree + 2);
     FEValues<dim>     stokes_fe_values(
       stokes_fe,
       quadrature_formula,
       update_values | update_quadrature_points | update_JxW_values |
         (rebuild_stokes_matrix == true ? update_gradients : UpdateFlags(0)));
* 
     FEValues<dim> temperature_fe_values(temperature_fe,
                                         quadrature_formula,
                                         update_values);
* 
     const unsigned int dofs_per_cell = stokes_fe.n_dofs_per_cell();
     const unsigned int n_q_points    = quadrature_formula.size();
* 
     FullMatrix<double> local_matrix(dofs_per_cell, dofs_per_cell);
     Vector<double>     local_rhs(dofs_per_cell);
* 
     std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);
* 
 @endcode
 
* 接下来我们需要一个向量，它将包含在正交点的前一个时间层次的温度解的值，以组装动量方程右边的源项。让我们把这个向量称为 <code>old_solution_values</code>  。    
* 我们接下来创建的一组向量包含了基函数的评估以及它们的梯度和对称梯度，这些梯度将被用于创建矩阵。将这些放到自己的数组中，而不是每次需要时都向FEValues对象询问这些信息，是为了加速装配过程的优化，详见 step-22  。    
* 最后两个声明是用来从整个FE系统中提取各个块（速度、压力、温度）的。
* 

* 
* @code
     std::vector<double> old_temperature_values(n_q_points);
* 
     std::vector<Tensor<1, dim>>          phi_u(dofs_per_cell);
     std::vector<SymmetricTensor<2, dim>> grads_phi_u(dofs_per_cell);
     std::vector<double>                  div_phi_u(dofs_per_cell);
     std::vector<double>                  phi_p(dofs_per_cell);
* 
     const FEValuesExtractors::Vector velocities(0);
     const FEValuesExtractors::Scalar pressure(dim);
* 
 @endcode
* 
* 现在开始对问题中的所有单元进行循环。我们正在为这个装配例程处理两个不同的DoFHandlers，所以我们必须为使用中的两个对象设置两个不同的单元格迭代器。这可能看起来有点奇怪，因为斯托克斯系统和温度系统都使用相同的网格，但这是保持自由度同步的唯一方法。循环中的第一条语句也是非常熟悉的，按照更新标志的规定对有限元数据进行更新，将局部数组清零，并在正交点处获得旧解的值。然后，我们准备在单元上的正交点上进行循环。
* 

* 
* @code
     auto       cell             = stokes_dof_handler.begin_active();
     const auto endc             = stokes_dof_handler.end();
     auto       temperature_cell = temperature_dof_handler.begin_active();
* 
     for (; cell != endc; ++cell, ++temperature_cell)
       {
         stokes_fe_values.reinit(cell);
         temperature_fe_values.reinit(temperature_cell);
* 
         local_matrix = 0;
         local_rhs    = 0;
* 
         temperature_fe_values.get_function_values(old_temperature_solution,
                                                   old_temperature_values);
* 
         for (unsigned int q = 0; q < n_q_points; ++q)
           {
             const double old_temperature = old_temperature_values[q];
* 
 @endcode
* 
* 接下来我们提取与内积中的条款有关的基函数的值和梯度。如 step-22 所示，这有助于加速装配。            
* 一旦完成这些，我们就开始在局部矩阵的行和列上进行循环，并将相关的产品送入矩阵。右手边是由重力方向的温度驱动的强迫项（在我们的例子中是垂直方向）。 请注意，右手边的项总是生成的，而矩阵的贡献只有在 <code>rebuild_matrices</code> 标志要求时才会更新。
* 

* 
* @code
             for (unsigned int k = 0; k < dofs_per_cell; ++k)
               {
                 phi_u[k] = stokes_fe_values[velocities].value(k, q);
                 if (rebuild_stokes_matrix)
                   {
                     grads_phi_u[k] =
                       stokes_fe_values[velocities].symmetric_gradient(k, q);
                     div_phi_u[k] =
                       stokes_fe_values[velocities].divergence(k, q);
                     phi_p[k] = stokes_fe_values[pressure].value(k, q);
                   }
               }
* 
             if (rebuild_stokes_matrix)
               for (unsigned int i = 0; i < dofs_per_cell; ++i)
                 for (unsigned int j = 0; j < dofs_per_cell; ++j)
                   local_matrix(i, j) +=
                     (EquationData::eta 2 (grads_phi_u[i] grads_phi_u[j])
* 
-
                      div_phi_u[i] phi_p[j]
* 
- phi_p[i] div_phi_u[j])
                     stokes_fe_values.JxW(q);
* 
             const Point<dim> gravity =
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
-((dim == 2) ? (Point<dim>(0, 1)) : (Point<dim>(0, 0, 1)));
             for (unsigned int i = 0; i < dofs_per_cell; ++i)
               local_rhs(i) += (-EquationData::density EquationData::beta
                                gravity phi_u[i] old_temperature)
                               stokes_fe_values.JxW(q);
           }
* 
 @endcode
* 
* 在所有单元的循环中，最后一步是将局部贡献输入到全局矩阵和向量结构中，以达到  <code>local_dof_indices</code>  中指定的位置。 同样，我们让AffineConstraints类来做单元格矩阵元素插入全局矩阵的工作，它已经浓缩了悬挂节点的约束。
* 

* 
* @code
         cell->get_dof_indices(local_dof_indices);
* 
         if (rebuild_stokes_matrix == true)
           stokes_constraints.distribute_local_to_global(local_matrix,
                                                         local_rhs,
                                                         local_dof_indices,
                                                         stokes_matrix,
                                                         stokes_rhs);
         else
           stokes_constraints.distribute_local_to_global(local_rhs,
                                                         local_dof_indices,
                                                         stokes_rhs);
       }
* 
     rebuild_stokes_matrix = false;
* 
     std::cout << std::endl;
   }
* 
 
* 
 @endcode
 
* <a name="BoussinesqFlowProblemassemble_temperature_matrix"></a> <h4>BoussinesqFlowProblem::assemble_temperature_matrix</h4> <h4>BoussinesqFlowProblem::assemble_temperature_matrix</h4>.   
* 这个函数组装温度方程中的矩阵。温度矩阵由两部分组成，一个质量矩阵和时间步长乘以刚度矩阵，刚度矩阵由拉普拉斯项乘以扩散量给出。由于该矩阵取决于时间步长（从一个步长到另一个步长），温度矩阵需要在每个时间步长进行更新。我们可以简单地在每个时间步长中重新生成矩阵，但这并不真正有效，因为质量和拉普拉斯矩阵只有在我们改变网格时才会改变。因此，我们通过在这个函数中生成两个单独的矩阵，一个是质量矩阵，一个是刚度（扩散）矩阵，这样做更有效率。一旦我们知道了实际的时间步长，我们将把这个矩阵加上刚度矩阵乘以时间步长的总和。  
*所以这第一步的细节非常简单。如果我们需要重建矩阵（即网格发生了变化），我们将数据结构归零，得到一个正交公式和一个FEValues对象，并为基础函数创建局部矩阵、局部dof指数和评估结构。
* 

* 
* @code
   template <int dim>
   void BoussinesqFlowProblem<dim>::assemble_temperature_matrix()
   {
     if (rebuild_temperature_matrices == false)
       return;
* 
     temperature_mass_matrix      = 0;
     temperature_stiffness_matrix = 0;
* 
     QGauss<dim>   quadrature_formula(temperature_degree + 2);
     FEValues<dim> temperature_fe_values(temperature_fe,
                                         quadrature_formula,
                                         update_values | update_gradients |
                                           update_JxW_values);
* 
     const unsigned int dofs_per_cell = temperature_fe.n_dofs_per_cell();
     const unsigned int n_q_points    = quadrature_formula.size();
* 
     FullMatrix<double> local_mass_matrix(dofs_per_cell, dofs_per_cell);
     FullMatrix<double> local_stiffness_matrix(dofs_per_cell, dofs_per_cell);
* 
     std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);
* 
     std::vector<double>         phi_T(dofs_per_cell);
     std::vector<Tensor<1, dim>> grad_phi_T(dofs_per_cell);
* 
 @endcode
* 
* 现在，让我们开始对三角形中的所有单元进行循环。我们需要将局部矩阵清零，更新有限元评价，然后在每个正交点上循环矩阵的行和列，然后我们创建质量矩阵和刚度矩阵（拉普拉斯项乘以扩散  <code>EquationData::kappa</code>  。最后，我们让约束对象将这些值插入全局矩阵中，并直接将约束条件浓缩到矩阵中。
* 

* 
* @code
     for (const auto &cell : temperature_dof_handler.active_cell_iterators())
       {
         local_mass_matrix      = 0;
         local_stiffness_matrix = 0;
* 
         temperature_fe_values.reinit(cell);
* 
         for (unsigned int q = 0; q < n_q_points; ++q)
           {
             for (unsigned int k = 0; k < dofs_per_cell; ++k)
               {
                 grad_phi_T[k] = temperature_fe_values.shape_grad(k, q);
                 phi_T[k]      = temperature_fe_values.shape_value(k, q);
               }
* 
             for (unsigned int i = 0; i < dofs_per_cell; ++i)
               for (unsigned int j = 0; j < dofs_per_cell; ++j)
                 {
                   local_mass_matrix(i, j) +=
                     (phi_T[i] phi_T[j] temperature_fe_values.JxW(q));
                   local_stiffness_matrix(i, j) +=
                     (EquationData::kappa grad_phi_T[i] grad_phi_T[j]
                      temperature_fe_values.JxW(q));
                 }
           }
* 
         cell->get_dof_indices(local_dof_indices);
* 
         temperature_constraints.distribute_local_to_global(
           local_mass_matrix, local_dof_indices, temperature_mass_matrix);
         temperature_constraints.distribute_local_to_global(
           local_stiffness_matrix,
           local_dof_indices,
           temperature_stiffness_matrix);
       }
* 
     rebuild_temperature_matrices = false;
   }
* 
 
* 
 @endcode
* 
* <a name="BoussinesqFlowProblemassemble_temperature_system"></a> <h4>BoussinesqFlowProblem::assemble_temperature_system</h4>.   
* 这个函数对温度矩阵进行第二部分的装配工作，实际添加压力质量和刚度矩阵（时间步长在这里起作用），以及创建依赖于速度的右手边。这个函数中的右侧装配的声明与其他装配例程中使用的声明基本相同，只是这次我们把自己限制在矢量上。我们将计算温度系统的残差，这意味着我们必须评估二阶导数，由更新标志  <code>update_hessians</code>  指定。  
* 温度方程是通过流体速度与斯托克斯系统耦合的。解决方案的这两部分与不同的DoFHandlers相关联，因此我们需要再次创建第二个FEValues对象来评估正交点的速度。
* 

* 
* @code
   template <int dim>
   void BoussinesqFlowProblem<dim>::assemble_temperature_system(
     const double maximal_velocity)
   {
     const bool use_bdf2_scheme = (timestep_number != 0);
* 
     if (use_bdf2_scheme == true)
       {
         temperature_matrix.copy_from(temperature_mass_matrix);
         temperature_matrix=
           (2 time_step + old_time_step) / (time_step + old_time_step);
         temperature_matrix.add(time_step, temperature_stiffness_matrix);
       }
     else
       {
         temperature_matrix.copy_from(temperature_mass_matrix);
         temperature_matrix.add(time_step, temperature_stiffness_matrix);
       }
* 
     temperature_rhs = 0;
* 
     const QGauss<dim> quadrature_formula(temperature_degree + 2);
     FEValues<dim>     temperature_fe_values(temperature_fe,
                                         quadrature_formula,
                                         update_values | update_gradients |
                                           update_hessians |
                                           update_quadrature_points |
                                           update_JxW_values);
     FEValues<dim>     stokes_fe_values(stokes_fe,
                                    quadrature_formula,
                                    update_values);
* 
     const unsigned int dofs_per_cell = temperature_fe.n_dofs_per_cell();
     const unsigned int n_q_points    = quadrature_formula.size();
* 
     Vector<double> local_rhs(dofs_per_cell);
* 
     std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);
* 
 @endcode
* 
* 接下来是向量的声明，用来保存旧的和较早的解数值（分别作为时间级别 $n-1$ 和 $n-2$ 的符号）以及当前单元的正交点的梯度。我们还声明了一个对象来保存温度的右侧值（ <code>gamma_values</code> ），并且我们再次使用温度基函数的快捷方式。最终，我们需要找到温度极值和计算域的直径，这将用于稳定参数的定义（我们得到了最大速度作为这个函数的输入）。
* 

* 
* @code
     std::vector<Tensor<1, dim>> old_velocity_values(n_q_points);
     std::vector<Tensor<1, dim>> old_old_velocity_values(n_q_points);
     std::vector<double>         old_temperature_values(n_q_points);
     std::vector<double>         old_old_temperature_values(n_q_points);
     std::vector<Tensor<1, dim>> old_temperature_grads(n_q_points);
     std::vector<Tensor<1, dim>> old_old_temperature_grads(n_q_points);
     std::vector<double>         old_temperature_laplacians(n_q_points);
     std::vector<double>         old_old_temperature_laplacians(n_q_points);
* 
     EquationData::TemperatureRightHandSide<dim> temperature_right_hand_side;
     std::vector<double>                         gamma_values(n_q_points);
* 
     std::vector<double>         phi_T(dofs_per_cell);
     std::vector<Tensor<1, dim>> grad_phi_T(dofs_per_cell);
* 
     const std::pair<double, double> global_T_range =
       get_extrapolated_temperature_range();
* 
     const FEValuesExtractors::Vector velocities(0);
* 
 @endcode
 
* 现在，让我们开始对三角形中的所有单元进行循环。同样，我们需要两个单元格迭代器，平行地走过两个涉及到斯托克斯和温度部分的DoFHandler对象的单元格。在这个循环中，我们首先将局部rhs设置为零，然后在正交点上获得旧的解函数的值和导数，因为它们将被用于稳定参数的定义和作为方程的系数。请注意，由于温度有自己的DoFHandler和FEValues对象，我们在正交点得到整个解（反正只有标量温度场），而对于斯托克斯部分，我们只限于通过使用 <code>stokes_fe_values[velocities].get_function_values</code> 提取速度部分（而忽略压力部分）。
* 

* 
* @code
     auto       cell        = temperature_dof_handler.begin_active();
     const auto endc        = temperature_dof_handler.end();
     auto       stokes_cell = stokes_dof_handler.begin_active();
* 
     for (; cell != endc; ++cell, ++stokes_cell)
       {
         local_rhs = 0;
* 
         temperature_fe_values.reinit(cell);
         stokes_fe_values.reinit(stokes_cell);
* 
         temperature_fe_values.get_function_values(old_temperature_solution,
                                                   old_temperature_values);
         temperature_fe_values.get_function_values(old_old_temperature_solution,
                                                   old_old_temperature_values);
* 
         temperature_fe_values.get_function_gradients(old_temperature_solution,
                                                      old_temperature_grads);
         temperature_fe_values.get_function_gradients(
           old_old_temperature_solution, old_old_temperature_grads);
* 
         temperature_fe_values.get_function_laplacians(
           old_temperature_solution, old_temperature_laplacians);
         temperature_fe_values.get_function_laplacians(
           old_old_temperature_solution, old_old_temperature_laplacians);
* 
         temperature_right_hand_side.value_list(
           temperature_fe_values.get_quadrature_points(), gamma_values);
* 
         stokes_fe_values[velocities].get_function_values(stokes_solution,
                                                          old_velocity_values);
         stokes_fe_values[velocities].get_function_values(
           old_stokes_solution, old_old_velocity_values);
* 
 @endcode
* 
* 接下来，我们根据引言中的讨论，用专用函数计算用于稳定的人工黏度。有了这个，我们就可以进入正交点和局部rhs矢量分量的循环了。这里的术语相当冗长，但其定义遵循本方案介绍中开发的时间-离散系统。BDF-2方案比用于第一时间步的后向欧拉方案多需要一个旧时间步的术语（并且涉及更复杂的因素）。当所有这些都完成后，我们将局部向量分配到全局向量中（包括悬挂节点约束）。
* 

* 
* @code
         const double nu =
           compute_viscosity(old_temperature_values,
                             old_old_temperature_values,
                             old_temperature_grads,
                             old_old_temperature_grads,
                             old_temperature_laplacians,
                             old_old_temperature_laplacians,
                             old_velocity_values,
                             old_old_velocity_values,
                             gamma_values,
                             maximal_velocity,
                             global_T_range.second
* 
- global_T_range.first,
                             cell->diameter());
* 
         for (unsigned int q = 0; q < n_q_points; ++q)
           {
             for (unsigned int k = 0; k < dofs_per_cell; ++k)
               {
                 grad_phi_T[k] = temperature_fe_values.shape_grad(k, q);
                 phi_T[k]      = temperature_fe_values.shape_value(k, q);
               }
* 
             const double T_term_for_rhs =
               (use_bdf2_scheme ?
                  (old_temperature_values[q] (1 + time_step / old_time_step)
* 
-
                   old_old_temperature_values[q] (time_step time_step) /
                     (old_time_step (time_step + old_time_step))) :
                  old_temperature_values[q]);
* 
             const Tensor<1, dim> ext_grad_T =
               (use_bdf2_scheme ?
                  (old_temperature_grads[q] (1 + time_step / old_time_step)
* 
-
                   old_old_temperature_grads[q] time_step / old_time_step) :
                  old_temperature_grads[q]);
* 
             const Tensor<1, dim> extrapolated_u =
               (use_bdf2_scheme ?
                  (old_velocity_values[q] (1 + time_step / old_time_step)
* 
-
                   old_old_velocity_values[q] time_step / old_time_step) :
                  old_velocity_values[q]);
* 
             for (unsigned int i = 0; i < dofs_per_cell; ++i)
               local_rhs(i) +=
                 (T_term_for_rhs phi_T[i]
* 
-
                  time_step extrapolated_u ext_grad_T phi_T[i]
* 
-
                  time_step nu ext_grad_T grad_phi_T[i] +
                  time_step gamma_values[q] phi_T[i])
                 temperature_fe_values.JxW(q);
           }
* 
         cell->get_dof_indices(local_dof_indices);
         temperature_constraints.distribute_local_to_global(local_rhs,
                                                            local_dof_indices,
                                                            temperature_rhs);
       }
   }
* 
 
* 
 @endcode
 
* <a name="BoussinesqFlowProblemsolve"></a> <h4>BoussinesqFlowProblem::solve</h4>   
* 这个函数解决了线性方程组的问题。在介绍之后，我们从斯托克斯系统开始，在这里我们需要生成我们的块舒尔预处理程序。由于所有相关的动作都在类 <code>BlockSchurPreconditioner</code> 中实现，我们所要做的就是适当地初始化这个类。我们需要传递的是压力质量矩阵的 <code>InverseMatrix</code> 对象，我们使用相应的类和我们已经生成的IC预处理器以及速度-速度矩阵的AMG预处理器来设置。注意， <code>Mp_preconditioner</code> 和 <code>Amg_preconditioner</code> 都只是指针，所以我们用 <code>*</code> 来传递实际的预处理对象。  
* 一旦预处理程序准备就绪，我们就为该块系统创建一个GMRES求解器。由于我们正在使用特里诺斯数据结构，我们必须在求解器中设置相应的模板参数。GMRES需要在内部存储每次迭代的临时向量（见 step-22 结果部分的讨论）&ndash；它可以使用的向量越多，通常表现越好。为了控制内存需求，我们将向量的数量设置为100。这意味着在求解器的100次迭代中，每个临时向量都可以被存储。如果求解器需要更频繁地迭代以获得指定的容忍度，它将通过每100次迭代重新开始，在一个减少的向量集上工作。  
* 有了这一切的设置，我们求解系统并在斯托克斯系统中分配约束条件，即悬挂节点和无流体边界条件，以便即使在受约束的道夫也有适当的解值。最后，我们把迭代次数写在屏幕上。
* 

* 
* @code
   template <int dim>
   void BoussinesqFlowProblem<dim>::solve()
   {
     std::cout << "   Solving..." << std::endl;
* 
     {
       const LinearSolvers::InverseMatrix<TrilinosWrappers::SparseMatrix,
                                          TrilinosWrappers::PreconditionIC>
         mp_inverse(stokes_preconditioner_matrix.block(1, 1),
                   Mp_preconditioner);
* 
       const LinearSolvers::BlockSchurPreconditioner<
         TrilinosWrappers::PreconditionAMG,
         TrilinosWrappers::PreconditionIC>
         preconditioner(stokes_matrix, mp_inverse,Amg_preconditioner);
* 
       SolverControl solver_control(stokes_matrix.m(),
                                    1e-6 stokes_rhs.l2_norm());
* 
       SolverGMRES<TrilinosWrappers::MPI::BlockVector> gmres(
         solver_control,
         SolverGMRES<TrilinosWrappers::MPI::BlockVector>::AdditionalData(100));
* 
       for (unsigned int i = 0; i < stokes_solution.size(); ++i)
         if (stokes_constraints.is_constrained(i))
           stokes_solution(i) = 0;
* 
       gmres.solve(stokes_matrix, stokes_solution, stokes_rhs, preconditioner);
* 
       stokes_constraints.distribute(stokes_solution);
* 
       std::cout << "   " << solver_control.last_step()
                 << " GMRES iterations for Stokes subsystem." << std::endl;
     }
* 
 @endcode
* 
* 一旦我们知道了斯托克斯解，我们就可以根据最大速度确定新的时间步长。我们必须这样做以满足CFL条件，因为对流项在温度方程中得到了明确的处理，正如在介绍中所讨论的。这里使用的时间步长公式的确切形式将在本程序的结果部分讨论。    
* 这里有一个插曲。该公式包含一个除以速度的最大值。然而，在计算开始时，我们有一个恒定的温度场（我们以恒定的温度开始，只有在源作用的第一个时间步长后，它才会成为非恒定的）。恒定温度意味着没有浮力作用，所以速度为零。除以它不可能导致任何好的结果。    
* 为了避免产生无限的时间步长，我们要问最大的速度是否非常小（特别是小于我们在下面任何一个时间步长中遇到的值），如果是，我们就不除以零，而是除以一个小值，从而产生一个大的但有限的时间步长。
* 

* 
* @code
     old_time_step                 = time_step;
     const double maximal_velocity = get_maximal_velocity();
* 
     if (maximal_velocity >= 0.01)
       time_step = 1. / (1.7 dim std::sqrt(1. dim)) / temperature_degree
                   GridTools::minimal_cell_diameter(triangulation) /
                   maximal_velocity;
     else
       time_step = 1. / (1.7 dim std::sqrt(1. dim)) / temperature_degree
                   GridTools::minimal_cell_diameter(triangulation) / .01;
* 
     std::cout << "   "
               << "Time step: " << time_step << std::endl;
* 
     temperature_solution = old_temperature_solution;
* 
 @endcode
* 
* 接下来我们用函数  <code>assemble_temperature_system()</code>  设置温度系统和右手边。 知道了温度方程的矩阵和右手边，我们设置了一个预处理程序和一个求解器。温度矩阵是一个质量矩阵（特征值在1左右）加上一个拉普拉斯矩阵（特征值在0和 $ch^{-2}$ 之间）乘以一个与时间步长成比例的小数  $k_n$  。因此，产生的对称和正定矩阵的特征值在 $[1,1+k_nh^{-2}]$ 范围内（至于常数）。这个矩阵即使对于小的网格尺寸也只是适度的条件不良，我们通过简单的方法得到一个相当好的预处理，例如用一个不完全的Cholesky分解预处理（IC），因为我们也用于预处理压力质量矩阵求解器。作为一个求解器，我们选择共轭梯度法CG。和以前一样，我们通过模板参数 <code>TrilinosWrappers::MPI::Vector</code> 告诉求解器使用Trilinos向量。最后，我们求解，分配悬挂节点约束，并写出迭代次数。
* 

* 
* @code
     assemble_temperature_system(maximal_velocity);
     {
       SolverControl solver_control(temperature_matrix.m(),
                                    1e-8 temperature_rhs.l2_norm());
       SolverCG<TrilinosWrappers::MPI::Vector> cg(solver_control);
* 
       TrilinosWrappers::PreconditionIC preconditioner;
       preconditioner.initialize(temperature_matrix);
* 
       cg.solve(temperature_matrix,
                temperature_solution,
                temperature_rhs,
                preconditioner);
* 
       temperature_constraints.distribute(temperature_solution);
* 
       std::cout << "   " << solver_control.last_step()
                 << " CG iterations for temperature." << std::endl;
* 
 @endcode
* 
* 在这个函数的结尾，我们通过向量步进，读出最大和最小的温度值，我们也想输出这些值。这在确定选择时间步长的正确常数时将会很方便，正如本程序的结果部分所讨论的那样。
* 

* 
* @code
       double min_temperature = temperature_solution(0),
              max_temperature = temperature_solution(0);
       for (unsigned int i = 0; i < temperature_solution.size(); ++i)
         {
           min_temperature =
             std::min<double>(min_temperature, temperature_solution(i));
           max_temperature =
             std::max<double>(max_temperature, temperature_solution(i));
         }
* 
       std::cout << "   Temperature range: " << min_temperature << ' '
                 << max_temperature << std::endl;
     }
   }
* 
 
* 
 @endcode
* 
* <a name="BoussinesqFlowProblemoutput_results"></a> <h4>BoussinesqFlowProblem::output_results</h4>   
* 该函数将解决方案写入VTK输出文件，用于可视化，每隔10个时间步长就会完成。这通常是一个相当简单的任务，因为deal.II库提供的函数几乎为我们完成了所有的工作。与以前的例子相比，有一个新的函数。我们想把斯托克斯解和温度都看作一个数据集，但我们已经根据两个不同的DoFHandler对象完成了所有的计算。幸运的是，DataOut类已经准备好处理这个问题。我们所要做的就是不要在开始时附加一个单一的DoFHandler，然后将其用于所有添加的向量，而是为每个向量分别指定DoFHandler。剩下的就像  step-22  中所做的那样。我们创建解决方案的名称（这些名称将出现在各个组件的可视化程序中）。第一个 <code>dim</code> 分量是矢量速度，然后我们有斯托克斯部分的压力，而温度是标量。这些信息是用DataComponentInterpretation辅助类读出来的。接下来，我们将数据向量与它们的DoFHandler对象连接起来，根据自由度建立补丁，这些补丁是描述可视化程序数据的（子）元素。最后，我们打开一个文件（包括时间步数），并将vtk数据写入其中。
* 

* 
* @code
   template <int dim>
   void BoussinesqFlowProblem<dim>::output_results() const
   {
     if (timestep_number % 10 != 0)
       return;
* 
     std::vector<std::string> stokes_names(dim, "velocity");
     stokes_names.emplace_back("p");
     std::vector<DataComponentInterpretation::DataComponentInterpretation>
       stokes_component_interpretation(
         dim + 1, DataComponentInterpretation::component_is_scalar);
     for (unsigned int i = 0; i < dim; ++i)
       stokes_component_interpretation[i] =
         DataComponentInterpretation::component_is_part_of_vector;
* 
     DataOut<dim> data_out;
     data_out.add_data_vector(stokes_dof_handler,
                              stokes_solution,
                              stokes_names,
                              stokes_component_interpretation);
     data_out.add_data_vector(temperature_dof_handler,
                              temperature_solution,
                              "T");
     data_out.build_patches(std::min(stokes_degree, temperature_degree));
* 
     std::ofstream output("solution-" +
                          Utilities::int_to_string(timestep_number, 4) + ".vtk");
     data_out.write_vtk(output);
   }
* 
 
* 
 @endcode
* 
* <a name="BoussinesqFlowProblemrefine_mesh"></a> <h4>BoussinesqFlowProblem::refine_mesh</h4>   
* 这个函数负责自适应网格细化的工作。这个函数执行的三个任务是：首先找出需要细化/粗化的单元，然后实际进行细化，最终在两个不同的网格之间转移解向量。第一个任务是通过对温度使用成熟的凯利误差估计器来实现的（对于这个程序，我们主要关注的是温度，我们需要在高温度梯度的区域保持准确，同时也不能有太多的数值扩散）。第二项任务是实际进行再塑形。这也只涉及到基本函数，例如 <code>refine_and_coarsen_fixed_fraction</code> ，它可以细化那些具有最大估计误差的单元，这些误差合计占80%，并粗化那些具有最小误差的单元，这些误差合计占10%。  
* 如果像这样实施，我们会得到一个不会有太大进展的程序。请记住，我们期望的温度场几乎是不连续的（扩散率 $\kappa$ 毕竟非常小），因此我们可以预期，一个自由适应的网格会越来越细化到大梯度的区域。网格大小的减少将伴随着时间步数的减少，需要超多的时间步数来解决给定的最终时间。这也将导致在几个网格细化周期后，网格的不连续性解决得比开始时好得多。  
* 特别是为了防止时间步长的减少和相应的大量时间步数，我们限制了网格的最大细化深度。为此，在细化指标应用于单元格后，我们简单地在所有最细的单元格上循环，如果它们会导致网格级别过高，则取消选择它们进行细化。
* 

* 
* @code
   template <int dim>
   void
   BoussinesqFlowProblem<dim>::refine_mesh(const unsigned int max_grid_level)
   {
     Vector<float> estimated_error_per_cell(triangulation.n_active_cells());
* 
     KellyErrorEstimator<dim>::estimate(temperature_dof_handler,
                                        QGauss<dim
* 
- 1>(temperature_degree + 1),
                                        {},
                                        temperature_solution,
                                        estimated_error_per_cell);
* 
     GridRefinement::refine_and_coarsen_fixed_fraction(triangulation,
                                                       estimated_error_per_cell,
                                                       0.8,
                                                       0.1);
     if (triangulation.n_levels() > max_grid_level)
       for (auto &cell :
            triangulation.active_cell_iterators_on_level(max_grid_level))
         cell->clear_refine_flag();
* 
 @endcode
* 
* 作为网格细化的一部分，我们需要将旧网格中的解向量转移到新的网格中。为此，我们使用SolutionTransfer类，我们必须准备好需要转移到新网格的解向量（一旦我们完成了细化，就会失去旧的网格，所以转移必须与细化同时发生）。我们肯定需要的是当前温度和旧温度（BDF-2时间步长需要两个旧的解决方案）。由于SolutionTransfer对象只支持在每个dof处理程序中传输一个对象，我们需要在一个数据结构中收集两个温度解决方案。此外，我们也选择转移斯托克斯解，因为我们需要前两个时间步长的速度，其中只有一个是在飞行中计算的。    
* 因此，我们为斯托克斯和温度的DoFHandler对象初始化了两个SolutionTransfer对象，将它们附加到旧的dof处理程序中。有了这些，我们就可以准备三角测量和数据向量的细化了（按照这个顺序）。
* 

* 
* @code
     std::vector<TrilinosWrappers::MPI::Vector> x_temperature(2);
     x_temperature[0]                            = temperature_solution;
     x_temperature[1]                            = old_temperature_solution;
     TrilinosWrappers::MPI::BlockVector x_stokes = stokes_solution;
* 
     SolutionTransfer<dim, TrilinosWrappers::MPI::Vector> temperature_trans(
       temperature_dof_handler);
     SolutionTransfer<dim, TrilinosWrappers::MPI::BlockVector> stokes_trans(
       stokes_dof_handler);
* 
     triangulation.prepare_coarsening_and_refinement();
     temperature_trans.prepare_for_coarsening_and_refinement(x_temperature);
     stokes_trans.prepare_for_coarsening_and_refinement(x_stokes);
* 
 @endcode
* 
* 现在一切都准备好了，所以进行细化，在新的网格上重新创建dof结构，并在 <code>setup_dofs</code> 函数中初始化矩阵结构和新的向量。接下来，我们实际执行网格之间的插值解。我们为温度创建另一份临时向量（现在与新网格相对应），并让插值函数完成这项工作。然后，产生的向量数组被写入各自的向量成员变量中。    
* 记住，约束集将在setup_dofs()调用中为新的三角结构进行更新。
* 

* 
* @code
     triangulation.execute_coarsening_and_refinement();
     setup_dofs();
* 
     std::vector<TrilinosWrappers::MPI::Vector> tmp(2);
     tmp[0].reinit(temperature_solution);
     tmp[1].reinit(temperature_solution);
     temperature_trans.interpolate(x_temperature, tmp);
* 
     temperature_solution     = tmp[0];
     old_temperature_solution = tmp[1];
* 
 @endcode
* 
* 在解决方案被转移后，我们再对转移后的解决方案执行约束。
* 

* 
* @code
     temperature_constraints.distribute(temperature_solution);
     temperature_constraints.distribute(old_temperature_solution);
* 
 @endcode
* 
* 对于斯托克斯向量，一切都一样&ndash；除了我们不需要另一个临时向量，因为我们只是插值一个向量。最后，我们必须告诉程序，矩阵和预处理程序需要重新生成，因为网格已经改变。
* 

* 
* @code
     stokes_trans.interpolate(x_stokes, stokes_solution);
* 
     stokes_constraints.distribute(stokes_solution);
* 
     rebuild_stokes_matrix         = true;
     rebuild_temperature_matrices  = true;
     rebuild_stokes_preconditioner = true;
   }
* 
 
* 
 @endcode
 
* <a name="BoussinesqFlowProblemrun"></a> <h4>BoussinesqFlowProblem::run</h4>   
* 这个函数执行Boussinesq程序中的所有基本步骤。它首先设置一个网格（根据空间维度，我们选择一些不同级别的初始细化和额外的自适应细化步骤，然后在 <code>dim</code> 维度上创建一个立方体，并首次设置了道夫。由于我们想用一个自适应细化的网格开始时间步进，我们执行一些预细化步骤，包括所有的装配、求解和细化，但实际上没有在时间上推进。相反，我们使用被人诟病的 <code>goto</code> 语句，在网格细化后立即跳出时间循环，从 <code>start_time_iteration</code> 标签开始的新网格上重新开始。( <code>goto</code> 的使用在 step-26 中讨论) 。  
* 在我们开始之前，我们将初始值投影到网格上，并获得 <code>old_temperature_solution</code> 矢量的第一个数据。然后，我们初始化时间步数和时间步长，开始时间循环。
* 

* 
* @code
   template <int dim>
   void BoussinesqFlowProblem<dim>::run()
   {
     const unsigned int initial_refinement     = (dim == 2 ? 4 : 2);
     const unsigned int n_pre_refinement_steps = (dim == 2 ? 4 : 3);
* 
 
     GridGenerator::hyper_cube(triangulation);
     global_Omega_diameter = GridTools::diameter(triangulation);
* 
     triangulation.refine_global(initial_refinement);
* 
     setup_dofs();
* 
     unsigned int pre_refinement_step = 0;
* 
   start_time_iteration:
* 
     VectorTools::project(temperature_dof_handler,
                          temperature_constraints,
                          QGauss<dim>(temperature_degree + 2),
                          EquationData::TemperatureInitialValues<dim>(),
                          old_temperature_solution);
* 
     timestep_number = 0;
     time_step = old_time_step = 0;
* 
     double time = 0;
* 
     do
       {
         std::cout << "Timestep " << timestep_number << ":  t=" << time
                   << std::endl;
* 
 @endcode
* 
* 时间循环的第一步是显而易见的；我们组装斯托克斯系统、预调节器、温度矩阵（矩阵和预调节器实际上只在我们之前重修的情况下才会改变），然后进行求解。在继续下一个时间步骤之前，我们必须检查我们是否应该首先完成预精炼步骤，或者是否应该重新啮合（每五个时间步骤），精炼到一个与初始精炼和预精炼步骤一致的水平。循环的最后一个步骤是推进解，即把解复制到下一个 "老 "时间级别。
* 

* 
* @code
         assemble_stokes_system();
         build_stokes_preconditioner();
         assemble_temperature_matrix();
* 
         solve();
* 
         output_results();
* 
         std::cout << std::endl;
* 
         if ((timestep_number == 0) &&
             (pre_refinement_step < n_pre_refinement_steps))
           {
             refine_mesh(initial_refinement + n_pre_refinement_steps);
             ++pre_refinement_step;
             goto start_time_iteration;
           }
         else if ((timestep_number > 0) && (timestep_number % 5 == 0))
           refine_mesh(initial_refinement + n_pre_refinement_steps);
* 
         time += time_step;
         ++timestep_number;
* 
         old_stokes_solution          = stokes_solution;
         old_old_temperature_solution = old_temperature_solution;
         old_temperature_solution     = temperature_solution;
       }
 @endcode
* 
* 做以上所有的工作，直到我们到达时间100。
* 

* 
* @code
     while (time <= 100);
   }
 } // namespace Step31
* 
 
* 
 @endcode
* 
* <a name="Thecodemaincodefunction"></a> <h3>The <code>main</code> function</h3>。
 

* 
* 主函数看起来与所有其他程序几乎相同。
* 

* 
* 有一个区别是我们必须要注意的。这个程序使用的是Trilinos，通常，Trilinos被配置成可以使用MPI在%parallel中运行。这并不意味着它<i>has</i>可以在%parallel中运行，事实上这个程序（不像 step-32 ）根本没有尝试使用MPI在%parallel中做任何事情。然而，Trilinos希望MPI系统被初始化。我们通过创建一个类型为 Utilities::MPI::MPI_InitFinalize 的对象来做到这一点，该对象使用给main()的参数（即 <code>argc</code> 和 <code>argv</code> ）初始化MPI（如果可用的话），并在对象超出范围时再次去初始化它。
* 

* 
* @code
 int main(int argc, charargv[])
 {
   try
     {
       using namespace dealii;
       using namespace Step31;
* 
       Utilities::MPI::MPI_InitFinalize mpi_initialization(
         argc, argv, numbers::invalid_unsigned_int);
* 
 @endcode
 
* 这个程序只能在串行中运行。否则，抛出一个异常。
* 

* 
* @code
       AssertThrow(Utilities::MPI::n_mpi_processes(MPI_COMM_WORLD) == 1,
                   ExcMessage(
                     "This program can only be run in serial, use ./step-31"));
* 
       BoussinesqFlowProblem<2> flow_problem;
       flow_problem.run();
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
* 
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
* 

* <a name="Resultsin2d"></a><h3> Results in 2d </h3>。
* 

* 当你在2D中运行该程序时，输出将看起来像这样：<code><pre>活动单元的数量：256（在5层）自由度的数量：3556（2178+289+1089
* 时间步数0：t=0 正在组装......   重新建立斯托克斯预处理程序...   解算...   斯托克斯子系统的GMRES迭代次数为0。  时间步长：0.919118 温度的9次CG迭代。  温度范围。
* 
* - .16687 1.30011
* 活动单元的数量：280（在6层）自由度数量：4062（2490+327+1245）。
* 时间步数 0: t=0 正在组装...   重建斯托克斯预处理程序...   解算...   斯托克斯子系统的GMRES迭代次数为0。  时间步长：0.459559温度的9次CG迭代。  温度范围。
* 
* - .0982971 0.598503
* 活动单元的数量：520（在7层）自由度数量：7432（4562+589+2281）。
* 时间步数 0: t=0 正在组装...   重建斯托克斯预处理程序...   解算...   斯托克斯子系统的GMRES迭代次数为0。  时间步长：0.229779 温度的9次CG迭代。  温度范围。
* 
* - .0551098 0.294493
* 活动单元的数量：1072（在8层）自由度的数量：15294（9398+1197+4699
* 时间步数 0: t=0 正在组装...   重建斯托克斯预处理程序...   解算...   斯托克斯子系统的GMRES迭代次数为0。  时间步长：0.11489 温度的9次CG迭代。  温度范围。
* 
* - .0273524 0.156861
* 活动单元数：2116（9层）自由度数：30114（18518+2337+9259）。
* 时间步数 0: t=0 正在组装...   重建斯托克斯预处理程序...   解算...   斯托克斯子系统的GMRES迭代次数为0。  时间步长：0.0574449 温度的9次CG迭代。  温度范围。
* 
* - .014993 0.0738328
* 时间步数1：t=0.0574449 装配...   解决...   斯托克斯子系统的56次GMRES迭代。  时间步长：0.0574449 温度的9次CG迭代。  温度范围。
* 
* - .0273934 0.14488
* ...</pre></code>
* 在开始的时候，我们自适应地细化了几次网格，并且总是返回到时间步长为零的地方，在新细化的网格上重新开始。只有这样，我们才开始实际的时间迭代。
* 该程序运行了一段时间。时间步数为0、500、1000、1500、2000、3000、4000和5000的温度场看起来是这样的（注意用于温度的色标并不总是相同）。
*  <table align="center" class="doxtable">
  <tr>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.solution.00.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.solution.01.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.solution.02.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.solution.03.png" alt="">
    </td>
  </tr>
  <tr>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.solution.04.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.solution.05.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.solution.06.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.solution.07.png" alt="">
    </td>
  </tr>
</table>  
* 这里显示的视觉效果是使用例子的一个版本生成的，该版本在传输网格后没有强制执行约束。
* 可以看出，我们有三个加热流体的热源，因此产生了一个浮力效应，使流体的热袋上升并旋转。通过烟囱效应，这三股气流被来自外部并想加入上升气流的流体压在一起。请注意，由于流体最初处于静止状态，与后来被充分发展的流场拖过源头的流体相比，最初在源头上的那些部分获得的加热时间更长。因此，它是更热的，这一事实可以从三个烟羽的红色尖端看出。还请注意流场的相对精细的特征，这是我们选择的温度方程的复杂传输稳定化的结果。
* 除了上面的图片之外，下面的图片显示了自适应网格和同一时间步长的流场。
*  <table align="center" class="doxtable">
  <tr>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.grid.00.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.grid.01.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.grid.02.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.grid.03.png" alt="">
    </td>
  </tr>
  <tr>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.grid.04.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.grid.05.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.grid.06.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.2d.grid.07.png" alt="">
    </td>
  </tr>
</table>  
* 

* <a name="Resultsin3d"></a><h3> Results in 3d </h3> 。
* 

* 当然，同样的事情也可以在3D中完成，将 <code>main()</code> 中BoussinesqFlowProblem对象的templateparameter从2改为3，这样，现在的输出看起来如下。
<code><pre>活动单元的数量：64（在3层）自由度的数量：3041（2187+125+729
* 时间步数 0: t=0 正在组装...   重建斯托克斯预处理程序...   解算...   斯托克斯子系统的GMRES迭代次数为0。  时间步长：2.45098 温度的9次CG迭代。  温度范围。
* 
* - .675683 4.94725
* 活动单元数：288（在4层）自由度数：12379（8943+455+2981）。
* 时间步数 0: t=0 正在组装...   重新建立斯托克斯预处理程序...   解算...   斯托克斯子系统的GMRES迭代次数为0。  时间步长：1.22549 温度的9次CG迭代。  温度范围。
* 
* - .527701 2.25764
* 活动单元的数量：1296（在5层）自由度的数量：51497（37305+1757+12435
* 时间步数 0: t=0 正在组装...   重新建立斯托克斯预处理程序...   解算...   斯托克斯子系统的GMRES迭代次数为0。  时间步长：0.612745温度的10次CG迭代。  温度范围。
* 
* - .496942 0.847395
* 活动单元的数量：5048（在6层）自由度的数量：192425（139569+6333+46523）。
* 时间步数 0: t=0 正在组装...   重建斯托克斯预处理程序...   解算...   斯托克斯子系统的GMRES迭代次数为0。  时间步长：0.306373 温度的10次CG迭代。  温度范围。
* 
* - .267683 0.497739
* 时间步数1：t=0.306373 装配...   解决...   斯托克斯子系统的27次GMRES迭代。  时间步长：0.306373 温度的10次CG迭代。  温度范围。
* 
* - .461787 0.958679
* ...</pre></code>。
* 在时间步长为0,50,100,150,200,300,400,500,600,700,和800的情况下，将温度等值线可视化，得到以下图示。
*  <table align="center" class="doxtable">
  <tr>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.3d.solution.00.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.3d.solution.01.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.3d.solution.02.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.3d.solution.03.png" alt="">
    </td>
  </tr>
  <tr>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.3d.solution.04.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.3d.solution.05.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.3d.solution.06.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.3d.solution.07.png" alt="">
    </td>
  </tr>
  <tr>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.3d.solution.08.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.3d.solution.09.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.3d.solution.10.png" alt="">
    </td>
    <td>
    </td>
  </tr>
</table>  
* 第一幅图看起来像三只刺猬，这是因为我们的方案基本上是将源乘以第一时间步长投射到网格上，以获得第一时间步的温度场。由于源函数是不连续的，我们需要从这个投影中期待过冲和欠冲。这就是事实上发生的情况（在2d中更容易检查），并导致等值面的皱缩外观。 这里所显示的视觉效果是用一个例子的版本生成的，该版本在传输网格后没有强制执行约束。
* 

* 
* <a name="Numericalexperimentstodetermineoptimalparameters"></a><h3> Numerical experiments to determine optimal parameters </h3>.
* 

* 这个程序有三个参数，我们在理论上并没有掌握如何以最佳方式选择。这些参数是。 <ul>   <li>  时间步骤必须满足CFL条件  $k\le \min_K \frac{c_kh_K}{\|\mathbf{u}\|_{L^\infty(K)}}$  。这里， $c_k$ 是无量纲的，但什么是正确的值？   <li>  在计算人工黏度时，@f{eqnarray*}
  \nu_\alpha(T)|_K
  =
  \beta
  \|\mathbf{u}\|_{L^\infty(K)}
  \min\left\{
    h_K,
    h_K^\alpha
    \frac{\|R_\alpha(T)\|_{L^\infty(K)}}{c(\mathbf{u},T)}
  \right\},
@f} 。
*与 $c(\mathbf{u},T) =
      c_R\ \|\mathbf{u}\|_{L^\infty(\Omega)} \ \mathrm{var}(T)
      \ |\mathrm{diam}(\Omega)|^{\alpha-2}$  。     这里，无量纲%数 $\beta,c_R$ 的选择是有意义的。 </ul>  在所有这些情况下，我们将不得不期待每个值的正确选择取决于其他值，而且很可能也取决于用于温度的有限元的间隔尺寸和多项式程度。下面我们将讨论一些数值实验来选择常数  $c_k$  和  $\beta$  。
* 下面，我们将不讨论 $c_R$ 的选择。在程序中，我们把它设置为 $c_R=2^{\frac{4-2\alpha}{d}}$ 。这个值的原因有点复杂，与程序的历史而不是推理有关：虽然全局缩放参数 $c(\mathbf{u},T)$ 的正确公式如上所示，但程序（包括随deal.II 6.2提供的版本）最初有一个错误，即我们计算的是 $c(\mathbf{u},T) =
      \|\mathbf{u}\|_{L^\infty(\Omega)} \ \mathrm{var}(T)
      \ \frac{1}{|\mathrm{diam}(\Omega)|^{\alpha-2}}$ ，而我们将缩放参数设为1。由于我们只在 $\mathrm{diam}(\Omega)=2^{1/d}$ 的单位平方/立方体上进行计算，这完全等同于使用 $c_R=\left(2^{1/d}\right)^{4-2\alpha}=2^{\frac{4-2\alpha}{d}}$ 的正确公式。由于 $c_R$ 的这个值对目前的程序来说似乎很好用，我们纠正了程序中的公式，并将 $c_R$ 设置为一个能完全重现我们之前结果的值。然而，我们将在 step-32 中再次讨论这个问题。
* 然而，现在回到讨论选择 $c_k$ 和 $\beta$ 的什么值。
* 

* <a name="Choosingicsubksubiandbeta"></a><h4> Choosing <i>c<sub>k</sub></i><i>c<sub>k</sub></i> and beta </h4> 。
* 

* 这两个常数肯定在某种程度上有联系。原因很容易看出来。在纯平流问题的情况下， $\frac{\partial T}{\partial t} + \mathbf{u}\cdot\nabla T = \gamma$ ，任何显式方案都必须满足形式为 $k\le \min_K \frac{c_k^a h_K}{\|\mathbf{u}\|_{L^\infty(K)}}$ 的CFL条件。另一方面，对于纯扩散问题， $\frac{\partial T}{\partial t} + \nu \Delta T = \gamma$ ，显式方案需要满足一个条件 $k\le \min_K \frac{c_k^d h_K^2}{\nu}$ 。因此，鉴于上述 $\nu$ 的形式，像我们这里要解决的对流扩散问题将导致 $
k\le \min_K \min \left\{
  \frac{c_k^a h_K}{\|\mathbf{u}\|_{L^\infty(K)}},
  \frac{c_k^d h_K^2}{\beta \|\mathbf{u}\|_{L^\infty(K)} h_K}\right\}
  =
  \min_K \left( \min \left\{
  c_k^a,
  \frac{c_k^d}{\beta}\right\}
  \frac{h_K}{\|\mathbf{u}\|_{L^\infty(K)}} \right)
$ 形式的条件。由此可见，我们必须面对这样一个事实：我们可能想把 $\beta$ 选得更大，以提高数值方案的稳定性（通过增加人工扩散的数量），但我们必须付出更小的代价，因此也需要更多的时间步骤。因此，在实践中，我们要尽可能选择小的 $\beta$ ，以保持传输问题的充分稳定，同时尽量选择大的时间步长，以减少总体工作量。
* 要找到正确的平衡，唯一的办法是做一些计算实验。这就是我们所做的。我们略微修改了程序，以允许无网格细化（所以我们不必总是等待那么久），并选择 $
  \nu(T)|_K
  =
  \beta
  \|\mathbf{u}\|_{L^\infty(K)} h_K
$ 来消除常数 $c_R$ 的影响（我们知道通过使用这个版本的 $\nu(T)$ 作为人工粘度，解决方案是稳定的，但我们可以改善一些事情
* 
*--即让解决方案更清晰
* 
但我们可以通过使用这个人工粘度的更复杂的公式来改善情况**--即使解决方案更加清晰**）。) 然后我们对不同的值 $c_k,\beta$ 运行程序，观察域中的最大和最小温度。我们期望看到的情况是这样的。如果我们选择的时间步长过大（即选择一个比理论上允许的大的 $c_k$ ），那么我们将得到温度的指数增长。如果我们选择 $\beta$ 太小，传输稳定就会变得不充分，解决方案将显示出明显的振荡，但不是指数增长。
* 

*<a name="ResultsforQsub1subelements"></a><h5>Results for Q<sub>1</sub> elements</h5>。
* 

* 以下是我们对 $\beta=0.01, \beta=0.1$ 和 $\beta=0.5$ ， $c_k$ 的不同选择，以及2d中的双线性元素（ <code>temperature_degree=1</code> ）得到的结果。
*  <table align="center" class="doxtable">
  <tr>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.timestep.q1.beta=0.01.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.timestep.q1.beta=0.03.png" alt="">
    </td>
  </tr>
  <tr>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.timestep.q1.beta=0.1.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.timestep.q1.beta=0.5.png" alt="">
    </td>
  </tr>
</table>  
* 解释这些图形的方法是这样的：对于 $\beta=0.01$ 和 $c_k=\frac 12,\frac 14$ ，我们看到指数增长或至少是大的变化，但如果我们选择 $k=\frac 18\frac{h_K}{\|\mathbf{u}\|_{L^\infty(K)}}$ 或更小，那么这个方案是稳定的，尽管有点摇摆不定。对于更多的人工扩散，我们可以选择 $k=\frac 14\frac{h_K}{\|\mathbf{u}\|_{L^\infty(K)}}$ 或更小的 $\beta=0.03$ ， $k=\frac 13\frac{h_K}{\|\mathbf{u}\|_{L^\infty(K)}}$ 或更小的 $\beta=0.1$ ，并再次需要 $k=\frac 1{15}\frac{h_K}{\|\mathbf{u}\|_{L^\infty(K)}}$ 的 $\beta=0.5$ （这次是因为许多扩散需要一个小的时间步长）。
* 那么如何选择呢？如果我们只是对大的时间步长感兴趣，那么我们会选择 $\beta=0.1$ 和 $k=\frac 13\frac{h_K}{\|\mathbf{u}\|_{L^\infty(K)}}$ .另一方面，我们也对准确性感兴趣，在这里，实际调查这些曲线所显示的内容可能是有趣的。为此，请注意，我们从零温度开始，而且我们的来源是正的&mdash；所以我们会直观地期望温度永远不会降到零以下。但它确实如此，这是使用连续补充物来近似不连续的解决方案时，吉布现象的结果。因此，我们可以看到，把 $\beta$ 放得太小是不好的：太少的人工扩散会导致没有被扩散掉的过冲和欠冲。另一方面，对于大的 $\beta$ ，最低温度在开始时下降到零以下，但随后很快就扩散回零。
* 另一方面，我们也来看看最高温度。观察溶液的视频，我们可以看到，最初流体处于静止状态。源源不断地加热同一体积的流体，其温度在开始时呈线性增长，直到其浮力能够使其向上移动。因此，最热的那部分流体被带离了溶液，取而代之的流体只被加热了很短的时间就被带出了源区，因此仍然比最初的气泡冷。如果 $\kappa=0$ （在程序中是非零的，但非常小），那么流体中最热的部分应该随着温度恒定的流动而被平移。这就是我们在最小的 $\beta$ 图中所看到的：在达到最高温度时，它几乎不再变化。另一方面，人工扩散越大，热点被扩散的程度越大。请注意，对于这个标准，时间步长并没有发挥重要的作用。
* 因此，总结起来，最好的选择似乎是 $\beta=0.03$ 和 $k=\frac 14\frac{h_K}{\|\mathbf{u}\|_{L^\infty(K)}}$ 。曲线有点摇摆不定，但总的来说，图片看起来很合理，但由于Gibb的现象，在接近开始时间时出现了一些过冲和欠冲的情况。
* 

* <a name="ResultsforQsub2subelements"></a><h5>Results for Q<sub>2</sub> elements</h5> 。
 

* 我们也可以对更高的序数重复同样的实验。下面是温度的双二次方形状函数(  <code>temperature_degree=2</code> )的图形，同时对斯托克斯系统的 $Q_2/Q_1$ 稳定泰勒-霍德元素进行weretain。
*  <table align="center" class="doxtable">
  <tr>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.timestep.q2.beta=0.01.png" alt="">
    </td>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.timestep.q2.beta=0.03.png" alt="">
    </td>
  </tr>
  <tr>
    <td>
        <img src="https://www.dealii.org/images/steps/developer/step-31.timestep.q2.beta=0.1.png" alt="">
    </td>
  </tr>
</table>  
* 同样， $\beta$ 的小值会导致较少的扩散，但我们必须选择非常小的时间步长来保持事情的控制。 $\beta$ 的大值会导致更多的扩散，但同样需要很小的时间步长。最佳值似乎是 $\beta=0.03$ ，就像 $Q_1$ 元素一样，然后我们必须选择 $k=\frac 18\frac{h_K}{\|\mathbf{u}\|_{L^\infty(K)}}$ &mdash；正好是 $Q_1$ 元素的一半大小。 ]元素，如果我们把CFL条件说成是要求时间步长足够小，以便在每个时间步长中运输的距离不超过一个<i>grid point</i>的距离（对于 $Q_1$ 元素是 $h_K$ ，但对于 $Q_2$ 元素是 $h_K/2$ ），这一事实可能并不令人惊讶。事实证明， $\beta$ 需要稍微大一点，以便在模拟后期获得稳定的结果，时间大于60，所以我们实际上在代码中选择它作为 $\beta = 0.034$ 。
* 

* <a name="Resultsfor3d"></a><h5>Results for 3d</h5> 。
* 

* 人们可以在3D中重复这些实验，找到每个 $\beta$ 值的最佳时间步骤，并找到 $\beta$ 的最佳值。我们发现，对于已经在2D中使用的相同的 $\beta$ ，时间步长需要小一点，大约是1.2倍左右。这很容易解释：时间步长的限制是 $k=\min_K \frac{ch_K}{\|\mathbf{u}\|_{L^\infty(K)}}$ ，其中 $h_K$ 是单元的<i>diameter</i>。然而，真正需要的是网格点之间的距离，它是 $\frac{h_K}{\sqrt{d}}$ 。所以更合适的形式是 $k=\min_K \frac{ch_K}{\|\mathbf{u}\|_{L^\infty(K)}\sqrt{d}}$  。
* 第二个发现是需要选择 $\beta$ 稍微大一点（大约 $\beta=0.05$ 左右）。这就再次减少了我们可以采取的时间步骤。
* 

* 
* 

* <a name="Conclusions"></a><h5>Conclusions</h5> 。
 

* 结论是，从上面的简单计算来看， $\beta=0.034$ 似乎是2D中稳定参数的良好选择，而 $\beta=0.05$ 则是3D中的稳定参数。以独立维度的方式，我们可以将其建模为 $\beta=0.017d$ 。如果在更细的网格上做更长时间的计算（几千个时间步长），就会发现时间步长还不够小，为了稳定，必须把上述数值再降低一些（大约是 $\frac 78$ 的一个系数）。
* 因此，调和2D、3D和可变多项式度并考虑到所有因素的公式如下：@f{eqnarray*}
  k =
  \frac 1{2 \cdot 1.7} \frac 1{\sqrt{d}}
  \frac 2d
  \frac 1{q_T}
  \frac{h_K}{\|\mathbf{u}\|_{L^\infty(K)}}
  =
  \frac 1{1.7 d\sqrt{d}}
  \frac 1{q_T}
  \frac{h_K}{\|\mathbf{u}\|_{L^\infty(K)}}.
@f} 。
* 在第一种形式中（方程的中心）， $\frac
1{2 \cdot 1.7}$ 是一个普遍的常数， $\frac 1{\sqrt{d}}$ 是说明单元直径和网格点分离之间的差异的因素， $\frac 2d$ 说明 $\beta$ 随着空间尺寸的增加而增加， $\frac 1{q_T}$ 说明高阶元素的网格点之间的距离， $\frac{h_K}{\|\mathbf{u}\|_{L^\infty(K)}}$ 说明相对于单元尺寸的局部传输速度。这就是我们在程序中使用的公式。
* 至于是使用 $Q_1$ 还是 $Q_2$ 元素来计算温度的问题，以下考虑可能是有用的。首先，解决温度方程在总体方案中几乎不是一个因素，因为几乎所有的计算时间都用于解决每个时间步骤中的斯托克斯系统。因此，温度方程的高阶元素并不是一个重要的缺点。另一方面，如果比较一下由于不连续的源描述而产生的过冲和欠冲的大小，就会发现，对于上述 $\beta$ 和 $k$ 的选择， $Q_1$ 的解下降到 $-0.47$ 左右，而 $Q_2$ 的解只到 $-0.13$ （记住，精确解根本不应该变成负数。这意味着 $Q_2$ 解明显更准确；因此程序使用这些高阶元素，尽管我们在较小的时间步长方面付出了代价。
* 

* <a name="Possibilitiesforextensions"></a><h3> Possibilities for extensions </h3> 。
 

* 有各种方法可以扩展当前的程序。当然，特别感兴趣的是使其更快和/或提高程序的分辨率，特别是在三维中。这是 step-32 教程程序的主题，它将实现在集群上以%并行方式解决这个问题的策略。它也是更大的开源代码ASPECT（见https://aspect.geodynamics.org/）的基础，它可以解决现实的问题，并构成了 step-32 的进一步发展。
* 另一个方向是使流体流动更加逼真。这个程序最初是用来模拟各种情况的，模拟地幔中的物质对流，也就是外地核和固体地壳之间的区域：在那里，物质从下面被加热，从上面被冷却，导致热对流。然而，这种流体的物理学原理要比这个程序中显示的复杂得多。地幔材料的粘度与温度有很大关系，即 $\eta=\eta(T)$ ，这种关系经常被模拟为粘度随着温度的升高而呈指数下降。其次，地幔的大部分动态是由化学反应决定的，主要是构成地幔的各种晶体的相变；因此，斯托克斯方程右边的浮力项不仅取决于温度，而且还取决于某个特定位置的化学成分，这些化学成分被流场平流，但也作为压力和温度的函数而变化。在后面的教程中，我们也将研究其中的一些影响。
* 

* <a name="PlainProg"></a><h1> The plain program</h1>  @include "step-31.cc" 。
* */


