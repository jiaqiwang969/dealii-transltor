//include/deal.II-translator/A-tutorial/step-58_0.txt
/**
 * @page step_58 The step-58 tutorial program
 * 本教程依赖于  step-26  ,  step-29  。 @htmlonly <table
 * class="tutorial" width="50%"> <tr><th colspan="2"><b><small>Table of
 * contents</small></b><b><small>Table of contents</small></b></th></tr>
 * <tr><td width="50%" valign="top">
 * <ol>
 * <li> <a href="#Intro" class=bold>Introduction</a><a href="#Intro"
 * class=bold>Introduction</a>
 * <ul>
 * <li><a href="#Anoteaboutthecharacteroftheequations">A note about the
 * character of the equations</a><a
 * href="#Anoteaboutthecharacteroftheequations">A note about the character of
 * the equations</a>
 * <li><a href="#Thegeneralideaofoperatorsplitting">The general idea of
 * operator splitting</a><a href="#Thegeneralideaofoperatorsplitting">The
 * general idea of operator splitting</a>
 * <li><a href="#OperatorsplittingtheLiesplittingapproach">Operator splitting:
 * the "Lie splitting" approach</a><a
 * href="#OperatorsplittingtheLiesplittingapproach">Operator splitting: the
 * "Lie splitting" approach</a>
 * <li><a href="#OperatorsplittingtheStrangsplittingapproach">Operator
 * splitting: the "Strang splitting" approach</a><a
 * href="#OperatorsplittingtheStrangsplittingapproach">Operator splitting: the
 * "Strang splitting" approach</a>
 * <li><a href="#Timediscretization">Time discretization</a><a
 * href="#Timediscretization">Time discretization</a>
 * <li><a href="#Spatialdiscretizationanddealingwithcomplexvariables">Spatial
 * discretization and dealing with complex variables</a><a
 * href="#Spatialdiscretizationanddealingwithcomplexvariables">Spatial
 * discretization and dealing with complex variables</a>
 * <li><a href="#Linearsolvers">Linear solvers</a><a
 * href="#Linearsolvers">Linear solvers</a>
 * <li><a href="#Definitionofthetestcase">Definition of the test case</a><a
 * href="#Definitionofthetestcase">Definition of the test case</a>
 * </ul>
 * <li> <a href="#CommProg" class=bold>The commented program</a><a
 * href="#CommProg" class=bold>The commented program</a>
 * <ul>
 * <li><a href="#Includefiles">Include files</a><a
 * href="#Includefiles">Include files</a>
 * <li><a href="#ThecodeNonlinearSchroedingerEquationcodeclass">The
 * <code>NonlinearSchroedingerEquation</code> class</a><a
 * href="#ThecodeNonlinearSchroedingerEquationcodeclass">The
 * <code>NonlinearSchroedingerEquation</code> class</a>
 * <li><a href="#Equationdata">Equation data</a><a
 * href="#Equationdata">Equation data</a>
 * <li><a
 * href="#ImplementationofthecodeNonlinearSchroedingerEquationcodeclass">Implementation
 * of the <code>NonlinearSchroedingerEquation</code> class</a> ]<a
 * href="#ImplementationofthecodeNonlinearSchroedingerEquationcodeclass">Implementation
 * of the <code>NonlinearSchroedingerEquation</code> class</a>
 * <ul>
 * <li><a href="#Settingupdatastructuresandassemblingmatrices">Setting up data
 * structures and assembling matrices</a><a
 * href="#Settingupdatastructuresandassemblingmatrices">Setting up data
 * structures and assembling matrices</a>
 * <li><a href="#ImplementingtheStrangsplittingsteps">Implementing the Strang
 * splitting steps</a><a
 * href="#ImplementingtheStrangsplittingsteps">Implementing the Strang
 * splitting steps</a>
 * <li><a href="#Creatinggraphicaloutput">Creating graphical output</a><a
 * href="#Creatinggraphicaloutput">Creating graphical output</a>
 * <li><a href="#Runningthesimulation">Running the simulation</a><a
 * href="#Runningthesimulation">Running the simulation</a>
 * <li><a href="#Themainfunction">The main() function</a><a
 * href="#Themainfunction">The main() function</a>
 * </ul>
 * </ul>
 * </ol></td><td width="50%" valign="top"><ol>
 * <li value="3"> <a href="#Results" class=bold>Results</a><a href="#Results"
 * class=bold>Results</a>
 * <ul>
 * <li><a href="#Visualizingthesolution">Visualizing the solution</a><a
 * href="#Visualizingthesolution">Visualizing the solution</a>
 * <li><a href="#Possibilitiesforextensions">Possibilities for
 * extensions</a><a href="#Possibilitiesforextensions">Possibilities for
 * extensions</a>
 * <ul>
 * <li><a href="#Betterlinearsolvers"> Better linear solvers </a><a
 * href="#Betterlinearsolvers"> Better linear solvers </a>
 * <li><a href="#Boundaryconditions"> Boundary conditions </a><a
 * href="#Boundaryconditions"> Boundary conditions </a>
 * <li><a href="#Adaptivemeshes"> Adaptive meshes </a><a
 * href="#Adaptivemeshes"> Adaptive meshes </a>
 * </ul>
 * </ul>
 * <li> <a href="#PlainProg" class=bold>The plain program</a><a
 * href="#PlainProg" class=bold>The plain program</a>
 * </ol> </td> </tr> </table>
 * @endhtmlonly
 * <br>
 * <i>This program was contributed by Wolfgang Bangerth (Colorado State
 * University) and Yong-Yong Cai (<a href="http://www.csrc.ac.cn/en/">Beijing
 * Computational Science Research Center</a><a
 * href="http://www.csrc.ac.cn/en/">Beijing Computational Science Research
 * Center</a>, CSRC) and is the result of the first author's time as a visitor
 * at CSRC.
 *
 * This material is based upon work partially supported by National Science
 * Foundation grants OCI-1148116, OAC-1835673, DMS-1821210, and EAR-1925595;
 * and by the Computational Infrastructure in Geodynamics initiative (CIG),
 * through the National Science Foundation under Award No. EAR-1550901 and The
 * University of California-Davis. </i>。 <a name="Intro"></a><a
 * name="Introduction"></a><h1>Introduction</h1> 。   函数
 * $\psi=\psi(\mathbf x,t)$ 和势 $V=V(\mathbf x)$ 的<a
 * href="https://en.wikipedia.org/wiki/Nonlinear_Schr%C3%B6dinger_equation">Nonlinear
 * Schr&ouml;dinger Equation
 * (NLSE)</a>是量子力学和非线性光学中经常使用的一个模型。如果用适当的量子进行测量（以便
 * $\hbar=1$ ），则读作如下。
 * @f{align*}{
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - i \frac{\partial \psi}{\partial t}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \frac 12 \Delta \psi
 * + V \psi
 * + \kappa |\psi|^2 \psi
 * &= 0
 * \qquad\qquad
 * &
 * \text{in}\; \Omega\times (0,T),
 * \\
 * \psi(\mathbf x,0) &= \psi_0(\mathbf x)
 * &
 * \text{in}\; \Omega,
 * \\
 * \psi(\mathbf x,t) &= 0
 * &
 * \text{on}\; \partial\Omega\times (0,T).
 * @f}
 * 如果没有电位，即 $V(\mathbf x)=0$
 * ，那么它可以用来描述光在光纤中的传播。如果 $V(\mathbf
 * x)\neq 0$ ，该方程有时也被称为<a
 * href="https://en.wikipedia.org/wiki/Gross%E2%80%93Pitaevskii_equation">Gross-Pitaevskii
 * equation</a>，可用于模拟<a
 * href="https://en.wikipedia.org/wiki/Bose%E2%80%93Einstein_condensate">Bose-Einstein
 * condensates</a>的时间依赖行为。
 * 对于这个特定的教程程序，方程的物理解释对我们来说不是很重要。相反，我们想用它作为一个模型，让我们解释两个方面。
 *
 * - 这是一个<b>complex-valued equation</b>的 $\psi \in H^1(\Omega,{\mathbb
 * C})$ 。我们以前在 step-29
 * 中看到过复值方程，但那里选择了将方程分成实部和虚部，结果是解决了两个实值方程的系统。相比之下，这里的目标是展示如何解决我们将所有东西都保留为复数的问题。
 *
 * 这个方程是一个很好的模型问题，可以解释<b>operator
 * splitting
 * methods</b>如何工作。这是因为它有一些具有根本不同性质的项：一方面，
 * $- \frac 12 \Delta \psi$
 * 是一个常规的空间算子，其方式我们以前已经见过多次；另一方面，
 * $\kappa |\psi(\mathbf x,t)|^2 \psi$
 * 没有空间或时间导数，即它是一个纯粹的局部算子。事实证明，我们对这些项中的每一项都有有效的方法（特别是，我们对后者有分析解），而且我们可能最好对这些项进行不同的、单独的处理。我们将在下文中详细解释这一点。
 *
 *
 * <a name="Anoteaboutthecharacteroftheequations"></a><h3>A note about the
 * character of the equations</h3>
 *
 *  乍一看，这些方程似乎是抛物线，与热力方程相似（见
 * step-26
 * ），因为只有一个时间导数和两个空间导数。事实上，如果我们暂时假设势
 * $V=0$ 和 $\kappa=0$
 * ，就会更容易看出这不是正确的解释。那么我们就会有这样的方程
 * @f{align*}{
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - i \frac{\partial \psi}{\partial t}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \frac 12 \Delta \psi
 * &= 0.
 * @f}
 * 如果我们把解分成实部和虚部， $\psi=v+iw$ 和
 * $v=\textrm{Re}\;\psi,\; w=\textrm{Im}\;\psi$ ，那么我们可以像在
 * step-29 中一样，把一个方程分成实部和虚部。
 * @f{align*}{
 * \frac{\partial w}{\partial t}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \frac 12 \Delta v
 * &= 0,
 * \\
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -\frac{\partial v}{\partial t}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \frac 12 \Delta w
 * &= 0.
 * @f}
 * 毫不奇怪，时间导数前面的因子 $i$
 * 将方程的实部和虚部结合起来。如果我们想进一步理解这个方程，可以用其中一个方程的时间导数，例如
 * @f{align*}{
 * \frac{\partial^2 w}{\partial t^2}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \frac 12 \Delta \frac{\partial v}{\partial t}
 * &= 0,
 * @f}
 * （这里我们假设，至少在某种形式上，我们把空间和时间导数相抵消），然后把另一个方程插入其中。
 * @f{align*}{
 * \frac{\partial^2 w}{\partial t^2}
 * + \frac 14 \Delta^2 w
 * &= 0.
 * @f}
 * 这个方程是双曲线的，在性质上与波浪方程相似。如果你看一下这个程序的
 * "结果
 * "部分的视频，这一点也会很明显）。此外，我们也可以得出与
 * $v$
 * 相同的方程。因此，对于NLSE来说，更好的假设是将其视为一个双曲的波传播方程，而不是像热方程那样的扩散方程。你可能会问，算子
 * $\Delta^2$ 以正号出现，而在波浪方程中， $\Delta$
 * 是负号，这是否正确？这确实是正确的。在与测试函数相乘并通过部分积分后，我们希望得到一个正的（半）定义形式。因此，从
 * $-\Delta u$ 我们得到 $+(\nabla v,\nabla u)$
 * 。同样，经过两次积分，我们从 $+\Delta^2 u$ 得到 $+(\Delta
 * v,\Delta u)$
 * 的形式。在这两种情况下，我们都能得到所需的正号。)
 * 当然，实数NLSE也有 $V\psi$ 和 $\kappa|\psi|^2\psi$
 * 项。然而，这些都是低阶的空间衍生物，虽然它们显然很重要，但它们并不改变方程的特征。
 * 在任何情况下，本讨论的目的是要弄清楚什么样的时间步进方案可能适合该方程。结论是，作为一个双曲型方程，我们需要选择一个满足CFL型条件的时间步长。如果我们使用显式方法（我们不会这样做），我们将不得不研究与空间运算器相对应的矩阵的特征值。如果你跟随视频讲座的讨论(
 * @dealiiVideoLectureSeeAlso{26,27,28})
 * ，那么你会记得，模式是需要确保 $k^s \propto h^t$ ，其中
 * $k$ 是时间步长， $h$ 是网格宽度，而 $s,t$
 * 无论你采用原始方程( $s=1,t=2$
 * )还是只对实部或虚部进行重构，结果都是如果我们要使用显式时间步长方法，我们需要选择
 * $k \propto h^2$ 。这是不可行的，原因与 step-26
 * 中的热方程相同。这将产生不切实际的小的时间步长，甚至只有适度精细的网格。相反，我们必须使用隐式时间步长方法，然后可以选择一个更平衡的
 * $k \propto h$
 * 。事实上，我们将使用隐式的Crank-Nicolson方法，正如我们之前在
 * step-23 中对正波方程所做的那样。
 *
 *  <a name="Thegeneralideaofoperatorsplitting"></a><h3>The general idea of
 * operator splitting</h3> 。
 *
 *  @dealiiVideoLecture{30.25}
 * 如果我们把NLSE看作是一个常微分方程，其中的右手边恰好有空间导数，即把它写为
 * @f{align*}{
 * \frac{d\psi}{dt}
 * &=
 * i\frac 12 \Delta \psi
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i V \psi
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi|^2 \psi,
 * \qquad\qquad
 * &
 * \text{for}\; t \in (0,T),
 * \\
 * \psi(0) &= \psi_0,
 * @f}
 * 人们可能会想通过对时间间隔 $[t_{n},t_{n+1}]$
 * 的两边积分来 "正式解决 "它，并得到
 * @f{align*}{
 * \psi(t_{n+1})
 * &=
 * \psi(t_n)
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 * i\frac 12 \Delta \psi(t)
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i V \psi(t)
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi(t)|^2 \psi(t)
 * \right)
 * \;
 * dt.
 * @f}
 * 当然，这不是那么简单的：积分中的 $\psi(t)$
 * 仍在根据微分方程随时间变化，所以我们不能只是评估积分（或通过正交轻松近似），因为我们不知道
 * $\psi(t)$
 * 。但我们可以用下面的单独贡献来写，这将使我们能够分别处理不同的条款。
 * @f{align*}{
 * \psi(t_{n+1})
 * &=
 * \psi(t_n)
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 * i\frac 12 \Delta \psi(t)
 * \right)
 * \;
 * dt
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i V \psi(t)
 * \right)
 * \;
 * dt
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi(t)|^2 \,\psi(t)
 * \right)
 * \;
 * dt.
 * @f}
 * 现在可以把这个方程解读为以下方式。对于每个时间间隔
 * $[t_{n},t_{n+1}]$ ，溶液中的变化 $\psi(t_{n+1})-\psi(t_{n})$
 * 由三个贡献组成。
 *
 * - 拉普拉斯算子的贡献。
 *
 * - 势的贡献 $V$  。
 *
 * - "相位 "项的贡献  $-i\kappa |\psi(t)|^2\,\psi(t)$  .
 * <i>Operator
 * splitting</i>是现在的一种近似技术，允许我们分别处理这些贡献中的每一个。(如果我们想的话。在实践中，我们将把前两项放在一起处理，而把最后一项分开。但这是一个细节，从概念上讲，我们可以以不同的方式处理所有这些贡献）。)
 * 为此，让我们介绍三个独立的 "解决方案"。
 * @f{align*}{
 * \psi^{(1)}(t_{n+1})
 * &=
 * \psi(t_n)
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 * i\frac 12 \Delta \psi^{(1)}(t)
 * \right)
 * \;
 * dt,
 * \\
 * \psi^{(2)}(t_{n+1})
 * &=
 * \psi(t_n)
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i V \psi^{(2)}(t)
 * \right)
 * \;
 * dt,
 * \\
 * \psi^{(3)}(t_{n+1})
 * &=
 * \psi(t_n)
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi^{(3)}(t)|^2 \,\psi^{(3)}(t)
 * \right)
 * \;
 * dt.
 * @f}
 *
 * 这三个 "解决方案
 * "可以被认为是满足了以下的微分方程。
 * @f{align*}{
 * \frac{d\psi^{(1)}}{dt}
 * &=
 * i\frac 12 \Delta \psi^{(1)},
 * \qquad
 * &
 * \text{for}\; t \in (t_n,t_{n+1}),
 * \qquad\qquad\text{with initial condition}\;
 * \psi^{(1)}(t_n) &= \psi(t_n),
 * \\
 * \frac{d\psi^{(2)}}{dt}
 * &=
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i V \psi^{(2)},
 * &
 * \text{for}\; t \in (t_n,t_{n+1}),
 * \qquad\qquad\text{with initial condition}\;
 * \psi^{(2)}(t_n) &= \psi(t_n),
 * \\
 * \frac{d\psi^{(3)}}{dt}
 * &=
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi^{(3)}|^2 \,\psi^{(3)},
 * &
 * \text{for}\; t \in (t_n,t_{n+1}),
 * \qquad\qquad\text{with initial condition}\;
 * \psi^{(3)}(t_n) &= \psi(t_n).
 * @f}
 * 换句话说，它们都是以 $\psi^{(k)}$
 * 为起点的轨迹，并恰好整合了三条准则中的一条的影响。在我们的时间间隔内，这些条款的增量分别是
 * $I^{(1)}=\psi^{(1)}(t_{n+1})-\psi(t_n)$ 、
 * $I^{(2)}=\psi^{(2)}(t_{n+1})-\psi(t_n)$ 和
 * $I^{(3)}=\psi^{(3)}(t_{n+1})-\psi(t_n)$  。
 * 现在我们可以合理地假设（这是一个近似值！），由于所有这三种效应引起的变化是由三个单独的增量的总和来近似的。
 * @f{align*}{
 * \psi(t_{n+1})-\psi(t_n)
 * \approx
 * I^{(1)} + I^{(2)} + I^{(3)}.
 * @f}
 * 这个直觉确实是正确的，尽管这个近似并不精确：准确的左手边和术语
 * $I^{(1)}+I^{(2)}+I^{(3)}$ 之间的差异（即从 $t_n$ 移动到
 * $t_{n+1}$
 * 时准确解决方案<i>exact</i>的增量与右手边三部分组成的增量之间的差异），正比于
 * $\Delta t=t_{n+1}-t_{n}$
 * 。换句话说，这种方法引入了一个大小为 ${\cal O}(\Delta t)$
 * 的误差。到目前为止，我们所做的一切都没有在时间或空间上离散化，所以<i>overall</i>的误差将是
 * ${\cal O}(\Delta t)$
 * 加上我们在近似积分时犯的任何错误（时间离散化误差）加上我们在近似
 * $\psi$ 的空间依赖关系时犯的任何错误（空间误差）。
 * 在我们继续讨论运算符拆分之前，让我们谈谈为什么要这样做？答案很简单。对于
 * $\psi^{(k)}$
 * 的一些独立方程，我们可能有办法比把所有东西放在一起一次解决更有效地解决它们。例如，在目前的情况下，尤其是与之相关的。
 * $\psi^{(3)}$ 的方程式，即。
 * @f{align*}{
 * \frac{d\psi^{(3)}}{dt}
 * &=
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi^{(3)}|^2 \,\psi^{(3)},
 * \qquad\qquad
 * &
 * \text{for}\; t \in (t_n,t_{n+1}),
 * \qquad\qquad\text{with initial condition}\;
 * \psi^{(3)}(t_n) &= \psi(t_n),
 * @f}
 * 或等价的。
 * @f{align*}{
 * \psi^{(3)}(t_{n+1})
 * &=
 * \psi(t_n)
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi^{(3)}(t)|^2 \,\psi^{(3)}(t)
 * \right)
 * \;
 * dt,
 * @f}
 * 可以准确地解决：方程的解法是
 * @f{align*}{
 * \psi^{(3)}(t) = e^{-i\kappa|\psi(t_n)|^2 (t-t_{n})} \psi(t_n).
 * @f}
 * 如果(i)你把这个解插入微分方程，(ii)意识到 $|\psi^{(3)}|$
 * 的幅度是常数，即指数中的 $|\psi(t_n)|^2$ 项实际上等于
 * $|\psi^{(3)}(t)|^2$ ，这就很容易看出。换句话说，
 * $\psi^{(3)}(t)$
 * 的ODE的解只改变了它的<i>phase</i>，但复值函数
 * $\psi^{(3)}(t)$ 的<i>magnitude</i>保持不变。这使得计算 $I^{(3)}$
 * 特别方便：我们实际上不需要解决任何ODE，我们可以用手写出解。使用算子拆分方法，没有任何一种计算
 * $I^{(1)},I^{(2)}$
 * 的方法需要处理非线性项和所有相关的不愉快：只要我们允许自己使用算子拆分方法，我们就可以摆脱只解决<i>linear</i>的问题了。
 * 其次，如果不同的项所描述的不同的物理效应具有不同的时间尺度，我们经常使用算子拆分。例如，想象一下，我们确实有某种扩散方程的情况。扩散作用缓慢，但如果
 * $\kappa$ 很大，那么 $-i\kappa |\psi^{(3)}(t)|^2 \,\psi^{(3)}(t)$
 * 项的 "相位旋转
 * "作用很快。如果我们把一切都放在一起处理，这就意味着必须采取相当小的时间步长。但是有了算子分割，我们可以对扩散采取大的时间步长
 * $\Delta t=t_{n+1}-t_{n}$
 * ，并且（假设我们没有分析解）使用具有许多小时间步长的ODE求解器来整合从
 * $t_n$ 到 $t_{n+1}$ 的 "相位旋转
 * "方程。换句话说，算子分割使我们能够将慢速和快速的时间尺度结合起来，并以不同的方式处理它们，并根据每种情况调整方法。
 *
 *  <a name="OperatorsplittingtheLiesplittingapproach"></a><h3>Operator
 * splitting: the "Lie splitting" approach</h3> 。
 *
 *  虽然上述方法允许平行计算三个贡献 $I^{(k)}$
 * ，但如果我们愿意，如果我们不让 $\psi^{(k)}$
 * 的轨迹全部从 $\psi(t_n)$ 开始，而让轨迹从 $\psi(t_n)$
 * 开始，该方法可以变得稍微准确和容易实施。 ]，而是让
 * $\psi^{(2)}$ 的轨迹从 $\psi^{(1)}$ 的轨迹的<i>end
 * point</i>开始，即 $\psi^{(1)}(t_{n+1})$ ；同样，我们将从
 * $\psi^{(3)}$ 的轨迹的终点开始，即 $\psi^{(2)}(t_{n+1})$
 * 。这种方法被称为 "Lie
 * splitting"，其误差顺序与上述方法相同，即分割误差为
 * ${\cal O}(\Delta t)$  。
 * 运算符拆分的这一变化可以写成以下内容（仔细比较初始条件和上面的条件）。
 * @f{align*}{
 * \frac{d\psi^{(1)}}{dt}
 * &=
 * i\frac 12 \Delta \psi^{(1)},
 * \qquad
 * &
 * \text{for}\; t \in (t_n,t_{n+1}),
 * \qquad\qquad\text{with initial condition}\;
 * \psi^{(1)}(t_n) &= \psi(t_n),
 * \\
 * \frac{d\psi^{(2)}}{dt}
 * &=
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i V \psi^{(2)},
 * &
 * \text{for}\; t \in (t_n,t_{n+1}),
 * \qquad\qquad\text{with initial condition}\;
 * \psi^{(2)}(t_n) &= \psi^{(1)}(t_{n+1}),
 * \\
 * \frac{d\psi^{(3)}}{dt}
 * &=
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi^{(3)}|^2 \,\psi^{(3)},
 * &
 * \text{for}\; t \in (t_n,t_{n+1}),
 * \qquad\qquad\text{with initial condition}\;
 * \psi^{(3)}(t_n) &= \psi^{(2)}(t_{n+1}).
 * @f}
 * 显然，虽然上面的公式意味着我们应该以这种特定的顺序来解决这些问题，但首先解决轨迹3，然后是2，然后是1，或任何其他的排列组合也同样有效。
 * 然后，这些方程的综合形式是
 * @f{align*}{
 * \psi^{(1)}(t_{n+1})
 * &=
 * \psi(t_n)
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 * i\frac 12 \Delta \psi^{(1)}(t)
 * \right)
 * \;
 * dt,
 * \\
 * \psi^{(2)}(t_{n+1})
 * &=
 * \psi^{(1)}(t_{n+1})
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i V \psi^{(2)}(t)
 * \right)
 * \;
 * dt,
 * \\
 * \psi^{(3)}(t_{n+1})
 * &=
 * \psi^{(2)}(t_{n+1})
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi^{(3)}(t)|^2 \,\psi^{(3)}(t)
 * \right)
 * \;
 * dt.
 * @f}
 * 从实用的角度来看，这样做的好处是我们需要保持较少的解向量。一旦
 * $\psi^{(1)}(t_n)$ 被计算出来，我们就不再需要 $\psi(t_n)$
 * 了；一旦 $\psi^{(2)}(t_n)$ 被计算出来，我们就不再需要
 * $\psi^{(1)}(t_n)$ 了。一旦 $\psi^{(3)}(t_n)$
 * 被计算出来，我们就可以直接称之为 $\psi(t_{n+1})$
 * ，因为如果你把第一个方程插入第二个方程，然后再插入第三个方程，你会发现
 * $\psi^{(3)}(t_n)$ 的右边现在包含所有三个物理效应的贡献。
 * @f{align*}{
 * \psi^{(3)}(t_{n+1})
 * &=
 * \psi(t_n)
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 * i\frac 12 \Delta \psi^{(1)}(t)
 * \right)
 * \;
 * dt
 * +
 * \int_{t_n}^{t_{n+1}}
 * \left(
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i V \psi^{(2)}(t)
 * \right)
 * \;
 * dt+
 * \int_{t_n}^{t_{n+1}}
 * \left(
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi^{(3)}(t)|^2 \,\psi^{(3)}(t)
 * \right)
 * \;
 * dt.
 * @f}
 * 换句话说，Lie拆分法比上述的原始方法简单得多，因为数据处理要简单得多。
 *
 *  <a name="OperatorsplittingtheStrangsplittingapproach"></a><h3>Operator
 * splitting: the "Strang splitting" approach</h3>。
 *
 *  如上所述，Lie分裂法只有 ${\cal O}(\Delta t)$
 * 的准确性。如果我们使用一阶时间微分，例如使用显式或隐式Eulermethods来解决
 * $\psi^{(k)}$
 * 的微分方程，这是可接受的。这是因为这些时间积分方法引入了与
 * $\Delta t$
 * 本身成正比的误差，因此分割误差与我们无论如何都会引入的误差成正比，并不会减少整体收敛的顺序。
 * 但我们通常希望使用更高的阶数
 *
 * - 例如，<a href="https://en.wikipedia.org/wiki/Crank%E2%80%93Nicolson_method">Crank-Nicolson</a>或<a href="https://en.wikipedia.org/wiki/Backward_differentiation_formula">BDF2</a>方法
 *
 * 因为这些方法通常不会比简单的欧拉方法更昂贵。如果我们使用
 * ${\cal O}(\Delta t^2)$
 * 的时隙方法，但由于算子分裂而再次失去准确性，那将是一种耻辱。
 * 这就是<a href="https://en.wikipedia.org/wiki/Strang_splitting">Strang
 * splitting</a>方法的作用。如果我们只有两部分，就更容易解释，因此让我们把拉普拉斯算子和势的影响合二为一，把相位旋转合二为一。事实上，这就是我们在代码中要做的，因为用拉普拉斯方程求解，无论有无电势，其代价都是一样的。
 *
 * 所以我们把这两个步骤合并起来）。)
 * 上面的Lie拆分方法将做以下工作。它计算出以下两个ODE的解。
 * @f{align*}{
 * \frac{d\psi^{(1)}}{dt}
 * &=
 * i\frac 12 \Delta \psi^{(1)}
 *
 * -i V \psi^{(1)},
 * \qquad
 * &
 * \text{for}\; t \in (t_n,t_{n+1}),
 * \qquad\qquad\text{with initial condition}\;
 * \psi^{(1)}(t_n) &= \psi(t_n),
 * \\
 * \frac{d\psi^{(2)}}{dt}
 * &=
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi^{(2)}|^2 \,\psi^{(2)},
 * &
 * \text{for}\; t \in (t_n,t_{n+1}),
 * \qquad\qquad\text{with initial condition}\;
 * \psi^{(2)}(t_n) &= \psi^{(1)}(t_{n+1}),
 * @f}
 * 然后使用近似值 $\psi(t_{n+1}) \approx \psi^{(2)}(t_{n+1})$
 * 。换句话说，我们首先为物理效应一做一个完整的时间步骤，然后为物理效应二做一个完整的时间步骤。在时间步数结束时的解决方案只是分别由这些物理效应引起的增量的总和。
 * 相比之下，<a href="https://en.wikipedia.org/wiki/Gilbert_Strang">Gil
 * Strang</a>（20世纪中期开始的数值分析领域的泰斗之一）发现，先对一个物理效应做一个半步，然后对另一个物理效应做一个全时步，再对第一个物理效应做一个半步，这样更准确。哪个是哪个并不重要，但由于做相位旋转是如此简单，我们将使用这个效应做半步，然后只需要用拉普拉斯算子加电势做一个空间解。这种算子拆分方法现在是
 * ${\cal O}(\Delta t^2)$
 * 准确的。写在公式中，这产生了以下的步骤序列。
 * @f{align*}{
 * \frac{d\psi^{(1)}}{dt}
 * &=
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi^{(1)}|^2 \,\psi^{(1)},
 * &&
 * \text{for}\; t \in (t_n,t_n+\tfrac 12\Delta t),
 * \qquad\qquad&\text{with initial condition}\;
 * \psi^{(1)}(t_n) &= \psi(t_n),
 * \\
 * \frac{d\psi^{(2)}}{dt}
 * &=
 * i\frac 12 \Delta \psi^{(2)}
 *
 * -i V \psi^{(2)},
 * \qquad
 * &&
 * \text{for}\; t \in (t_n,t_{n+1}),
 * \qquad\qquad&\text{with initial condition}\;
 * \psi^{(2)}(t_n) &= \psi^{(1)}(t_n+\tfrac 12\Delta t),
 * \\
 * \frac{d\psi^{(3)}}{dt}
 * &=
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\kappa |\psi^{(3)}|^2 \,\psi^{(3)},
 * &&
 * \text{for}\; t \in (t_n+\tfrac 12\Delta t,t_{n+1}),
 * \qquad\qquad&\text{with initial condition}\;
 * \psi^{(3)}(t_n) &= \psi^{(2)}(t_{n+1}).
 * @f}
 * 如前所述，第一和第三步可以准确地计算出这个特定的方程，得出的结果是
 * @f{align*}{
 * \psi^{(1)}(t_n+\tfrac 12\Delta t) &= e^{-i\kappa|\psi(t_n)|^2 \tfrac
 * 12\Delta t} \; \psi(t_n),
 * \\
 * \psi^{(3)}(t_{n+1}) &= e^{-i\kappa|\psi^{(2)}(t_{n+1})|^2 \tfrac
 * 12\Delta t} \; \psi^{(2)}(t_{n+1}).
 * @f}
 *
 * 这就是我们要在这个程序中实现的东西：在每个时间步骤中，我们执行三个步骤，即
 *
 * - 通过分析整合相位旋转方程的半个时间步长，更新每个节点的解值。
 *
 * - 解决对应于 $\psi^{(2)}$ 的全步骤的时空方程，即 $-i\frac{\partial\psi^{(2)}}{\partial t}
 *
 *
 *
 *
 *
 * - \frac 12 \Delta \psi^{(2)} + V \psi^{(2)} = 0$
 * ，其初始条件等于上述第一个半步骤的解。
 *
 * - 通过对相位旋转方程再进行半个时间步长的分析积分，更新每个节点的解值。
 * 这一结构将以明显的方式反映在程序的主时间环中。
 *
 *
 * <a name="Timediscretization"></a><h3>Time discretization</h3> 。
 *
 * 从上面的讨论中，我们应该清楚地看到，我们在每个时间步长中要解决的唯一部分微分方程是
 * @f{align*}{
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\frac{\partial\psi^{(2)}}{\partial t}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -
 * \frac 12 \Delta \psi^{(2)} + V \psi^{(2)} = 0.
 * @f}
 * 这个方程是线性的。此外，我们只需要解决从 $t_n$ 到
 * $t_{n+1}$ 的问题，也就是说，正好是一个时间步骤。
 * 为了做到这一点，我们将应用二阶精确的Crank-Nicolson方案，我们已经在其他一些时间相关的代码中使用过了（特别是：
 * step-23  和  step-26  ）。它的内容如下。
 * @f{align*}{
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\frac{\psi^{(n,2)}-\psi^{(n,1)}}{k_{n+1}}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -
 * \frac 12 \Delta \left[\frac 12
 * \left(\psi^{(n,2)}+\psi^{(n,1)}\right)\right]
 * +
 * V \left[\frac 12 \left(\psi^{(n,2)}+\psi^{(n,1)}\right)\right] = 0.
 * @f}
 * 这里，"先前 "的解决方案 $\psi^{(n,1)}$
 * （或这部分时间步骤的
 * "初始条件"）是第一个阶段旋转半步的输出；当前步骤的输出将用
 * $\psi^{(n,2)}$ 表示。  $k_{n+1}=t_{n+1}-t_n$
 * 是时间步骤的长度。人们可以争论 $\psi^{(n,1)}$ 和
 * $\psi^{(n,1)}$ 是生活在时间步长 $n$ 还是 $n+1$
 * 以及它们的上限值应该是什么。这是一个没有实际影响的哲学讨论，人们可以把
 * $\psi^{(n,1)}$ 看作是类似于 $\psi^{(n+\tfrac 13)}$ 的东西，而把
 * $\psi^{(n,2)}$ 看作是 $\psi^{(n+\tfrac 23)}$
 * ，如果这有助于澄清事情的话。
 *
 * 不过， $n+\frac 13$ 也不能理解为" $t_n$
 * 之后的第三个时间步骤"，而更像是
 * "我们已经完成了时间步骤 $n+1$
 * 所需的三分之一的工作"）。) 如果我们将整个方程与
 * $k_{n+1}$ 相乘，并将未知数 $\psi^{(n+1,2)}$
 * 的条款排序到左边，将已知数 $\psi^{(n,2)}$
 * 的条款排序到右边，那么我们得到以下（空间）偏微分方程，需要在每个时间步长中解决。
 * @f{align*}{
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\psi^{(n,2)}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -
 * \frac 14 k_{n+1} \Delta \psi^{(n,2)}
 * +
 * \frac 12 k_{n+1} V \psi^{(n,2)}
 * =
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -i\psi^{(n,1)}
 * +
 * \frac 14 k_{n+1} \Delta \psi^{(n,1)}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -
 * \frac 12 k_{n+1} V \psi^{(n,1)}.
 * @f}
 *
 *
 *
 * <a
 * name="Spatialdiscretizationanddealingwithcomplexvariables"></a><h3>Spatial
 * discretization and dealing with complex variables</h3> 。
 *
 *  如上所述，先前处理复值解的教程程序（即 step-29
 * ）将解的实部和虚部分开。因此，它把一切都简化为实数运算。与此相反，我们在这里希望保持复数值的东西。
 * 这方面的第一部分是，我们需要将离散化的解决方案定义为
 * $\psi_h^n(\mathbf x)=\sum_j \Psi^n_j \varphi_j(\mathbf x) \approx
 * \psi(\mathbf x,t_n)$ ，其中 $\varphi_j$
 * 是通常的形状函数（是实值的），但时间步长 $n$
 * 的扩展系数 $\Psi^n_j$
 * 现在是复值的。这在deal.II中很容易做到：我们只需要用
 * Vector<std::complex<double>>
 * 而不是Vector<double>来存储这些系数。
 * 更有趣的是如何建立和解决线性系统。显然，这只对上面讨论的Strang拆分的第二步有必要，即上一小节中的时间离散化。我们通过将
 * $\psi^n$ 直接替换为 $\psi^n_h$
 * 并乘以一个测试函数，得到完全离散的版本。
 * @f{align*}{
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -iM\Psi^{(n,2)}
 * +
 * \frac 14 k_{n+1} A \Psi^{(n,2)}
 * +
 * \frac 12 k_{n+1} W \Psi^{(n,2)}
 * =
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -iM\Psi^{(n+1,1)}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -
 * \frac 14 k_{n+1} A \Psi^{(n,1)}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * -
 * \frac 12 k_{n+1} W \Psi^{(n,1)},
 * @f}
 * 或者以更紧凑的方式写。
 * @f{align*}{
 * \left[
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
 * -iM
 *  +
 *  \frac 14 k_{n+1} A
 *  +
 *  \frac 12 k_{n+1} W
 * \right] \Psi^{(n,2)}
 * =
 * \left[
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
 * -iM
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
 * -
 *  \frac 14 k_{n+1} A
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
 * -
 * \frac 12 k_{n+1} W
 * \right] \Psi^{(n,1)}.
 * @f}
 * 这里，矩阵是以其明显的方式定义的。
 * @f{align*}{
 * M_{ij} &= (\varphi_i,\varphi_j), \\
 * A_{ij} &= (\nabla\varphi_i,\nabla\varphi_j), \\
 * W_{ij} &= (\varphi_i,V \varphi_j).
 * @f}
 * 请注意，所有的矩阵都是对称的、实值的，而且至少是正半无限的，不过对于系统矩阵
 * $C =
 *
 * -iM + \frac 14 k_{n+1} A + \frac 12 k_{n+1} W$ 和右侧的相应矩阵 $R
 * =
 *
 * -iM
 *
 * - \frac 14 k_{n+1} A
 *
 * - \frac 12 k_{n+1} W$ 来说，显然不是这样的。
 *
 *  <a name="Linearsolvers"></a><h3>Linear solvers</h3> 。
 *
 *  @dealiiVideoLecture{34}
 * 关于解决程序的唯一剩下的重要问题是如何解决复值线性系统
 * @f{align*}{
 * C \Psi^{(n+1,2)}
 * =
 * R \Psi^{(n+1,1)},
 * @f}
 * 矩阵 $C =
 *
 * -iM + \frac 14 k_{n+1} A + \frac 12 k_{n+1} W$
 * 的右手边很容易被计算为已知矩阵与上一步骤的解的乘积，像往常一样，这归结为矩阵
 * $C$
 * 具有什么属性的问题。如果它是对称和正定的，那么我们可以使用共轭梯度法。
 * 不幸的是，该矩阵唯一有用的属性是它是复数对称的，即
 * $C_{ij}=C_{ji}$ ，回顾一下 $M,A,W$
 * 都是对称的，就不难发现。然而，它不是<a
 * href="https://en.wikipedia.org/wiki/Hermitian_matrix">Hermitian</a>，这就要求
 * $C_{ij}=\bar C_{ji}$ ，其中横杠表示完全共轭。
 * 复杂的对称性可以被用于迭代求解器，正如快速的文献搜索所显示的那样。我们在这里不会试图变得复杂（实际上是把这个问题留给下面的<a
 * href="#extensions">Possibilities for
 * extensions</a>部分），而是简单地用老式的好办法来解决没有属性的问题。直接求解器。这不是最好的，特别是对于大问题，但对于一个教程程序来说，这已经足够了。
 *
 *  <a name="Definitionofthetestcase"></a><h3>Definition of the test case</h3>
 * 。
 * NLSE的初始条件通常被选择来代表特定的物理情况。这超出了本方案的范围，但只要说这些初始条件是(i)位于不同点的粒子的波函数的叠加，以及(ii)因为 $|\psi(\mathbf x,t)|^2$ 对应于粒子密度函数，积分@f[
 * N(t) = \int_\Omega |\psi(\mathbf x,t)|^2
 * @f]对应于系统中的粒子数。显然，如果要在物理上正确，如果系统是封闭的， $N(t)$ 最好是一个常数，如果有吸收边界条件， $\frac{dN}{dt}<0$ 则是常数）。重要的一点是，我们应该选择初始条件，使@f[
 * N(0) = \int_\Omega |\psi_0(\mathbf x)|^2 @f]有意义。
 * 我们在这里使用的，主要是因为它的图形很好，如下：@f[
 * \psi_0(\mathbf x) = \sqrt{\sum_{k=1}^4 \alpha_k e^{-\frac{r_k^2}{R^2}}},
 * @f]其中 $r_k = |\mathbf x-\mathbf x_k|$ 是与（固定）位置 $\mathbf x_k$ 的距离，而 $\alpha_k$ 的选择是为了使我们所添加的每个高斯都能为 $N(0)$ 添加整数的粒子。我们通过确保@f[
 * \int_\Omega \alpha_k e^{-\frac{r_k^2}{R^2}}
 * @f]是一个正整数来实现这一点。换句话说，我们需要选择 $\alpha$ 作为@f[
 * \left(\int_\Omega e^{-\frac{r_k^2}{R^2}}\right)^{-1} =
 * \left(R^d\sqrt{\pi^d}\right)^{-1}, @f]的整数倍，暂时假设
 * $\Omega={\mathbb R}^d$
 *
 * --当然不是这样的，但我们会忽略积分的微小差异。
 * 因此，我们选择 $\alpha_k=\left(R^d\sqrt{\pi^d}\right)^{-1}$
 * 为所有，而 $R=0.1$ 。这个 $R$
 * 足够小，以至于精确（无限）积分和 $\Omega$
 * 上的积分之间的差异不应该太在意。我们选择 $\mathbf x_k$
 * 这四个点作为 $(\pm 0.3, 0), (0, \pm 0.3)$
 *
 * --也离 $\Omega$ 的边界足够远，以保证我们自己的安全。
 * 为简单起见，我们在正方形 $[-1,1]^2$ 上提出问题。对于边界条件，我们将使用@f[
 * \nabla\psi(\mathbf x,t)\cdot \mathbf n=0 \qquad\qquad \forall \mathbf x\in\partial\Omega.
 * @f]形式的时间无关的诺伊曼条件，这不是一个现实的边界条件选择，但对于我们想在这里展示的东西来说是足够的。我们将在下面的<a href="#extensions">Possibilities for extensions</a>部分对此作进一步评论。
 * 最后，我们选择 $\kappa=1$ ，势为@f[
 * V(\mathbf x)
 * =
 * \begin{cases} 0 & \text{if}\; |\mathbf x|<0.7
 *              \\
 *              1000 & \text{otherwise}.
 * \end{cases}
 * @f]，使用大的势可以确保波函数 $\psi$ 在半径为0.7的圆外保持较小。构成初始条件的所有高斯都在这个圆内，解决方案将主要在这个圆内振荡，有少量的能量辐射到圆外。大势的使用也确保了非物理边界条件不会产生太大影响。
 *
 *  <a name="CommProg"></a> <h1> The commented program</h1>。 <a
 * name="Includefiles"></a> <h3>Include files</h3>
 * 程序以通常的包含文件开始，所有这些文件你现在应该都见过了。
 *
 * @code
 * #include <deal.II/base/logstream.h>
 * #include <deal.II/lac/vector.h>
 * #include <deal.II/lac/full_matrix.h>
 * #include <deal.II/lac/dynamic_sparsity_pattern.h>
 * #include <deal.II/lac/sparse_matrix.h>
 * #include <deal.II/lac/block_sparse_matrix.h>
 * #include <deal.II/lac/block_vector.h>
 * #include <deal.II/lac/affine_constraints.h>
 * #include <deal.II/lac/sparse_direct.h>
 * #include <deal.II/grid/tria.h>
 * #include <deal.II/grid/grid_generator.h>
 * #include <deal.II/grid/grid_refinement.h>
 * #include <deal.II/dofs/dof_handler.h>
 * #include <deal.II/dofs/dof_tools.h>
 * #include <deal.II/fe/fe_q.h>
 * #include <deal.II/fe/fe_values.h>
 * #include <deal.II/numerics/data_out.h>
 * #include <deal.II/numerics/vector_tools.h>
 * #include <deal.II/numerics/error_estimator.h>
 * #include <deal.II/numerics/matrix_tools.h>
 *
 * #include <fstream>
 * #include <iostream>
 *
 *
 * @endcode
 *
 * 然后照例将本程序的所有内容放入一个命名空间，并将deal.II命名空间导入到我们将要工作的命名空间中。
 *
 * @code
 * namespace Step58
 * {
 * using namespace dealii;
 *
 * @endcode
 *
 * <a name="ThecodeNonlinearSchroedingerEquationcodeclass"></a> <h3>The
 * <code>NonlinearSchroedingerEquation</code> class</h3>
 * 然后是主类。它看起来非常像 step-4 或 step-6
 * 中的相应类，唯一的例外是，矩阵和向量以及其他所有与线性系统相关的元素现在都存储为
 * `std::complex<double>` 类型，而不仅仅是`double`。
 *
 *
 * @code
 * template <int dim>
 * class NonlinearSchroedingerEquation
 * {
 * public:
 *   NonlinearSchroedingerEquation();
 *   void run();
 *
 * private:
 *   void setup_system();
 *   void assemble_matrices();
 *   void do_half_phase_step();
 *   void do_full_spatial_step();
 *   void output_results() const;
 *
 *
 *   Triangulation<dim> triangulation;
 *   FE_Q<dim>          fe;
 *   DoFHandler<dim>    dof_handler;
 *
 *   AffineConstraints<std::complex<double>> constraints;
 *
 *   SparsityPattern                    sparsity_pattern;
 *   SparseMatrix<std::complex<double>> system_matrix;
 *   SparseMatrix<std::complex<double>> rhs_matrix;
 *
 *   Vector<std::complex<double>> solution;
 *   Vector<std::complex<double>> system_rhs;
 *
 *   double       time;
 *   double       time_step;
 *   unsigned int timestep_number;
 *
 *   double kappa;
 * };
 *
 *
 *
 * @endcode
 *
 * <a name="Equationdata"></a> <h3>Equation data</h3>.
 *
 * 在我们继续填写主类的细节之前，让我们定义与问题相对应的方程数据，即初始值，以及一个右手类。(我们将重复使用初始条件也用于边界值，我们只是保持边界值不变)。我们使用派生自Function类模板的类来做这件事，这个模板之前已经用过很多次了，所以下面的内容看起来并不令人惊讶。唯一值得注意的是，我们这里有一个复值问题，所以我们必须提供Function类的第二个模板参数（否则会默认为`double`）。此外，`value()`函数的返回类型当然也是复数。
 * 这些函数准确地返回什么，在介绍部分的最后已经讨论过了。
 *
 *
 * @code
 * template <int dim>
 * class InitialValues : public Function<dim, std::complex<double>>
 * {
 * public:
 *   InitialValues()
 *     : Function<dim, std::complex<double>>(1)
 *   {}
 *
 *   virtual std::complex<double>
 *   value(const Point<dim> &p, const unsigned int component = 0) const override;
 * };
 *
 *
 *
 * template <int dim>
 * std::complex<double>
 * InitialValues<dim>::value(const Point<dim> & p,
 *                           const unsigned int component) const
 * {
 *   static_assert(dim == 2, "This initial condition only works in 2d.");
 *
 *   (void)component;
 *   Assert(component == 0, ExcIndexRange(component, 0, 1));
 *
 *   const std::vector<Point<dim>> vortex_centers = {{0,
 *
 * -0.3},
 *                                                   {0, +0.3},
 *                                                   {+0.3, 0},
 *                                                   {-0.3, 0}};
 *
 *   const double R = 0.1;
 *   const double alpha =
 *     1. / (std::pow(R, dim) std::pow(numbers::PI, dim / 2.));
 *
 *   double sum = 0;
 *   for (const auto &vortex_center : vortex_centers)
 *     {
 *       const Tensor<1, dim> distance = p
 *
 * - vortex_center;
 *       const double         r        = distance.norm();
 *
 *       sum += alpha std::exp(-(r r) / (R R));
 *     }
 *
 *   return {std::sqrt(sum), 0.};
 * }
 *
 *
 *
 * template <int dim>
 * class Potential : public Function<dim>
 * {
 * public:
 *   Potential() = default;
 *   virtual double value(const Point<dim> & p,
 *                        const unsigned int component = 0) const override;
 * };
 *
 *
 *
 * template <int dim>
 * double Potential<dim>::value(const Point<dim> & p,
 *                              const unsigned int component) const
 * {
 *   (void)component;
 *   Assert(component == 0, ExcIndexRange(component, 0, 1));
 *
 *   return (Point<dim>().distance(p) > 0.7 ? 1000 : 0);
 * }
 *
 *
 *
 * @endcode
 *
 * <a
 * name="ImplementationofthecodeNonlinearSchroedingerEquationcodeclass"></a>
 * <h3>Implementation of the <code>NonlinearSchroedingerEquation</code>
 * class</h3>.
 *
 * 我们首先指定了类的构造函数的实现。这里没有什么值得惊奇的，也许我们选择了二次（
 * $Q_2$  ）拉格朗日元素
 *
 * - 解决方案预计是平滑的，所以我们选择了比最低限度更高的多项式度数。
 *
 *
 * @code
 * template <int dim>
 * NonlinearSchroedingerEquation<dim>::NonlinearSchroedingerEquation()
 *   : fe(2)
 *   , dof_handler(triangulation)
 *   , time(0)
 *   , time_step(1. / 128)
 *   , timestep_number(0)
 *   , kappa(1)
 * {}
 *
 *
 * @endcode
 *
 * <a name="Settingupdatastructuresandassemblingmatrices"></a> <h4>Setting up
 * data structures and assembling matrices</h4>
 *
 * 下一个函数是在程序开始时，也就是在第一个时间步骤之前，设置网格、DoFHandler以及矩阵和向量。如果你已经阅读了至少到
 * step-6 为止的教程程序，那么前几行是相当标准的。
 *
 *
 * @code
 * template <int dim>
 * void NonlinearSchroedingerEquation<dim>::setup_system()
 * {
 *   GridGenerator::hyper_cube(triangulation,
 *
 * -1, 1);
 *   triangulation.refine_global(6);
 *
 *   std::cout << "Number of active cells: " << triangulation.n_active_cells()
 *             << std::endl;
 *
 *   dof_handler.distribute_dofs(fe);
 *
 *   std::cout << "Number of degrees of freedom: " << dof_handler.n_dofs()
 *             << std::endl
 *             << std::endl;
 *
 *   DynamicSparsityPattern dsp(dof_handler.n_dofs(), dof_handler.n_dofs());
 *   DoFTools::make_sparsity_pattern(dof_handler, dsp);
 *   sparsity_pattern.copy_from(dsp);
 *
 *   system_matrix.reinit(sparsity_pattern);
 *   rhs_matrix.reinit(sparsity_pattern);
 *
 *   solution.reinit(dof_handler.n_dofs());
 *   system_rhs.reinit(dof_handler.n_dofs());
 *
 *   constraints.close();
 * }
 *
 *
 *
 * @endcode
 *
 * 接下来，我们组装相关的矩阵。按照我们对斯特朗分裂的空间步骤（即每个时间步骤中三个部分步骤中的第二个步骤）的Crank-Nicolson离散化的写法，我们被引导到线性系统
 * $\left[
 *
 * -iM  +  \frac 14 k_{n+1} A + \frac 12 k_{n+1} W \right] \Psi^{(n,2)} =
 * \left[
 *
 * -iM
 *
 *
 *
 * -  \frac 14 k_{n+1} A
 *
 * - \frac 12 k_{n+1} W \right] \Psi^{(n,1)}$
 * 。换句话说，这里有两个矩阵在起作用
 *
 * --一个是左手边的，一个是右手边的。我们分别建立这些矩阵。(我们可以避免建立右手边的矩阵，而只是在每个时间步骤中对
 * $\Psi^{(n,1)}$
 * 形成矩阵的作用*。这可能更有效，也可能不更有效，但是对于这个程序来说，效率并不是最重要的）。)
 *
 *
 * @code
 * template <int dim>
 * void NonlinearSchroedingerEquation<dim>::assemble_matrices()
 * {
 *   const QGauss<dim> quadrature_formula(fe.degree + 1);
 *
 *   FEValues<dim> fe_values(fe,
 *                           quadrature_formula,
 *                           update_values | update_gradients |
 *                             update_quadrature_points | update_JxW_values);
 *
 *   const unsigned int dofs_per_cell = fe.n_dofs_per_cell();
 *   const unsigned int n_q_points    = quadrature_formula.size();
 *
 *   FullMatrix<std::complex<double>> cell_matrix_lhs(dofs_per_cell,
 *                                                    dofs_per_cell);
 *   FullMatrix<std::complex<double>> cell_matrix_rhs(dofs_per_cell,
 *                                                    dofs_per_cell);
 *
 *   std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);
 *   std::vector<double>                  potential_values(n_q_points);
 *   const Potential<dim>                 potential;
 *
 *   for (const auto &cell : dof_handler.active_cell_iterators())
 *     {
 *       cell_matrix_lhs = std::complex<double>(0.);
 *       cell_matrix_rhs = std::complex<double>(0.);
 *
 *       fe_values.reinit(cell);
 *
 *       potential.value_list(fe_values.get_quadrature_points(),
 *                            potential_values);
 *
 *       for (unsigned int q_index = 0; q_index < n_q_points; ++q_index)
 *         {
 *           for (unsigned int k = 0; k < dofs_per_cell; ++k)
 *             {
 *               for (unsigned int l = 0; l < dofs_per_cell; ++l)
 *                 {
 *                   const std::complex<double> i = {0, 1};
 *
 *                   cell_matrix_lhs(k, l) +=
 *                     (-i fe_values.shape_value(k, q_index)
 *                        fe_values.shape_value(l, q_index) +
 *                      time_step / 4 fe_values.shape_grad(k, q_index)
 *                        fe_values.shape_grad(l, q_index) +
 *                      time_step / 2 potential_values[q_index]
 *                        fe_values.shape_value(k, q_index)
 *                        fe_values.shape_value(l, q_index))
 *                     fe_values.JxW(q_index);
 *
 *                   cell_matrix_rhs(k, l) +=
 *                     (-i fe_values.shape_value(k, q_index)
 *                        fe_values.shape_value(l, q_index)
 *
 * -
 *                      time_step / 4 fe_values.shape_grad(k, q_index)
 *                        fe_values.shape_grad(l, q_index)
 *
 * -
 *                      time_step / 2 potential_values[q_index]
 *                        fe_values.shape_value(k, q_index)
 *                        fe_values.shape_value(l, q_index))
 *                     fe_values.JxW(q_index);
 *                 }
 *             }
 *         }
 *
 *       cell->get_dof_indices(local_dof_indices);
 *       constraints.distribute_local_to_global(cell_matrix_lhs,
 *                                              local_dof_indices,
 *                                              system_matrix);
 *       constraints.distribute_local_to_global(cell_matrix_rhs,
 *                                              local_dof_indices,
 *                                              rhs_matrix);
 *     }
 * }
 *
 *
 * @endcode
 *
 * <a name="ImplementingtheStrangsplittingsteps"></a> <h4>Implementing the
 * Strang splitting steps</h4>
 *
 * 在建立了上述所有数据结构后，我们现在可以实现构成斯特朗分裂方案的部分步骤。我们从推进阶段的半步开始，这被用作每个时间步骤的第一和最后一部分。
 * 为此，回顾一下，对于第一个半步，我们需要计算
 * $\psi^{(n,1)} = e^{-i\kappa|\psi^{(n,0)}|^2 \tfrac 12\Delta t} \;
 * \psi^{(n,0)}$  。这里， $\psi^{(n,0)}=\psi^{(n)}$ 和 $\psi^{(n,1)}$
 * 是空间的函数，分别对应于前一个完整时间步骤的输出和三个部分步骤中第一个步骤的结果。必须为第三个部分步骤计算相应的解决方案，即
 * $\psi^{(n,3)} = e^{-i\kappa|\psi^{(n,2)}|^2 \tfrac 12\Delta t} \;
 * \psi^{(n,2)}$  ，其中 $\psi^{(n,3)}=\psi^{(n+1)}$
 * 是整个时间步骤的结果，其输入 $\psi^{(n,2)}$
 * 是斯特朗分割的空间步骤的结果。
 * 一个重要的认识是，虽然 $\psi^{(n,0)}(\mathbf x)$
 * 可能是一个有限元函数（即，是片状多项式），但对于我们使用指数因子更新相位的
 * "旋转
 * "函数来说，情况不一定如此（回顾一下，该函数的振幅在该步骤中保持不变）。换句话说，我们可以在每一个点
 * $\mathbf x\in\Omega$ 计算* $\psi^{(n,1)}(\mathbf x)$
 * ，但我们不能在网格上表示它，因为它不是一个片状多项式函数。在一个离散的环境中，我们能做的最好的事情就是计算一个投影或内插。换句话说，我们可以计算
 * $\psi_h^{(n,1)}(\mathbf x) = \Pi_h \left(e^{-i\kappa|\psi_h^{(n,0)}(\mathbf
 * x)|^2 \tfrac 12\Delta t} \; \psi_h^{(n,0)}(\mathbf x) \right)$ ，其中
 * $\Pi_h$
 * 是一个投影或内插算子。如果我们选择插值，情况就特别简单。那么，我们需要计算的就是在节点点上的右手边的值*，并将这些作为自由度向量
 * $\Psi^{(n,1)}$
 * 的节点值。这很容易做到，因为在这里使用的拉格朗日有限元的节点点上评估右手边，需要我们只看节点向量的一个（复值）条目。换句话说，我们需要做的是计算
 * $\Psi^{(n,1)}_j = e^{-i\kappa|\Psi^{(n,0)}_j|^2 \tfrac 12\Delta t} \;
 * \Psi^{(n,0)}_j$ ，其中 $j$
 * 在我们解向量的所有条目上循环。这就是下面这个函数的作用
 *
 * - 事实上，它甚至没有为 $\Psi^{(n,0)}$ 和 $\Psi^{(n,1)}$ 使用单独的向量，而只是适当地更新同一个向量。
 *
 *
 * @code
 * template <int dim>
 * void NonlinearSchroedingerEquation<dim>::do_half_phase_step()
 * {
 *   for (auto &value : solution)
 *     {
 *       const std::complex<double> i         = {0, 1};
 *       const double               magnitude = std::abs(value);
 *
 *       value = std::exp(-i kappa magnitude magnitude (time_step / 2))
 *               value;
 *     }
 * }
 *
 *
 *
 * @endcode
 *
 * 下一步是求解每个时间步骤中的线性系统，即我们使用的Strang分割的后半步。记得它的形式是
 * $C\Psi^{(n,2)} = R\Psi^{(n,1)}$ ，其中 $C$ 和 $R$
 * 是我们之前组装的矩阵。
 * 我们在这里解决这个问题的方法是使用直接求解器。我们首先使用
 * SparseMatrix::vmult() 函数求出右边的 $r=R\Psi^{(n,1)}$
 * ，并将结果放入`system_rhs`变量。然后我们调用
 * SparseDirectUMFPACK::solver() ，该函数以矩阵 $C$
 * 和右手边的向量为参数，并将解决方案返回到同一向量`system_rhs`中。最后一步是将计算出的解放回`solution`变量中。
 *
 *
 * @code
 * template <int dim>
 * void NonlinearSchroedingerEquation<dim>::do_full_spatial_step()
 * {
 *   rhs_matrix.vmult(system_rhs, solution);
 *
 *   SparseDirectUMFPACK direct_solver;
 *   direct_solver.solve(system_matrix, system_rhs);
 *
 *   solution = system_rhs;
 * }
 *
 *
 *
 * @endcode
 *
 * <a name="Creatinggraphicaloutput"></a> <h4>Creating graphical output</h4> *
 * <h4>Creating graphical output</h4>.
 *
 *
 * 我们应该讨论的最后一个辅助函数和类是那些创建图形输出的函数。对斯特朗分裂的局部和空间部分运行半步和全步的结果是，我们在每个时间步长结束时将`solution`向量
 * $\Psi^n$
 * 更新为正确的值。它的条目包含有限元网格节点上的解的复数。
 * 复数不容易被可视化。我们可以输出它们的实部和虚部，即字段
 * $\text{Re}(\psi_h^{(n)}(\mathbf x))$ 和 $\text{Im}(\psi_h^{(n)}(\mathbf
 * x))$ ，这正是DataOut类在通过 DataOut::add_data_vector()
 * 附加复数向量，然后调用 DataOut::build_patches(). 时所做的。
 *
 *
 * 但很多时候，我们对解向量的实部和虚部并不特别感兴趣，而是对解的幅度
 * $|\psi|$ 和相位角 $\text{arg}(\psi)$
 * 等衍生量感兴趣。在这里这样的量子系统的背景下，幅度本身并不那么有趣，相反，"振幅"，
 * $|\psi|^2$
 * 才是一个物理属性：它对应于在一个特定的状态场所找到一个粒子的概率密度。将计算出的量放入输出文件的方式，以便于可视化
 *
 * - 如同在以前众多的教程程序中使用的那样
 *
 * 是使用DataPostprocessor和派生类的设施。具体来说，一个复数的振幅和它的相位角都是标量，因此DataPostprocessorScalar类是我们要做的正确工具。
 * 因此，我们在这里做的是实现两个类`ComplexAmplitude`和`ComplexPhase`，为DataOut决定生成输出的每一点计算解决方案的振幅
 * $|\psi_h|^2$ 和相位 $\text{arg}(\psi_h)$
 * ，以实现可视化。下面有相当多的模板代码，这两个类中的第一个唯一有趣的部分是它的`evaluate_vector_field()`函数如何计算`computed_quantities`对象。
 * （还有一个相当尴尬的事实是，<a
 * href="https://en.cppreference.com/w/cpp/numeric/complex/norm">std::norm()</a>函数并没有计算人们天真的想象，即
 * $|\psi|$ ，而是返回 $|\psi|^2$
 * 。一个标准函数以这样的方式被错误地命名，这当然是相当令人困惑的......)
 *
 *
 * @code
 * namespace DataPostprocessors
 * {
 *   template <int dim>
 *   class ComplexAmplitude : public DataPostprocessorScalar<dim>
 *   {
 *   public:
 *     ComplexAmplitude();
 *
 *     virtual void evaluate_vector_field(
 *       const DataPostprocessorInputs::Vector<dim> &inputs,
 *       std::vector<Vector<double>> &computed_quantities) const override;
 *   };
 *
 *
 *   template <int dim>
 *   ComplexAmplitude<dim>::ComplexAmplitude()
 *     : DataPostprocessorScalar<dim>("Amplitude", update_values)
 *   {}
 *
 *
 *   template <int dim>
 *   void ComplexAmplitude<dim>::evaluate_vector_field(
 *     const DataPostprocessorInputs::Vector<dim> &inputs,
 *     std::vector<Vector<double>> &               computed_quantities) const
 *   {
 *     Assert(computed_quantities.size() == inputs.solution_values.size(),
 *            ExcDimensionMismatch(computed_quantities.size(),
 *                                 inputs.solution_values.size()));
 *
 *     for (unsigned int q = 0; q < computed_quantities.size(); ++q)
 *       {
 *         Assert(computed_quantities[q].size() == 1,
 *                ExcDimensionMismatch(computed_quantities[q].size(), 1));
 *         Assert(inputs.solution_values[q].size() == 2,
 *                ExcDimensionMismatch(inputs.solution_values[q].size(), 2));
 *
 *         const std::complex<double> psi(inputs.solution_values[q](0),
 *                                        inputs.solution_values[q](1));
 *         computed_quantities[q](0) = std::norm(psi);
 *       }
 *   }
 *
 *
 *
 * @endcode
 *
 * 其中第二个后处理程序类计算每一点的复值解决方案的相位角。换句话说，如果我们表示
 * $\psi(\mathbf x,t)=r(\mathbf x,t) e^{i\varphi(\mathbf x,t)}$
 * ，那么这个类就会计算 $\varphi(\mathbf x,t)$ 。函数<a
 * href="https://en.cppreference.com/w/cpp/numeric/complex/arg">std::arg</a>为我们做这个，并将角度作为
 * $-\pi$ 和 $+\pi$ 之间的一个实数返回。
 * 由于我们将在结果部分详细解释的原因，我们实际上没有在产生输出的每个位置输出这个值。相反，我们取该阶段所有评估点的最大值，然后用这个最大值填充每个评估点的输出域。
 *
 * 本质上，我们将相位角作为一个片状常数域来输出，其中每个单元都有自己的常数值。一旦你读完下面的讨论就会明白其中的原因。
 *
 *
 * @code
 *   template <int dim>
 *   class ComplexPhase : public DataPostprocessorScalar<dim>
 *   {
 *   public:
 *     ComplexPhase();
 *
 *     virtual void evaluate_vector_field(
 *       const DataPostprocessorInputs::Vector<dim> &inputs,
 *       std::vector<Vector<double>> &computed_quantities) const override;
 *   };
 *
 *
 *   template <int dim>
 *   ComplexPhase<dim>::ComplexPhase()
 *     : DataPostprocessorScalar<dim>("Phase", update_values)
 *   {}
 *
 *
 *   template <int dim>
 *   void ComplexPhase<dim>::evaluate_vector_field(
 *     const DataPostprocessorInputs::Vector<dim> &inputs,
 *     std::vector<Vector<double>> &               computed_quantities) const
 *   {
 *     Assert(computed_quantities.size() == inputs.solution_values.size(),
 *            ExcDimensionMismatch(computed_quantities.size(),
 *                                 inputs.solution_values.size()));
 *
 *     double max_phase =
 *
 * -numbers::PI;
 *     for (unsigned int q = 0; q < computed_quantities.size(); ++q)
 *       {
 *         Assert(computed_quantities[q].size() == 1,
 *                ExcDimensionMismatch(computed_quantities[q].size(), 1));
 *         Assert(inputs.solution_values[q].size() == 2,
 *                ExcDimensionMismatch(inputs.solution_values[q].size(), 2));
 *
 *         max_phase =
 *           std::max(max_phase,
 *                    std::arg(
 *                      std::complex<double>(inputs.solution_values[q](0),
 *                                           inputs.solution_values[q](1))));
 *       }
 *
 *     for (auto &output : computed_quantities)
 *       output(0) = max_phase;
 *   }
 *
 * } // namespace DataPostprocessors
 *
 *
 * @endcode
 *
 * 在这样实现了这些后处理程序后，我们像往常一样创建输出。如同许多其他时间相关的教程程序一样，我们在DataOut上附加标志，表示时间步数和当前模拟时间。
 *
 *
 * @code
 * template <int dim>
 * void NonlinearSchroedingerEquation<dim>::output_results() const
 * {
 *   const DataPostprocessors::ComplexAmplitude<dim> complex_magnitude;
 *   const DataPostprocessors::ComplexPhase<dim>     complex_phase;
 *
 *   DataOut<dim> data_out;
 *
 *   data_out.attach_dof_handler(dof_handler);
 *   data_out.add_data_vector(solution, "Psi");
 *   data_out.add_data_vector(solution, complex_magnitude);
 *   data_out.add_data_vector(solution, complex_phase);
 *   data_out.build_patches();
 *
 *   data_out.set_flags(DataOutBase::VtkFlags(time, timestep_number));
 *
 *   const std::string filename =
 *     "solution-" + Utilities::int_to_string(timestep_number, 3) + ".vtu";
 *   std::ofstream output(filename);
 *   data_out.write_vtu(output);
 * }
 *
 *
 *
 * @endcode
 *
 * <a name="Runningthesimulation"></a> <h4>Running the simulation</h4>
 *
 * 剩下的步骤是我们如何设置这个程序的整体逻辑。这其实是比较简单的。设置数据结构；将初始条件插值到有限元空间；然后迭代所有时间步长，在每个时间步长上执行斯特朗分割法的三个部分。每隔10个时间步长，我们就生成图形输出。这就是了。
 *
 *
 * @code
 * template <int dim>
 * void NonlinearSchroedingerEquation<dim>::run()
 * {
 *   setup_system();
 *   assemble_matrices();
 *
 *   time = 0;
 *   VectorTools::interpolate(dof_handler, InitialValues<dim>(), solution);
 *   output_results();
 *
 *   const double end_time = 1;
 *   for (; time <= end_time; time += time_step)
 *     {
 *       ++timestep_number;
 *
 *       std::cout << "Time step " << timestep_number << " at t=" << time
 *                 << std::endl;
 *
 *       do_half_phase_step();
 *       do_full_spatial_step();
 *       do_half_phase_step();
 *
 *       if (timestep_number % 1 == 0)
 *         output_results();
 *     }
 * }
 * } // namespace Step58
 *
 *
 *
 * @endcode
 *
 * <a name="Themainfunction"></a> <h4>The main() function</h4>。
 *
 * 其余的又是锅炉板，和以前几乎所有的教程程序完全一样。
 *
 * @code
 * int main()
 * {
 * try
 *   {
 *     using namespace Step58;
 *
 *     NonlinearSchroedingerEquation<2> nse;
 *     nse.run();
 *   }
 * catch (std::exception &exc)
 *   {
 *     std::cerr << std::endl
 *               << std::endl
 *               << "----------------------------------------------------"
 *               << std::endl;
 *     std::cerr << "Exception on processing: " << std::endl
 *               << exc.what() << std::endl
 *               << "Aborting!" << std::endl
 *               << "----------------------------------------------------"
 *               << std::endl;
 *     return 1;
 *   }
 * catch (...)
 *   {
 *     std::cerr << std::endl
 *               << std::endl
 *               << "----------------------------------------------------"
 *               << std::endl;
 *     std::cerr << "Unknown exception!" << std::endl
 *               << "Aborting!" << std::endl
 *               << "----------------------------------------------------"
 *               << std::endl;
 *     return 1;
 *   }
 * return 0;
 * }
 * @endcode
 * <a name="Results"></a><h1>Results</h1> 。
 *
 * 运行代码的结果是屏幕输出如下：```活动单元数：4096自由度数：16641
 * 时间步数1在t=0时间步数2在t=0.00390625时间步数3在t=0.0078125时间步数4在t=0.0117188[...]``运行程序也会产生大量的输出文件，我们将在下面看到。
 *
 *  <a name="Visualizingthesolution"></a><h3>Visualizing the solution</h3> 。
 *
 * 该程序的`output_results()`函数产生的输出文件由许多变量组成。解（分为实部和虚部），振幅和相位。如果我们将这四个场可视化，在几个时间步骤后，我们会得到如下图像（在时间
 * $t=0.242$ ，精确地说。 <div class="twocolumn" style="width: 80%">
 * <div> <img
 * src="https://www.dealii.org/images/steps/developer/step-58.re.png"
 * alt="Real part of the solution at t=0.242" width="400"> </div> <div> <img
 * src="https://www.dealii.org/images/steps/developer/step-58.im.png"
 * alt="Imaginary part of the solution at t=0.242" width="400"> </div> <div>
 * <img
 * src="https://www.dealii.org/images/steps/developer/step-58.magnitude.png"
 * alt="Amplitude of the solution at t=0.242" width="400"> </div> <div> <img
 * src="https://www.dealii.org/images/steps/developer/step-58.phase.png"
 * alt="Phase of the solution at t=0.242" width="400"> </div> </div>
 * 虽然上述解决方案的实部和虚部并不特别有趣（因为从物理角度来看，相位的全局偏移以及实部和虚部之间的平衡是没有意义的），但将解决方案的振幅
 * $|\psi(\mathbf x,t)|^2$ 和相位 $\text{arg}(\psi(\mathbf x,t))$
 * 可视化，尤其是它们的演变，则更有趣。这就导致了以下的图片。
 * 这里显示的相位图显然有一些缺陷。
 *
 * - 首先，相位是一个 "循环量"，但是色标对接近 $-\pi$ 的值和接近 $+\pi$ 的值使用了根本不同的颜色。这是个麻烦的问题
 *
 * - 我们需要的是一个 "循环色图"，对相位范围的两个极端使用相同的颜色。这样的颜色图存在，例如见<a href="https://nicoguaro.github.io/posts/cyclic_colormaps/">this
 * blog post of Nicolás Guarín-Zapata</a>或<a
 * href="https://stackoverflow.com/questions/23712207/cyclic-colormap-without-visual-distortions-for-use-in-phase-angle-plots">this
 * StackExchange
 * post</a>。问题是，作者最喜欢的两个大的可视化软件包之一VisIt并没有内置这些颜色图。无奈之下，我只好使用Paraview，因为它已经实现了上面帖子中提到的几种颜色地图。下面的图片使用了`nic_Edge`地图，其中两个极端值都显示为黑色。
 *
 * - 在相位缠绕的单元格上有一个问题。如果在单元格的某个评估点，相位值接近 $-\pi$ ，而在另一个评估点则接近 $+\pi$ ，那么我们真正希望发生的是整个单元格的颜色接近于极端值。但是，相反，可视化程序产生了一个线性插值，其中单元格内的值，即评估点之间的值，是在这两个值之间线性插值的，基本上涵盖了整个可能的相位值范围，因此，在一个单元格的过程中，从深红色到深绿色的整个彩虹色循环往复。解决这个问题的方法是将每个单元的相位值作为一个片断常数输出。因为对接近 $-\pi$ 和 $+\pi$ 的值进行平均会导致一个与实际相位角无关的平均值，`ComplexPhase'类只是使用每个单元上遇到的最大*相位角。
 * 经过这些修改，现在的相位图看起来如下。 <p
 * align="center"> <img
 * src="https://www.dealii.org/images/steps/developer/step-58.phase-cyclic.png"
 * alt="Phase of the solution at t=0.242, with a cyclic color map"
 * width="400"> </p>
 * 最后，我们可以用它来生成一部电影。(准确地说，这段视频又有两个全局细化周期，时间步长是上面程序中使用的一半。)
 * 这几行字的作者用VisIt制作了这部电影，因为这是他比较熟悉的，并使用了一个黑客的颜色地图，它也是循环的。
 *
 * - 尽管这个颜色图缺乏上面链接中提到的写帖子的人所采用的所有技巧。然而，如果你看一下半径为0.7的圆以外的域的阴影部分，它显示了作为波浪方程的解决方案的特点，在这个圆中，电势为零。
 *
 * 你可以看到每次有一个凸点（显示振幅 $|\psi_h(\mathbf
 * x,t)|^2$
 * ）撞到电势大的区域时：一个波从那里向外传播。看看这个视频吧。
 * @htmlonly <p align="center"> <iframe width="560" height="315"
 * src="https://www.youtube.com/embed/nraszP3GZHk" frameborder="0"
 * allow="accelerometer; autoplay; encrypted-media; gyroscope;
 * picture-in-picture" allowfullscreen></iframe> </p> @endhtmlonly
 *
 * 那么，为什么我最终会在电势 $V(\mathbf x)$ 较大的区域设置阴影？在那个外部区域，解决方案是相对较小的。它也是相对平滑的。因此，在某种近似程度上，该区域的方程简化为@f[
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - i \frac{\partial \psi}{\partial t}
 * + V \psi
 * \approx 0,
 * @f]，或者也许更容易阅读：@f[
 * \frac{\partial \psi}{\partial t} \approx
 *
 * - i V \psi.
 * @f]在这个近似有效的程度上（除其他外，消除了你在视频中看到的行波），这个方程有一个解@f[
 * \psi(\mathbf x, t) = \psi(\mathbf x, 0) e^{-i V t}. @f] 因为 $V$
 * 很大，这意味着相位的变化相当快*。如果你把注意力放在域的半透明外部，你可以看到这一点。如果你把这个区域的颜色和域的内部一样，这个快速闪烁的外部区域可能是迷幻的，但也会分散内部发生的事情；也很难真正看到辐射波，在视频的开头很容易看到。
 *
 *  <a name="extensions"></a><a
 * name="Possibilitiesforextensions"></a><h3>Possibilities for extensions</h3>
 * 。
 *
 *  <a name="Betterlinearsolvers"></a><h4> Better linear solvers </h4> 。
 * 这里选择的解算器实在是太简单了。我们在这里所做的是在每一个步骤中把矩阵交给一个稀疏的直接求解器，让它找到线性系统的解。但我们知道，我们可以做得更好。
 *
 * - 首先，我们应该利用这样一个事实，即矩阵实际上并没有从时间步长到时间步长的变化。这是一个假象，因为我们在这里有恒定的边界值，而且我们不改变时间步长。
 *
 * - 这两个假设在实际应用中可能不成立。但至少在这种情况下，只对矩阵进行一次因式分解（即计算一次 $L$ 和 $U$ 因子），然后在接下来的所有时间步长中使用这些因子，直到矩阵 $C$ 发生变化，需要进行新的因式分解。SparseDirectUMFPACK类的接口允许这样做。
 *
 * - 然而，最终，稀疏直接求解器只对相对较小的问题有效，比如说最多几十万个未知数。除此之外，我们需要迭代求解器，如共轭梯度法（用于对称和正定问题）或GMRES。我们已经在其他教程程序中使用了许多这样的方法。在所有情况下，它们都需要伴随着良好的预处理程序。对于目前的情况，原则上可以使用GMRES
 *
 * - 一种不需要矩阵的任何特定属性的方法
 *
 * 但最好是实施一个迭代方案，利用我们知道的这个问题的一个结构特征：矩阵是复数对称的（尽管不是赫米特的）。
 *
 *  <a name="Boundaryconditions"></a><h4> Boundary conditions </h4> 。
 *
 * 为了能够用于实际的、现实的问题，非线性Schr&ouml;dinger方程的求解器需要利用对手头的问题有意义的边界条件。在此，我们将自己限制在简单的诺伊曼边界条件上
 *
 * 但这些条件实际上对问题没有意义。事实上，这些方程通常是在一个无限的域上提出的。但是，由于我们不能在无限域上进行计算，我们需要在某个地方截断它，而提出对这个人为的小域有意义的边界条件。广泛使用的方法是使用<a
 * href="https://en.wikipedia.org/wiki/Perfectly_matched_layer">Perfectly
 * Matched
 * Layer</a>方法，该方法对应于衰减的一种特殊形式。在不同的情况下，它也被用于
 * step-62 。
 *
 *  <a name="Adaptivemeshes"></a><h4> Adaptive meshes </h4> 。
 *
 * 最后，我们从经验和其他许多教程程序中知道，使用自适应细化的网格是值得的，而不是这里使用的单网格。事实上，在这里添加这些并不困难。它只是需要周期性的重塑和将解决方案从一个网格转移到下一个网格。
 * step-26 将是一个很好的指南，说明如何实现这一点。
 *
* <a name="PlainProg"></a><h1> The plain program</h1>  @include "step-58.cc" .
 *
 */


