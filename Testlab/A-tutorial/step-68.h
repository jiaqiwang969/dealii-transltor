//include/deal.II-translator/A-tutorial/step-68_0.txt
/**
 * @page step_68 The step-68 tutorial program
 * 本教程依赖于  step-19  。 @htmlonly <table class="tutorial"
 * width="50%"> <tr><th colspan="2"><b><small>Table of
 * contents</small></b><b><small>Table of contents</small></b></th></tr>
 * <tr><td width="50%" valign="top">
 * <ol>
 * <li> <a href="#Intro" class=bold>Introduction</a><a href="#Intro"
 * class=bold>Introduction</a>
 * <ul>
 * <li><a
 * href="#Simulationofthemotionofmasslesstracerparticlesinavorticalflow">Simulation
 * of the motion of massless tracer particles in a vortical flow</a><a
 * href="#Simulationofthemotionofmasslesstracerparticlesinavorticalflow">Simulation
 * of the motion of massless tracer particles in a vortical flow</a>
 * <li><a href="#ParticlesindealII">Particles in deal.II</a><a
 * href="#ParticlesindealII">Particles in deal.II</a>
 * <li><a href="#Challengesrelatedtodistributedparticlesimulations">Challenges
 * related to distributed particle simulations</a><a
 * href="#Challengesrelatedtodistributedparticlesimulations">Challenges
 * related to distributed particle simulations</a>
 * <ul>
 * <li><a href="#Parallelparticlegeneration">Parallel particle
 * generation</a><a href="#Parallelparticlegeneration">Parallel particle
 * generation</a>
 * <li><a href="#Particleexchange">Particle exchange</a><a
 * href="#Particleexchange">Particle exchange</a>
 * <li><a href="#Balancingmeshandparticleload">Balancing mesh and particle
 * load</a><a href="#Balancingmeshandparticleload">Balancing mesh and particle
 * load</a>
 * </ul>
 * <li><a href="#Thetestcase">The testcase</a><a href="#Thetestcase">The
 * testcase</a>
 * </ul>
 * <li> <a href="#CommProg" class=bold>The commented program</a><a
 * href="#CommProg" class=bold>The commented program</a>
 * <ul>
 * <li><a href="#Includefiles">Include files</a><a
 * href="#Includefiles">Include files</a>
 * <li><a href="#Runtimeparameterhandling">Run-time parameter handling</a><a
 * href="#Runtimeparameterhandling">Run-time parameter handling</a>
 * <li><a href="#Velocityprofile">Velocity profile</a><a
 * href="#Velocityprofile">Velocity profile</a>
 * <li><a href="#ThecodeParticleTrackingcodeclassdeclaration">The
 * <code>ParticleTracking</code> class declaration</a><a
 * href="#ThecodeParticleTrackingcodeclassdeclaration">The
 * <code>ParticleTracking</code> class declaration</a>
 * <li><a href="#ThecodePatricleTrackingcodeclassimplementation">The
 * <code>PatricleTracking</code> class implementation</a> ]<a
 * href="#ThecodePatricleTrackingcodeclassimplementation">The
 * <code>PatricleTracking</code> class implementation</a>
 * <ul>
 * <li><a href="#Constructor">Constructor</a><a
 * href="#Constructor">Constructor</a>
 * <li><a href="#Cellweight">Cell weight</a><a href="#Cellweight">Cell
 * weight</a>
 * <li><a href="#Particlesgeneration">Particles generation</a><a
 * href="#Particlesgeneration">Particles generation</a>
 * <li><a href="#BackgroundDOFsandinterpolation">Background DOFs and
 * interpolation</a><a href="#BackgroundDOFsandinterpolation">Background DOFs
 * and interpolation</a>
 * <li><a href="#Timeintegrationofthetrajectories">Time integration of the
 * trajectories</a><a href="#Timeintegrationofthetrajectories">Time
 * integration of the trajectories</a>
 * <li><a href="#Dataoutput">Data output</a><a href="#Dataoutput">Data
 * output</a>
 * <li><a href="#Runningthesimulation">Running the simulation</a><a
 * href="#Runningthesimulation">Running the simulation</a>
 * </ul>
 * <li><a href="#Themainfunction">The main() function</a><a
 * href="#Themainfunction">The main() function</a>
 * </ul>
 * </ol></td><td width="50%" valign="top"><ol>
 * <li value="3"> <a href="#Results" class=bold>Results</a><a href="#Results"
 * class=bold>Results</a>
 * <ul>
 * <li><a href="#Motionoftheparticles"> Motion of the particles </a><a
 * href="#Motionoftheparticles"> Motion of the particles </a>
 * <li><a href="#Dynamicloadbalancing"> Dynamic load balancing </a><a
 * href="#Dynamicloadbalancing"> Dynamic load balancing </a>
 * <li><a href="#Possibilitiesforextensions">Possibilities for
 * extensions</a><a href="#Possibilitiesforextensions">Possibilities for
 * extensions</a>
 * </ul>
 * <li> <a href="#PlainProg" class=bold>The plain program</a><a
 * href="#PlainProg" class=bold>The plain program</a>
 * </ol> </td> </tr> </table>
 * @endhtmlonly
 * <br>
 * <i> This program was contributed by Bruno Blais (Polytechnique Montréal),
 * Toni El Geitani Nehme (Polytechnique Montréal), Rene Gassmöller
 * (University of California Davis), and Peter Munch (Technical University of
 * Munich and Helmholtz-Zentrum Geesthacht). Bruno Blais was supported by
 * NSERC Discovery grant RGPIN-2020-04510, by Compute Canada and Calcul
 * Québec. </i> <a name="Introduction"></a><h1>Introduction</h1>   <a
 * name="Simulationofthemotionofmasslesstracerparticlesinavorticalflow"></a><h3>Simulation
 * of the motion of massless tracer particles in a vortical flow</h3> * <a
 * name="Simulationofthemotionofmasslesstracerparticlesinavorticalflow"></a><h3>Simulation
 * of the motion of massless tracer particles in a vortical flow</h3>。
 *
 * 粒子在大量应用的数值模型中发挥着重要作用。粒子通常被用作无质量的追踪器，以显示瞬时流动的动态。它们也可以作为更复杂的有限元模型的一部分发挥固有的作用，如颗粒在单元（PIC）方法
 * @cite GLHPW2018
 * ，或者它们甚至可以用来模拟颗粒物质的运动，如离散元素法（DEM）
 * @cite Blais2019
 * 。在DEM的情况下，所产生的模型不再与有限元方法有关，而只是导致了一个描述颗粒运动和它们碰撞动态的常微分方程系统。所有这些模型都可以用deal.II的粒子处理能力来建立。
 * 在本步骤中，我们使用粒子作为无质量的追踪器来说明涡流的动态。由于粒子是无质量追踪器，每个粒子 $i$ 的位置由以下的常微分方程（ODE）描述：@f[
 * \frac{d \textbf{x}_i}{dt} =\textbf{u}(\textbf{x}_i)
 * @f]
 * 其中 $\textbf{x}_i$ 是粒子 $i$ 的位置， $\textbf{u}(\textbf{x}_i)$ 是其位置的流速。在本步骤中，使用显式欧拉方法解决这个ODE。得到的方案是：@f[
 * \textbf{x}_{i}^{n+1} = \textbf{x}_{i}^{n} + \Delta t \; \textbf{u}(\textbf{x}_{i}^{n})
 * @f] 。
 * 其中 $\textbf{x}_{i}^{n+1}$ 和 $\textbf{x}_{i}^{n}$ 分别是粒子 $i$
 * 在时间 $t+\Delta t$ 和 $t$ 的位置， $\Delta t$
 * 是时间步骤。在本步骤中，粒子位置的速度以两种不同的方式获得。
 *
 * - 通过评估粒子位置的速度函数。
 *
 * 通过在背景三角图上评估速度函数，并使用有限元支持，在粒子的位置进行内插。
 * 第一种方法并不实用，因为速度剖面通常不是以分析方式知道的。第二种方法，基于对粒子位置的内插求解，完全模仿了现实计算流体动力学模拟中的做法，这也是我们在
 * step-19
 * 中对粒子位置的有限元求解进行评估的方式。在这一步中，我们说明了这两种策略。
 * 我们注意到，使用四阶Runge-Kutta方法或其他适当的方案对粒子的运动进行时间积分，可以获得更大的精度。
 * 实施一个更先进的时间积分方案将是这一步骤的直接延伸。
 * <a name="ParticlesindealII"></a><h3>Particles in deal.II</h3>
 *
 *  在交易二中， Particles::Particle
 * 是非常简单和灵活的实体，可以用来建立PIC、DEM或任何类型的基于粒子的模型。粒子在现实空间中有一个位置，在它们所在的元素的参考空间中有一个位置，还有一个唯一的ID。在大多数情况下，包含粒子的模拟需要大量的粒子。因此，通过一个集合所有粒子的实体来处理所有的粒子变得很有意义。
 * 默认情况下，粒子没有直径、质量或任何其他我们通常期望的物理粒子的物理属性。然而，通过ParticleHandler，粒子可以访问
 * Particles::PropertyPool.
 * 这个PropertyPool是一个数组，可以用来存储与粒子相关的任意数量的属性。因此，用户可以建立他们自己的粒子解算器，并将所需的属性赋予粒子（例如，质量、电荷、直径、温度等）。在本教程中，它被用来存储流体速度的值和粒子所属的过程ID。
 * <a
 * name="Challengesrelatedtodistributedparticlesimulations"></a><h3>Challenges
 * related to distributed particle simulations</h3> 。
 *
 * 尽管本步骤不是计算密集型的，但包括许多粒子的模拟可能是计算要求很高的，需要并行化。
 *
 * - 在分布式三角形上生成粒子。
 *
 * - 在处理器之间交换离开本地域的粒子。
 *
 * - 负载平衡模拟，使每个处理器都有类似的计算负载。这些挑战和它们在deal.II中的解决方案已经在 @cite GLHPW2018 中详细讨论过了，但我们将在下文中总结它们。
 * 当然，还有一些关于简单设置使用粒子的代码的问题。这些问题在
 * step-19  中已经基本解决了。一些更高级的技术也将在
 * step-70  中讨论。 <a name="Parallelparticlegeneration"></a><h4>Parallel
 * particle generation</h4> 。
 *
 * 以可扩展的方式生成分布式粒子并不简单，在找到它们所在的单元之前，必须首先确定它们所属的处理器。交易.II通过
 * Particles::Generator 命名空间提供了许多生成粒子的功能。
 * 其中一些粒子生成器只在本地拥有的子域上创建粒子。例如，
 * Particles::Generators::regular_reference_locations()
 * 在本地子域的每个单元内创建相同参考位置的粒子，
 * Particles::Generators::probabilistic_locations()
 * 使用全局定义的概率密度函数来确定在本地生成粒子的数量和位置。
 * 在其他情况下，如本步骤，粒子必须在单元格上的特定位置生成，而这些单元格可能只属于处理器的一个子集。在大多数情况下，粒子的插入只在有限的时间步数内完成，因此，不构成计算成本的很大一部分。对于这些情况，deal.II提供了方便的
 * Particles::Generators
 * ，可以在全局范围内插入粒子，即使粒子不在启动创建粒子的调用的并行进程所拥有的单元中。生成器首先定位粒子所处的子域，确定它们位于哪个单元中，并在处理器之间交换必要的信息，以确保生成的粒子具有正确的属性。因此，这种类型的粒子生成可能是通信密集型的。
 * Particles::Generators::dof_support_points 和
 * Particles::Generators::quadrature_points
 * 分别使用三角法和相关DoFHandler或四分法的点来生成粒子。用于生成粒子的三角法可以是用于背景网格的同一三角法，在这种情况下，这些函数与上一段所述的
 * Particles::Generators::regular_reference_locations()
 * 函数非常相似。然而，用于生成粒子的三角形也可以与背景网格的三角形不同（不匹配），这对于生成特定形状的粒子（如本例），或者在两个不同的计算网格之间传递信息（如
 * step-70 ）是很有用的。 此外， Particles::ParticleHandler
 * 类提供了 Particles::ParticleHandler::insert_global_particles()
 * 函数，可以从任意点的矢量和边界盒的全局矢量中插入粒子。在本步骤中，我们在非匹配三角形上使用
 * Particles::Generators::quadrature_points()
 * 函数来插入位于圆盘形状的位置上的粒子。 <a
 * name="Particleexchange"></a><h4>Particle exchange</h4>
 *
 * 当粒子在平行分布式计算中移动时，它们可能会离开本地拥有的子域，并需要转移到它们的新主人进程中。这种情况可能以两种非常不同的方式出现。首先，如果先前拥有的进程知道丢失的粒子的新主人（例如，因为粒子从一个处理器的本地拥有的单元移动到一个分布式三角计算的相邻的幽灵单元），那么转移可以作为每个进程和新主人之间的点对点通信来有效处理。每当粒子被分类到新单元时，这种转移就会自动发生。第二，以前的所有者可能不知道粒子被转移到哪个进程。在这种情况下，粒子会被默认丢弃，因为在全局范围内搜索粒子的主人可能会很昂贵。
 * step-19
 * 展示了这样一个被丢弃的粒子如何仍然可以被收集、解释，并可能被用户重新插入。在本例中，我们通过在时间步骤上施加一个CFL准则来防止第二种情况，以确保粒子最多只能移动到本地进程的幽灵层，因此可以自动发送到邻近的进程。
 * <a name="Balancingmeshandparticleload"></a><h4>Balancing mesh and particle
 * load</h4>
 *
 * 在本节中，我们只讨论了分布式计算中针对粒子的挑战。粒子与有限元解决方案共享的并行挑战（并行输出，网格细化过程中的数据传输）可以用其他例子中已经讨论过的有限元问题的解决方案来解决。
 * <a name="Thetestcase"></a><h3>The testcase</h3>
 *
 * 在本步骤中，我们使用粒子作为无质量追踪器来说明一个特殊的涡流的动力学：Rayleigh--Kothe涡流。这种流动模式通常被用作界面跟踪方法（如流体体积和水平集方法）的复杂测试案例，因为它导致了流体的强烈旋转和拉长
 * @cite Blais2013  。 这个Rayleigh-Kothe涡流的流函数 $\Psi$
 * 被定义为。
 * @f[
 * \Psi = \frac{1}{\pi} \sin^2 (\pi x) \sin^2 (\pi y) \cos \left( \pi \frac{t}{T} \right)
 * @f]其中 $T$ 是流动周期的一半。二维的速度曲线（ $\textbf{u}=[u,v]^T$ ）为：@f{eqnarray*}
 * u &=&
 *
 *
 *
 * - \frac{\partial\Psi}{\partial y} =
 *
 * -2 \sin^2 (\pi x) \sin (\pi y) \cos (\pi y)  \cos \left( \pi \frac{t}{T}
 * \right)\\ v &=&  \frac{\partial\Psi}{\partial x} = 2 \cos(\pi x) \sin(\pi
 * x) \sin^2 (\pi y) \cos \left( \pi \frac{t}{T} \right) @f} 。
 *
 * 该速度剖面在以下动画中得到说明。 @htmlonly <p
 * align="center"> <iframe width="560" height="500"
 * src="https://www.youtube.com/embed/m6hQm7etji8" frameborder="0"
 * allow="accelerometer; autoplay; encrypted-media; gyroscope;
 * picture-in-picture" allowfullscreen></iframe> </p> @endhtmlonly
 *
 * 可以看出，由于 $\cos \left( \pi \frac{t}{T} \right)$
 * 项的作用，这个速度会周期性地逆转，材料在每一个长度为
 * $t=2T$
 * 的周期后会结束在其起始位置。我们将精确地运行这个教程程序一个周期，并将最终的粒子位置与初始位置进行比较，以说明这一流动特性。这个例子使用测试案例产生了两个模型，它们对粒子的处理略有不同。第一个模型将精确的分析速度解作为每个粒子的速度。因此，在这个模型中，分配给粒子的速度是没有错误的，在给定的时间内，粒子位置与分析位置的任何偏差都是由于使用时间步进法精确求解粒子的运动方程的错误造成的。在第二个模型中，理论速度场首先被内插到一个有限元矢量空间中（以模拟速度是通过求解一个有限元问题得到的情况，与
 * step-19
 * 中每个粒子的ODE取决于一个有限元解的方式相同）。然后在粒子的位置上对这个有限元
 * "解决方案
 * "进行评估，以解决其运动方程。这两种情况之间的差异允许评估所选择的有限元空间是否足够准确，以所选择的粒子平流方案的最佳收敛率来平流粒子，这个问题在实践中对确定组合算法的准确性很重要（例如，见
 * @cite Gassmoller2019 ）。
 *
 *  <a name="CommProg"></a> <h1> The commented program</h1>。 <a
 * name="Includefiles"></a> <h3>Include files</h3>。
 *
 *
 * @code
 * #include <deal.II/base/bounding_box.h>
 * #include <deal.II/base/conditional_ostream.h>
 * #include <deal.II/base/discrete_time.h>
 * #include <deal.II/base/mpi.h>
 * #include <deal.II/base/parameter_acceptor.h>
 * #include <deal.II/base/timer.h>
 *
 * #include <deal.II/distributed/cell_weights.h>
 * #include <deal.II/distributed/solution_transfer.h>
 * #include <deal.II/distributed/tria.h>
 *
 * #include <deal.II/dofs/dof_handler.h>
 * #include <deal.II/dofs/dof_tools.h>
 *
 * #include <deal.II/fe/fe_q.h>
 * #include <deal.II/fe/fe_system.h>
 * #include <deal.II/fe/mapping_q.h>
 *
 * #include <deal.II/grid/grid_generator.h>
 * #include <deal.II/grid/grid_tools.h>
 *
 * #include <deal.II/lac/la_parallel_vector.h>
 * #include <deal.II/lac/vector.h>
 *
 * #include <deal.II/numerics/data_out.h>
 * #include <deal.II/numerics/vector_tools.h>
 *
 * @endcode
 *
 * 从下面的include文件中，我们导入了ParticleHandler类，该类允许你管理浮在
 * Particles::Particle), 上的粒子集合（类型为 Particles::Particle),
 * 的对象，代表具有一些附加属性（如id）的点集合）。
 * 命名空间Particles中的方法和类允许人们轻松实现Particle-In-Cell方法和分布三角上的粒子追踪。
 *
 *
 * @code
 * #include <deal.II/particles/particle_handler.h>
 *
 * @endcode
 *
 * 我们导入粒子发生器，使我们能够插入粒子。在本步骤中，粒子是使用非匹配的超壳三角法进行全局插入的。
 *
 *
 * @code
 * #include <deal.II/particles/generators.h>
 *
 * @endcode
 * 由于粒子没有形成三角形，它们有自己特定的DataOut类，这将使我们能够把它们写成常用的并行vtu格式（或任何数量的其他文件格式）。
 *
 *
 * @code
 * #include <deal.II/particles/data_out.h>
 *
 * #include <cmath>
 * #include <iostream>
 *
 *
 *
 * namespace Step68
 * {
 * using namespace dealii;
 *
 * @endcode
 *
 * <a name="Runtimeparameterhandling"></a> <h3>Run-time parameter
 * handling</h3>
 *
 * 与 step-60
 * 中的做法类似，我们设置了一个持有我们问题的所有参数的类，并从ParameterAcceptor类派生出来，以简化参数文件的管理和创建。
 * ParameterAcceptor范式要求所有的参数都可以被ParameterAcceptor方法写入。为了避免出现很难追踪的bug（比如写成`if
 * (time = 0)`而不是`if(time ==
 * 0)`），我们在一个外部类中声明所有的参数，该类在实际的`ParticleTracking`类之前被初始化，并将其作为`const`引用传递给主类。
 * 该类的构造函数负责该类的成员与ParameterHandler中的相应条目之间的连接。由于使用了
 * ParameterHandler::add_parameter()
 * 方法，这种连接是微不足道的，但要求这个类的所有成员都是可写的。
 *
 *
 * @code
 * class ParticleTrackingParameters : public ParameterAcceptor
 * {
 * public:
 *   ParticleTrackingParameters();
 *
 * @endcode
 *
 * 这个类主要由成员变量组成，描述了粒子跟踪模拟及其离散化的细节。下面的参数是关于输出应该写到哪里，速度的空间离散化（默认是
 * $Q_1$
 * ），时间步长和输出频率（在我们再次产生图形输出之前应该经过多少时间步长）。
 *
 *
 * @code
 *   std::string output_directory = "./";
 *
 *   unsigned int velocity_degree       = 1;
 *   double       time_step             = 0.002;
 *   double       final_time            = 4.0;
 *   unsigned int output_frequency      = 10;
 *   unsigned int repartition_frequency = 5;
 *
 * @endcode
 * 我们允许每一个网格都可以独立地进行细化。在本教程中，流体网格上没有物理学的解析，其速度是分析计算的。
 *
 *
 * @code
 *   unsigned int fluid_refinement              = 4;
 *   unsigned int particle_insertion_refinement = 3;
 * };
 *
 *
 *
 * @endcode
 * 还有一个任务就是声明我们在输入文件中可以接受哪些运行时参数。由于我们的参数数量非常有限，所有的参数都在同一章节中声明。
 *
 *
 * @code
 * ParticleTrackingParameters::ParticleTrackingParameters()
 *   : ParameterAcceptor("Particle Tracking Problem/")
 * {
 *   add_parameter(
 *     "Velocity degree", velocity_degree, "", prm, Patterns::Integer(1));
 *
 *   add_parameter("Output frequency",
 *                 output_frequency,
 *                 "Iteration frequency at which output results are written",
 *                 prm,
 *                 Patterns::Integer(1));
 *
 *   add_parameter("Repartition frequency",
 *                 repartition_frequency,
 *                 "Iteration frequency at which the mesh is load balanced",
 *                 prm,
 *                 Patterns::Integer(1));
 *
 *   add_parameter("Output directory", output_directory);
 *
 *   add_parameter("Time step", time_step, "", prm, Patterns::Double());
 *
 *   add_parameter("Final time",
 *                 final_time,
 *                 "End time of the simulation",
 *                 prm,
 *                 Patterns::Double());
 *
 *   add_parameter("Fluid refinement",
 *                 fluid_refinement,
 *                 "Refinement level of the fluid domain",
 *                 prm,
 *                 Patterns::Integer(0));
 *
 *   add_parameter(
 *     "Particle insertion refinement",
 *     particle_insertion_refinement,
 *     "Refinement of the volumetric mesh used to insert the particles",
 *     prm,
 *     Patterns::Integer(0));
 * }
 *
 *
 *
 * @endcode
 *
 * <a name="Velocityprofile"></a> <h3>Velocity profile</h3>.
 *
 * 速度曲线是作为一个函数对象提供的。这个函数在例子中是硬编码的。
 *
 *
 * @code
 * template <int dim>
 * class Vortex : public Function<dim>
 * {
 * public:
 *   Vortex()
 *     : Function<dim>(dim)
 *   {}
 *
 *
 *   virtual void vector_value(const Point<dim> &point,
 *                             Vector<double> &  values) const override;
 * };
 *
 *
 * @endcode
 *
 * Rayleigh-Kothe顶点的速度曲线是随时间变化的。因此，必须从函数对象中收集模拟中的当前时间（t）。
 *
 *
 * @code
 * template <int dim>
 * void Vortex<dim>::vector_value(const Point<dim> &point,
 *                                Vector<double> &  values) const
 * {
 *   const double T = 4;
 *   const double t = this->get_time();
 *
 *   const double px = numbers::PI point(0);
 *   const double py = numbers::PI point(1);
 *   const double pt = numbers::PI / T t;
 *
 *   values[0] =
 *
 * -2 cos(pt) pow(sin(px), 2) sin(py) cos(py);
 *   values[1] = 2 cos(pt) pow(sin(py), 2) sin(px) cos(px);
 *   if (dim == 3)
 *     {
 *       values[2] = 0;
 *     }
 * }
 *
 *
 *
 * @endcode
 *
 * <a name="ThecodeParticleTrackingcodeclassdeclaration"></a> <h3>The
 * <code>ParticleTracking</code> class declaration</h3>.
 *
 * 我们现在准备介绍我们教程程序的主类。
 *
 *
 * @code
 * template <int dim>
 * class ParticleTracking
 * {
 * public:
 *   ParticleTracking(const ParticleTrackingParameters &par,
 *                    const bool                        interpolated_velocity);
 *   void run();
 *
 * private:
 * @endcode
 *
 * 这个函数负责在背景网格之上初始生成粒子。
 *
 *
 * @code
 *   void generate_particles();
 *
 * @endcode
 *
 * 当速度剖面被内插到粒子的位置时，必须首先使用自由度进行存储。因此，与其他并行情况一样（例如
 * step-40 ），我们在背景网格上初始化自由度。
 *
 *
 * @code
 *   void setup_background_dofs();
 *
 * @endcode
 *
 * 在其中一个测试案例中，该函数被映射到背景网格上，并使用有限元插值来计算粒子位置的速度。这个函数计算三角形的支持点处的函数值。
 *
 *
 * @code
 *   void interpolate_function_to_field();
 *
 * @endcode
 *
 * 接下来的两个函数分别负责对速度场在粒子位置插值或分析计算的情况下进行显式欧拉时间积分的步骤。
 *
 *
 * @code
 *   void euler_step_interpolated(const double dt);
 *   void euler_step_analytical(const double dt);
 *
 * @endcode
 *
 * `cell_weight()`函数向三角计算表明在这个单元上预计会发生多少计算工作，因此需要对域进行划分，以便每个MPI等级收到大致相等的工作量（可能不是相等数量的单元）。虽然该函数是从外部调用的，但它与该类内部的相应信号相连，因此它可以是
 * "私有 "的。
 *
 *
 * @code
 *   unsigned int cell_weight(
 *     const typename parallel::distributed::Triangulation<dim>::cell_iterator
 *       &cell,
 *     const typename parallel::distributed::Triangulation<dim>::CellStatus
 *       status) const;
 *
 * @endcode
 *
 * 以下两个函数分别负责输出粒子的模拟结果和背景网格上的速度曲线。
 *
 *
 * @code
 *   void output_particles(const unsigned int it);
 *   void output_background(const unsigned int it);
 *
 * @endcode
 *
 * 这个类的私有成员与其他并行deal.II例子相似。参数被存储为`const`成员。值得注意的是，我们保留了`Vortex`类的成员，因为它的时间必须随着模拟的进行而被修改。
 *
 *
 *
 *
 * @code
 *   const ParticleTrackingParameters &par;
 *
 *   MPI_Comm                                  mpi_communicator;
 *   parallel::distributed::Triangulation<dim> background_triangulation;
 *   Particles::ParticleHandler<dim>           particle_handler;
 *
 *   DoFHandler<dim>                            fluid_dh;
 *   FESystem<dim>                              fluid_fe;
 *   MappingQ1<dim>                             mapping;
 *   LinearAlgebra::distributed::Vector<double> velocity_field;
 *
 *   Vortex<dim> velocity;
 *
 *   ConditionalOStream pcout;
 *
 *   bool interpolated_velocity;
 * };
 *
 *
 *
 * @endcode
 *
 * <a name="ThecodePatricleTrackingcodeclassimplementation"></a> <h3>The
 * <code>PatricleTracking</code> class implementation</h3>。    <a
 * name="Constructor"></a> <h4>Constructor</h4>.
 *
 * 构造函数和析构函数是相当微不足道的。它们与  step-40
 * 中的做法非常相似。我们将我们想要工作的处理器设置为所有可用的机器（`MPI_COMM_WORLD`），并初始化
 * <code>pcout</code>
 * 变量，只允许处理器0输出任何东西到标准输出。
 *
 *
 *
 *
 * @code
 * template <int dim>
 * ParticleTracking<dim>::ParticleTracking(const ParticleTrackingParameters &par,
 *                                         const bool interpolated_velocity)
 *   : par(par)
 *   , mpi_communicator(MPI_COMM_WORLD)
 *   , background_triangulation(mpi_communicator)
 *   , fluid_dh(background_triangulation)
 *   , fluid_fe(FE_Q<dim>(par.velocity_degree), dim)
 *   , pcout(std::cout, Utilities::MPI::this_mpi_process(mpi_communicator) == 0)
 *   , interpolated_velocity(interpolated_velocity)
 *
 * {}
 *
 *
 *
 * @endcode
 *  <a name="Cellweight"></a> <h4>Cell weight</h4>。
 *
 * 这个函数是让我们动态地平衡本例计算负荷的关键部分。该函数为每个单元赋予一个权重，代表该单元的计算工作。在这里，大部分的工作预计会发生在粒子上，因此这个函数的返回值（代表
 * "这个单元的工作"）是根据当前单元中的粒子数量来计算。该函数与三角形内部的cell_weight()信号相连，每一个单元将被调用一次，每当三角形在等级之间重新划分领域时（该连接是在该类的generate_particles()函数中创建的）。
 *
 *
 * @code
 * template <int dim>
 * unsigned int ParticleTracking<dim>::cell_weight(
 *   const typename parallel::distributed::Triangulation<dim>::cell_iterator
 *     &                                                                  cell,
 *   const typename parallel::distributed::Triangulation<dim>::CellStatus status)
 *   const
 * {
 * @endcode
 *
 * 我们不给我们不拥有的单元分配任何权重（即人工或幽灵单元）。
 *
 *
 * @code
 *   if (!cell->is_locally_owned())
 *     return 0;
 *
 * @endcode
 *
 * 这决定了粒子工作与细胞工作相比有多重要（默认情况下每个细胞的权重为1000）。我们把每个粒子的权重设置得更高，以表明在这个例子中，粒子的负载是唯一对分配单元很重要的。这个数字的最佳值取决于应用，可以从0（廉价的粒子操作，昂贵的单元操作）到远远大于1000（昂贵的粒子操作，廉价的单元操作，就像本例中假定的那样）。
 *
 *
 * @code
 *   const unsigned int particle_weight = 10000;
 *
 * @endcode
 *
 * 这个例子没有使用自适应细化，因此每个单元都应该有`CELL_PERSIST`的状态。然而这个函数也可以用来在细化过程中分配负载，因此我们也考虑细化或粗化的单元。
 *
 *
 * @code
 *   if (status == parallel::distributed::Triangulation<dim>::CELL_PERSIST ||
 *       status == parallel::distributed::Triangulation<dim>::CELL_REFINE)
 *     {
 *       const unsigned int n_particles_in_cell =
 *         particle_handler.n_particles_in_cell(cell);
 *       return n_particles_in_cell particle_weight;
 *     }
 *   else if (status == parallel::distributed::Triangulation<dim>::CELL_COARSEN)
 *     {
 *       unsigned int n_particles_in_cell = 0;
 *
 *       for (unsigned int child_index = 0; child_index < cell->n_children();
 *            ++child_index)
 *         n_particles_in_cell +=
 *           particle_handler.n_particles_in_cell(cell->child(child_index));
 *
 *       return n_particles_in_cell particle_weight;
 *     }
 *
 *   Assert(false, ExcInternalError());
 *   return 0;
 * }
 *
 *
 *
 * @endcode
 *
 * <a name="Particlesgeneration"></a> <h4>Particles generation</h4>.
 *
 * 这个函数生成示踪粒子和这些粒子演化的背景三角图。
 *
 *
 * @code
 * template <int dim>
 * void ParticleTracking<dim>::generate_particles()
 * {
 * @endcode
 *
 * 我们创建了一个超立方体三角图，并对其进行全局细化。这个三角形覆盖了粒子的全部运动轨迹。
 *
 *
 * @code
 *   GridGenerator::hyper_cube(background_triangulation, 0, 1);
 *   background_triangulation.refine_global(par.fluid_refinement);
 *
 * @endcode
 *
 * 为了在重新划分三角形时考虑粒子，该算法需要知道三件事。
 * 1.给每个单元分配多少权重（里面有多少粒子）；2.在运送数据之前如何包装粒子；3.在重新分区之后如何解开粒子的包装。
 * 我们将正确的函数附加到信号里面
 * parallel::distributed::Triangulation.
 * 这些信号将在每次调用repartition()函数时被调用。这些连接只需要创建一次，所以我们不妨在这个类的构造函数中设置它们，但为了这个例子，我们要把粒子相关的指令分组。
 *
 *
 * @code
 *   background_triangulation.signals.cell_weight.connect(
 *     [&](
 *       const typename parallel::distributed::Triangulation<dim>::cell_iterator
 *         &cell,
 *       const typename parallel::distributed::Triangulation<dim>::CellStatus
 *         status)
 *
 * -> unsigned int { return this->cell_weight(cell, status); });
 *
 *   background_triangulation.signals.pre_distributed_repartition.connect(
 *     [this]() { this->particle_handler.register_store_callback_function(); });
 *
 *   background_triangulation.signals.post_distributed_repartition.connect(
 *     [&]() { this->particle_handler.register_load_callback_function(false); });
 *
 * @endcode
 *
 * 这将初始化粒子所处的背景三角，以及粒子的属性数量。
 *
 *
 * @code
 *   particle_handler.initialize(background_triangulation, mapping, 1 + dim);
 *
 * @endcode
 *
 * 我们创建一个粒子三角图，它只用于生成将用于插入粒子的点。这个三角形是一个偏离模拟域中心的超壳。这将被用来生成一个充满粒子的圆盘，这将使我们能够很容易地监测由于漩涡而产生的运动。
 *
 *
 * @code
 *   Point<dim> center;
 *   center[0] = 0.5;
 *   center[1] = 0.75;
 *   if (dim == 3)
 *     center[2] = 0.5;
 *
 *   const double outer_radius = 0.15;
 *   const double inner_radius = 0.01;
 *
 *   parallel::distributed::Triangulation<dim> particle_triangulation(
 *     MPI_COMM_WORLD);
 *
 *   GridGenerator::hyper_shell(
 *     particle_triangulation, center, inner_radius, outer_radius, 6);
 *   particle_triangulation.refine_global(par.particle_insertion_refinement);
 *
 * @endcode
 * 我们为粒子发生器生成必要的边界盒。这些边界框是用来快速识别插入的粒子位于哪个进程的子域中，以及哪个单元拥有它。
 *
 *
 * @code
 *   const auto my_bounding_box = GridTools::compute_mesh_predicate_bounding_box(
 *     background_triangulation, IteratorFilters::LocallyOwnedCell());
 *   const auto global_bounding_boxes =
 *     Utilities::MPI::all_gather(MPI_COMM_WORLD, my_bounding_box);
 *
 * @endcode
 *
 * 我们生成一个空的属性向量。一旦粒子生成，我们将把属性赋予它们。
 *
 *
 * @code
 *   std::vector<std::vector<double>> properties(
 *     particle_triangulation.n_locally_owned_active_cells(),
 *     std::vector<double>(dim + 1, 0.));
 *
 * @endcode
 *
 * 我们在单点正交的位置生成粒子。因此，在每个单元的中心点将生成一个粒子。
 *
 *
 * @code
 *   Particles::Generators::quadrature_points(particle_triangulation,
 *                                            QMidpoint<dim>(),
 *                                            global_bounding_boxes,
 *                                            particle_handler,
 *                                            mapping,
 *                                            properties);
 *
 *   pcout << "Number of particles inserted: "
 *         << particle_handler.n_global_particles() << std::endl;
 * }
 *
 *
 *
 * @endcode
 *
 * <a name="BackgroundDOFsandinterpolation"></a> <h4>Background DOFs and
 * interpolation</h4>.
 *
 * 这个函数设置了用于速度插值的背景自由度，并分配了存储整个速度场解决方案的场向量。
 *
 *
 * @code
 * template <int dim>
 * void ParticleTracking<dim>::setup_background_dofs()
 * {
 *   fluid_dh.distribute_dofs(fluid_fe);
 *   const IndexSet locally_owned_dofs = fluid_dh.locally_owned_dofs();
 *   IndexSet       locally_relevant_dofs;
 *   DoFTools::extract_locally_relevant_dofs(fluid_dh, locally_relevant_dofs);
 *
 *   velocity_field.reinit(locally_owned_dofs,
 *                         locally_relevant_dofs,
 *                         mpi_communicator);
 * }
 *
 *
 *
 * @endcode
 *
 * 这个函数负责将涡流速度场插值到场向量上。这可以通过使用
 * VectorTools::interpolate() 函数相当容易地实现。
 *
 *
 * @code
 * template <int dim>
 * void ParticleTracking<dim>::interpolate_function_to_field()
 * {
 *   velocity_field.zero_out_ghost_values();
 *   VectorTools::interpolate(mapping, fluid_dh, velocity, velocity_field);
 *   velocity_field.update_ghost_values();
 * }
 *
 *
 *
 * @endcode
 *
 * <a name="Timeintegrationofthetrajectories"></a> <h4>Time integration of the
 * trajectories</h4>。
 *
 * 我们使用分析定义的速度场来整合粒子的轨迹。这证明了粒子的一个相对微不足道的用法。
 *
 *
 * @code
 * template <int dim>
 * void ParticleTracking<dim>::euler_step_analytical(const double dt)
 * {
 *   const unsigned int this_mpi_rank =
 *     Utilities::MPI::this_mpi_process(mpi_communicator);
 *   Vector<double> particle_velocity(dim);
 *
 * @endcode
 *
 * 使用粒子迭代器在域中的所有粒子上循环运行
 *
 *
 * @code
 *   for (auto &particle : particle_handler)
 *     {
 * @endcode
 *
 * 我们使用粒子的当前位置来计算其速度。
 *
 *
 * @code
 *       Point<dim> particle_location = particle.get_location();
 *       velocity.vector_value(particle_location, particle_velocity);
 *
 * @endcode
 *
 * 这将更新粒子的位置，并将旧的位置设置为等于粒子的新位置。
 *
 *
 * @code
 *       for (int d = 0; d < dim; ++d)
 *         particle_location[d] += particle_velocity[d] dt;
 *
 *       particle.set_location(particle_location);
 *
 * @endcode
 *
 * 我们在粒子属性中存储处理器ID（一个标量）和粒子速度（一个矢量）。在这个例子中，这样做纯粹是为了可视化的目的。
 *
 *
 * @code
 *       ArrayView<double> properties = particle.get_properties();
 *       for (int d = 0; d < dim; ++d)
 *         properties[d] = particle_velocity[d];
 *       properties[dim] = this_mpi_rank;
 *     }
 * }
 *
 *
 *
 * @endcode
 *
 * 与前面的函数相反，在这个函数中，我们通过将自由度处的速度场的值插值到粒子的位置来整合粒子的轨迹。
 *
 *
 * @code
 * template <int dim>
 * void ParticleTracking<dim>::euler_step_interpolated(const double dt)
 * {
 *   Vector<double> local_dof_values(fluid_fe.dofs_per_cell);
 *
 * @endcode
 *
 * 我们循环计算所有的局部粒子。虽然这可以直接通过循环所有的单元格来实现，但这将迫使我们循环许多不包含粒子的单元格。相反，我们在所有的粒子上循环，但是，我们得到粒子所在的单元格的参考，然后在该单元格内循环所有的粒子。这使我们能够从
 * "velocity_field
 * "向量中收集一次速度值，并将其用于该单元中的所有粒子。
 *
 *
 * @code
 *   auto particle = particle_handler.begin();
 *   while (particle != particle_handler.end())
 *     {
 *       const auto cell =
 *         particle->get_surrounding_cell(background_triangulation);
 *       const auto dh_cell =
 *         typename DoFHandler<dim>::cell_iterator(*cell, &fluid_dh);
 *
 *       dh_cell->get_dof_values(velocity_field, local_dof_values);
 *
 * @endcode
 *
 * 接下来，通过评估粒子位置的有限元解来计算粒子位置的速度。这基本上是第19步中粒子平流功能的一个优化版本，但我们不是为每个单元创建正交对象和FEValues对象，而是用手来进行评估，这在一定程度上更有效率，而且只对本教程重要，因为粒子工作是整个程序的主要成本。
 *
 *
 * @code
 *       const auto pic = particle_handler.particles_in_cell(cell);
 *       Assert(pic.begin() == particle, ExcInternalError());
 *       for (auto &p : pic)
 *         {
 *           const Point<dim> reference_location = p.get_reference_location();
 *           Tensor<1, dim>   particle_velocity;
 *           for (unsigned int j = 0; j < fluid_fe.dofs_per_cell; ++j)
 *             {
 *               const auto comp_j = fluid_fe.system_to_component_index(j);
 *
 *               particle_velocity[comp_j.first] +=
 *                 fluid_fe.shape_value(j, reference_location)
 *                 local_dof_values[j];
 *             }
 *
 *           Point<dim> particle_location = particle->get_location();
 *           for (int d = 0; d < dim; ++d)
 *             particle_location[d] += particle_velocity[d] dt;
 *           p.set_location(particle_location);
 *
 * @endcode
 * 同样，我们在粒子属性中存储了粒子的速度和处理器的ID，以达到可视化的目的。
 *
 *
 * @code
 *           ArrayView<double> properties = p.get_properties();
 *           for (int d = 0; d < dim; ++d)
 *             properties[d] = particle_velocity[d];
 *
 *           properties[dim] =
 *             Utilities::MPI::this_mpi_process(mpi_communicator);
 *
 *           ++particle;
 *         }
 *     }
 * }
 *
 *
 *
 * @endcode
 *
 * <a name="Dataoutput"></a> <h4>Data output</h4>
 *
 * 接下来的两个函数负责将粒子和背景网格用pvtu记录写入vtu。这可以确保在并行启动仿真时，仿真结果可以被可视化。
 *
 *
 * @code
 * template <int dim>
 * void ParticleTracking<dim>::output_particles(const unsigned int it)
 * {
 *   Particles::DataOut<dim, dim> particle_output;
 *
 *   std::vector<std::string> solution_names(dim, "velocity");
 *   solution_names.push_back("process_id");
 *
 *   std::vector<DataComponentInterpretation::DataComponentInterpretation>
 *     data_component_interpretation(
 *       dim, DataComponentInterpretation::component_is_part_of_vector);
 *   data_component_interpretation.push_back(
 *     DataComponentInterpretation::component_is_scalar);
 *
 *   particle_output.build_patches(particle_handler,
 *                                 solution_names,
 *                                 data_component_interpretation);
 *   const std::string output_folder(par.output_directory);
 *   const std::string file_name(interpolated_velocity ?
 *                                 "interpolated-particles" :
 *                                 "analytical-particles");
 *
 *   pcout << "Writing particle output file: " << file_name << "-" << it
 *         << std::endl;
 *
 *   particle_output.write_vtu_with_pvtu_record(
 *     output_folder, file_name, it, mpi_communicator, 6);
 * }
 *
 *
 *
 * template <int dim>
 * void ParticleTracking<dim>::output_background(const unsigned int it)
 * {
 *   std::vector<std::string> solution_names(dim, "velocity");
 *   std::vector<DataComponentInterpretation::DataComponentInterpretation>
 *     data_component_interpretation(
 *       dim, DataComponentInterpretation::component_is_part_of_vector);
 *
 *   DataOut<dim> data_out;
 *
 * @endcode
 *  将解决方案的数据附加到data_out对象上
 *
 *
 * @code
 *   data_out.attach_dof_handler(fluid_dh);
 *   data_out.add_data_vector(velocity_field,
 *                            solution_names,
 *                            DataOut<dim>::type_dof_data,
 *                            data_component_interpretation);
 *   Vector<float> subdomain(background_triangulation.n_active_cells());
 *   for (unsigned int i = 0; i < subdomain.size(); ++i)
 *     subdomain(i) = background_triangulation.locally_owned_subdomain();
 *   data_out.add_data_vector(subdomain, "subdomain");
 *
 *   data_out.build_patches(mapping);
 *
 *   const std::string output_folder(par.output_directory);
 *   const std::string file_name("background");
 *
 *   pcout << "Writing background field file: " << file_name << "-" << it
 *         << std::endl;
 *
 *   data_out.write_vtu_with_pvtu_record(
 *     output_folder, file_name, it, mpi_communicator, 6);
 * }
 *
 *
 *
 * @endcode
 *
 * <a name="Runningthesimulation"></a> <h4>Running the simulation</h4>
 * 这个函数协调了整个模拟过程。它与其他时间相关的教程程序非常相似
 *
 * - 以 step-21 或 step-26 为例。注意，我们使用DiscreteTime类来监控时间、时间步长和 step- 数。这个函数相对来说是比较简单的。
 *
 *
 *
 *
 * @code
 * template <int dim>
 * void ParticleTracking<dim>::run()
 * {
 *   DiscreteTime discrete_time(0, par.final_time, par.time_step);
 *
 *   generate_particles();
 *
 *   pcout << "Repartitioning triangulation after particle generation"
 *         << std::endl;
 *   background_triangulation.repartition();
 *
 * @endcode
 *
 * 我们通过在分析法和插值法的情况下进行时间步长为0的显式欧拉迭代来设置粒子的初始属性。
 *
 *
 * @code
 *   if (interpolated_velocity)
 *     {
 *       setup_background_dofs();
 *       interpolate_function_to_field();
 *       euler_step_interpolated(0.);
 *     }
 *   else
 *     euler_step_analytical(0.);
 *
 *   output_particles(discrete_time.get_step_number());
 *   if (interpolated_velocity)
 *     output_background(discrete_time.get_step_number());
 *
 * @endcode
 *  粒子是通过循环的时间进行平流的。
 *
 *
 * @code
 *   while (!discrete_time.is_at_end())
 *     {
 *       discrete_time.advance_time();
 *       velocity.set_time(discrete_time.get_previous_time());
 *
 *       if ((discrete_time.get_step_number() % par.repartition_frequency) == 0)
 *         {
 *           background_triangulation.repartition();
 *           if (interpolated_velocity)
 *             setup_background_dofs();
 *         }
 *
 *       if (interpolated_velocity)
 *         {
 *           interpolate_function_to_field();
 *           euler_step_interpolated(discrete_time.get_previous_step_size());
 *         }
 *       else
 *         euler_step_analytical(discrete_time.get_previous_step_size());
 *
 * @endcode
 *
 * 在粒子被移动之后，有必要确定它们现在所在的单元。这可以通过调用
 * <code>sort_particles_into_subdomains_and_cells</code> 来实现。
 *
 *
 * @code
 *       particle_handler.sort_particles_into_subdomains_and_cells();
 *
 *       if ((discrete_time.get_step_number() % par.output_frequency) == 0)
 *         {
 *           output_particles(discrete_time.get_step_number());
 *           if (interpolated_velocity)
 *             output_background(discrete_time.get_step_number());
 *         }
 *     }
 * }
 *
 * } // namespace Step68
 *
 *
 *
 * @endcode
 *
 * <a name="Themainfunction"></a> <h3>The main() function</h3>。
 *
 *
 * 代码的其余部分，即`main()`函数，是标准的。我们注意到，我们用分析速度和插值速度运行粒子跟踪，并产生两种结果
 *
 *
 * @code
 * int main(int argc, charargv[])
 * {
 * using namespace Step68;
 * using namespace dealii;
 * deallog.depth_console(1);
 *
 * try
 *   {
 *     Utilities::MPI::MPI_InitFinalize mpi_initialization(argc, argv, 1);
 *
 *     std::string prm_file;
 *     if (argc > 1)
 *       prm_file = argv[1];
 *     else
 *       prm_file = "parameters.prm";
 *
 *     ParticleTrackingParameters par;
 *     ParameterAcceptor::initialize(prm_file);
 *     {
 *       Step68::ParticleTracking<2> particle_tracking(par, false);
 *       particle_tracking.run();
 *     }
 *     {
 *       Step68::ParticleTracking<2> particle_tracking(par, true);
 *       particle_tracking.run();
 *     }
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
 *
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
 *
 * return 0;
 * }
 * @endcode
 * <a name="Results"></a><h1>Results</h1> 。
 *
 * 如果你没有在命令行上指定一个参数文件作为参数，程序将尝试默认读取文件
 * "parameters.prm"，并将执行代码。
 * 在任何数量的核心上，模拟输出将看起来像。
 * @code
 * bash$ mpirun
 *
 * -np 4 ./step-68 parameters.prm
 * Number of particles inserted: 606
 * Repartitioning triangulation after particle generation
 * Writing particle output file: analytical-particles-0
 * Writing particle output file: analytical-particles-10
 * Writing particle output file: analytical-particles-20
 * Writing particle output file: analytical-particles-30
 * ...
 * Number of particles inserted: 606
 * Repartitioning triangulation after particle generation
 * Writing particle output file: interpolated-particles-0
 * Writing background field file: background-0
 * Writing particle output file: interpolated-particles-10
 * Writing background field file: background-10
 * Writing particle output file: interpolated-particles-20
 * Writing background field file: background-20
 * Writing particle output file: interpolated-particles-30
 * Writing background field file: background-30
 * ...
 * Writing particle output file: interpolated-particles-1980
 * Writing background field file: background-1980
 * Writing particle output file: interpolated-particles-1990
 * Writing background field file: background-1990
 * Writing particle output file: interpolated-particles-2000
 * Writing background field file: background-2000
 * @endcode
 *
 * 我们注意到，在默认情况下，仿真会以分析速度运行粒子跟踪2000次迭代，然后从头开始，以相同的时间运行速度插值的粒子跟踪。每10次迭代都会写出结果。
 * <a name="Motionoftheparticles"></a><h3> Motion of the particles </h3>
 *
 * 下面的动画显示了粒子被流场吸引时的轨迹。我们看到，在流场的整个持续时间之后，粒子又回到了它们的初始配置，这是预料之中的。
 * @htmlonly <p align="center"> <iframe width="560" height="500"
 * src="https://www.youtube.com/embed/EbgS5Ch35Xs" frameborder="0"
 * allow="accelerometer; autoplay; encrypted-media; gyroscope;
 * picture-in-picture" allowfullscreen></iframe> </p> @endhtmlonly
 *
 * <a name="Dynamicloadbalancing"></a><h3> Dynamic load balancing </h3>
 *
 * 下面的动画显示了动态负载平衡的影响。我们清楚地看到，子域适应自己以平衡每个子域的粒子数量。然而，完美的负载平衡并没有达到，部分原因是由于背景网格的粗糙性。
 * @htmlonly <p align="center"> <iframe width="560" height="500"
 * src="https://www.youtube.com/embed/ubUcsR4ECj4" frameborder="0"
 * allow="accelerometer; autoplay; encrypted-media; gyroscope;
 * picture-in-picture" allowfullscreen></iframe> </p> @endhtmlonly
 *
 *
 *  <a name="Possibilitiesforextensions"></a><h3>Possibilities for
 * extensions</h3> * <h3>Possibilities for extensions</h3>.
 *
 * 这个程序强调了在deal.II中处理粒子的一些主要能力，特别是它们在分布式并行模拟中使用的能力。然而，这个步骤可以以多种方式进行扩展。
 *
 * 高阶时间积分（例如使用Runge-Kutta
 * 4方法）可以用来提高精度，或者在相同精度下允许更大的时间步长。
 *
 * - 完整的运动方程（含惯性）可以为粒子求解。在这种情况下，粒子需要有额外的属性，如它们的质量，如 step-19 ，如果还想考虑与流体的相互作用，它们的直径。
 *
 * - 耦合到流动求解器。这一步可以直接与任何解决斯托克斯方程（ step-32 、 step-70 ）或纳维-斯托克斯方程（例如 step-57 ）的并行程序相耦合。
 *
 * - 计算两个模型之间最终粒子位置的差异，可以量化插值误差对粒子运动的影响。
 *
* <a name="PlainProg"></a><h1> The plain program</h1>  @include "step-68.cc"  。
 *
 */


