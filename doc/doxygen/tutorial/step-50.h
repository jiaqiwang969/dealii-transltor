//include/deal.II-translator/A-tutorial/step-50_0.txt
/**
 * @page step_50 The step-50 tutorial program
 * 本教程依赖于  step-16  ,  step-37  。 @htmlonly <table
 * class="tutorial" width="50%"> <tr><th colspan="2"><b><small>Table of
 * contents</small></b><b><small>Table of contents</small></b></th></tr>
 * <tr><td width="50%" valign="top">
 * <ol>
 * <li> <a href="#Intro" class=bold>Introduction</a><a href="#Intro"
 * class=bold>Introduction</a>
 * <ul>
 * <li><a href="#Thetestcase">The testcase</a><a href="#Thetestcase">The
 * testcase</a>
 * <li><a href="#Workloadimbalanceforgeometricmultigridmethods">Workload
 * imbalance for geometric multigrid methods</a><a
 * href="#Workloadimbalanceforgeometricmultigridmethods">Workload imbalance
 * for geometric multigrid methods</a>
 * <li><a href="#Workloadimbalanceforalgebraicmultigridmethods">Workload
 * imbalance for algebraic multigrid methods</a><a
 * href="#Workloadimbalanceforalgebraicmultigridmethods">Workload imbalance
 * for algebraic multigrid methods</a>
 * <li><a href="#Runningtheprogram">Running the program</a><a
 * href="#Runningtheprogram">Running the program</a>
 * </ul>
 * <li> <a href="#CommProg" class=bold>The commented program</a><a
 * href="#CommProg" class=bold>The commented program</a>
 * <ul>
 * <li><a href="#Includefiles">Include files</a><a
 * href="#Includefiles">Include files</a>
 * <li><a href="#Coefficientsandhelperclasses">Coefficients and helper
 * classes</a><a href="#Coefficientsandhelperclasses">Coefficients and helper
 * classes</a>
 * <li><a href="#Runtimeparameters">Run time parameters</a><a
 * href="#Runtimeparameters">Run time parameters</a>
 * <li><a href="#LaplaceProblemclass">LaplaceProblem class</a><a
 * href="#LaplaceProblemclass">LaplaceProblem class</a>
 * <ul>
 * <li><a
 * href="#LaplaceProblemsetup_system">LaplaceProblem::setup_system()</a><a
 * href="#LaplaceProblemsetup_system">LaplaceProblem::setup_system()</a>
 * <li><a
 * href="#LaplaceProblemsetup_multigrid">LaplaceProblem::setup_multigrid()</a><a
 * href="#LaplaceProblemsetup_multigrid">LaplaceProblem::setup_multigrid()</a>
 * <li><a
 * href="#LaplaceProblemassemble_system">LaplaceProblem::assemble_system()</a><a
 * href="#LaplaceProblemassemble_system">LaplaceProblem::assemble_system()</a>
 * <li><a
 * href="#LaplaceProblemassemble_multigrid">LaplaceProblem::assemble_multigrid()</a><a
 * href="#LaplaceProblemassemble_multigrid">LaplaceProblem::assemble_multigrid()</a>
 * <li><a
 * href="#LaplaceProblemassemble_rhs">LaplaceProblem::assemble_rhs()</a><a
 * href="#LaplaceProblemassemble_rhs">LaplaceProblem::assemble_rhs()</a>
 * <li><a href="#LaplaceProblemsolve">LaplaceProblem::solve()</a><a
 * href="#LaplaceProblemsolve">LaplaceProblem::solve()</a>
 * </ul>
 * <li><a href="#Theerrorestimator">The error estimator</a><a
 * href="#Theerrorestimator">The error estimator</a>
 * <ul>
 * <li><a
 * href="#LaplaceProblemrefine_grid">LaplaceProblem::refine_grid()</a><a
 * href="#LaplaceProblemrefine_grid">LaplaceProblem::refine_grid()</a>
 * <li><a
 * href="#LaplaceProblemoutput_results">LaplaceProblem::output_results()</a><a
 * href="#LaplaceProblemoutput_results">LaplaceProblem::output_results()</a>
 * <li><a href="#LaplaceProblemrun">LaplaceProblem::run()</a><a
 * href="#LaplaceProblemrun">LaplaceProblem::run()</a>
 * </ul>
 * <li><a href="#Themainfunction">The main() function</a><a
 * href="#Themainfunction">The main() function</a>
 * </ul>
 * </ol></td><td width="50%" valign="top"><ol>
 * <li value="3"> <a href="#Results" class=bold>Results</a><a href="#Results"
 * class=bold>Results</a>
 * <ul>
 * <li><a href="#Possibilitiesforextensions"> Possibilities for extensions
 * </a><a href="#Possibilitiesforextensions"> Possibilities for extensions
 * </a>
 * <ul>
 * <li><a href="#Testingconvergenceandhigherorderelements"> Testing
 * convergence and higher order elements </a><a
 * href="#Testingconvergenceandhigherorderelements"> Testing convergence and
 * higher order elements </a>
 * <li><a href="#Coarsesolver"> Coarse solver </a><a href="#Coarsesolver">
 * Coarse solver </a>
 * </ul>
 * </ul>
 * <li> <a href="#PlainProg" class=bold>The plain program</a><a
 * href="#PlainProg" class=bold>The plain program</a>
 * </ol> </td> </tr> </table>
 * @endhtmlonly
 * <br>
 * <i> This program was contributed by Thomas C. Clevenger and Timo Heister.
 * <br>
 * This material is based upon work partly supported by the National Science
 * Foundation Award DMS-2028346, OAC-2015848, EAR-1925575, by the
 * Computational Infrastructure in Geodynamics initiative (CIG), through the
 * NSF under Award EAR-0949446 and EAR-1550901 and The University of
 * California
 *
 * -- Davis. </i>
 * @dealiiTutorialDOI{10.5281/zenodo.4004166,https://zenodo.org/badge/DOI/10.5281/zenodo.4004166.svg}
 * @note
 * 作为这个程序的先决条件，你需要同时安装p4est和PETScor
 * Trilinos库。在<a href="../../readme.html"
 * target="body">README</a>文件中描述了deal.II和这些附加库的安装情况。
 *
 *  <a name="Intro"></a><a name="Introduction"></a><h1>Introduction</h1>
 *
 * 这个例子展示了deal.II中的多级函数在平行分布式网格上的应用，并给出了几何多栅和代数多栅方法的比较。考虑了两种几何多网格(GMG)的预处理方法：一种是类似于
 * step-16
 * 中的基于矩阵的版本（但用于并行计算），另一种是
 * step-37
 * 中讨论的无矩阵版本。我们的目标是找出哪种方法能够为大型并行计算提供最好的解算器。
 * 本教程是基于  @cite clevenger_par_gmg
 * 中的一个数值例子。请参阅该出版物，以了解交易.II中多网格实现的详细背景。我们将在下面的文字中总结一些结果。
 * 代数多网格方法显然是最容易用deal.II实现的，因为诸如
 * TrilinosWrappers::PreconditionAMG 和 PETScWrappers::PreconditionBoomerAMG
 * 这样的类本质上是黑布尔调节器，即使对于并行计算，也只需要几行就可以设置好。另一方面，几何多网格方法需要对整个代码库进行修改
 *
 * - 不是非常多，但必须知道自己在做什么。
 * 本程序的结果将显示，代数和几何多网格方法的性能大致相当<i>when
 * using matrix-based
 * formulations</i>，而无矩阵的几何多网格方法对于这里所考虑的问题来说要好得多。次要的结论是，当每个处理器的未知数小于20,000个时，基于矩阵的几何多网格方法确实不能很好地扩展。
 *
 *  <a name="Thetestcase"></a><h3>The testcase</h3>
 * 我们考虑变系数拉普拉斯的弱表述
 * @f{align*}
 * (\epsilon \nabla u, \nabla v) = (f,v) \quad \forall v \in V_h
 * @f}
 * 在域 $\Omega = [-1,1]^\text{dim} \setminus [0,1]^\text{dim}$
 * （二维为L形域，三维为Fichera角）上，如果
 * $\min(x,y,z)>-\frac{1}{2}$ ，则为 $\epsilon = 100$ 。换句话说，
 * $\epsilon$
 * 是沿着域的边缘或面的小的，这些边缘或面跑到再入角，在下面的图中会看到。
 * 边界条件在整个边界上是 $u=0$ ，右手边是 $f=1$
 * 。我们使用连续的 $Q_2$ 元素来表示离散的有限元空间
 * $V_h$ ，并使用来自 @cite karakashian2003posteriori
 * 的基于单元的后验误差估计器 $e(K) = e_{\text{cell}}(K) +
 * e_{\text{face}}(K)$ 。
 * @f{align*}
 * e_{\text{cell}}(K) &= h^2 \| f + \epsilon \triangle u \|_K^2, \\
 * e_{\text{face}}(K) &= \sum_F h_F \| \jump{ \epsilon \nabla u \cdot n } \|_F^2,
 * @f}
 * 适应性地细化网格。(这是KellyErrorEstimator类中使用的Kellyerror估计器的一般化，KellyErrorEstimator类在大多数其他教程程序中驱动网格细化。)下图是2D的解决方案和细化的可视化：
 * <img width="400px"
 * src="https://www.dealii.org/images/steps/developer/step-50-2d-solution.png"
 * alt="">
 * 在3D中，解决方案看起来类似(见下文)。在左边你可以看到解决方案，在右边我们展示了靠近域中心的
 * $x$ 的切片，显示了自适应细化的网格。 <table width="60%"
 * align="center"> <tr> <td align="center"> <img width="400px"
 * src="https://www.dealii.org/images/steps/developer/step-50-3d-solution.png"
 * alt=""> </td> <td align="center"> <img width="400px"
 * src="https://www.dealii.org/images/steps/developer/step-50-refinement.png"
 * alt=""> </td> </tr> </table>
 * 在二维和三维中，你都可以看到自适应细化拾取了角部奇点和粘度跳跃的内部奇点，而沿着分离两个粘度的线的界面（正确）没有被细化，因为它被充分解决了。
 *
 *  <a name="Workloadimbalanceforgeometricmultigridmethods"></a><h3>Workload
 * imbalance for geometric multigrid methods</h3>
 * 如上所述，这个程序的目的是展示代数和几何多网格方法在这个问题上的应用，并且是在并行计算中的应用。使算法扩展到大型并行机器的一个重要组成部分是确保每个处理器都有相同的工作量要做。更确切地说，重要的是没有一小部分处理器比其他处理器有更多的工作，因为如果是这样的话，很大一部分处理器将闲置，等待一小部分处理器完成工作。相反，一小部分处理器拥有大量<i>less</i>的工作并不是一个问题，因为大多数处理器会继续生产，只有一小部分处理器在完成工作后会闲置。)
 * 对于活跃的网格，我们使用 parallel::distributed::Triangulation
 * 类，正如在 step-40 中所做的那样，它使用外部库<a
 * href="http://www.p4est.org/">p4est</a>中的功能来分配活跃单元在处理器之间。对于多级层次结构中的非活动单元，deal.II实现了我们所说的
 * "第一子规则"，对于层次结构中的每个单元，我们递归地将一个单元的父级分配给第一个子单元的所有者。下面的图给出了这样一个分布的例子。左图表示使用空间填充曲线划分的二维网格样本的活动单元（这也是p4est用来划分单元的方法）；中图给出活动网格的树状表示；右图给出单元的多级层次。颜色和数字代表不同的处理器。树状图中的圆形节点是非活动单元，使用
 * "长子规则 "进行分配。 <img width="800px"
 * src="https://www.dealii.org/images/steps/developer/step-50-workload-example.png"
 * alt=""> 在这个例子中，屏幕上的输出包括一个 "分区效率
 * "的数值，这个数值由 MGTools::workload_imbalance(). 表示，用
 * $\mathbb{E}$
 * 来量化在多网格层次结构的每一层上没有完美工作平衡所产生的开销。这种不平衡在上面的例子中很明显：虽然
 * $\ell=2$
 * 层在三个处理器的四个单元中尽可能的平衡，但粗略的
 * $\ell=0$ 层只有一个处理器的工作，而 $\ell=1$
 * 层只有两个处理器的工作，其中一个的工作是另一个的三倍。
 * 对于定义 $\mathbb{E}$ ，需要注意的是，由于我们使用局部平滑来定义多网格层次（见 @ref mg_paper "多网格论文 "
 * 中对局部平滑的描述），一个单元的细化水平与该单元的多网格水平相对应。现在，让
 * $N_{\ell}$ 为 $\ell$
 * 层的单元数（包括活动和非活动单元）， $N_{\ell,p}$
 * 为进程 $p$ 所拥有的子集。我们还将用 $P$
 * 表示处理器的总数。假设任何一个处理器的工作量与该处理器拥有的单元格数量成正比，每个处理器的最佳工作量为
 * @f{align*}
 * W_{\text{opt}} = \frac1{P}\sum_{\ell} N_{\ell} = \sum_{\ell}\left(\frac1{P}\sum_{p}N_{\ell,p}\right).
 * @f}
 * 接下来，假设每一层的工作都是同步的（即在V型循环的每一层，在进入下一层之前，所有的处理器都必须完成工作），每一层的极限工作由以下公式给出
 * @f{align*}
 * W_\ell = \max_{p} N_{\ell,p},
 * @f}
 * 而总的并行复杂度
 * @f{align*}
 * W = \sum_{\ell} W_\ell.
 * @f}
 * 然后我们将 $\mathbb{E}$
 * 定义为最佳分区与当前分区的并行复杂度的比率
 * @f{align*}
 * \mathbb{E} = \frac{W_{\text{opt}}}{W}.
 * @f}
 * 对于上面的例子分布，我们有
 * @f{align*}
 * W_{\text{opt}}&=\frac{1}{P}\sum_{\ell} N_{\ell} = \frac{1}{3} \left(1+4+4\right)= 3 \qquad
 * \\
 * W &= \sum_\ell W_\ell = 1 + 2 + 3 = 6
 * \\
 * \mathbb{E} &= \frac{W_{\text{opt}}}{W} = \frac12.
 * @f}
 * 该值  MGTools::workload_imbalance()$=  1/mathbb{E}。 $ then represents
 * the factor increase in timings we expect for GMG methods (vmults, assembly,
 * etc.) due to the imbalance of the mesh partition compared to a perfectly
 * load-balanced workload. We will report on these in the results section
 * below for a sequence of meshes, and compare with the observed slow-downs as
 * we go to larger and larger processor numbers (where, typically, the load
 * imbalance becomes larger as well).
 *
 * These sorts of considerations are considered in much greater detail in
 * @cite clevenger_par_gmg, which contains a full discussion of the partition
 * efficiency model and the effect the imbalance has on the GMG V-cycle
 * timing. In summary, the value of $  `mathbb{E}的价值 $ is highly
 * dependent on the degree of local mesh refinement used and has an optimal
 * value $  `mathbb{E}。\约1  $ for globally refined meshes. Typically for
 * adaptively refined meshes, the number of processors used to distribute a
 * single mesh has a negative impact on $  Mathematbb{E}。 $ but only up to a
 * leveling off point, where the imbalance remains relatively constant for an
 * increasing number of processors, and further refinement has very little
 * impact on $  1/2.x.x. $. Finally, $  1/mathbb{E]。 $ was shown to give an
 * accurate representation of the slowdown in parallel scaling expected for
 * the timing of a V-cycle.
 *
 * It should be noted that there is potential for some asynchronous work
 * between multigrid levels, specifically with purely nearest neighbor MPI
 * communication, and an adaptive mesh could be constructed such that the
 * efficiency model would far overestimate the V-cycle slowdown due to the
 * asynchronous work "covering up" the imbalance (which assumes
 * synchronization over levels). However, for most realistic adaptive meshes
 * the expectation is that this asynchronous work will only cover up a very
 * small portion of the imbalance and the efficiency model will describe the
 * slowdown very well.
 *
 *
 * <a name="Workloadimbalanceforalgebraicmultigridmethods"></a><h3>Workload
 * imbalance for algebraic multigrid methods</h3>
 *
 *
 * The considerations above show that one has to expect certain limits on the
 * scalability of the geometric multigrid algorithm as it is implemented in
 * deal.II because even in cases where the finest levels of a mesh are
 * perfectly load balanced, the coarser levels may not be. At the same time,
 * the coarser levels are weighted less (the contributions of $  W_\ell  $ to
 * $  W  $ are small) because coarser levels have fewer cells and,
 * consequently, do not contribute to the overall run time as much as finer
 * levels. In other words, imbalances in the coarser levels may not lead to
 * large effects in the big picture.
 *
 * Algebraic multigrid methods are of course based on an entirely different
 * approach to creating a hierarchy of levels. In particular, they create
 * these purely based on analyzing the system matrix, and very sophisticated
 * algorithms for ensuring that the problem is well load-balanced on every
 * level are implemented in both the hypre and ML/MueLu packages that underly
 * the TrilinosWrappers::PreconditionAMG and
 * PETScWrappers::PreconditionBoomerAMG classes. In some sense, these
 * algorithms are simpler than for geometric multigrid methods because they
 * only deal with the matrix itself, rather than all of the connotations of
 * meshes, neighbors, parents, and other geometric entities. At the same time,
 * much work has also been put into making algebraic multigrid methods scale
 * to very large problems, including questions such as reducing the number of
 * processors that work on a given level of the hierarchy to a subset of all
 * processors, if otherwise processors would spend less time on computations
 * than on communication. (One might note that it is of course possible to
 * implement these same kinds of ideas also in geometric multigrid algorithms
 * where one purposefully idles some processors on coarser levels to reduce
 * the amount of communication. deal.II just doesn't do this at this time.)
 *
 * These are not considerations we typically have to worry about here,
 * however: For most purposes, we use algebraic multigrid methods as black-box
 * methods.
 *
 *
 *
 * <a name="Runningtheprogram"></a><h3>Running the program</h3>
 *
 *
 * As mentioned above, this program can use three different ways of solving
 * the linear system: matrix-based geometric multigrid ("MB"), matrix-free
 * geometric multigrid ("MF"), and algebraic multigrid ("AMG"). The directory
 * in which this program resides has input files with suffix `.prm` for all
 * three of these options, and for both 2d and 3d.
 *
 * You can execute the program as in
 *
 * @code
 * ./step-50 gmg_mb_2d.prm
 * @endcode
 *
 * and this will take the run-time parameters from the given input file (here,
 * `gmg_mb_2d.prm`).
 *
 * The program is intended to be run in parallel, and you can achieve this
 * using a command such as
 *
 * @code
 * mpirun
 *
 * -np 4 ./step-50 gmg_mb_2d.prm
 * @endcode
 *
 * if you want to, for example, run on four processors. (That said, the
 * program is also ready to run with, say, `-np 28672` if that's how many
 * processors you have available.)
 *
 *
 * <a name="CommProg"></a> <h1> The commented program</h1>
 *
 *  <a name="Includefiles"></a> <h3>Include files</h3>
 *
 *
 *
 * The include files are a combination of step-40, step-16, and step-37:
 *
 *
 *
 *
 *
 * @code
 * #include <deal.II/base/conditional_ostream.h>
 * #include <deal.II/base/data_out_base.h>
 * #include <deal.II/base/index_set.h>
 * #include <deal.II/base/logstream.h>
 * #include <deal.II/base/quadrature_lib.h>
 * #include <deal.II/base/timer.h>
 * #include <deal.II/base/parameter_handler.h>
 * #include <deal.II/distributed/grid_refinement.h>
 * #include <deal.II/distributed/tria.h>
 * #include <deal.II/dofs/dof_tools.h>
 * #include <deal.II/fe/fe_q.h>
 * #include <deal.II/fe/fe_values.h>
 * #include <deal.II/grid/grid_generator.h>
 * #include <deal.II/grid/grid_refinement.h>
 * #include <deal.II/grid/tria.h>
 * #include <deal.II/lac/affine_constraints.h>
 * #include <deal.II/lac/dynamic_sparsity_pattern.h>
 * #include <deal.II/lac/solver_cg.h>
 *
 * @endcode
 *
 *
 * We use the same strategy as in step-40 to switch between PETSc and
 * Trilinos:
 *
 *
 *
 *
 *
 * @code
 * #include <deal.II/lac/generic_linear_algebra.h>
 *
 * @endcode
 *
 *
 * Comment the following preprocessor definition in or out if you have PETSc
 * and Trilinos installed and you prefer using PETSc in this example:
 *
 *
 *
 * @code
 * #define FORCE_USE_OF_TRILINOS
 *
 * namespace LA
 * {
 * #if defined(DEAL_II_WITH_PETSC) && !defined(DEAL_II_PETSC_WITH_COMPLEX) && \
 * !(defined(DEAL_II_WITH_TRILINOS) && defined(FORCE_USE_OF_TRILINOS))
 * using namespace dealii::LinearAlgebraPETSc;
 * #  define USE_PETSC_LA
 * #elif defined(DEAL_II_WITH_TRILINOS)
 * using namespace dealii::LinearAlgebraTrilinos;
 * #else
 * #  error DEAL_II_WITH_PETSC or DEAL_II_WITH_TRILINOS required
 * #endif
 * } // namespace LA
 *
 * #include <deal.II/matrix_free/matrix_free.h>
 * #include <deal.II/matrix_free/operators.h>
 * #include <deal.II/matrix_free/fe_evaluation.h>
 * #include <deal.II/multigrid/mg_coarse.h>
 * #include <deal.II/multigrid/mg_constrained_dofs.h>
 * #include <deal.II/multigrid/mg_matrix.h>
 * #include <deal.II/multigrid/mg_smoother.h>
 * #include <deal.II/multigrid/mg_tools.h>
 * #include <deal.II/multigrid/mg_transfer.h>
 * #include <deal.II/multigrid/multigrid.h>
 * #include <deal.II/multigrid/mg_transfer_matrix_free.h>
 * #include <deal.II/numerics/data_out.h>
 * #include <deal.II/numerics/vector_tools.h>
 *
 * @endcode
 *
 *
 * The following files are used to assemble the error estimator like in
 * step-12:
 *
 *
 *
 * @code
 * #include <deal.II/fe/fe_interface_values.h>
 * #include <deal.II/meshworker/mesh_loop.h>
 *
 * using namespace dealii;
 *
 *
 * @endcode
 *
 *
 *  <a name="Coefficientsandhelperclasses"></a> <h3>Coefficients and helper
 * classes</h3>
 *
 *
 *
 * MatrixFree operators must use the
 * dealii::LinearAlgebra::distributed::Vector vector type. Here we define
 * operations which copy to and from Trilinos vectors for compatibility with
 * the matrix-based code. Note that this functionality does not currently
 * exist for PETSc vector types, so Trilinos must be installed to use the
 * MatrixFree solver in this tutorial.
 *
 *
 *
 * @code
 * namespace ChangeVectorTypes
 * {
 * template <typename number>
 * void copy(LA::MPI::Vector &                                         out,
 *           const dealii::LinearAlgebra::distributed::Vector<number> &in)
 * {
 *   dealii::LinearAlgebra::ReadWriteVector<double> rwv(
 *     out.locally_owned_elements());
 *   rwv.import(in, VectorOperation::insert);
 * #ifdef USE_PETSC_LA
 *   AssertThrow(false,
 *               ExcMessage("CopyVectorTypes::copy() not implemented for "
 *                          "PETSc vector types."));
 * #else
 *   out.import(rwv, VectorOperation::insert);
 * #endif
 * }
 *
 *
 *
 * template <typename number>
 * void copy(dealii::LinearAlgebra::distributed::Vector<number> &out,
 *           const LA::MPI::Vector &                             in)
 * {
 *   dealii::LinearAlgebra::ReadWriteVector<double> rwv;
 * #ifdef USE_PETSC_LA
 *   (void)in;
 *   AssertThrow(false,
 *               ExcMessage("CopyVectorTypes::copy() not implemented for "
 *                          "PETSc vector types."));
 * #else
 *   rwv.reinit(in);
 * #endif
 *   out.import(rwv, VectorOperation::insert);
 * }
 * } // namespace ChangeVectorTypes
 *
 *
 * @endcode
 *
 *
 * Let's move on to the description of the problem we want to solve. We set
 * the right-hand side function to 1.0. The @p value function returning a
 * VectorizedArray is used by the matrix-free code path.
 *
 *
 *
 * @code
 * template <int dim>
 * class RightHandSide : public Function<dim>
 * {
 * public:
 * virtual double value(const Point<dim> &  [4.x.0] ,
 *                      const unsigned int  [4.x.1]  = 0) const override
 * {
 *   return 1.0;
 * }
 *
 *
 * template <typename number>
 * VectorizedArray<number>
 * value(const Point<dim, VectorizedArray<number>> &  [4.x.2] ,
 *       const unsigned int  [4.x.3]  = 0) const
 * {
 *   return VectorizedArray<number>(1.0);
 * }
 * };
 *
 *
 * @endcode
 *
 *
 * This next class represents the diffusion coefficient. We use a variable
 * coefficient which is 100.0 at any point where at least one coordinate is
 * less than
 *
 * -0.5, and 1.0 at all other points. As above, a separate value() returning a
 * VectorizedArray is used for the matrix-free code. An @p average() function
 * computes the arithmetic average for a set of points.
 *
 *
 *
 * @code
 * template <int dim>
 * class Coefficient : public Function<dim>
 * {
 * public:
 * virtual double value(const Point<dim> &p,
 *                      const unsigned int  [4.x.4]  = 0) const override;
 *
 * template <typename number>
 * VectorizedArray<number> value(const Point<dim, VectorizedArray<number>> &p,
 *                               const unsigned int  [4.x.5]  = 0) const;
 *
 * template <typename number>
 * number average_value(const std::vector<Point<dim, number>> &points) const;
 *
 * @endcode
 *
 *
 * When using a coefficient in the MatrixFree framework, we also need a
 * function that creates a Table of coefficient values for a set of cells
 * provided by the MatrixFree operator argument here.
 *
 *
 *
 * @code
 * template <typename number>
 * std::shared_ptr<Table<2, VectorizedArray<number>>> make_coefficient_table(
 *   const MatrixFree<dim, number, VectorizedArray<number>> &mf_storage) const;
 * };
 *
 *
 *
 * template <int dim>
 * double Coefficient<dim>::value(const Point<dim> &p, const unsigned int) const
 * {
 * for (int d = 0; d < dim; ++d)
 *   {
 *     if (p[d] <
 *
 * -0.5)
 *       return 100.0;
 *   }
 * return 1.0;
 * }
 *
 *
 *
 * template <int dim>
 * template <typename number>
 * VectorizedArray<number>
 * Coefficient<dim>::value(const Point<dim, VectorizedArray<number>> &p,
 *                       const unsigned int) const
 * {
 * VectorizedArray<number> return_value = VectorizedArray<number>(1.0);
 * for (unsigned int i = 0; i < VectorizedArray<number>::size(); ++i)
 *   {
 *     for (int d = 0; d < dim; ++d)
 *       if (p[d][i] <
 *
 * -0.5)
 *         {
 *           return_value[i] = 100.0;
 *           break;
 *         }
 *   }
 *
 * return return_value;
 * }
 *
 *
 *
 * template <int dim>
 * template <typename number>
 * number Coefficient<dim>::average_value(
 * const std::vector<Point<dim, number>> &points) const
 * {
 * number average(0);
 * for (unsigned int i = 0; i < points.size(); ++i)
 *   average += value(points[i]);
 * average /= points.size();
 *
 * return average;
 * }
 *
 *
 *
 * template <int dim>
 * template <typename number>
 * std::shared_ptr<Table<2, VectorizedArray<number>>>
 * Coefficient<dim>::make_coefficient_table(
 * const MatrixFree<dim, number, VectorizedArray<number>> &mf_storage) const
 * {
 * auto coefficient_table =
 *   std::make_shared<Table<2, VectorizedArray<number>>>();
 *
 * FEEvaluation<dim,
 *
 * -1, 0, 1, number> fe_eval(mf_storage);
 *
 * const unsigned int n_cells    = mf_storage.n_cell_batches();
 * const unsigned int n_q_points = fe_eval.n_q_points;
 *
 * coefficient_table->reinit(n_cells, 1);
 *
 * for (unsigned int cell = 0; cell < n_cells; ++cell)
 *   {
 *     fe_eval.reinit(cell);
 *
 *     VectorizedArray<number> average_value = 0.;
 *     for (unsigned int q = 0; q < n_q_points; ++q)
 *       average_value += value(fe_eval.quadrature_point(q));
 *     average_value /= n_q_points;
 *
 *     (*coefficient_table)(cell, 0) = average_value;
 *   }
 *
 * return coefficient_table;
 * }
 *
 *
 *
 * @endcode
 *
 *
 *  <a name="Runtimeparameters"></a> <h3>Run time parameters</h3>
 *
 *
 *
 * We will use ParameterHandler to pass in parameters at runtime.  The
 * structure @p Settings parses and stores these parameters to be queried
 * throughout the program.
 *
 *
 *
 * @code
 * struct Settings
 * {
 * bool try_parse(const std::string &prm_filename);
 *
 * enum SolverType
 * {
 *   gmg_mb,
 *   gmg_mf,
 *   amg
 * };
 *
 * SolverType solver;
 *
 * int          dimension;
 * double       smoother_dampen;
 * unsigned int smoother_steps;
 * unsigned int n_steps;
 * bool         output;
 * };
 *
 *
 *
 * bool Settings::try_parse(const std::string &prm_filename)
 * {
 * ParameterHandler prm;
 * prm.declare_entry("dim", "2", Patterns::Integer(), "The problem dimension.");
 * prm.declare_entry("n_steps",
 *                   "10",
 *                   Patterns::Integer(0),
 *                   "Number of adaptive refinement steps.");
 * prm.declare_entry("smoother dampen",
 *                   "1.0",
 *                   Patterns::Double(0.0),
 *                   "Dampen factor for the smoother.");
 * prm.declare_entry("smoother steps",
 *                   "1",
 *                   Patterns::Integer(1),
 *                   "Number of smoother steps.");
 * prm.declare_entry("solver",
 *                   "MF",
 *                   Patterns::Selection("MF|MB|AMG"),
 *                   "Switch between matrix-free GMG, "
 *                   "matrix-based GMG, and AMG.");
 * prm.declare_entry("output",
 *                   "false",
 *                   Patterns::Bool(),
 *                   "Output graphical results.");
 *
 * if (prm_filename.size() == 0)
 *   {
 *     std::cout << "****  Error: No input file provided!\n"
 *               << "****  Error: Call this program as './step-50 input.prm\n"
 *               << "\n"
 *               << "****  You may want to use one of the input files in this\n"
 *               << "****  directory, or use the following default values\n"
 *               << "****  to create an input file:\n";
 *     if (Utilities::MPI::this_mpi_process(MPI_COMM_WORLD) == 0)
 *       prm.print_parameters(std::cout, ParameterHandler::Text);
 *     return false;
 *   }
 *
 * try
 *   {
 *     prm.parse_input(prm_filename);
 *   }
 * catch (std::exception &e)
 *   {
 *     if (Utilities::MPI::this_mpi_process(MPI_COMM_WORLD) == 0)
 *       std::cerr << e.what() << std::endl;
 *     return false;
 *   }
 *
 * if (prm.get("solver") == "MF")
 *   this->solver = gmg_mf;
 * else if (prm.get("solver") == "MB")
 *   this->solver = gmg_mb;
 * else if (prm.get("solver") == "AMG")
 *   this->solver = amg;
 * else
 *   AssertThrow(false, ExcNotImplemented());
 *
 * this->dimension       = prm.get_integer("dim");
 * this->n_steps         = prm.get_integer("n_steps");
 * this->smoother_dampen = prm.get_double("smoother dampen");
 * this->smoother_steps  = prm.get_integer("smoother steps");
 * this->output          = prm.get_bool("output");
 *
 * return true;
 * }
 *
 *
 *
 * @endcode
 *
 *
 *  <a name="LaplaceProblemclass"></a> <h3>LaplaceProblem class</h3>
 *
 *
 *
 * This is the main class of the program. It looks very similar to step-16,
 * step-37, and step-40. For the MatrixFree setup, we use the
 * MatrixFreeOperators::LaplaceOperator class which defines `local_apply()`,
 * `compute_diagonal()`, and `set_coefficient()` functions internally. Note
 * that the polynomial degree is a template parameter of this class. This is
 * necessary for the matrix-free code.
 *
 *
 *
 * @code
 * template <int dim, int degree>
 * class LaplaceProblem
 * {
 * public:
 * LaplaceProblem(const Settings &settings);
 * void run();
 *
 * private:
 * @endcode
 *
 *
 * We will use the following types throughout the program. First the
 * matrix-based types, after that the matrix-free classes. For the matrix-free
 * implementation, we use @p float for the level operators.
 *
 *
 *
 * @code
 * using MatrixType         = LA::MPI::SparseMatrix;
 * using VectorType         = LA::MPI::Vector;
 * using PreconditionAMG    = LA::MPI::PreconditionAMG;
 * using PreconditionJacobi = LA::MPI::PreconditionJacobi;
 *
 * using MatrixFreeLevelMatrix = MatrixFreeOperators::LaplaceOperator<
 *   dim,
 *   degree,
 *   degree + 1,
 *   1,
 *   LinearAlgebra::distributed::Vector<float>>;
 * using MatrixFreeActiveMatrix = MatrixFreeOperators::LaplaceOperator<
 *   dim,
 *   degree,
 *   degree + 1,
 *   1,
 *   LinearAlgebra::distributed::Vector<double>>;
 *
 * using MatrixFreeLevelVector  = LinearAlgebra::distributed::Vector<float>;
 * using MatrixFreeActiveVector = LinearAlgebra::distributed::Vector<double>;
 *
 * void setup_system();
 * void setup_multigrid();
 * void assemble_system();
 * void assemble_multigrid();
 * void assemble_rhs();
 * void solve();
 * void estimate();
 * void refine_grid();
 * void output_results(const unsigned int cycle);
 *
 * Settings settings;
 *
 * MPI_Comm           mpi_communicator;
 * ConditionalOStream pcout;
 *
 * parallel::distributed::Triangulation<dim> triangulation;
 * const MappingQ1<dim>                      mapping;
 * FE_Q<dim>                                 fe;
 *
 * DoFHandler<dim> dof_handler;
 *
 * IndexSet                  locally_owned_dofs;
 * IndexSet                  locally_relevant_dofs;
 * AffineConstraints<double> constraints;
 *
 * MatrixType             system_matrix;
 * MatrixFreeActiveMatrix mf_system_matrix;
 * VectorType             solution;
 * VectorType             right_hand_side;
 * Vector<double>         estimated_error_square_per_cell;
 *
 * MGLevelObject<MatrixType> mg_matrix;
 * MGLevelObject<MatrixType> mg_interface_in;
 * MGConstrainedDoFs         mg_constrained_dofs;
 *
 * MGLevelObject<MatrixFreeLevelMatrix> mf_mg_matrix;
 *
 * TimerOutput computing_timer;
 * };
 *
 *
 * @endcode
 *
 *
 * The only interesting part about the constructor is that we construct the
 * multigrid hierarchy unless we use AMG. For that, we need to parse the run
 * time parameters before this constructor completes.
 *
 *
 *
 * @code
 * template <int dim, int degree>
 * LaplaceProblem<dim, degree>::LaplaceProblem(const Settings &settings)
 * : settings(settings)
 * , mpi_communicator(MPI_COMM_WORLD)
 * , pcout(std::cout, (Utilities::MPI::this_mpi_process(mpi_communicator) == 0))
 * , triangulation(mpi_communicator,
 *                 Triangulation<dim>::limit_level_difference_at_vertices,
 *                 (settings.solver == Settings::amg) ?
 *                   parallel::distributed::Triangulation<dim>::default_setting :
 *                   parallel::distributed::Triangulation<
 *                     dim>::construct_multigrid_hierarchy)
 * , mapping()
 * , fe(degree)
 * , dof_handler(triangulation)
 * , computing_timer(pcout, TimerOutput::never, TimerOutput::wall_times)
 * {
 * GridGenerator::hyper_L(triangulation,
 *
 * -1., 1.,  [4.x.6]  false);
 * triangulation.refine_global(1);
 * }
 *
 *
 *
 * @endcode
 *
 *
 *  <a name="LaplaceProblemsetup_system"></a>
 * <h4>LaplaceProblem::setup_system()</h4>
 *
 *
 *
 * Unlike step-16 and step-37, we split the set up into two parts,
 * setup_system() and setup_multigrid(). Here is the typical setup_system()
 * function for the active mesh found in most tutorials. For matrix-free, the
 * active mesh set up is similar to step-37; for matrix-based (GMG and AMG
 * solvers), the setup is similar to step-40.
 *
 *
 *
 * @code
 * template <int dim, int degree>
 * void LaplaceProblem<dim, degree>::setup_system()
 * {
 * TimerOutput::Scope timing(computing_timer, "Setup");
 *
 * dof_handler.distribute_dofs(fe);
 *
 * DoFTools::extract_locally_relevant_dofs(dof_handler, locally_relevant_dofs);
 * locally_owned_dofs = dof_handler.locally_owned_dofs();
 *
 * solution.reinit(locally_owned_dofs, mpi_communicator);
 * right_hand_side.reinit(locally_owned_dofs, mpi_communicator);
 * constraints.reinit(locally_relevant_dofs);
 * DoFTools::make_hanging_node_constraints(dof_handler, constraints);
 *
 * VectorTools::interpolate_boundary_values(
 *   mapping, dof_handler, 0, Functions::ZeroFunction<dim>(), constraints);
 * constraints.close();
 *
 * switch (settings.solver)
 *   {
 *     case Settings::gmg_mf:
 *       {
 *         typename MatrixFree<dim, double>::AdditionalData additional_data;
 *         additional_data.tasks_parallel_scheme =
 *           MatrixFree<dim, double>::AdditionalData::none;
 *         additional_data.mapping_update_flags =
 *           (update_gradients | update_JxW_values | update_quadrature_points);
 *         std::shared_ptr<MatrixFree<dim, double>> mf_storage =
 *           std::make_shared<MatrixFree<dim, double>>();
 *         mf_storage->reinit(mapping,
 *                            dof_handler,
 *                            constraints,
 *                            QGauss<1>(degree + 1),
 *                            additional_data);
 *
 *         mf_system_matrix.initialize(mf_storage);
 *
 *         const Coefficient<dim> coefficient;
 *         mf_system_matrix.set_coefficient(
 *           coefficient.make_coefficient_table(*mf_storage));
 *
 *         break;
 *       }
 *
 *     case Settings::gmg_mb:
 *     case Settings::amg:
 *       {
 * #ifdef USE_PETSC_LA
 *         DynamicSparsityPattern dsp(locally_relevant_dofs);
 *         DoFTools::make_sparsity_pattern(dof_handler, dsp, constraints);
 *
 *         SparsityTools::distribute_sparsity_pattern(dsp,
 *                                                    locally_owned_dofs,
 *                                                    mpi_communicator,
 *                                                    locally_relevant_dofs);
 *
 *         system_matrix.reinit(locally_owned_dofs,
 *                              locally_owned_dofs,
 *                              dsp,
 *                              mpi_communicator);
 * #else
 *         TrilinosWrappers::SparsityPattern dsp(locally_owned_dofs,
 *                                               locally_owned_dofs,
 *                                               locally_relevant_dofs,
 *                                               mpi_communicator);
 *         DoFTools::make_sparsity_pattern(dof_handler, dsp, constraints);
 *         dsp.compress();
 *         system_matrix.reinit(dsp);
 * #endif
 *
 *         break;
 *       }
 *
 *     default:
 *       Assert(false, ExcNotImplemented());
 *   }
 * }
 *
 * @endcode
 *
 *
 *  <a name="LaplaceProblemsetup_multigrid"></a>
 * <h4>LaplaceProblem::setup_multigrid()</h4>
 *
 *
 *
 * This function does the multilevel setup for both matrix-free and
 * matrix-based GMG. The matrix-free setup is similar to that of step-37, and
 * the matrix-based is similar to step-16, except we must use appropriate
 * distributed sparsity patterns.
 *
 *
 *
 * The function is not called for the AMG approach, but to err on the safe
 * side, the main `switch` statement of this function nevertheless makes sure
 * that the function only operates on known multigrid settings by throwing an
 * assertion if the function were called for anything other than the two
 * geometric multigrid methods.
 *
 *
 *
 * @code
 * template <int dim, int degree>
 * void LaplaceProblem<dim, degree>::setup_multigrid()
 * {
 * TimerOutput::Scope timing(computing_timer, "Setup multigrid");
 *
 * dof_handler.distribute_mg_dofs();
 *
 * mg_constrained_dofs.clear();
 * mg_constrained_dofs.initialize(dof_handler);
 *
 * const std::set<types::boundary_id> boundary_ids = {types::boundary_id(0)};
 * mg_constrained_dofs.make_zero_boundary_constraints(dof_handler, boundary_ids);
 *
 * const unsigned int n_levels = triangulation.n_global_levels();
 *
 * switch (settings.solver)
 *   {
 *     case Settings::gmg_mf:
 *       {
 *         mf_mg_matrix.resize(0, n_levels
 *
 * - 1);
 *
 *         for (unsigned int level = 0; level < n_levels; ++level)
 *           {
 *             IndexSet relevant_dofs;
 *             DoFTools::extract_locally_relevant_level_dofs(dof_handler,
 *                                                           level,
 *                                                           relevant_dofs);
 *             AffineConstraints<double> level_constraints;
 *             level_constraints.reinit(relevant_dofs);
 *             level_constraints.add_lines(
 *               mg_constrained_dofs.get_boundary_indices(level));
 *             level_constraints.close();
 *
 *             typename MatrixFree<dim, float>::AdditionalData additional_data;
 *             additional_data.tasks_parallel_scheme =
 *               MatrixFree<dim, float>::AdditionalData::none;
 *             additional_data.mapping_update_flags =
 *               (update_gradients | update_JxW_values |
 *                update_quadrature_points);
 *             additional_data.mg_level = level;
 *             std::shared_ptr<MatrixFree<dim, float>> mf_storage_level(
 *               new MatrixFree<dim, float>());
 *             mf_storage_level->reinit(mapping,
 *                                      dof_handler,
 *                                      level_constraints,
 *                                      QGauss<1>(degree + 1),
 *                                      additional_data);
 *
 *             mf_mg_matrix[level].initialize(mf_storage_level,
 *                                            mg_constrained_dofs,
 *                                            level);
 *
 *             const Coefficient<dim> coefficient;
 *             mf_mg_matrix[level].set_coefficient(
 *               coefficient.make_coefficient_table(*mf_storage_level));
 *
 *             mf_mg_matrix[level].compute_diagonal();
 *           }
 *
 *         break;
 *       }
 *
 *     case Settings::gmg_mb:
 *       {
 *         mg_matrix.resize(0, n_levels
 *
 * - 1);
 *         mg_matrix.clear_elements();
 *         mg_interface_in.resize(0, n_levels
 *
 * - 1);
 *         mg_interface_in.clear_elements();
 *
 *         for (unsigned int level = 0; level < n_levels; ++level)
 *           {
 *             IndexSet dof_set;
 *             DoFTools::extract_locally_relevant_level_dofs(dof_handler,
 *                                                           level,
 *                                                           dof_set);
 *
 *             {
 * #ifdef USE_PETSC_LA
 *               DynamicSparsityPattern dsp(dof_set);
 *               MGTools::make_sparsity_pattern(dof_handler, dsp, level);
 *               dsp.compress();
 *               SparsityTools::distribute_sparsity_pattern(
 *                 dsp,
 *                 dof_handler.locally_owned_mg_dofs(level),
 *                 mpi_communicator,
 *                 dof_set);
 *
 *               mg_matrix[level].reinit(
 *                 dof_handler.locally_owned_mg_dofs(level),
 *                 dof_handler.locally_owned_mg_dofs(level),
 *                 dsp,
 *                 mpi_communicator);
 * #else
 *               TrilinosWrappers::SparsityPattern dsp(
 *                 dof_handler.locally_owned_mg_dofs(level),
 *                 dof_handler.locally_owned_mg_dofs(level),
 *                 dof_set,
 *                 mpi_communicator);
 *               MGTools::make_sparsity_pattern(dof_handler, dsp, level);
 *
 *               dsp.compress();
 *               mg_matrix[level].reinit(dsp);
 * #endif
 *             }
 *
 *             {
 * #ifdef USE_PETSC_LA
 *               DynamicSparsityPattern dsp(dof_set);
 *               MGTools::make_interface_sparsity_pattern(dof_handler,
 *                                                        mg_constrained_dofs,
 *                                                        dsp,
 *                                                        level);
 *               dsp.compress();
 *               SparsityTools::distribute_sparsity_pattern(
 *                 dsp,
 *                 dof_handler.locally_owned_mg_dofs(level),
 *                 mpi_communicator,
 *                 dof_set);
 *
 *               mg_interface_in[level].reinit(
 *                 dof_handler.locally_owned_mg_dofs(level),
 *                 dof_handler.locally_owned_mg_dofs(level),
 *                 dsp,
 *                 mpi_communicator);
 * #else
 *               TrilinosWrappers::SparsityPattern dsp(
 *                 dof_handler.locally_owned_mg_dofs(level),
 *                 dof_handler.locally_owned_mg_dofs(level),
 *                 dof_set,
 *                 mpi_communicator);
 *
 *               MGTools::make_interface_sparsity_pattern(dof_handler,
 *                                                        mg_constrained_dofs,
 *                                                        dsp,
 *                                                        level);
 *               dsp.compress();
 *               mg_interface_in[level].reinit(dsp);
 * #endif
 *             }
 *           }
 *         break;
 *       }
 *
 *     default:
 *       Assert(false, ExcNotImplemented());
 *   }
 * }
 *
 *
 * @endcode
 *
 *
 *  <a name="LaplaceProblemassemble_system"></a>
 * <h4>LaplaceProblem::assemble_system()</h4>
 *
 *
 *
 * The assembly is split into three parts: `assemble_system()`,
 * `assemble_multigrid()`, and `assemble_rhs()`. The `assemble_system()`
 * function here assembles and stores the (global) system matrix and the
 * right-hand side for the matrix-based methods. It is similar to the assembly
 * in step-40.
 *
 *
 *
 * Note that the matrix-free method does not execute this function as it does
 * not need to assemble a matrix, and it will instead assemble the right-hand
 * side in assemble_rhs().
 *
 *
 *
 * @code
 * template <int dim, int degree>
 * void LaplaceProblem<dim, degree>::assemble_system()
 * {
 * TimerOutput::Scope timing(computing_timer, "Assemble");
 *
 * const QGauss<dim> quadrature_formula(degree + 1);
 *
 * FEValues<dim> fe_values(fe,
 *                         quadrature_formula,
 *                         update_values | update_gradients |
 *                           update_quadrature_points | update_JxW_values);
 *
 * const unsigned int dofs_per_cell = fe.n_dofs_per_cell();
 * const unsigned int n_q_points    = quadrature_formula.size();
 *
 * FullMatrix<double> cell_matrix(dofs_per_cell, dofs_per_cell);
 * Vector<double>     cell_rhs(dofs_per_cell);
 *
 * std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);
 *
 * const Coefficient<dim> coefficient;
 * RightHandSide<dim>     rhs;
 * std::vector<double>    rhs_values(n_q_points);
 *
 * for (const auto &cell : dof_handler.active_cell_iterators())
 *   if (cell->is_locally_owned())
 *     {
 *       cell_matrix = 0;
 *       cell_rhs    = 0;
 *
 *       fe_values.reinit(cell);
 *
 *       const double coefficient_value =
 *         coefficient.average_value(fe_values.get_quadrature_points());
 *       rhs.value_list(fe_values.get_quadrature_points(), rhs_values);
 *
 *       for (unsigned int q_point = 0; q_point < n_q_points; ++q_point)
 *         for (unsigned int i = 0; i < dofs_per_cell; ++i)
 *           {
 *             for (unsigned int j = 0; j < dofs_per_cell; ++j)
 *               cell_matrix(i, j) +=
 *                 coefficient_value                // epsilon(x)
 *                 fe_values.shape_grad(i, q_point) // grad phi_i(x)
 *                 fe_values.shape_grad(j, q_point) // grad phi_j(x)
 *                 fe_values.JxW(q_point);            // dx
 *
 *             cell_rhs(i) +=
 *               fe_values.shape_value(i, q_point) // grad phi_i(x)
 *               rhs_values[q_point]               // f(x)
 *               fe_values.JxW(q_point);             // dx
 *           }
 *
 *       cell->get_dof_indices(local_dof_indices);
 *       constraints.distribute_local_to_global(cell_matrix,
 *                                              cell_rhs,
 *                                              local_dof_indices,
 *                                              system_matrix,
 *                                              right_hand_side);
 *     }
 *
 * system_matrix.compress(VectorOperation::add);
 * right_hand_side.compress(VectorOperation::add);
 * }
 *
 *
 * @endcode
 *
 *
 *  <a name="LaplaceProblemassemble_multigrid"></a>
 * <h4>LaplaceProblem::assemble_multigrid()</h4>
 *
 *
 *
 * The following function assembles and stores the multilevel matrices for the
 * matrix-based GMG method. This function is similar to the one found in
 * step-16, only here it works for distributed meshes. This difference amounts
 * to adding a condition that we only assemble on locally owned level cells
 * and a call to compress() for each matrix that is built.
 *
 *
 *
 * @code
 * template <int dim, int degree>
 * void LaplaceProblem<dim, degree>::assemble_multigrid()
 * {
 * TimerOutput::Scope timing(computing_timer, "Assemble multigrid");
 *
 * QGauss<dim> quadrature_formula(degree + 1);
 *
 * FEValues<dim> fe_values(fe,
 *                         quadrature_formula,
 *                         update_values | update_gradients |
 *                           update_quadrature_points | update_JxW_values);
 *
 * const unsigned int dofs_per_cell = fe.n_dofs_per_cell();
 * const unsigned int n_q_points    = quadrature_formula.size();
 *
 * FullMatrix<double> cell_matrix(dofs_per_cell, dofs_per_cell);
 *
 * std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);
 *
 * const Coefficient<dim> coefficient;
 *
 * std::vector<AffineConstraints<double>> boundary_constraints(
 *   triangulation.n_global_levels());
 * for (unsigned int level = 0; level < triangulation.n_global_levels(); ++level)
 *   {
 *     IndexSet dof_set;
 *     DoFTools::extract_locally_relevant_level_dofs(dof_handler,
 *                                                   level,
 *                                                   dof_set);
 *     boundary_constraints[level].reinit(dof_set);
 *     boundary_constraints[level].add_lines(
 *       mg_constrained_dofs.get_refinement_edge_indices(level));
 *     boundary_constraints[level].add_lines(
 *       mg_constrained_dofs.get_boundary_indices(level));
 *
 *     boundary_constraints[level].close();
 *   }
 *
 * for (const auto &cell : dof_handler.cell_iterators())
 *   if (cell->level_subdomain_id() == triangulation.locally_owned_subdomain())
 *     {
 *       cell_matrix = 0;
 *       fe_values.reinit(cell);
 *
 *       const double coefficient_value =
 *         coefficient.average_value(fe_values.get_quadrature_points());
 *
 *       for (unsigned int q_point = 0; q_point < n_q_points; ++q_point)
 *         for (unsigned int i = 0; i < dofs_per_cell; ++i)
 *           for (unsigned int j = 0; j < dofs_per_cell; ++j)
 *             cell_matrix(i, j) +=
 *               coefficient_value fe_values.shape_grad(i, q_point)
 *               fe_values.shape_grad(j, q_point) fe_values.JxW(q_point);
 *
 *       cell->get_mg_dof_indices(local_dof_indices);
 *
 *       boundary_constraints[cell->level()].distribute_local_to_global(
 *         cell_matrix, local_dof_indices, mg_matrix[cell->level()]);
 *
 *       for (unsigned int i = 0; i < dofs_per_cell; ++i)
 *         for (unsigned int j = 0; j < dofs_per_cell; ++j)
 *           if (mg_constrained_dofs.is_interface_matrix_entry(
 *                 cell->level(), local_dof_indices[i], local_dof_indices[j]))
 *             mg_interface_in[cell->level()].add(local_dof_indices[i],
 *                                                local_dof_indices[j],
 *                                                cell_matrix(i, j));
 *     }
 *
 * for (unsigned int i = 0; i < triangulation.n_global_levels(); ++i)
 *   {
 *     mg_matrix[i].compress(VectorOperation::add);
 *     mg_interface_in[i].compress(VectorOperation::add);
 *   }
 * }
 *
 *
 *
 * @endcode
 *
 *
 *  <a name="LaplaceProblemassemble_rhs"></a>
 * <h4>LaplaceProblem::assemble_rhs()</h4>
 *
 *
 *
 * The final function in this triptych assembles the right-hand side vector
 * for the matrix-free method
 *
 * -- because in the matrix-free framework, we don't have to assemble the
 * matrix and can get away with only assembling the right hand side. We could
 * do this by extracting the code from the `assemble_system()` function above
 * that deals with the right hand side, but we decide instead to go all in on
 * the matrix-free approach and do the assembly using that way as well.
 *
 *
 *
 * The result is a function that is similar to the one found in the "Use
 * FEEvaluation::read_dof_values_plain() to avoid resolving constraints"
 * subsection in the "Possibilities for extensions" section of step-37.
 *
 *
 *
 * The reason for this function is that the MatrixFree operators do not take
 * into account non-homogeneous Dirichlet constraints, instead treating all
 * Dirichlet constraints as homogeneous. To account for this, the right-hand
 * side here is assembled as the residual $  r_0 = f-Au_0  $, where $  u_0  $
 * is a zero vector except in the Dirichlet values. Then when solving, we have
 * that the solution is $  u = u_0 + A^{-1}r_0  $. This can be seen as a
 * Newton iteration on a linear system with initial guess $  u_0  $. The CG
 * solve in the `solve()` function below computes $  A^{-1}r_0  $ and the call
 * to `constraints.distribute()` (which directly follows) adds the $  u_0  $.
 *
 *
 *
 * Obviously, since we are considering a problem with zero Dirichlet boundary,
 * we could have taken a similar approach to step-37 `assemble_rhs()`, but
 * this additional work allows us to change the problem declaration if we so
 * choose.
 *
 *
 *
 * This function has two parts in the integration loop: applying the negative
 * of matrix $  A  $ to $  u_0  $ by submitting the negative of the gradient,
 * and adding the right-hand side contribution by submitting the value $  f
 * $. We must be sure to use `read_dof_values_plain()` for evaluating $  u_0
 * $ as `read_dof_vaues()` would set all Dirichlet values to zero.
 *
 *
 *
 * Finally, the system_rhs vector is of type LA::MPI::Vector, but the
 * MatrixFree class only work for dealii::LinearAlgebra::distributed::Vector.
 * Therefore we must compute the right-hand side using MatrixFree
 * functionality and then use the functions in the `ChangeVectorType`
 * namespace to copy it to the correct type.
 *
 *
 *
 * @code
 * template <int dim, int degree>
 * void LaplaceProblem<dim, degree>::assemble_rhs()
 * {
 * TimerOutput::Scope timing(computing_timer, "Assemble right-hand side");
 *
 * MatrixFreeActiveVector solution_copy;
 * MatrixFreeActiveVector right_hand_side_copy;
 * mf_system_matrix.initialize_dof_vector(solution_copy);
 * mf_system_matrix.initialize_dof_vector(right_hand_side_copy);
 *
 * solution_copy = 0.;
 * constraints.distribute(solution_copy);
 * solution_copy.update_ghost_values();
 * right_hand_side_copy = 0;
 * const Table<2, VectorizedArray<double>> &coefficient =
 *  (mf_system_matrix.get_coefficient());
 *
 * RightHandSide<dim> right_hand_side_function;
 *
 * FEEvaluation<dim, degree, degree + 1, 1, double> phi(
 *  mf_system_matrix.get_matrix_free());
 *
 * for (unsigned int cell = 0;
 *      cell < mf_system_matrix.get_matrix_free()->n_cell_batches();
 *      ++cell)
 *   {
 *     phi.reinit(cell);
 *     phi.read_dof_values_plain(solution_copy);
 *     phi.evaluate(EvaluationFlags::gradients);
 *
 *     for (unsigned int q = 0; q < phi.n_q_points; ++q)
 *       {
 *         phi.submit_gradient(-1.0
 *                               (coefficient(cell, 0) phi.get_gradient(q)),
 *                             q);
 *         phi.submit_value(
 *           right_hand_side_function.value(phi.quadrature_point(q)), q);
 *       }
 *
 *     phi.integrate_scatter(EvaluationFlags::values |
 *                             EvaluationFlags::gradients,
 *                           right_hand_side_copy);
 *   }
 *
 * right_hand_side_copy.compress(VectorOperation::add);
 *
 * ChangeVectorTypes::copy(right_hand_side, right_hand_side_copy);
 * }
 *
 *
 *
 * @endcode
 *
 *
 *  <a name="LaplaceProblemsolve"></a> <h4>LaplaceProblem::solve()</h4>
 *
 *
 *
 * Here we set up the multigrid preconditioner, test the timing of a single
 * V-cycle, and solve the linear system. Unsurprisingly, this is one of the
 * places where the three methods differ the most.
 *
 *
 *
 * @code
 * template <int dim, int degree>
 * void LaplaceProblem<dim, degree>::solve()
 * {
 * TimerOutput::Scope timing(computing_timer, "Solve");
 *
 * SolverControl solver_control(1000, 1.e-10 right_hand_side.l2_norm());
 * solver_control.enable_history_data();
 *
 * solution = 0.;
 *
 * @endcode
 *
 *
 * The solver for the matrix-free GMG method is similar to step-37, apart from
 * adding some interface matrices in complete analogy to step-16.
 *
 *
 *
 * @code
 * switch (settings.solver)
 *   {
 *     case Settings::gmg_mf:
 *       {
 *         computing_timer.enter_subsection("Solve: Preconditioner setup");
 *
 *         MGTransferMatrixFree<dim, float> mg_transfer(mg_constrained_dofs);
 *         mg_transfer.build(dof_handler);
 *
 *         SolverControl coarse_solver_control(1000, 1e-12, false, false);
 *         SolverCG<MatrixFreeLevelVector> coarse_solver(coarse_solver_control);
 *         PreconditionIdentity            identity;
 *         MGCoarseGridIterativeSolver<MatrixFreeLevelVector,
 *                                     SolverCG<MatrixFreeLevelVector>,
 *                                     MatrixFreeLevelMatrix,
 *                                     PreconditionIdentity>
 *           coarse_grid_solver(coarse_solver, mf_mg_matrix[0], identity);
 *
 *         using Smoother = dealii::PreconditionJacobi<MatrixFreeLevelMatrix>;
 *         MGSmootherPrecondition<MatrixFreeLevelMatrix,
 *                                Smoother,
 *                                MatrixFreeLevelVector>
 *           smoother;
 *         smoother.initialize(mf_mg_matrix,
 *                             typename Smoother::AdditionalData(
 *                               settings.smoother_dampen));
 *         smoother.set_steps(settings.smoother_steps);
 *
 *         mg::Matrix<MatrixFreeLevelVector> mg_m(mf_mg_matrix);
 *
 *         MGLevelObject<
 *           MatrixFreeOperators::MGInterfaceOperator<MatrixFreeLevelMatrix>>
 *           mg_interface_matrices;
 *         mg_interface_matrices.resize(0, triangulation.n_global_levels()
 *
 * - 1);
 *         for (unsigned int level = 0; level < triangulation.n_global_levels();
 *              ++level)
 *           mg_interface_matrices[level].initialize(mf_mg_matrix[level]);
 *         mg::Matrix<MatrixFreeLevelVector> mg_interface(mg_interface_matrices);
 *
 *         Multigrid<MatrixFreeLevelVector> mg(
 *           mg_m, coarse_grid_solver, mg_transfer, smoother, smoother);
 *         mg.set_edge_matrices(mg_interface, mg_interface);
 *
 *         PreconditionMG<dim,
 *                        MatrixFreeLevelVector,
 *                        MGTransferMatrixFree<dim, float>>
 *           preconditioner(dof_handler, mg, mg_transfer);
 *
 * @endcode
 *
 *
 * Copy the solution vector and right-hand side from LA::MPI::Vector to
 * dealii::LinearAlgebra::distributed::Vector so that we can solve.
 *
 *
 *
 * @code
 *         MatrixFreeActiveVector solution_copy;
 *         MatrixFreeActiveVector right_hand_side_copy;
 *         mf_system_matrix.initialize_dof_vector(solution_copy);
 *         mf_system_matrix.initialize_dof_vector(right_hand_side_copy);
 *
 *         ChangeVectorTypes::copy(solution_copy, solution);
 *         ChangeVectorTypes::copy(right_hand_side_copy, right_hand_side);
 *         computing_timer.leave_subsection("Solve: Preconditioner setup");
 *
 * @endcode
 *
 *
 * Timing for 1 V-cycle.
 *
 *
 *
 * @code
 *         {
 *           TimerOutput::Scope timing(computing_timer,
 *                                     "Solve: 1 multigrid V-cycle");
 *           preconditioner.vmult(solution_copy, right_hand_side_copy);
 *         }
 *         solution_copy = 0.;
 *
 * @endcode
 *
 *
 * Solve the linear system, update the ghost values of the solution, copy back
 * to LA::MPI::Vector and distribute constraints.
 *
 *
 *
 * @code
 *         {
 *           SolverCG<MatrixFreeActiveVector> solver(solver_control);
 *
 *           TimerOutput::Scope timing(computing_timer, "Solve: CG");
 *           solver.solve(mf_system_matrix,
 *                        solution_copy,
 *                        right_hand_side_copy,
 *                        preconditioner);
 *         }
 *
 *         solution_copy.update_ghost_values();
 *         ChangeVectorTypes::copy(solution, solution_copy);
 *         constraints.distribute(solution);
 *
 *         break;
 *       }
 *
 * @endcode
 *
 *
 * Solver for the matrix-based GMG method, similar to step-16, only using a
 * Jacobi smoother instead of a SOR smoother (which is not implemented in
 * parallel).
 *
 *
 *
 * @code
 *     case Settings::gmg_mb:
 *       {
 *         computing_timer.enter_subsection("Solve: Preconditioner setup");
 *
 *         MGTransferPrebuilt<VectorType> mg_transfer(mg_constrained_dofs);
 *         mg_transfer.build(dof_handler);
 *
 *         SolverControl        coarse_solver_control(1000, 1e-12, false, false);
 *         SolverCG<VectorType> coarse_solver(coarse_solver_control);
 *         PreconditionIdentity identity;
 *         MGCoarseGridIterativeSolver<VectorType,
 *                                     SolverCG<VectorType>,
 *                                     MatrixType,
 *                                     PreconditionIdentity>
 *           coarse_grid_solver(coarse_solver, mg_matrix[0], identity);
 *
 *         using Smoother = LA::MPI::PreconditionJacobi;
 *         MGSmootherPrecondition<MatrixType, Smoother, VectorType> smoother;
 *
 * #ifdef USE_PETSC_LA
 *         smoother.initialize(mg_matrix);
 *         Assert(
 *           settings.smoother_dampen == 1.0,
 *           ExcNotImplemented(
 *             "PETSc's PreconditionJacobi has no support for a damping parameter."));
 * #else
 *         smoother.initialize(mg_matrix, settings.smoother_dampen);
 * #endif
 *
 *         smoother.set_steps(settings.smoother_steps);
 *
 *         mg::Matrix<VectorType> mg_m(mg_matrix);
 *         mg::Matrix<VectorType> mg_in(mg_interface_in);
 *         mg::Matrix<VectorType> mg_out(mg_interface_in);
 *
 *         Multigrid<VectorType> mg(
 *           mg_m, coarse_grid_solver, mg_transfer, smoother, smoother);
 *         mg.set_edge_matrices(mg_out, mg_in);
 *
 *
 *         PreconditionMG<dim, VectorType, MGTransferPrebuilt<VectorType>>
 *           preconditioner(dof_handler, mg, mg_transfer);
 *
 *         computing_timer.leave_subsection("Solve: Preconditioner setup");
 *
 * @endcode
 *
 *
 * Timing for 1 V-cycle.
 *
 *
 *
 * @code
 *         {
 *           TimerOutput::Scope timing(computing_timer,
 *                                     "Solve: 1 multigrid V-cycle");
 *           preconditioner.vmult(solution, right_hand_side);
 *         }
 *         solution = 0.;
 *
 * @endcode
 *
 *
 * Solve the linear system and distribute constraints.
 *
 *
 *
 * @code
 *         {
 *           SolverCG<VectorType> solver(solver_control);
 *
 *           TimerOutput::Scope timing(computing_timer, "Solve: CG");
 *           solver.solve(system_matrix,
 *                        solution,
 *                        right_hand_side,
 *                        preconditioner);
 *         }
 *
 *         constraints.distribute(solution);
 *
 *         break;
 *       }
 *
 * @endcode
 *
 *
 * Solver for the AMG method, similar to step-40.
 *
 *
 *
 * @code
 *     case Settings::amg:
 *       {
 *         computing_timer.enter_subsection("Solve: Preconditioner setup");
 *
 *         PreconditionAMG                 preconditioner;
 *         PreconditionAMG::AdditionalData Amg_data;
 *
 * #ifdef USE_PETSC_LA
 *         Amg_data.symmetric_operator = true;
 * #else
 *         Amg_data.elliptic              = true;
 *         Amg_data.smoother_type         = "Jacobi";
 *         Amg_data.higher_order_elements = true;
 *         Amg_data.smoother_sweeps       = settings.smoother_steps;
 *         Amg_data.aggregation_threshold = 0.02;
 * #endif
 *
 *         Amg_data.output_details = false;
 *
 *         preconditioner.initialize(system_matrix, Amg_data);
 *         computing_timer.leave_subsection("Solve: Preconditioner setup");
 *
 * @endcode
 *
 *
 * Timing for 1 V-cycle.
 *
 *
 *
 * @code
 *         {
 *           TimerOutput::Scope timing(computing_timer,
 *                                     "Solve: 1 multigrid V-cycle");
 *           preconditioner.vmult(solution, right_hand_side);
 *         }
 *         solution = 0.;
 *
 * @endcode
 *
 *
 * Solve the linear system and distribute constraints.
 *
 *
 *
 * @code
 *         {
 *           SolverCG<VectorType> solver(solver_control);
 *
 *           TimerOutput::Scope timing(computing_timer, "Solve: CG");
 *           solver.solve(system_matrix,
 *                        solution,
 *                        right_hand_side,
 *                        preconditioner);
 *         }
 *         constraints.distribute(solution);
 *
 *         break;
 *       }
 *
 *     default:
 *       Assert(false, ExcInternalError());
 *   }
 *
 * pcout << "   Number of CG iterations:      " << solver_control.last_step()
 *       << std::endl;
 * }
 *
 *
 * @endcode
 *
 *
 *  <a name="Theerrorestimator"></a> <h3>The error estimator</h3>
 *
 *
 *
 * We use the FEInterfaceValues class to assemble an error estimator to decide
 * which cells to refine. See the exact definition of the cell and face
 * integrals in the introduction. To use the method, we define Scratch and
 * Copy objects for the MeshWorker::mesh_loop() with much of the following
 * code being in essence as was set up in step-12 already (or at least similar
 * in spirit).
 *
 *
 *
 * @code
 * template <int dim>
 * struct ScratchData
 * {
 * ScratchData(const Mapping<dim> &      mapping,
 *             const FiniteElement<dim> &fe,
 *             const unsigned int        quadrature_degree,
 *             const UpdateFlags         update_flags,
 *             const UpdateFlags         interface_update_flags)
 *   : fe_values(mapping, fe, QGauss<dim>(quadrature_degree), update_flags)
 *   , fe_interface_values(mapping,
 *                         fe,
 *                         QGauss<dim
 *
 * - 1>(quadrature_degree),
 *                         interface_update_flags)
 * {}
 *
 *
 * ScratchData(const ScratchData<dim> &scratch_data)
 *   : fe_values(scratch_data.fe_values.get_mapping(),
 *               scratch_data.fe_values.get_fe(),
 *               scratch_data.fe_values.get_quadrature(),
 *               scratch_data.fe_values.get_update_flags())
 *   , fe_interface_values(scratch_data.fe_values.get_mapping(),
 *                         scratch_data.fe_values.get_fe(),
 *                         scratch_data.fe_interface_values.get_quadrature(),
 *                         scratch_data.fe_interface_values.get_update_flags())
 * {}
 *
 * FEValues<dim>          fe_values;
 * FEInterfaceValues<dim> fe_interface_values;
 * };
 *
 *
 *
 * struct CopyData
 * {
 * CopyData()
 *   : cell_index(numbers::invalid_unsigned_int)
 *   , value(0.)
 * {}
 *
 * CopyData(const CopyData &) = default;
 *
 * struct FaceData
 * {
 *   unsigned int cell_indices[2];
 *   double       values[2];
 * };
 *
 * unsigned int          cell_index;
 * double                value;
 * std::vector<FaceData> face_data;
 * };
 *
 *
 * template <int dim, int degree>
 * void LaplaceProblem<dim, degree>::estimate()
 * {
 * TimerOutput::Scope timing(computing_timer, "Estimate");
 *
 * VectorType temp_solution;
 * temp_solution.reinit(locally_owned_dofs,
 *                      locally_relevant_dofs,
 *                      mpi_communicator);
 * temp_solution = solution;
 *
 * const Coefficient<dim> coefficient;
 *
 * estimated_error_square_per_cell.reinit(triangulation.n_active_cells());
 *
 * using Iterator = typename DoFHandler<dim>::active_cell_iterator;
 *
 * @endcode
 *
 *
 * Assembler for cell residual $  h^2 \| f + \epsilon \triangle u \|_K^2  $
 *
 *
 *
 * @code
 * auto cell_worker = [&](const Iterator &  cell,
 *                        ScratchData<dim> &scratch_data,
 *                        CopyData &        copy_data) {
 *   FEValues<dim> &fe_values = scratch_data.fe_values;
 *   fe_values.reinit(cell);
 *
 *   RightHandSide<dim> rhs;
 *   const double       rhs_value = rhs.value(cell->center());
 *
 *   const double nu = coefficient.value(cell->center());
 *
 *   std::vector<Tensor<2, dim>> hessians(fe_values.n_quadrature_points);
 *   fe_values.get_function_hessians(temp_solution, hessians);
 *
 *   copy_data.cell_index = cell->active_cell_index();
 *
 *   double residual_norm_square = 0.;
 *   for (unsigned k = 0; k < fe_values.n_quadrature_points; ++k)
 *     {
 *       const double residual = (rhs_value + nu trace(hessians[k]));
 *       residual_norm_square += residual residual fe_values.JxW(k);
 *     }
 *
 *   copy_data.value =
 *     cell->diameter() cell->diameter() residual_norm_square;
 * };
 *
 * @endcode
 *
 *
 * Assembler for face term $  \sum_F h_F \| jump{\epsilon \nabla u \cdot n}.\|
 * $
 *
 *
 *
 * @code
 * auto face_worker = [&](const Iterator &    cell,
 *                        const unsigned int &f,
 *                        const unsigned int &sf,
 *                        const Iterator &    ncell,
 *                        const unsigned int &nf,
 *                        const unsigned int &nsf,
 *                        ScratchData<dim> &  scratch_data,
 *                        CopyData &          copy_data) {
 *   FEInterfaceValues<dim> &fe_interface_values =
 *     scratch_data.fe_interface_values;
 *   fe_interface_values.reinit(cell, f, sf, ncell, nf, nsf);
 *
 *   copy_data.face_data.emplace_back();
 *   CopyData::FaceData &copy_data_face = copy_data.face_data.back();
 *
 *   copy_data_face.cell_indices[0] = cell->active_cell_index();
 *   copy_data_face.cell_indices[1] = ncell->active_cell_index();
 *
 *   const double coeff1 = coefficient.value(cell->center());
 *   const double coeff2 = coefficient.value(ncell->center());
 *
 *   std::vector<Tensor<1, dim>> grad_u[2];
 *
 *   for (unsigned int i = 0; i < 2; ++i)
 *     {
 *       grad_u[i].resize(fe_interface_values.n_quadrature_points);
 *       fe_interface_values.get_fe_face_values(i).get_function_gradients(
 *         temp_solution, grad_u[i]);
 *     }
 *
 *   double jump_norm_square = 0.;
 *
 *   for (unsigned int qpoint = 0;
 *        qpoint < fe_interface_values.n_quadrature_points;
 *        ++qpoint)
 *     {
 *       const double jump =
 *         coeff1 grad_u[0][qpoint] fe_interface_values.normal(qpoint)
 *
 * -
 *         coeff2 grad_u[1][qpoint] fe_interface_values.normal(qpoint);
 *
 *       jump_norm_square += jump jump fe_interface_values.JxW(qpoint);
 *     }
 *
 *   const double h           = cell->face(f)->measure();
 *   copy_data_face.values[0] = 0.5 h jump_norm_square;
 *   copy_data_face.values[1] = copy_data_face.values[0];
 * };
 *
 * auto copier = [&](const CopyData &copy_data) {
 *   if (copy_data.cell_index != numbers::invalid_unsigned_int)
 *     estimated_error_square_per_cell[copy_data.cell_index] += copy_data.value;
 *
 *   for (auto &cdf : copy_data.face_data)
 *     for (unsigned int j = 0; j < 2; ++j)
 *       estimated_error_square_per_cell[cdf.cell_indices[j]] += cdf.values[j];
 * };
 *
 * const unsigned int n_gauss_points = degree + 1;
 * ScratchData<dim>   scratch_data(mapping,
 *                               fe,
 *                               n_gauss_points,
 *                               update_hessians | update_quadrature_points |
 *                                 update_JxW_values,
 *                               update_values | update_gradients |
 *                                 update_JxW_values | update_normal_vectors);
 * CopyData           copy_data;
 *
 * @endcode
 *
 *
 * We need to assemble each interior face once but we need to make sure that
 * both processes assemble the face term between a locally owned and a ghost
 * cell. This is achieved by setting the MeshWorker::assemble_ghost_faces_both
 * flag. We need to do this, because we do not communicate the error estimator
 * contributions here.
 *
 *
 *
 * @code
 * MeshWorker::mesh_loop(dof_handler.begin_active(),
 *                       dof_handler.end(),
 *                       cell_worker,
 *                       copier,
 *                       scratch_data,
 *                       copy_data,
 *                       MeshWorker::assemble_own_cells |
 *                         MeshWorker::assemble_ghost_faces_both |
 *                         MeshWorker::assemble_own_interior_faces_once,
 *                        [4.x.7] nullptr,
 *                       face_worker);
 *
 * const double global_error_estimate =
 *   std::sqrt(Utilities::MPI::sum(estimated_error_square_per_cell.l1_norm(),
 *                                 mpi_communicator));
 * pcout << "   Global error estimate:        " << global_error_estimate
 *       << std::endl;
 * }
 *
 *
 * @endcode
 *
 *
 *  <a name="LaplaceProblemrefine_grid"></a>
 * <h4>LaplaceProblem::refine_grid()</h4>
 *
 *
 *
 * We use the cell-wise estimator stored in the vector @p estimate_vector and
 * refine a fixed number of cells (chosen here to roughly double the number of
 * DoFs in each step).
 *
 *
 *
 * @code
 * template <int dim, int degree>
 * void LaplaceProblem<dim, degree>::refine_grid()
 * {
 * TimerOutput::Scope timing(computing_timer, "Refine grid");
 *
 * const double refinement_fraction = 1. / (std::pow(2.0, dim)
 *
 * - 1.);
 * parallel::distributed::GridRefinement::refine_and_coarsen_fixed_number(
 *   triangulation, estimated_error_square_per_cell, refinement_fraction, 0.0);
 *
 * triangulation.execute_coarsening_and_refinement();
 * }
 *
 *
 * @endcode
 *
 *
 *  <a name="LaplaceProblemoutput_results"></a>
 * <h4>LaplaceProblem::output_results()</h4>
 *
 *
 *
 * The output_results() function is similar to the ones found in many of the
 * tutorials (see step-40 for example).
 *
 *
 *
 * @code
 * template <int dim, int degree>
 * void LaplaceProblem<dim, degree>::output_results(const unsigned int cycle)
 * {
 * TimerOutput::Scope timing(computing_timer, "Output results");
 *
 * VectorType temp_solution;
 * temp_solution.reinit(locally_owned_dofs,
 *                      locally_relevant_dofs,
 *                      mpi_communicator);
 * temp_solution = solution;
 *
 * DataOut<dim> data_out;
 * data_out.attach_dof_handler(dof_handler);
 * data_out.add_data_vector(temp_solution, "solution");
 *
 * Vector<float> subdomain(triangulation.n_active_cells());
 * for (unsigned int i = 0; i < subdomain.size(); ++i)
 *   subdomain(i) = triangulation.locally_owned_subdomain();
 * data_out.add_data_vector(subdomain, "subdomain");
 *
 * Vector<float> level(triangulation.n_active_cells());
 * for (const auto &cell : triangulation.active_cell_iterators())
 *   level(cell->active_cell_index()) = cell->level();
 * data_out.add_data_vector(level, "level");
 *
 * if (estimated_error_square_per_cell.size() > 0)
 *   data_out.add_data_vector(estimated_error_square_per_cell,
 *                            "estimated_error_square_per_cell");
 *
 * data_out.build_patches();
 *
 * const std::string pvtu_filename = data_out.write_vtu_with_pvtu_record(
 *   "", "solution", cycle, mpi_communicator, 2  [4.x.8] );
 *
 * pcout << "   Wrote " << pvtu_filename << std::endl;
 * }
 *
 *
 * @endcode
 *
 *
 *  <a name="LaplaceProblemrun"></a> <h4>LaplaceProblem::run()</h4>
 *
 *
 *
 * As in most tutorials, this function calls the various functions defined
 * above to setup, assemble, solve, and output the results.
 *
 *
 *
 * @code
 * template <int dim, int degree>
 * void LaplaceProblem<dim, degree>::run()
 * {
 * for (unsigned int cycle = 0; cycle < settings.n_steps; ++cycle)
 *   {
 *     pcout << "Cycle " << cycle << ':' << std::endl;
 *     if (cycle > 0)
 *       refine_grid();
 *
 *     pcout << "   Number of active cells:       "
 *           << triangulation.n_global_active_cells();
 *
 * @endcode
 *
 *
 * We only output level cell data for the GMG methods (same with DoF data
 * below). Note that the partition efficiency is irrelevant for AMG since the
 * level hierarchy is not distributed or used during the computation.
 *
 *
 *
 * @code
 *     if (settings.solver == Settings::gmg_mf ||
 *         settings.solver == Settings::gmg_mb)
 *       pcout << " (" << triangulation.n_global_levels() << " global levels)"
 *             << std::endl
 *             << "   Partition efficiency:         "
 *             << 1.0 / MGTools::workload_imbalance(triangulation);
 *     pcout << std::endl;
 *
 *     setup_system();
 *
 * @endcode
 *
 *
 * Only set up the multilevel hierarchy for GMG.
 *
 *
 *
 * @code
 *     if (settings.solver == Settings::gmg_mf ||
 *         settings.solver == Settings::gmg_mb)
 *       setup_multigrid();
 *
 *     pcout << "   Number of degrees of freedom: " << dof_handler.n_dofs();
 *     if (settings.solver == Settings::gmg_mf ||
 *         settings.solver == Settings::gmg_mb)
 *       {
 *         pcout << " (by level: ";
 *         for (unsigned int level = 0; level < triangulation.n_global_levels();
 *              ++level)
 *           pcout << dof_handler.n_dofs(level)
 *                 << (level == triangulation.n_global_levels()
 *
 * - 1 ? ")" :
 *                                                                    ", ");
 *       }
 *     pcout << std::endl;
 *
 * @endcode
 *
 *
 * For the matrix-free method, we only assemble the right-hand side. For both
 * matrix-based methods, we assemble both active matrix and right-hand side,
 * and only assemble the multigrid matrices for matrix-based GMG.
 *
 *
 *
 * @code
 *     if (settings.solver == Settings::gmg_mf)
 *       assemble_rhs();
 *     else  [4.x.9]
 *       {
 *         assemble_system();
 *         if (settings.solver == Settings::gmg_mb)
 *           assemble_multigrid();
 *       }
 *
 *     solve();
 *     estimate();
 *
 *     if (settings.output)
 *       output_results(cycle);
 *
 *     computing_timer.print_summary();
 *     computing_timer.reset();
 *   }
 * }
 *
 *
 * @endcode
 *
 *
 *  <a name="Themainfunction"></a> <h3>The main() function</h3>
 *
 *
 *
 * This is a similar main function to step-40, with the exception that we
 * require the user to pass a .prm file as a sole command line argument (see
 * step-29 and the documentation of the ParameterHandler class for a complete
 * discussion of parameter files).
 *
 *
 *
 * @code
 * int main(int argc, charargv[])
 * {
 * using namespace dealii;
 * Utilities::MPI::MPI_InitFinalize mpi_initialization(argc, argv, 1);
 *
 * Settings settings;
 * if (!settings.try_parse((argc > 1) ? (argv[1]) : ""))
 *   return 0;
 *
 * try
 *   {
 *     constexpr unsigned int fe_degree = 2;
 *
 *     switch (settings.dimension)
 *       {
 *         case 2:
 *           {
 *             LaplaceProblem<2, fe_degree> test(settings);
 *             test.run();
 *
 *             break;
 *           }
 *
 *         case 3:
 *           {
 *             LaplaceProblem<3, fe_degree> test(settings);
 *             test.run();
 *
 *             break;
 *           }
 *
 *         default:
 *           Assert(false, ExcMessage("This program only works in 2d and 3d."));
 *       }
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
 *     MPI_Abort(MPI_COMM_WORLD, 1);
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
 *     MPI_Abort(MPI_COMM_WORLD, 2);
 *     return 1;
 *   }
 *
 * return 0;
 * }
 * @endcode
 *
 * <a name="Results"></a><h1>Results</h1>
 *
 *
 * When you run the program using the following command
 *
 * @code
 * mpirun
 *
 * -np 16 ./step-50  gmg_mf_2d.prm
 * @endcode
 *
 * the screen output should look like the following:
 *
 * @code
 * Cycle 0:
 * Number of active cells:       12 (2 global levels)
 * Partition efficiency:         0.1875
 * Number of degrees of freedom: 65 (by level: 21, 65)
 * Number of CG iterations:      10
 * Global error estimate:        0.355373
 * Wrote solution_00.pvtu
 *
 *
 *
 *
 * +---------------------------------------------+------------+------------+
 * | Total wallclock time elapsed since start    |    0.0163s |            |
 * |                                             |            |            |
 * | Section                         | no. calls |  wall time | % of total |
 * +---------------------------------+-----------+------------+------------+
 * | Assemble right-hand side        |         1 |  0.000374s |       2.3% |
 * | Estimate                        |         1 |  0.000724s |       4.4% |
 * | Output results                  |         1 |   0.00277s |        17% |
 * | Setup                           |         1 |   0.00225s |        14% |
 * | Setup multigrid                 |         1 |   0.00181s |        11% |
 * | Solve                           |         1 |   0.00364s |        22% |
 * | Solve: 1 multigrid V-cycle      |         1 |  0.000354s |       2.2% |
 * | Solve: CG                       |         1 |   0.00151s |       9.3% |
 * | Solve: Preconditioner setup     |         1 |   0.00125s |       7.7% |
 * +---------------------------------+-----------+------------+------------+
 *
 * Cycle 1:
 * Number of active cells:       24 (3 global levels)
 * Partition efficiency:         0.276786
 * Number of degrees of freedom: 139 (by level: 21, 65, 99)
 * Number of CG iterations:      10
 * Global error estimate:        0.216726
 * Wrote solution_01.pvtu
 *
 *
 *
 *
 * +---------------------------------------------+------------+------------+
 * | Total wallclock time elapsed since start    |    0.0169s |            |
 * |                                             |            |            |
 * | Section                         | no. calls |  wall time | % of total |
 * +---------------------------------+-----------+------------+------------+
 * | Assemble right-hand side        |         1 |  0.000309s |       1.8% |
 * | Estimate                        |         1 |   0.00156s |       9.2% |
 * | Output results                  |         1 |   0.00222s |        13% |
 * | Refine grid                     |         1 |   0.00278s |        16% |
 * | Setup                           |         1 |   0.00196s |        12% |
 * | Setup multigrid                 |         1 |    0.0023s |        14% |
 * | Solve                           |         1 |   0.00565s |        33% |
 * | Solve: 1 multigrid V-cycle      |         1 |  0.000349s |       2.1% |
 * | Solve: CG                       |         1 |   0.00285s |        17% |
 * | Solve: Preconditioner setup     |         1 |   0.00195s |        12% |
 * +---------------------------------+-----------+------------+------------+
 *
 * Cycle 2:
 * Number of active cells:       51 (4 global levels)
 * Partition efficiency:         0.41875
 * Number of degrees of freedom: 245 (by level: 21, 65, 225, 25)
 * Number of CG iterations:      11
 * Global error estimate:        0.112098
 * Wrote solution_02.pvtu
 *
 *
 *
 *
 * +---------------------------------------------+------------+------------+
 * | Total wallclock time elapsed since start    |    0.0183s |            |
 * |                                             |            |            |
 * | Section                         | no. calls |  wall time | % of total |
 * +---------------------------------+-----------+------------+------------+
 * | Assemble right-hand side        |         1 |  0.000274s |       1.5% |
 * | Estimate                        |         1 |   0.00127s |       6.9% |
 * | Output results                  |         1 |   0.00227s |        12% |
 * | Refine grid                     |         1 |    0.0024s |        13% |
 * | Setup                           |         1 |   0.00191s |        10% |
 * | Setup multigrid                 |         1 |   0.00295s |        16% |
 * | Solve                           |         1 |   0.00702s |        38% |
 * | Solve: 1 multigrid V-cycle      |         1 |  0.000398s |       2.2% |
 * | Solve: CG                       |         1 |   0.00376s |        21% |
 * | Solve: Preconditioner setup     |         1 |   0.00238s |        13% |
 * +---------------------------------+-----------+------------+------------+
 * .
 * .
 * .
 * @endcode
 *
 * Here, the timing of the `solve()` function is split up in 3 parts: setting
 * up the multigrid preconditioner, execution of a single multigrid V-cycle,
 * and the CG solver. The V-cycle that is timed is unnecessary for the overall
 * solve and only meant to give an insight at the different costs for AMG and
 * GMG. Also it should be noted that when using the AMG solver, "Workload
 * imbalance" is not included in the output since the hierarchy of coarse
 * meshes is not required.
 *
 * All results in this section are gathered on Intel Xeon Platinum 8280
 * (Cascade Lake) nodes which have 56 cores and 192GB per node and support
 * AVX-512 instructions, allowing for vectorization over 8 doubles
 * (vectorization used only in the matrix-free computations). The code is
 * compiled using gcc 7.1.0 with intel-mpi 17.0.3. Trilinos 12.10.1 is used
 * for the matrix-based GMG/AMG computations.
 *
 * We can then gather a variety of information by calling the program with the
 * input files that are provided in the directory in which step-50 is located.
 * Using these, and adjusting the number of mesh refinement steps, we can
 * produce information about how well the program scales.
 *
 * The following table gives weak scaling timings for this program on up to
 * 256M DoFs and 7,168 processors. (Recall that weak scaling keeps the number
 * of degrees of freedom per processor constant while increasing the number of
 * processors; i.e., it considers larger and larger problems.) Here, $
 * 矩阵{E}。 $ is the partition efficiency from the introduction (also
 * equal to 1.0/workload imbalance), "Setup" is a combination of setup, setup
 * multigrid, assemble, and assemble multigrid from the timing blocks, and
 * "Prec" is the preconditioner setup. Ideally all times would stay constant
 * over each problem size for the individual solvers, but since the partition
 * efficiency decreases from 0.371 to 0.161 from largest to smallest problem
 * size, we expect to see an approximately $  0.371/0.161=2.3  $ times
 * increase in timings for GMG. This is, in fact, pretty close to what we
 * really get:
 *
 * <table align="center" class="doxtable"> <tr> <th colspan="4"></th>
 * <th></th> <th colspan="4">MF-GMG</th> <th></th> <th colspan="4">MB-GMG</th>
 * <th></th> <th colspan="4">AMG</th> </tr> <tr> <th align="right">Procs</th>
 * <th align="right">Cycle</th> <th align="right">DoFs</th> <th
 * align="right">$  `mathbb{E}. $</th> <th></th> <th align="right">Setup</th>
 * <th align="right">Prec</th> <th align="right">Solve</th> <th
 * align="right">Total</th> <th></th> <th align="right">Setup</th> <th
 * align="right">Prec</th> <th align="right">Solve</th> <th
 * align="right">Total</th> <th></th> <th align="right">Setup</th> <th
 * align="right">Prec</th> <th align="right">Solve</th> <th
 * align="right">Total</th> </tr> <tr> <td align="right">112</th> <td
 * align="right">13</th> <td align="right">4M</th> <td align="right">0.37</th>
 * <td></td> <td align="right">0.742</th> <td align="right">0.393</th> <td
 * align="right">0.200</th> <td align="right">1.335</th> <td></td> <td
 * align="right">1.714</th> <td align="right">2.934</th> <td
 * align="right">0.716</th> <td align="right">5.364</th> <td></td> <td
 * align="right">1.544</th> <td align="right">0.456</th> <td
 * align="right">1.150</th> <td align="right">3.150</th> </tr> <tr> <td
 * align="right">448</th> <td align="right">15</th> <td align="right">16M</th>
 * <td align="right">0.29</th> <td></td> <td align="right">0.884</th> <td
 * align="right">0.535</th> <td align="right">0.253</th> <td
 * align="right">1.672</th> <td></td> <td align="right">1.927</th> <td
 * align="right">3.776</th> <td align="right">1.190</th> <td
 * align="right">6.893</th> <td></td> <td align="right">1.544</th> <td
 * align="right">0.456</th> <td align="right">1.150</th> <td
 * align="right">3.150</th> </tr> <tr> <td align="right">1,792</th> <td
 * align="right">17</th> <td align="right">65M</th> <td
 * align="right">0.22</th> <td></td> <td align="right">1.122</th> <td
 * align="right">0.686</th> <td align="right">0.309</th> <td
 * align="right">2.117</th> <td></td> <td align="right">2.171</th> <td
 * align="right">4.862</th> <td align="right">1.660</th> <td
 * align="right">8.693</th> <td></td> <td align="right">1.654</th> <td
 * align="right">0.546</th> <td align="right">1.460</th> <td
 * align="right">3.660</th> </tr> <tr> <td align="right">7,168</th> <td
 * align="right">19</th> <td align="right">256M</th> <td
 * align="right">0.16</th> <td></td> <td align="right">1.214</th> <td
 * align="right">0.893</th> <td align="right">0.521</th> <td
 * align="right">2.628</th> <td></td> <td align="right">2.386</th> <td
 * align="right">7.260</th> <td align="right">2.560</th> <td
 * align="right">12.206</th> <td></td> <td align="right">1.844</th> <td
 * align="right">1.010</th> <td align="right">1.890</th> <td
 * align="right">4.744</th> </tr> </table>
 *
 * On the other hand, the algebraic multigrid in the last set of columns is
 * relatively unaffected by the increasing imbalance of the mesh hierarchy
 * (because it doesn't use the mesh hierarchy) and the growth in time is
 * rather driven by other factors that are well documented in the literature
 * (most notably that the algorithmic complexity of some parts of algebraic
 * multigrid methods appears to be $ {cal O}(N\log N)  $ instead of $ {cal
 * O}(N)  $ for geometric multigrid).
 *
 * The upshort of the table above is that the matrix-free geometric multigrid
 * method appears to be the fastest approach to solving this equation if not
 * by a huge margin. Matrix-based methods, on the other hand, are consistently
 * the worst.
 *
 * The following figure provides strong scaling results for each method, i.e.,
 * we solve the same problem on more and more processors. Specifically, we
 * consider the problems after 16 mesh refinement cycles (32M DoFs) and 19
 * cycles (256M DoFs), on between 56 to 28,672 processors:
 *
 * <img width="600px"
 * src="https://www.dealii.org/images/steps/developer/step-50-strong-scaling.png"
 * alt="">
 *
 * While the matrix-based GMG solver and AMG scale similarly and have a
 * similar time to solution (at least as long as there is a substantial number
 * of unknowns per processor
 *
 * -- say, several 10,000), the matrix-free GMG solver scales much better and
 * solves the finer problem in roughly the same time as the AMG solver for the
 * coarser mesh with only an eighth of the number of processors. Conversely,
 * it can solve the same problem on the same number of processors in about one
 * eighth the time.
 *
 *
 * <a name="Possibilitiesforextensions"></a><h3> Possibilities for extensions
 * </h3>
 *
 *
 * <a name="Testingconvergenceandhigherorderelements"></a><h4> Testing
 * convergence and higher order elements </h4>
 *
 *
 * The finite element degree is currently hard-coded as 2, see the template
 * arguments of the main class. It is easy to change. To test, it would be
 * interesting to switch to a test problem with a reference solution. This
 * way, you can compare error rates.
 *
 * <a name="Coarsesolver"></a><h4> Coarse solver </h4>
 *
 *
 * A more interesting example would involve a more complicated coarse mesh
 * (see step-49 for inspiration). The issue in that case is that the coarsest
 * level of the mesh hierarchy is actually quite large, and one would have to
 * think about ways to solve the coarse level problem efficiently. (This is
 * not an issue for algebraic multigrid methods because they would just
 * continue to build coarser and coarser levels of the matrix, regardless of
 * their geometric origin.)
 *
 * In the program here, we simply solve the coarse level problem with a
 * Conjugate Gradient method without any preconditioner. That is acceptable if
 * the coarse problem is really small
 *
 * -- for example, if the coarse mesh had a single cell, then the coarse mesh
 * problems has a $  9\times 9  $ matrix in 2d, and a $  27\times 27  $ matrix
 * in 3d; for the coarse mesh we use on the $  L  $-shaped domain of the
 * current program, these sizes are $  21\times 21  $ in 2d and $  117\times
 * 117$ in
 * 3d.但是，如果粗网格由数百或数千个单元组成，这种方法将不再起作用，并可能开始主导每个V-cyle的整体运行时间。一个常见的方法是使用代数多网格预处理器解决粗网格问题；然而，这将需要组装粗矩阵（即使是无矩阵版本）作为AMG实现的输入。
 *
*<a name="PlainProg"></a><h1> The plain program</h1>  @include "step-50.cc"
 *
 */


