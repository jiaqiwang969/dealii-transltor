//include/deal.II-translator/A-tutorial/step-37_0.txt
/**
  @page step_37 The step-37 tutorial program  
* 本教程依赖于  step-16  ,  step-40  。
* @htmlonly
<table class="tutorial" width="50%">
<tr><th colspan="2"><b><small>Table of contents</small></b><b><small>Table of contents</small></b></th></tr>
<tr><td width="50%" valign="top">
<ol>
  <li> <a href="#Intro" class=bold>Introduction</a><a href="#Intro" class=bold>Introduction</a>
    <ul>
        <li><a href="#Thetestcase">The test case</a><a href="#Thetestcase">The test case</a>
        <li><a href="#Matrixvectorproductimplementation">Matrix-vector product implementation</a><a href="#Matrixvectorproductimplementation">Matrix-vector product implementation</a>
        <li><a href="#Combinationwithmultigrid">Combination with multigrid</a><a href="#Combinationwithmultigrid">Combination with multigrid</a>
        <li><a href="#UsingCPUdependentinstructionsvectorization">Using CPU-dependent instructions (vectorization)</a><a href="#UsingCPUdependentinstructionsvectorization">Using CPU-dependent instructions (vectorization)</a>
        <li><a href="#Runningmultigridonlargescaleparallelcomputers">Running multigrid on large-scale parallel computers</a><a href="#Runningmultigridonlargescaleparallelcomputers">Running multigrid on large-scale parallel computers</a>
    </ul>
  <li> <a href="#CommProg" class=bold>The commented program</a><a href="#CommProg" class=bold>The commented program</a>
    <ul>
        <li><a href="#Equationdata">Equation data</a><a href="#Equationdata">Equation data</a>
        <li><a href="#Matrixfreeimplementation">Matrix-free implementation</a><a href="#Matrixfreeimplementation">Matrix-free implementation</a>
      <ul>
        <li><a href="#Computationofcoefficient">Computation of coefficient</a><a href="#Computationofcoefficient">Computation of coefficient</a>
        <li><a href="#LocalevaluationofLaplaceoperator">Local evaluation of Laplace operator</a><a href="#LocalevaluationofLaplaceoperator">Local evaluation of Laplace operator</a>
      </ul>
        <li><a href="#LaplaceProblemclass">LaplaceProblem class</a><a href="#LaplaceProblemclass">LaplaceProblem class</a>
      <ul>
        <li><a href="#LaplaceProblemsetup_system">LaplaceProblem::setup_system</a><a href="#LaplaceProblemsetup_system">LaplaceProblem::setup_system</a>
        <li><a href="#LaplaceProblemassemble_rhs">LaplaceProblem::assemble_rhs</a><a href="#LaplaceProblemassemble_rhs">LaplaceProblem::assemble_rhs</a>
        <li><a href="#LaplaceProblemsolve">LaplaceProblem::solve</a><a href="#LaplaceProblemsolve">LaplaceProblem::solve</a>
        <li><a href="#LaplaceProblemoutput_results">LaplaceProblem::output_results</a> ]<a href="#LaplaceProblemoutput_results">LaplaceProblem::output_results</a>
        <li><a href="#LaplaceProblemrun">LaplaceProblem::run</a><a href="#LaplaceProblemrun">LaplaceProblem::run</a>
      </ul>
        <li><a href="#Thecodemaincodefunction">The <code>main</code> function</a><a href="#Thecodemaincodefunction">The <code>main</code> function</a>
      </ul>
</ol></td><td width="50%" valign="top"><ol>
  <li value="3"> <a href="#Results" class=bold>Results</a><a href="#Results" class=bold>Results</a>
    <ul>
        <li><a href="#Programoutput">Program output</a><a href="#Programoutput">Program output</a>
        <li><a href="#Comparisonwithasparsematrix">Comparison with a sparse matrix</a><a href="#Comparisonwithasparsematrix">Comparison with a sparse matrix</a>
        <li><a href="#ResultsforlargescaleparallelcomputationsonSuperMUC"> Results for large-scale parallel computations on SuperMUC</a><a href="#ResultsforlargescaleparallelcomputationsonSuperMUC"> Results for large-scale parallel computations on SuperMUC</a>
        <li><a href="#Adaptivity"> Adaptivity</a><a href="#Adaptivity"> Adaptivity</a>
        <li><a href="#Possibilitiesforextensions"> Possibilities for extensions</a><a href="#Possibilitiesforextensions"> Possibilities for extensions</a>
      <ul>
        <li><a href="#Kellyerrorestimator"> Kelly error estimator </a><a href="#Kellyerrorestimator"> Kelly error estimator </a>
        <li><a href="#Sharedmemoryparallelization"> Shared-memory parallelization</a><a href="#Sharedmemoryparallelization"> Shared-memory parallelization</a>
        <li><a href="#InhomogeneousDirichletboundaryconditions"> Inhomogeneous Dirichlet boundary conditions </a><a href="#InhomogeneousDirichletboundaryconditions"> Inhomogeneous Dirichlet boundary conditions </a>
      <ul>
        <li><a href="#UseFEEvaluationread_dof_values_plaintoavoidresolvingconstraints"> Use FEEvaluation::read_dof_values_plain() to avoid resolving constraints </a><a href="#UseFEEvaluationread_dof_values_plaintoavoidresolvingconstraints"> Use FEEvaluation::read_dof_values_plain() to avoid resolving constraints </a>
        <li><a href="#UseLaplaceOperatorwithasecondAffineConstraintsobjectwithoutDirichletconditions"> Use LaplaceOperator with a second AffineConstraints object without Dirichlet conditions </a><a href="#UseLaplaceOperatorwithasecondAffineConstraintsobjectwithoutDirichletconditions"> Use LaplaceOperator with a second AffineConstraints object without Dirichlet conditions </a>
    </ul>
    </ul>
    </ul>
  <li> <a href="#PlainProg" class=bold>The plain program</a><a href="#PlainProg" class=bold>The plain program</a>
</ol> </td> </tr> </table>
@endhtmlonly
*  <br>  
* <i>
This program was contributed by Katharina Kormann and Martin
Kronbichler.
* 
The algorithm for the matrix-vector product is based on the article <a
href="http://dx.doi.org/10.1016/j.compfluid.2012.04.012">A generic interface
for parallel cell-based finite element operator application</a><a
href="http://dx.doi.org/10.1016/j.compfluid.2012.04.012">A generic interface
for parallel cell-based finite element operator application</a> by Martin
Kronbichler and Katharina Kormann, Computers and Fluids 63:135&ndash;147,
2012, and the paper &quot;Parallel finite element operator application: Graph
partitioning and coloring&quot; by Katharina Kormann and Martin Kronbichler
in: Proceedings of the 7th IEEE International Conference on e-Science, 2011.
* 
This work was partly supported by the German Research Foundation (DFG) through
the project "High-order discontinuous Galerkin for the exa-scale" (ExaDG)
within the priority program "Software for Exascale Computing" (SPPEXA). The
large-scale computations shown in the results section of this tutorial program
were supported by Gauss Centre for Supercomputing e.V. (www.gauss-centre.eu)
by providing computing time on the GCS Supercomputer SuperMUC at Leibniz
Supercomputing Centre (LRZ, www.lrz.de) through project id pr83te. </i> 。
* <a name="Intro"></a><a name="Introduction"></a><h1>Introduction</h1> 。
 

* 这个例子展示了如何实现无矩阵方法，即不明确存储矩阵元素的方法，用于处理超立方体上系数可变的二阶Poissonequation。这个线性系统将用多网格方法来解决，并使用MPI的大规模并行性。
* 无矩阵方法的主要动机是，在今天的处理器上，对主内存的访问（即对不适合缓存的对象）已成为许多偏微分方程求解器的瓶颈。为了执行基于矩阵的矩阵-向量乘积，现代CPU花在等待数据从内存到达的时间远远多于实际进行浮点乘法和加法的时间。因此，如果我们可以通过重新计算矩阵元素，或者更确切地说，通过这些条目所代表的运算符，来替代在内存中查找矩阵元素，我们可能会在整体运行时间方面获胜，即使这需要大量额外的浮点运算。也就是说，用一个微不足道的实现来实现这一点是不够的，我们需要真正关注细节来获得性能。这个教程程序和上面提到的论文展示了如何实现这样一个方案，并展示了可以获得的速度提升。
* 

* <a name="Thetestcase"></a><h3>The test case</h3> 。
* 

* 在这个例子中，我们考虑泊松问题@f{eqnarray*}
* 
-
\nabla \cdot a(\mathbf x) \nabla u &=& 1, \\ u &=& 0 \quad \text{on}\
\partial \Omega @f}，其中 $a(\mathbf x)$ 是一个可变系数。下面，我们解释如何为这个问题实现矩阵-向量乘积而不明确形成矩阵。当然，对于其他方程也可以用类似的方法进行构造。
* 我们选择 $\Omega=[0,1]^3$ 和 $a(\mathbf x)=\frac{1}{0.05 +
2\|\mathbf x\|^2}$ 作为域。由于系数是围绕原点对称的，但域却不是，我们最终会得到一个非对称的解决方案。
* 

*<a name="Matrixvectorproductimplementation"></a><h3>Matrix-vector product implementation</h3> 。
* 

* 为了找出我们如何编写一个执行矩阵-向量乘积的代码，但不需要存储矩阵元素，让我们先看看一个有限元矩阵<i>A</i>是如何组装的：@f{eqnarray*}
A = \sum_{\mathrm{cell}=1}^{\mathrm{n\_cells}}
P_{\mathrm{cell,{loc-glob}}}^T A_{\mathrm{cell}} P_{\mathrm{cell,{loc-glob}}}.
@f} 。
* 在这个公式中，矩阵<i>P</i><sub>cell,loc-glob</sub>是一个矩形矩阵，定义了从当前单元的局部自由度到全局自由度的索引映射。可以建立这个运算器的信息通常被编码在 <code>local_dof_indices</code> 变量中，并被用于交易二中的汇编调用填充矩阵。这里，<i>A</i><sub>cell</sub>表示与<i>A</i>相关的单元矩阵。
* 如果我们要进行矩阵-向量乘积，我们可以因此使用@f{eqnarray*}
y &=& A\cdot u = \left(\sum_{\text{cell}=1}^{\mathrm{n\_cells}} P_\mathrm{cell,{loc-glob}}^T
A_\mathrm{cell} P_\mathrm{cell,{loc-glob}}\right) \cdot u
\\
&=& \sum_{\mathrm{cell}=1}^{\mathrm{n\_cells}} P_\mathrm{cell,{loc-glob}}^T
A_\mathrm{cell} u_\mathrm{cell}
\\
&=& \sum_{\mathrm{cell}=1}^{\mathrm{n\_cells}} P_\mathrm{cell,{loc-glob}}^T
v_\mathrm{cell},
@f}。
*其中<i>u</i><sub>cell</sub>是<i>u</i>在各个单元自由度上的值，<i>v</i><sub>cell</sub>=<i>A</i><sub>cell</sub><i>u</i><sub>cell</sub>相应地得到结果。因此一个天真的尝试来实现拉普拉斯的局部作用将使用以下代码。
* @code
Matrixfree<dim>::vmult (Vector<double>       &dst,
                        const Vector<double> &src) const
{
  dst = 0;
* 
  QGauss<dim>  quadrature_formula(fe.degree+1);
  FEValues<dim> fe_values (fe, quadrature_formula,
                           update_gradients | update_JxW_values|
                           update_quadrature_points);
* 
  const unsigned int   dofs_per_cell = fe.n_dofs_per_cell();
  const unsigned int   n_q_points    = quadrature_formula.size();
* 
  FullMatrix<double>   cell_matrix (dofs_per_cell, dofs_per_cell);
  Vector<double>       cell_src (dofs_per_cell),
                       cell_dst (dofs_per_cell);
  const Coefficient<dim> coefficient;
  std::vector<double> coefficient_values(n_q_points);
* 
  std::vector<unsigned int> local_dof_indices (dofs_per_cell);
* 
  for (const auto & cell : dof_handler.active_cell_iterators())
    {
      cell_matrix = 0;
      fe_values.reinit (cell);
      coefficient.value_list(fe_values.get_quadrature_points(),
                             coefficient_values);
* 
      for (unsigned int q=0; q<n_q_points; ++q)
        for (unsigned int i=0; i<dofs_per_cell; ++i)
          for (unsigned int j=0; j<dofs_per_cell; ++j)
            cell_matrix(i,j) += (fe_values.shape_grad(i,q)
                                 fe_values.shape_grad(j,q)
                                 fe_values.JxW(q)*
                                 coefficient_values[q]);
* 
      cell->get_dof_indices (local_dof_indices);
* 
      for (unsigned int i=0; i<dofs_per_cell; ++i)
        cell_src(i) = src(local_dof_indices(i));
* 
      cell_matrix.vmult (cell_dst, cell_src);
* 
      for (unsigned int i=0; i<dofs_per_cell; ++i)
        dst(local_dof_indices(i)) += cell_dst;
    }
}
@endcode
* 
* 这里我们忽略了边界条件以及我们可能拥有的任何悬空节点，尽管使用AffineConstraints类来包含这两者都不太困难。请注意，我们首先以常规方式生成局部矩阵，作为每个局部矩阵条目在所有正交点上的总和。为了形成上述公式中表达的实际乘积，我们提取了单元格相关自由度的 <code>src</code> 的值（<i>P</i>的作用 ]<sub>cell,loc-glob</sub>的作用），乘以局部矩阵（<i>A</i><sub>cell</sub>的作用），最后将结果加到目的向量 <code>dst</code> （<i>P</i><sub>cell,loc-glob</sub><sup>T</sup>的作用，在所有元素上相加）。原则上，这不会比这更难。
* 虽然这个代码是完全正确的，但它非常慢。对于每个单元，我们生成一个局部矩阵，这需要三个嵌套的循环，循环长度等于局部自由度的数量来计算。乘法本身是由两个嵌套循环完成的，这意味着它要便宜得多。
* 改善这个问题的一个方法是，从概念上讲，局部矩阵可以被认为是三个矩阵的乘积，@f{eqnarray*}
A_\mathrm{cell} = B_\mathrm{cell}^T D_\mathrm{cell} B_\mathrm{cell},
@f} 。
* 在拉普拉斯算子的例子中，<i>q</i>*dim+<i>d,i</i>)-<i>B</i><sub>cell</sub>的元素是由 <code>fe_values.shape_grad(i,q)[d]</code> 给出。这个矩阵由 <code>dim*n_q_points</code> 行和 @p dofs_per_cell 列组成。矩阵<i>D</i><sub>cell</sub>是对角线，包含 <code>fe_values.JxW(q) coefficient_values[q]</code> 的值（或者说， @p 这些值的二进制副本）。在工程文献中经常可以看到这种关于无限元素矩阵的表述。
* 当单元格矩阵被应用于一个矢量时，@f{eqnarray*}
A_\mathrm{cell}\cdot u_\mathrm{cell} = B_\mathrm{cell}^T
D_\mathrm{cell} B_\mathrm{cell} \cdot u_\mathrm{cell},
@f}。
* 那么，我们就不会形成矩阵与矩阵的乘积，而是每次将一个矩阵与一个向量从右到左相乘，这样就只形成三个连续的矩阵-向量乘积。这种方法消除了局部矩阵计算中的嵌套循环，从而将一个单元的工作复杂度从类似 $\mathcal
{O}(\mathrm{dofs\_per\_cell}^3)$ 降低到 $\mathcal
{O}(\mathrm{dofs\_per\_cell}^2)$  。对这一算法的解释是，我们首先将局部DoF上的值向量转换为正交点上的梯度向量。在第二个循环中，我们将这些梯度乘以积分权重和系数。第三次循环应用第二个梯度（转置形式），这样我们就得到了单元斗室上的（拉普拉斯）值矢量。
* 上述代码的瓶颈是对每一个 <code>cell</code> 调用 FEValues::reinit 所做的操作，其花费的时间与其他步骤加起来差不多（至少如果网格是非结构化的；deal.II可以识别梯度在结构化的网格上往往是不变的）。这当然不理想，我们希望能做得更好。该函数所做的是计算实空间的梯度，通过使用从实空间到参考单元的变形的Jacobian来转换参考单元上的梯度。这是对单元上的每个基函数和每个正交点进行的。雅各布系数并不取决于基函数，但它在不同的正交点上一般是不同的。如果你只建立一次矩阵，就像我们在之前的所有教程中所做的那样，没有什么需要优化的，因为 FEValues::reinit 需要在每个单元上调用。在这个过程中，转换是在计算本地矩阵元素时应用的。
* 然而，在一个无矩阵的实现中，我们会经常计算这些积分，因为迭代求解器在求解过程中会多次应用矩阵。因此，我们需要考虑是否能够缓存一些在运算器应用中被重用的数据，也就是积分计算。另一方面，我们意识到，我们不能缓存太多的数据，否则我们又会回到内存访问成为主导因素的情况。因此，我们不会在矩阵<i>B</i>中存储转换后的梯度，因为一般来说，对于曲线网格的每个基函数和每个元素上的每个正交点，它们都是不同的。
* 诀窍是去掉雅各布变换的因素，首先只在参考单元上应用梯度。这个操作将局部道夫上的数值矢量插值为正交点上的（单位坐标）梯度矢量。在这里，我们首先应用我们从梯度中分解出来的Jacobian，然后应用正交的权重，最后应用转置的Jacobian来准备第三个循环，通过单元格上的梯度来测试，并对正交点求和。
* 让我们再次以矩阵的形式来写。让矩阵<i>B</i><sub>cell</sub>表示与单元格相关的梯度矩阵，每一行都包含正交点的值。它由矩阵与矩阵的乘积构成@f{eqnarray*} B_\mathrm{cell} =
J_\mathrm{cell}^{-\mathrm T} B_\mathrm{ref\_cell}, @f}，其中<i>B</i><sub>ref_cell</sub>表示参考单元的梯度，<i>J</i> ]<sup>-T</sup><sub>cell</sub>表示从单元到实数单元转换的反转置Jacobian（在转换语言中，由<i>J</i><sup>-T</sup><sub>cell</sub>代表的操作为变数转换）。<i>J</i><sup>-T</sup><sub>cell</sub>是块对角线的，块的大小等于问题的维度。每个对角线区块都是雅各布变换，从定义单元到实际单元。
* 把事情放在一起，我们发现@f{eqnarray*}
A_\mathrm{cell} = B_\mathrm{cell}^T D B_\mathrm{cell}
                = B_\mathrm{ref\_cell}^T J_\mathrm{cell}^{-1}
                  D_\mathrm{cell}
                  J_\mathrm{cell}^{-\mathrm T} B_\mathrm{ref\_cell},
@f}。
* 所以我们计算积（从右边开始计算局部积）@f{eqnarray*}
v_\mathrm{cell} = B_\mathrm{ref\_cell}^T J_\mathrm{cell}^{-1} D J_\mathrm{cell}^{-\mathrm T}
B_\mathrm{ref\_cell} u_\mathrm{cell}, \quad
v = \sum_{\mathrm{cell}=1}^{\mathrm{n\_cells}} P_\mathrm{cell,{loc-glob}}^T
v_\mathrm{cell}.
@f} 。
* 
* @code
  FEValues<dim> fe_values_reference (fe, quadrature_formula,
                                     update_gradients);
  Triangulation<dim> reference_cell;
  GridGenerator::hyper_cube(reference_cell, 0., 1.);
  fe_values_reference.reinit (reference_cell.begin());
* 
  FEValues<dim> fe_values (fe, quadrature_formula,
                           update_inverse_jacobians | update_JxW_values |
                           update_quadrature_points);
* 
  for (const auto & cell : dof_handler.active_cell_iterators())
    {
      fe_values.reinit (cell);
      coefficient.value_list(fe_values.get_quadrature_points(),
                             coefficient_values);
* 
      cell->get_dof_indices (local_dof_indices);
* 
      for (unsigned int i=0; i<dofs_per_cell; ++i)
        cell_src(i) = src(local_dof_indices(i));
* 
      temp_vector = 0;
      for (unsigned int q=0; q<n_q_points; ++q)
        for (unsigned int d=0; d<dim; ++d)
          for (unsigned int i=0; i<dofs_per_cell; ++i)
            temp_vector(q*dim+d) +=
              fe_values_reference.shape_grad(i,q)[d] cell_src(i);
* 
      for (unsigned int q=0; q<n_q_points; ++q)
        {
          // apply the transposed inverse Jacobian of the mapping
          Tensor<1,dim> temp;
          for (unsigned int d=0; d<dim; ++d)
            temp[d] = temp_vector(q*dim+d);
          for (unsigned int d=0; d<dim; ++d)
            {
              double sum = 0;
              for (unsigned int e=0; e<dim; ++e)
                sum += fe_values.inverse_jacobian(q)[e][d]
                               temp[e];
              temp_vector(q*dim+d) = sum;
            }
* 
          // multiply by coefficient and integration weight
          for (unsigned int d=0; d<dim; ++d)
            temp_vector(q*dim+d)= fe_values.JxW(q) coefficient_values[q];
* 
          // apply the inverse Jacobian of the mapping
          for (unsigned int d=0; d<dim; ++d)
            temp[d] = temp_vector(q*dim+d);
          for (unsigned int d=0; d<dim; ++d)
            {
              double sum = 0;
              for (unsigned int e=0; e<dim; ++e)
                sum += fe_values.inverse_jacobian(q)[d][e]
                       temp[e];
              temp_vector(q*dim+d) = sum;
            }
        }
* 
      cell_dst = 0;
      for (unsigned int i=0; i<dofs_per_cell; ++i)
        for (unsigned int q=0; q<n_q_points; ++q)
          for (unsigned int d=0; d<dim; ++d)
            cell_dst(i) += fe_values_reference.shape_grad(i,q)[d]
                                   temp_vector(q*dim+d);
* 
      for (unsigned int i=0; i<dofs_per_cell; ++i)
        dst(local_dof_indices(i)) += cell_dst(i);
    }
}
@endcode
* 
* 注意我们是如何为参考单元格梯度创建一个额外的FEValues对象，以及如何将其初始化为参考单元格的。然后，实际的衍生数据由反转的雅各布矩阵来应用（deal.II将雅各布矩阵从实心单元到单位单元称为inverse_jacobian，因为前向转换是由单位单元到实心单元）。因子 $J_\mathrm{cell}^{-1} D_\mathrm{cell} J_\mathrm{cell}^{-\mathrm T}$ 是块对角线超过正交的。在这种形式下，人们意识到可变系数（可能通过张量表示）和一般的网格拓扑结构与雅各布变换对单元格导数的系数变换有类似的影响。
* 在这一点上，人们可能会想，为什么我们要分别存储矩阵 $J_\mathrm{cell}^{-\mathrm T}$ 和系数，而不是只存储完整的系数 $J_\mathrm{cell}^{-1} D_\mathrm{cell}
J_\mathrm{cell}^{-\mathrm T}$ 。后者将使用更少的内存，因为张量是对称的，在三维中具有六个独立的值，而对于前者，我们需要九个条目用于反转雅各布，一个用于正交权重和雅各布行列式，一个用于系数，总共是11个双数。原因是前者允许通过一个通用的缓存数据框架来实现通用的微分算子，而后者则专门存储拉普拉斯的系数。如果应用需要，这种特殊化可能会带来回报，值得考虑。请注意，deal.II的实现足够聪明，可以检测出笛卡尔或仿生几何，在这种情况下，Jacobian在整个单元中是恒定的，不需要为每个单元存储（实际上在不同的单元中也经常是一样的）。
* 从操作数的角度来看，最后一个最关键的优化是利用基函数中的张量积结构。这是可能的，因为我们将梯度从<i>B</i><sub>ref_cell</sub>描述的关系单元操作中剔除，即在关系单元的完全规则数据域上进行插值操作。我们举例说明在两个空间维度上降低复杂度的过程，但是同样的技术也可以用于更高的维度。在该单元上，基函数为张量积形式  $\phi(x,y,z) = \varphi_i(x) \varphi_j(y)$  。矩阵<i>B</i><sub>ref_cell</sub>计算第一分量的部分具有 $B_\mathrm{sub\_cell}^x = B_\mathrm{grad,x} \otimes B_\mathrm{val,y}$ 的形式，其中<i>B</i><sub>grad,x</sub>和<i>B</i><sub>val,y</sub>包含对所有一维正交点上所有一维基函数的评估。用含有基函数 $\varphi_i(x) \varphi_j(y)$ 所属系数的<i>U(j,i)</i>组成矩阵<i>U</i>，我们得到 $(B_\mathrm{grad,x} \otimes
B_\mathrm{val,y})u_\mathrm{cell} = B_\mathrm{val,y} U B_\mathrm{grad,x}$ 。这将计算这个乘积的复杂性从 $p^4$ 降低到 $2 p^3$ ，其中<i>p</i>-1是有限元的度数（即，相当于，<i>p</i>是每个坐标方向上的形状函数的数量），或者一般来说 $p^{2d}$  到 $d p^{d+1}$ 。我们之所以用多项式度数来看复杂度，是因为我们希望能够达到高度，并可能增加多项式度数<i>p</i>而不是网格分辨率。像这里所用的中等度数的好算法是独立于维度的多项式度数的线性算法，而不是基于矩阵的方案或通过FEValues的天真评估。在deal.II的实现中所使用的技术自20世纪80年代以来在谱元界已经建立。
* 实现一个无矩阵和基于单元的有限元算子需要与以前的教程程序中显示的通常的矩阵装配代码相比，有一些不同的程序设计。这样做的数据结构是MatrixFree类和FEEvaluation类，前者收集所有数据并对所有单元进行（并行）循环，后者利用张量积结构来评估有限元基函数。
* 本教程中显示的无矩阵的矩阵-向量乘积的实现比使用稀疏矩阵的线性元素的矩阵-向量乘积要慢，但由于张量乘积结构降低了复杂性，并且在计算过程中减少了内存转移，所以对所有高阶元素来说，速度更快。当在多核处理器上工作时，减少内存传输的影响尤其有利，因为在多核处理器上有多个处理单元共享内存的访问。在这种情况下，一个受计算约束的算法将显示出几乎完美的并行加速（除了可能通过涡轮模式改变处理器的时钟频率，取决于有多少个核心在工作），而一个受内存传输约束的算法可能无法实现类似的加速（即使当工作是完全并行的，我们可以期待完美的缩放，如在疏散矩阵-向量产品）。这种实现方式的另一个好处是，我们不必建立稀疏矩阵本身，这也可能是相当昂贵的，这取决于基础微分方程。此外，上述框架可以简单地推广到非线性运算，正如我们在 step-48 中演示的那样。
* 

* <a name="Combinationwithmultigrid"></a><h3>Combination with multigrid</h3> 。
* 

* 以上，我们花了很大的力气来实现一个不实际存储矩阵元素的矩阵-向量乘积。然而，在许多用户代码中，人们想要的不仅仅是做一些矩阵-向量乘积&mdash;在求解线性系统时，人们希望尽可能少做这些操作。理论上，我们可以使用CG方法，而不需要预处理；然而，这对拉普拉斯的效率并不高。相反，预处理是用来提高收敛速度的。不幸的是，大多数比较常用的预处理程序，如SSOR、ILU或代数多网格(AMG)不能在这里使用，因为它们的实现需要了解系统矩阵的元素。
* 一个解决方案是使用几何多网格方法，如 step-16 所示。它们是已知的非常快的方法，而且适合于我们的目的，因为所有的成分，包括不同网格层之间的转移，都可以用与细胞集合相关的矩阵-向量产品来表达。我们需要做的就是找到一个基于矩阵-向量乘积而不是所有矩阵条目的平滑器。一个这样的候选方法是阻尼雅可比迭代法，它需要访问矩阵对角线，但它在阻尼所有高频误差方面往往不够好。Jacobi方法的特性可以通过所谓的Chebyshev迭代进行几次改进。Chebyshev迭代是由矩阵-向量乘积的多项式表达式描述的，其中的系数可以被选择来实现某些特性，在这种情况下，可以平滑误差的高频分量，这些分量与雅可比预处理矩阵的特征值相关。在零度时，具有最佳阻尼参数的雅各布方法被检索出来，而高阶修正则用于改善平滑特性。切比雪夫平滑法在多网格中的有效性已经在文章<a href="http://www.sciencedirect.com/science/article/pii/S0021999103001943">
<i>M. Adams, M. Brezina, J. Hu, R. Tuminaro. Parallel multigrid smoothers:
polynomial versus Gauss&ndash;Seidel, J. Comput. Phys. 188:593&ndash;610,
2003</i><i>M. Adams, M. Brezina, J. Hu, R. Tuminaro. Parallel multigrid smoothers:
polynomial versus Gauss&ndash;Seidel, J. Comput. Phys. 188:593&ndash;610,
2003</i></a>中得到证明。这篇文章还指出了我们在这里利用的Chebyshev平滑器的另一个优势，即它们很容易并行化，而SOR/Gauss&ndash;Seidel平滑器则依赖于替换，对于这种替换，天真的并行化工作在矩阵的对角线子块上，从而降低了效率（更多细节见例如Y. Saad, IterativeMethods for Sparse Linear Systems, SIAM, 2nd edition, 2003, chapters 11 & 12）。
* 因此，在多网格框架中的实现是很简单的。本程序中的多网格实现与 step-16 类似，包括aptivity。
* 

*<a name="UsingCPUdependentinstructionsvectorization"></a><h3>Using CPU-dependent instructions (vectorization)</h3>。
* 

* FEEvaluation中用于评估的计算内核是以优化使用计算资源的方式编写的。为了达到这个目的，它们不对双倍数据类型进行操作，而是采用我们称之为VectorizedArray的东西（例如，查看 FEEvaluationBase::get_value, 的转向类型，该类型是针对恒定元素的VectorizedArray，以及针对向量有限元素的VectorizedArray的Tensor）。矢量数组是一个双数或浮点数的短数组，其长度取决于使用的特定计算机系统。例如，基于x86-64的系统支持流式SIMD扩展（SSE），处理器的矢量单元可以通过一条CPU指令处理两个双数（或四个单精度浮点）。较新的处理器（大约从2012年起）支持所谓的高级向量扩展（AVX），有256位操作数，可以分别使用四个双数和八个浮点数。矢量化是一个单指令/多数据（SIMD）的概念，也就是说，一条CPU指令被用来同时处理多个数据值。通常情况下，有限元程序不会明确使用矢量化，因为这个概念的好处只体现在算术密集型操作中。大部分典型的有限元工作负载的内存带宽有限（对稀疏矩阵和向量的操作），额外的计算能力是无用的。
* 在幕后，优化的BLAS包可能严重依赖矢量化。另外，优化的编译器可能会自动将涉及标准代码的循环转化为更有效的矢量化形式（deal.II在矢量更新的常规循环中使用OpenMP SIMD pragmas）。然而，数据流必须非常有规律，才能使编译器产生有效的代码。例如，受益于矢量化的原型操作的自动矢量化，即矩阵三乘法，在大多数编译器上都失败了（截至2012年初编写本教程和2016年底更新时，gcc和英特尔编译器都无法为 FullMatrix::mmult  ]函数，甚至在更简单的情况下也不行，即矩阵边界是编译时常量而不是 FullMatrix::mmult). 中的运行时常量。主要原因是在最内层循环（即应用矢量化的地方）要处理的信息不一定是矢量长度的倍数，留下部分资源没有使用。此外，有可能被一起处理的数据在内存中可能不是以连续的方式布置的，或者没有对准处理器需要的地址边界。或者编译器可能无法证明在一次加载几个元素时数据阵列不会重叠。
* 因此，在deal.II的无矩阵实现中，我们选择在最适合有限元计算的层次上应用矢量化。单元计算通常对所有单元完全相同（除了从向量读写时使用的间接寻址中的索引），因此可以使用SIMD来一次处理几个单元。在下面的所有内容中，你可以考虑用一个向量数组来存放几个单元的数据。记住，它与空间维度和元素数量无关，例如在张量或点中。
* 请注意，矢量化取决于代码运行的CPU，以及代码是为哪种CPU编译的。为了给你的计算机生成最快的FEEvaluation内核，你应该用所谓的<i>native</i>处理器变量编译deal.II。当使用gcc编译器时，可以通过在cmake构建设置中设置变量<tt>CMAKE_CXX_FLAGS</tt>为<tt>"-march=native"</tt>来启用它（在命令行中，指定<tt>-DCMAKE_CXX_FLAGS="-march=native"</tt>，更多信息见deal.II README）。其他编译器也有类似的选项。我们在本例的run()函数中输出当前的矢量化长度。
* 

* <a name="Runningmultigridonlargescaleparallelcomputers"></a><h3>Running multigrid on large-scale parallel computers</h3> 。
* 

* 如上所述，无矩阵框架中的所有组件都可以通过MPI使用域分解轻松并行化。由于在deal.II中通过p4est（详见 step-40 ）很容易获得大规模的并行网格，而且基于单元的无矩阵评估循环<i>only</i>需要将网格分解为每个处理器上大小基本相同的块，因此编写一个使用分布式内存的并行程序相对来说不需要做什么。当其他使用MPI的教程程序依赖于PETSc或Trilinos时，这个程序使用deal.II自己的并行向量设施。
* deal.II的并行向量类， LinearAlgebra::distributed::Vector, 持有解决方案的处理器本地部分，以及ghostedDoFs的数据字段，即由远程处理器拥有的DoFs，但由当前处理器拥有的单元访问。在 @ref GlossLocallyActiveDof 的 "词汇表 "中，这些自由度被称为本地活动自由度。函数 MatrixFree::initialize_dof_vector() 提供了一种设置这种设计的方法。请注意，悬挂节点可以与额外的托管自由度有关，这些自由度必须包括在分布式矢量中，但不属于 @ref
GlossLocallyActiveDof "词汇表 "意义上的本地活动自由度。此外，分布式向量持有本地拥有但其他处理器需要的DoF的MPI元数据。这个向量类设计的一个好处是对ghostedentries的访问方式。在向量的存储方案中，数据阵列延伸到解决方案的处理器本地部分之外，有更多的向量可用于重现自由度。这为所有本地活动自由度提供了一个连续的索引范围。(注意，索引范围取决于网格的具体配置。)由于无矩阵操作可以被认为是在做性能关键的线性代数，而性能关键的代码不能把时间浪费在做MPI全局到MPI局部的索引转换上，一个MPI等级的局部索引空间的可用性是很重要的。这里访问事物的方式是直接数组访问。这是通过 LinearAlgebra::distributed::Vector::local_element(), 提供的，但实际上很少需要，因为所有这些都发生在FEEvaluation的内部。
*  LinearAlgebra::distributed::Vector 的设计与我们之前在 step-40 和 step-32 中使用的 PETScWrappers::MPI::Vector 和 TrilinosWrappers::MPI::Vector 数据类型类似，但由于我们不需要这些库的任何其他并行功能，我们使用deal.II的 LinearAlgebra::distributed::Vector 类而不是在这个教程程序中链接另一个大型库。还要注意的是，PETSc和Trilinosvectors不提供对直接阵列访问的幽灵条目的细粒度控制，因为它们抽象出了必要的实现细节。
* 

* <a name="CommProg"></a> <h1> The commented program</h1>.
* 首先包括deal.II库中的必要文件。
* 

* 
* @code
 #include <deal.II/base/quadrature_lib.h>
 #include <deal.II/base/function.h>
 #include <deal.II/base/timer.h>
* 
 #include <deal.II/lac/affine_constraints.h>
 #include <deal.II/lac/solver_cg.h>
 #include <deal.II/lac/la_parallel_vector.h>
 #include <deal.II/lac/precondition.h>
* 
 #include <deal.II/fe/fe_q.h>
* 
 #include <deal.II/grid/tria.h>
 #include <deal.II/grid/grid_generator.h>
* 
 #include <deal.II/multigrid/multigrid.h>
 #include <deal.II/multigrid/mg_transfer_matrix_free.h>
 #include <deal.II/multigrid/mg_tools.h>
 #include <deal.II/multigrid/mg_coarse.h>
 #include <deal.II/multigrid/mg_smoother.h>
 #include <deal.II/multigrid/mg_matrix.h>
* 
 #include <deal.II/numerics/data_out.h>
 #include <deal.II/numerics/vector_tools.h>
* 
 @endcode
* 
* 这包括有效实现无矩阵方法的数据结构，或者用MatrixFree类的更通用的有限元算子。
* 

* 
* @code
 #include <deal.II/matrix_free/matrix_free.h>
 #include <deal.II/matrix_free/operators.h>
 #include <deal.II/matrix_free/fe_evaluation.h>
* 
 #include <iostream>
 #include <fstream>
* 
 
 namespace Step37
 {
   using namespace dealii;
* 
 
 @endcode
* 
* 为了高效，在无矩阵实现中进行的操作需要在编译时了解循环长度，这些长度是由有限元的度数给出的。因此，我们收集了两个模板参数的值，可以在代码中的一个地方改变。当然，我们可以把有限元的度数作为一个运行时的参数，通过编译所有可能的度数（比如，1到6之间）的计算核，并在运行时选择合适的核。在这里，我们只是选择二阶 $Q_2$ 元素，并选择维度3作为标准。
* 

* 
* @code
   const unsigned int degree_finite_element = 2;
   const unsigned int dimension             = 3;
* 
 
 @endcode
* 
* <a name="Equationdata"></a> <h3>Equation data</h3>。
 

* 
* 我们为泊松问题定义了一个可变系数函数。它与 step-5 中的函数类似，但我们使用的是 $a(\mathbf
 x)=\frac{1}{0.05 + 2\|\bf x\|^2}$ 的形式，而不是不连续的形式。这只是为了证明这种实现的可能性，而不是在物理上有什么意义。我们以与早期教程程序中的函数相同的方式定义系数。有一个新的函数，即一个带有模板参数 @p number. 的 @p value 方法 
* 

* 
* @code
   template <int dim>
   class Coefficient : public Function<dim>
   {
   public:
     virtual double value(const Point<dim> & p,
                          const unsigned int component = 0) const override;
* 
     template <typename number>
     number value(const Point<dim, number> &p,
                  const unsigned int        component = 0) const;
   };
* 
 
* 
 @endcode
* 
* 这就是上面提到的新函数。评估抽象类型 @p number. 的系数 它可能只是一个普通的双数，但它也可以是一个有点复杂的类型，我们称之为VectorizedArray。这种数据类型本质上是一个短的双数数组，正如在介绍中所讨论的那样，它可以容纳几个单元格的数据。例如，我们在这里评估的系数不是像通常那样在一个简单的点上，而是交给一个Point<dim,VectorizedArray<double>>点，在AVX的情况下，它实际上是四个点的集合。不要把VectorizedArray中的条目与点的不同坐标混淆。事实上，数据的布局是这样的： <code>p[0]</code> 返回一个VectorizedArray，它又包含了第一个点和第二个点的x坐标。你可以使用例如  <code>p[0][j]</code>  单独访问坐标，j=0,1,2,3，但建议尽可能地在VectorizedArray上定义操作，以便利用矢量操作。  
* 在函数的实现中，我们假设数字类型重载了基本的算术运算，所以我们只需照常写代码。然后，基类函数 @p value 是由双倍类型的模板函数计算出来的，以避免重复的代码。
* 

* 
* @code
   template <int dim>
   template <typename number>
   number Coefficient<dim>::value(const Point<dim, number> &p,
                                  const unsigned int  /*component*/ ) const
   {
     return 1. / (0.05 + 2. p.square());
   }
* 
 
* 
   template <int dim>
   double Coefficient<dim>::value(const Point<dim> & p,
                                  const unsigned int component) const
   {
     return value<double>(p, component);
   }
* 
 
 @endcode
* 
* <a name="Matrixfreeimplementation"></a> <h3>Matrix-free implementation</h3>.
 

* 
* 下面这个名为 <code>LaplaceOperator</code> 的类，实现了微分运算符。就所有的实用目的而言，它是一个矩阵，也就是说，你可以向它询问它的大小（成员函数 <code>m(), n()</code> ），你可以将它应用于一个矢量（ <code>vmult()</code> 函数）。当然，与实数矩阵的区别在于，这个类实际上并不存储矩阵的<i>elements</i>，而只知道如何计算运算符应用于向量时的动作。  
* 描述矩阵大小、从MatrixFree对象初始化以及通过vmult()和Tvmult()方法实现矩阵-向量乘积的各种接口的基础结构，是由本类派生的 MatrixFreeOperator::Base 类提供的。这里定义的LaplaceOperator类只需要提供几个接口，即通过vmult()函数中使用的apply_add()方法来实现运算符的实际操作，以及计算底层矩阵对角线项的方法。我们需要对角线来定义多梯度平滑器。由于我们考虑的是一个具有可变系数的问题，我们进一步实现了一个可以填充系数值的方法。  
* 请注意，文件 <code>include/deal.II/matrix_free/operators.h</code> 已经包含了通过类 MatrixFreeOperators::LaplaceOperator. 实现拉普拉斯的方法。出于教育目的，在这个教程程序中重新实现了该运算符，解释了其中的成分和概念。  
* 本程序利用了集成在deal.II中的有限元算子应用的数据缓存。这个数据缓存类被称为MatrixFree。它包含局部和全局自由度之间的映射信息（Jacobian）和索引关系。它还包含约束条件，如来自悬挂节点或迪里切特边界条件的约束。此外，它可以在所有单元上以%并行方式发出一个循环，确保只有不共享任何自由度的单元被处理（这使得循环在写入目标向量时是线程安全的）。与 @ref threads 模块中描述的WorkStream类相比，这是一个更先进的策略。当然，为了不破坏线程安全，我们在写进类全局结构时必须小心。  
* 实现拉普拉斯算子的类有三个模板参数，一个是维度（正如许多deal.II类所携带的），一个是有限元的度数（我们需要通过FEEvaluation类实现高效计算），还有一个是底层标量类型。我们希望对最终矩阵使用 <code>double</code> 数字（即双精度，64位浮点），但对多网格级矩阵使用浮点数（单精度，32位浮点数字）（因为那只是一个预处理程序，而浮点数的处理速度是两倍）。FEEvaluation类也需要一个模板参数，用于确定一维正交点的数量。在下面的代码中，我们把它硬编码为  <code>fe_degree+1</code>  。如果我们想独立于多项式程度来改变它，我们需要添加一个模板参数，就像在  MatrixFreeOperators::LaplaceOperator  类中所做的那样。  
* 作为附带说明，如果我们在同一个网格和自由度上实现了几个不同的操作（比如质量矩阵和拉普拉斯矩阵），我们将为每个操作者定义两个像现在这样的类（源自 MatrixFreeOperators::Base 类），并让它们都引用一般问题类中的同一个MatrixFree数据缓存。通过 MatrixFreeOperators::Base 的接口要求我们只提供一组最小的函数。这个概念允许编写具有许多无矩阵操作的复杂应用代码。  
*  

* 
*  @note  储存类型 <code>VectorizedArray<number></code> 的值需要注意。在这里，我们使用deal.II表类，它准备以正确的对齐方式保存数据。然而，存储例如一个 <code>std::vector<VectorizedArray<number> ></code> 是不可能用矢量的。数据与内存地址的边界需要一定的对齐（基本上，在AVX情况下，一个32字节长的VectorizedArray需要从一个能被32整除的内存地址开始）。表类（以及它所基于的AlignedVector类）确保这种对齐方式得到尊重，而 std::vector 一般不这样做，这可能会导致一些系统在奇怪的地方出现分段故障，或者其他系统的性能不理想。
* 

* 
* @code
   template <int dim, int fe_degree, typename number>
   class LaplaceOperator
     : public MatrixFreeOperators::
         Base<dim, LinearAlgebra::distributed::Vector<number>>
   {
   public:
     using value_type = number;
* 
     LaplaceOperator();
* 
     void clear() override;
* 
     void evaluate_coefficient(const Coefficient<dim> &coefficient_function);
* 
     virtual void compute_diagonal() override;
* 
   private:
     virtual void apply_add(
       LinearAlgebra::distributed::Vector<number> &      dst,
       const LinearAlgebra::distributed::Vector<number> &src) const override;
* 
     void
     local_apply(const MatrixFree<dim, number> &                   data,
                 LinearAlgebra::distributed::Vector<number> &      dst,
                 const LinearAlgebra::distributed::Vector<number> &src,
                 const std::pair<unsigned int, unsigned int> &cell_range) const;
* 
     void local_compute_diagonal(
       const MatrixFree<dim, number> &              data,
       LinearAlgebra::distributed::Vector<number> & dst,
       const unsigned int &                         dummy,
       const std::pair<unsigned int, unsigned int> &cell_range) const;
* 
     Table<2, VectorizedArray<number>> coefficient;
   };
* 
 
* 
 @endcode
* 
* 这是 @p LaplaceOperator 类的构造函数。它所做的就是调用基类 MatrixFreeOperators::Base, 的默认构造函数，而基类又是基于Subscriptor类的，它断言这个类在超出范围后不会被访问，例如在一个预处理程序中。
* 

* 
* @code
   template <int dim, int fe_degree, typename number>
   LaplaceOperator<dim, fe_degree, number>::LaplaceOperator()
     : MatrixFreeOperators::Base<dim,
                                 LinearAlgebra::distributed::Vector<number>>()
   {}
* 
 
* 
   template <int dim, int fe_degree, typename number>
   void LaplaceOperator<dim, fe_degree, number>::clear()
   {
     coefficient.reinit(0, 0);
     MatrixFreeOperators::Base<dim, LinearAlgebra::distributed::Vector<number>>::
       clear();
   }
* 
 
* 
 @endcode
 
* <a name="Computationofcoefficient"></a> <h4>Computation of coefficient</h4> * * <h4>Computation of coefficient</h4>.
 

* 
* 为了初始化系数，我们直接赋予它上面定义的系数类，然后选择带有向量数的方法 <code>coefficient_function.value</code> （编译器可以从点数据类型中推断出来）。下面将解释FEEvaluation类（及其模板参数）的使用。
* 

* 
* @code
   template <int dim, int fe_degree, typename number>
   void LaplaceOperator<dim, fe_degree, number>::evaluate_coefficient(
     const Coefficient<dim> &coefficient_function)
   {
     const unsigned int n_cells = this->data->n_cell_batches();
     FEEvaluation<dim, fe_degree, fe_degree + 1, 1, number> phi(*this->data);
* 
     coefficient.reinit(n_cells, phi.n_q_points);
     for (unsigned int cell = 0; cell < n_cells; ++cell)
       {
         phi.reinit(cell);
         for (unsigned int q = 0; q < phi.n_q_points; ++q)
           coefficient(cell, q) =
             coefficient_function.value(phi.quadrature_point(q));
       }
   }
* 
 
* 
 @endcode
* 
* <a name="LocalevaluationofLaplaceoperator"></a> <h4>Local evaluation of Laplace operator</h4> <h4>Local evaluation of Laplace operator</h4>.
 

* 
* 这里是这个类的主要功能，矩阵-向量乘积的评估（或者，一般来说，一个有限元算子的评估）。这是在一个函数中完成的，它需要四个参数，MatrixFree对象，目标和源向量，以及要处理的单元格范围。MatrixFree类中的方法 <code>cell_loop</code> 将在内部用一些单元格范围来调用这个函数，这些单元格范围是通过检查哪些单元格可以同时工作来获得的，这样写操作就不会引起任何竞赛条件。请注意，循环中使用的单元格范围并不是直接指当前网格中的（活动）单元格数量，而是一个单元格批次的集合。 换句话说，"单元 "可能是一个错误的开始，因为FEEvaluation将几个单元的数据分组在一起。这意味着在正交点的循环中，我们实际上是将几个单元的正交点作为一个块来看待。这样做是为了实现更高的矢量化程度。 这种 "单元 "或 "单元批 "的数量存储在MatrixFree中，可以通过 MatrixFree::n_cell_batches(). 查询。与deal.II单元迭代器相比，在这个类中，所有的单元都被布置在一个普通的数组中，不直接知道水平或相邻关系，这使得通过无符号整数索引单元成为可能。  
* 拉普拉斯运算符的实现是非常简单的。首先，我们需要创建一个对象FEEvaluation，它包含计算核，并有数据字段来存储临时结果（例如，在几个单元格集合的所有正交点上评估的梯度）。请注意，临时结果不会使用大量的内存，而且由于我们用元素顺序指定模板参数，数据被存储在堆栈中（没有昂贵的内存分配）。通常，只需要设置两个模板参数，维度作为第一个参数，有限元的度数作为第二个参数（这等于每个维度的自由度数减去FE_Q元素的一个）。然而，在这里我们也希望能够使用浮点数来进行多网格预处理，这是最后一个（第五个）模板参数。因此，我们不能依赖默认的模板参数，因此必须填写第三和第四个字段。第三个参数指定每个方向的正交点的数量，其默认值等于元素的度数加1。第四个参数设置分量的数量（在PDEs系统中也可以评估向量值函数，但默认是标量元素），最后一个参数设置数字类型。  
* 接下来，我们在给定的单元格范围内循环，然后继续进行实际的实现。  <ol>   <li>  告诉FEEvaluation对象我们要处理的（宏）单元。   <li>  读入源向量的值（  @p read_dof_values),  包括约束的解析。这存储了 $u_\mathrm{cell}$ ，如介绍中所述。   <li>  计算单元格梯度（有限元函数的评价）。由于FEEvaluation可以结合值计算和梯度计算，它使用一个统一的接口来处理0到2阶之间的各种导数。我们只想要梯度，不想要值，也不想要二阶导数，所以我们在梯度槽（第二槽）中将函数参数设置为真，而在值槽（第一槽）中设置为假。还有一个用于Hessian的第三槽，默认为假，所以不需要给它。请注意，FEEvaluation类在内部以一种有效的方式评估形状函数，一次只处理一个维度（如介绍中提到的使用形状函数和正交点的张量积形式）。与FEValues中使用的在所有局部自由度和正交点上循环的天真方法相比，在 $d$ 维度上，这给出了等于 $\mathcal O(d^2 (p+1)^{d+1})$ 的多项式度数 $p$ 的复杂度，并花费了 $\mathcal O(d (p+1)^{2d})$  。   <li>  接下来是雅各布变换的应用，乘以变量系数和正交权重。FEEvaluation有一个访问函数 @p get_gradient ，可以应用Jacobian并返回实空间中的梯度。然后，我们只需要乘以（标量）系数，并让函数 @p submit_gradient 应用第二个雅各布式（用于测试函数）和正交权重及雅各布式行列式（JxW）。注意，提交的梯度存储在与 @p get_gradient. 中读取梯度的地方相同的数据字段中。因此，你需要确保在调用 @p submit_gradient 后不要再从同一正交点读取该特定正交点。一般来说，当 @p get_gradient 被多次使用时，复制它的结果是个好主意。   <li>  接下来是对所有测试函数的正交点进行求和，对应于实际积分步骤。对于拉普拉斯算子，我们只是乘以梯度，所以我们用各自的参数集调用积分函数。如果你有一个方程，同时用测试函数的值和梯度进行测试，那么两个模板参数都需要设置为真。先调用积分函数的值，再单独调用梯度，会导致错误的结果，因为第二次调用会在内部覆盖第一次调用的结果。请注意，积分步骤的二次导数没有函数参数。   <li>  最终，介绍中提到的向量 $v_\mathrm{cell}$ 中的局部贡献需要被添加到结果向量中（并应用约束）。这是通过调用 @p distribute_local_to_global, 来完成的，该函数与AffineConstraints中的相应函数名称相同（只是我们现在将局部向量存储在FEEvaluation对象中，正如局部和全局自由度之间的指数一样）。   </ol>  
* 

* 
* @code
   template <int dim, int fe_degree, typename number>
   void LaplaceOperator<dim, fe_degree, number>::local_apply(
     const MatrixFree<dim, number> &                   data,
     LinearAlgebra::distributed::Vector<number> &      dst,
     const LinearAlgebra::distributed::Vector<number> &src,
     const std::pair<unsigned int, unsigned int> &     cell_range) const
   {
     FEEvaluation<dim, fe_degree, fe_degree + 1, 1, number> phi(data);
* 
     for (unsigned int cell = cell_range.first; cell < cell_range.second; ++cell)
       {
         AssertDimension(coefficient.size(0), data.n_cell_batches());
         AssertDimension(coefficient.size(1), phi.n_q_points);
* 
         phi.reinit(cell);
         phi.read_dof_values(src);
         phi.evaluate(EvaluationFlags::gradients);
         for (unsigned int q = 0; q < phi.n_q_points; ++q)
           phi.submit_gradient(coefficient(cell, q) phi.get_gradient(q), q);
         phi.integrate(EvaluationFlags::gradients);
         phi.distribute_local_to_global(dst);
       }
   }
* 
 
* 
 @endcode
* 
* 这个函数实现了 Base::apply_add() 接口的所有单元的循环。这是通过MatrixFree类的 @p cell_loop 来实现的，它接受这个类的operator()，参数为MatrixFree, OutVector, InVector, cell_range。当使用MPI并行化工作时（但没有线程），如本教程程序中所做的，单元格循环对应于以下三行代码。  
*  <div class=CodeFragmentInTutorialComment>


* 
* 
@code
 src.update_ghost_values();
 local_apply(*this->data, dst, src, std::make_pair(0U,
                                                   data.n_cell_batches()));
 dst.compress(VectorOperation::add);
 @endcode
* 
 </div>     
* 这里，两个调用update_ghost_values()和compress()为MPI执行处理器边界上的数据交换，一次是源向量，我们需要从远程处理器拥有的条目中读取，另一次是目的向量，我们已经积累了部分残差，需要添加到所有者处理器的相应条目中。然而， MatrixFree::cell_loop 不仅抽象出了这两个调用，而且还进行了一些额外的优化。一方面，它将把update_ghost_values()和compress()的调用拆开，以允许通信和计算的重叠。然后用三个代表从0到 MatrixFree::n_cell_batches(). 的单元格范围的分区来调用local_apply函数。另一方面，cell_loop也支持线程并行，在这种情况下，单元格范围被分割成更小的块，并以一种先进的方式安排，避免了几个线程对同一个向量条目的访问。这一特性在  step-48  中有解释。  
* 请注意，在单元格循环之后，受约束的自由度需要再次被触及，以获得合理的vmult()操作。由于装配循环会自动解决约束问题（就像 AffineConstraints::distribute_local_to_global() 中的调用一样），它不会计算约束自由度的任何贡献，使各自的条目为零。这将表示一个矩阵的受限自由度的行和列都是空的。然而，像CG这样的迭代求解器只对非星形矩阵有效。最简单的方法是将矩阵中对应于受限自由度的子块设置为同一矩阵，在这种情况下，矩阵的应用只是将右侧向量的元素复制到左侧。幸运的是，vmult()的实现 MatrixFreeOperators::Base 在apply_add()函数之外自动为我们做了这个，所以我们不需要在这里采取进一步的行动。  
* 当使用MatrixFree和FEEvaluation的组合与MPI并行时，有一个方面需要注意&mdash；用于访问向量的索引。出于性能的考虑，MatrixFree和FEEvaluation被设计为在MPI本地索引空间中访问向量，当与多个处理器一起工作时也是如此。在本地索引空间工作意味着除了不可避免的间接寻址外，在向量访问发生的地方不需要进行索引转换。然而，本地索引空间是模糊的：虽然标准的惯例是用0和本地大小之间的索引访问向量的本地拥有的范围，但对于重影项的编号并不那么明确，而且有些随意。对于矩阵-向量乘积，只有出现在本地拥有的单元格上的指数（加上那些通过悬挂节点约束引用的指数）是必要的。然而，在deal.II中，我们经常将重影元素上的所有自由度设置为重影向量条目，称为 @ref GlossLocallyRelevantDof "术语表中描述的局部相关自由度"。在这种情况下，尽管指的是同一个全局索引，但在两个可能的重影集中，重影向量条目的MPI本地索引一般会有所不同。为了避免问题，FEEvaluation通过一个名为 LinearAlgebra::distributed::Vector::partitioners_are_compatible. 的检查来检查用于矩阵-向量乘积的向量分区是否确实与MatrixFree中的索引分区相匹配。 为了方便， MatrixFreeOperators::Base 类包括一个机制来使鬼魂集适应正确的布局。这发生在向量的ghost区域，所以请记住，在调用vmult()方法后，目标和源向量的ghost区域都可能被修改。这是合法的，因为分布式deal.II矢量的ghost区域是一个可变的部分，并按需填充。在矩阵-向量乘积中使用的向量在进入vmult()函数时不能被重影，所以没有信息丢失。
* 

* 
* @code
   template <int dim, int fe_degree, typename number>
   void LaplaceOperator<dim, fe_degree, number>::apply_add(
     LinearAlgebra::distributed::Vector<number> &      dst,
     const LinearAlgebra::distributed::Vector<number> &src) const
   {
     this->data->cell_loop(&LaplaceOperator::local_apply, this, dst, src);
   }
* 
 
* 
 @endcode
* 
* 下面的函数实现了算子对角线的计算。计算无矩阵算子评价的矩阵项原来比评价算子更复杂。从根本上说，我们可以通过在<i>all</i>单位向量上应用算子来获得算子的矩阵表示。当然，这将是非常低效的，因为我们需要进行<i>n</i>运算符的评估来检索整个矩阵。此外，这种方法会完全忽视矩阵的稀疏性。然而，在单个单元上，这是一种方法，而且实际上效率并不低，因为单元内的所有自由度之间通常存在着耦合。  
* 我们首先将对角线向量初始化为正确的并行布局。这个向量被封装在基类 MatrixFreeOperators::Base. 中DiagonalMatrix类型的一个名为inverse_diagonal_entries的成员中，这个成员是一个共享指针，我们首先需要初始化它，然后得到代表矩阵中对角线条目的向量。至于实际的对角线计算，我们再次使用MatrixFree的cell_loop基础设施来调用一个名为local_compute_diagonal()的本地工作程序。由于我们只写进一个向量，而没有任何源向量，我们用一个<tt>unsigned int</tt>类型的假参数来代替源向量，以便与cell_loop接口确认。在循环之后，我们需要将受Dirichlet边界条件约束的向量条目设置为1（要么是MatrixFree内部AffineConstraints对象描述的边界上的条目，要么是自适应多网格中不同网格层次之间的索引）。这是通过函数 MatrixFreeOperators::Base::set_constrained_entries_to_one() 完成的，并与Base算子提供的矩阵-向量乘积中的设置相匹配。最后，我们需要反转对角线条目，这是基于Jacobi迭代的Chebyshev平滑器所要求的形式。在循环中，我们断言所有条目都是非零的，因为它们应该从积分中获得了正的贡献，或者被约束并被 @p set_constrained_entries_to_one() 以下的cell_loop处理。
* 

* 
* @code
   template <int dim, int fe_degree, typename number>
   void LaplaceOperator<dim, fe_degree, number>::compute_diagonal()
   {
     this->inverse_diagonal_entries.reset(
       new DiagonalMatrix<LinearAlgebra::distributed::Vector<number>>());
     LinearAlgebra::distributed::Vector<number> &inverse_diagonal =
       this->inverse_diagonal_entries->get_vector();
     this->data->initialize_dof_vector(inverse_diagonal);
     unsigned int dummy = 0;
     this->data->cell_loop(&LaplaceOperator::local_compute_diagonal,
                           this,
                           inverse_diagonal,
                           dummy);
* 
     this->set_constrained_entries_to_one(inverse_diagonal);
* 
     for (unsigned int i = 0; i < inverse_diagonal.locally_owned_size(); ++i)
       {
         Assert(inverse_diagonal.local_element(i) > 0.,
                ExcMessage("No diagonal entry in a positive definite operator "
                           "should be zero"));
         inverse_diagonal.local_element(i) =
           1. / inverse_diagonal.local_element(i);
       }
   }
* 
 
* 
 @endcode
* 
* 在本地计算循环中，我们通过循环本地矩阵的所有列来计算对角线，并在<i>i</i>的槽中放入条目1，在所有其他槽中放入条目0，也就是说，我们一次在一个单位向量上应用单元-明智的微分运算。调用 FEEvaluation::evaluate, 的内部部分是对正交点的循环，而 FEEvalution::integrate, 则与local_apply函数完全相同。之后，我们挑选出本地结果的第<i>i</i>个条目，并将其放入一个临时存储器中（因为我们在下一次循环迭代时覆盖了 FEEvaluation::get_dof_value() 后面数组中的所有条目）。最后，临时存储被写到目标向量中。注意我们是如何使用 FEEvaluation::get_dof_value() 和 FEEvaluation::submit_dof_value() 一方面对FEEvaluation用于积分的数据域进行读写，另一方面写入全局向量的。  
* 鉴于我们只对矩阵的对角线感兴趣，我们干脆扔掉沿途计算过的本地矩阵的所有其他条目。虽然计算完整的单元格矩阵，然后扔掉除对角线以外的所有东西看起来很浪费，但整合的效率很高，所以计算不会花费太多的时间。请注意，对于多项式程度来说，每个元素的算子评估的复杂度是 $\mathcal
 O((p+1)^{d+1})$ ，所以计算整个矩阵需要花费我们 $\mathcal O((p+1)^{2d+1})$ 次运算，与用FEValues计算对角线的复杂度 $\mathcal O((p+1)^{2d})$ 相差不大。由于FEEvaluation也由于矢量化和其他优化而大大加快了速度，所以用这个函数计算对角线实际上是最快的（简单的）变量。(有可能用 $\mathcal
 O((p+1)^{d+1})$ 操作中的和分解技术来计算对角线，这涉及到特别适应的内核&mdash;但由于这种内核只在特定的情况下有用，而对角线的计算通常不在关键路径上，它们没有在deal.II中实现。)   
* 请注意，在向量上调用distribution_local_to_global来将对角线条目累积到全局矩阵的代码有一些限制。对于具有悬挂节点约束的操作者来说，将一个受约束的DoF的积分贡献分配到distribution_local_to_global调用中的其他几个条目上，这里使用的向量接口并不完全计算对角线条目，而是将一些位于本地矩阵对角线上的贡献，最终在全局矩阵的对角线以外的位置上堆积起来。正如<a
 href="http://dx.doi.org/10.4208/cicp.101214.021015a">Kormann (2016),
 section 5.3</a>中所解释的，该结果在离散化精度上是正确的，但在数学上并不平等。在这个教程程序中，不会发生任何危害，因为对角线只用于没有悬挂节点约束出现的多网格级矩阵。
* 

* 
* @code
   template <int dim, int fe_degree, typename number>
   void LaplaceOperator<dim, fe_degree, number>::local_compute_diagonal(
     const MatrixFree<dim, number> &             data,
     LinearAlgebra::distributed::Vector<number> &dst,
     const unsigned int &,
     const std::pair<unsigned int, unsigned int> &cell_range) const
   {
     FEEvaluation<dim, fe_degree, fe_degree + 1, 1, number> phi(data);
* 
     AlignedVector<VectorizedArray<number>> diagonal(phi.dofs_per_cell);
* 
     for (unsigned int cell = cell_range.first; cell < cell_range.second; ++cell)
       {
         AssertDimension(coefficient.size(0), data.n_cell_batches());
         AssertDimension(coefficient.size(1), phi.n_q_points);
* 
         phi.reinit(cell);
         for (unsigned int i = 0; i < phi.dofs_per_cell; ++i)
           {
             for (unsigned int j = 0; j < phi.dofs_per_cell; ++j)
               phi.submit_dof_value(VectorizedArray<number>(), j);
             phi.submit_dof_value(make_vectorized_array<number>(1.), i);
* 
             phi.evaluate(EvaluationFlags::gradients);
             for (unsigned int q = 0; q < phi.n_q_points; ++q)
               phi.submit_gradient(coefficient(cell, q) phi.get_gradient(q),
                                   q);
             phi.integrate(EvaluationFlags::gradients);
             diagonal[i] = phi.get_dof_value(i);
           }
         for (unsigned int i = 0; i < phi.dofs_per_cell; ++i)
           phi.submit_dof_value(diagonal[i], i);
         phi.distribute_local_to_global(dst);
       }
   }
* 
 
* 
 @endcode
* 
* <a name="LaplaceProblemclass"></a> <h3>LaplaceProblem class</h3>.
 

* 
* 这个类是基于  step-16  中的一个。然而，我们用我们的无矩阵实现取代了SparseMatrix<double>类，这意味着我们也可以跳过稀疏性模式。请注意，我们用有限元的度数作为模板参数定义了LaplaceOperator类（该值在文件的顶部定义），并且我们用浮点数来表示多网格级的矩阵。  
* 该类还有一个成员变量，用来记录在我们真正去解决问题之前设置整个数据链的所有详细时间。此外，还有一个输出流（默认情况下是禁用的），可以用来输出各个设置操作的细节，而不是默认情况下只打印出的摘要。  
* 由于这个程序被设计成与MPI一起使用，我们也提供了通常的 @p pcout 输出流，只打印MPI等级为0的处理器的信息。这个程序使用的网格可以是基于p4est的分布式三角形（如果deal.II被配置为使用p4est），否则它就是一个只在没有MPI的情况下运行的串行网格。
* 

* 
* @code
   template <int dim>
   class LaplaceProblem
   {
   public:
     LaplaceProblem();
     void run();
* 
   private:
     void setup_system();
     void assemble_rhs();
     void solve();
     void output_results(const unsigned int cycle) const;
* 
 #ifdef DEAL_II_WITH_P4EST
     parallel::distributed::Triangulation<dim> triangulation;
 #else
     Triangulation<dim> triangulation;
 #endif
* 
     FE_Q<dim>       fe;
     DoFHandler<dim> dof_handler;
* 
     MappingQ1<dim> mapping;
* 
     AffineConstraints<double> constraints;
     using SystemMatrixType =
       LaplaceOperator<dim, degree_finite_element, double>;
     SystemMatrixType system_matrix;
* 
     MGConstrainedDoFs mg_constrained_dofs;
     using LevelMatrixType = LaplaceOperator<dim, degree_finite_element, float>;
     MGLevelObject<LevelMatrixType> mg_matrices;
* 
     LinearAlgebra::distributed::Vector<double> solution;
     LinearAlgebra::distributed::Vector<double> system_rhs;
* 
     double             setup_time;
     ConditionalOStream pcout;
     ConditionalOStream time_details;
   };
* 
 
* 
 @endcode
* 
* 当我们初始化有限元时，我们当然也要使用文件顶部指定的度数（否则，在某些时候会抛出一个异常，因为模板化的LaplaceOperator类中定义的计算内核和MatrixFree读出的有限元信息不匹配）。三角形的构造函数需要设置一个额外的标志，告诉网格要符合顶点上的2:1单元平衡，这对于几何多网格例程的收敛是必需的。对于分布式网格，我们还需要特别启用多网格的层次结构。
* 

* 
* @code
   template <int dim>
   LaplaceProblem<dim>::LaplaceProblem()
     :
 #ifdef DEAL_II_WITH_P4EST
     triangulation(
       MPI_COMM_WORLD,
       Triangulation<dim>::limit_level_difference_at_vertices,
       parallel::distributed::Triangulation<dim>::construct_multigrid_hierarchy)
     ,
 #else
     triangulation(Triangulation<dim>::limit_level_difference_at_vertices)
     ,
 #endif
     fe(degree_finite_element)
     , dof_handler(triangulation)
     , setup_time(0.)
     , pcout(std::cout, Utilities::MPI::this_mpi_process(MPI_COMM_WORLD) == 0)
     ,
 @endcode
 
* LaplaceProblem类拥有一个额外的输出流，收集关于设置阶段的详细时间。这个流被称为time_details，默认情况下通过这里指定的 @p false 参数被禁用。对于详细的时间，去掉 @p false 参数可以打印出所有的细节。
* 

* 
* @code
     time_details(std::cout,
                  false && Utilities::MPI::this_mpi_process(MPI_COMM_WORLD) == 0)
   {}
* 
 
* 
 @endcode
* 
* <a name="LaplaceProblemsetup_system"></a> <h4>LaplaceProblem::setup_system</h4>。
 

* 
* 设置阶段与 step-16 类似，由于LaplaceOperator类的存在而有相关的变化。首先要做的是设置DoFHandler，包括多网格层次的自由度，以及初始化悬挂节点的约束和同质二列条件。由于我们打算在%parallel的MPI中使用这个程序，我们需要确保约束条件能知道本地相关的自由度，否则在使用超过几亿个自由度时，存储会爆炸，见 step-40  。
* 

* 
* 一旦我们创建了多网格dof_handler和约束，我们就可以为全局矩阵算子以及多网格方案的每一级调用reinit函数。主要的操作是为问题设置 <code> MatrixFree </code> 实例。 <code>LaplaceOperator</code> 类的基类， MatrixFreeOperators::Base, 被初始化为一个指向MatrixFree对象的共享指针。这样，我们可以在这里简单地创建它，然后将它分别传递给系统矩阵和水平矩阵。为了设置MatrixFree，我们需要激活MatrixFree的AdditionalData字段中的更新标志，使其能够存储实空间中的正交点坐标（默认情况下，它只缓存梯度（反转置的雅各布）和JxW值的数据）。请注意，如果我们调用 reinit 函数而不指定级别（即给出  <code>level = numbers::invalid_unsigned_int</code>  ），MatrixFree 会在活动单元上构建一个循环。在本教程中，除了MPI之外，我们不使用线程，这就是为什么我们通过将 MatrixFree::AdditionalData::tasks_parallel_scheme 设置为 MatrixFree::AdditionalData::none. 来明确地禁用它 最后，系数被评估，向量被初始化，如上所述。
* 

* 
* @code
   template <int dim>
   void LaplaceProblem<dim>::setup_system()
   {
     Timer time;
     setup_time = 0;
* 
     system_matrix.clear();
     mg_matrices.clear_elements();
* 
     dof_handler.distribute_dofs(fe);
     dof_handler.distribute_mg_dofs();
* 
     pcout << "Number of degrees of freedom: " << dof_handler.n_dofs()
           << std::endl;
* 
     IndexSet locally_relevant_dofs;
     DoFTools::extract_locally_relevant_dofs(dof_handler, locally_relevant_dofs);
* 
     constraints.clear();
     constraints.reinit(locally_relevant_dofs);
     DoFTools::make_hanging_node_constraints(dof_handler, constraints);
     VectorTools::interpolate_boundary_values(
       mapping, dof_handler, 0, Functions::ZeroFunction<dim>(), constraints);
     constraints.close();
     setup_time += time.wall_time();
     time_details << "Distribute DoFs & B.C.     (CPU/wall) " << time.cpu_time()
                  << "s/" << time.wall_time() << "s" << std::endl;
     time.restart();
* 
     {
       typename MatrixFree<dim, double>::AdditionalData additional_data;
       additional_data.tasks_parallel_scheme =
         MatrixFree<dim, double>::AdditionalData::none;
       additional_data.mapping_update_flags =
         (update_gradients | update_JxW_values | update_quadrature_points);
       std::shared_ptr<MatrixFree<dim, double>> system_mf_storage(
         new MatrixFree<dim, double>());
       system_mf_storage->reinit(mapping,
                                 dof_handler,
                                 constraints,
                                 QGauss<1>(fe.degree + 1),
                                 additional_data);
       system_matrix.initialize(system_mf_storage);
     }
* 
     system_matrix.evaluate_coefficient(Coefficient<dim>());
* 
     system_matrix.initialize_dof_vector(solution);
     system_matrix.initialize_dof_vector(system_rhs);
* 
     setup_time += time.wall_time();
     time_details << "Setup matrix-free system   (CPU/wall) " << time.cpu_time()
                  << "s/" << time.wall_time() << "s" << std::endl;
     time.restart();
* 
 @endcode
* 
* 接下来，初始化所有层次上的多网格方法的矩阵。数据结构MGConstrainedDoFs保留了受边界条件约束的指数信息，以及不同细化层之间的边缘指数，如 step-16 教程程序中所述。然后，我们穿过网格的各个层次，在每个层次上构造约束和矩阵。这与原始网格上的系统矩阵的构造密切相关，只是在访问各层信息而不是活动单元时，在命名上略有不同。
* 

* 
* @code
     const unsigned int nlevels = triangulation.n_global_levels();
     mg_matrices.resize(0, nlevels
* 
- 1);
* 
     std::set<types::boundary_id> dirichlet_boundary;
     dirichlet_boundary.insert(0);
     mg_constrained_dofs.initialize(dof_handler);
     mg_constrained_dofs.make_zero_boundary_constraints(dof_handler,
                                                        dirichlet_boundary);
* 
     for (unsigned int level = 0; level < nlevels; ++level)
       {
         IndexSet relevant_dofs;
         DoFTools::extract_locally_relevant_level_dofs(dof_handler,
                                                       level,
                                                       relevant_dofs);
         AffineConstraints<double> level_constraints;
         level_constraints.reinit(relevant_dofs);
         level_constraints.add_lines(
           mg_constrained_dofs.get_boundary_indices(level));
         level_constraints.close();
* 
         typename MatrixFree<dim, float>::AdditionalData additional_data;
         additional_data.tasks_parallel_scheme =
           MatrixFree<dim, float>::AdditionalData::none;
         additional_data.mapping_update_flags =
           (update_gradients | update_JxW_values | update_quadrature_points);
         additional_data.mg_level = level;
         std::shared_ptr<MatrixFree<dim, float>> mg_mf_storage_level(
           new MatrixFree<dim, float>());
         mg_mf_storage_level->reinit(mapping,
                                     dof_handler,
                                     level_constraints,
                                     QGauss<1>(fe.degree + 1),
                                     additional_data);
* 
         mg_matrices[level].initialize(mg_mf_storage_level,
                                       mg_constrained_dofs,
                                       level);
         mg_matrices[level].evaluate_coefficient(Coefficient<dim>());
       }
     setup_time += time.wall_time();
     time_details << "Setup matrix-free levels   (CPU/wall) " << time.cpu_time()
                  << "s/" << time.wall_time() << "s" << std::endl;
   }
* 
 
* 
 @endcode
* 
* <a name="LaplaceProblemassemble_rhs"></a> <h4>LaplaceProblem::assemble_rhs</h4>
 

* 
* 组装函数非常简单，因为我们所要做的就是组装右侧。多亏了FEEvaluation和所有缓存在MatrixFree类中的数据，我们从 MatrixFreeOperators::Base, 中查询，这可以在几行中完成。由于这个调用没有被包装成一个 MatrixFree::cell_loop （这将是一个替代方案），我们一定不要忘记在装配结束时调用compress()，将右手边的所有贡献发送给各自自由度的所有者。
* 

* 
* @code
   template <int dim>
   void LaplaceProblem<dim>::assemble_rhs()
   {
     Timer time;
* 
     system_rhs = 0;
     FEEvaluation<dim, degree_finite_element> phi(
      system_matrix.get_matrix_free());
     for (unsigned int cell = 0;
          cell < system_matrix.get_matrix_free()->n_cell_batches();
          ++cell)
       {
         phi.reinit(cell);
         for (unsigned int q = 0; q < phi.n_q_points; ++q)
           phi.submit_value(make_vectorized_array<double>(1.0), q);
         phi.integrate(EvaluationFlags::values);
         phi.distribute_local_to_global(system_rhs);
       }
     system_rhs.compress(VectorOperation::add);
* 
     setup_time += time.wall_time();
     time_details << "Assemble right hand side   (CPU/wall) " << time.cpu_time()
                  << "s/" << time.wall_time() << "s" << std::endl;
   }
* 
 
* 
 @endcode
* 
* <a name="LaplaceProblemsolve"></a> <h4>LaplaceProblem::solve</h4>
 

* 
* 求解过程与 step-16 中类似。我们从转移的设置开始。对于 LinearAlgebra::distributed::Vector, 来说，有一个非常快速的转移类，叫做MGTransferMatrixFree，它用同样的快速和因子化核在网格层之间进行插值，这也被用于FEEvaluation。
* 

* 
* @code
   template <int dim>
   void LaplaceProblem<dim>::solve()
   {
     Timer                            time;
     MGTransferMatrixFree<dim, float> mg_transfer(mg_constrained_dofs);
     mg_transfer.build(dof_handler);
     setup_time += time.wall_time();
     time_details << "MG build transfer time     (CPU/wall) " << time.cpu_time()
                  << "s/" << time.wall_time() << "s\n";
     time.restart();
* 
 @endcode
 
* 作为一个平滑器，本教程程序使用切比雪夫迭代，而不是 step-16 中的SOR。（SOR很难实现，因为我们没有明确的矩阵元素，而且很难使其在%并行中有效工作）。 平滑器是用我们的水平矩阵和切比雪夫平滑器的强制性附加数据初始化的。我们在这里使用一个相对较高的度数（5），因为矩阵-向量乘积是比较便宜的。我们选择在平滑器中平滑出 $[1.2 \hat{\lambda}_{\max}/15,1.2 \hat{\lambda}_{\max}]$ 的范围，其中 $\hat{\lambda}_{\max}$ 是最大特征值的估计值（系数1.2在PreconditionChebyshev内部应用）。为了计算该特征值，Chebyshev初始化执行了几步没有预处理的CG算法。由于最高的特征值通常是最容易找到的，而且一个粗略的估计就足够了，我们选择10次迭代。最后，我们还设置了切比雪夫方法中的内部预处理类型，这是一个雅可比迭代。这由DiagonalMatrix类表示，该类得到了由我们的LaplaceOperator类提供的反对角线条目。    
* 在零级，我们以不同的方式初始化平滑器，因为我们想使用切比雪夫迭代作为求解器。PreconditionChebyshev允许用户切换到求解器模式，其中迭代次数在内部选择为正确值。在附加数据对象中，通过选择多项式程度为 @p numbers::invalid_unsigned_int. 来激活这一设置，然后算法将攻击粗级矩阵中最小和最大之间的所有特征值。切比雪夫平滑器的步数是这样选择的：切比雪夫收敛估计值保证将残差减少到变量 @p 平滑_范围中指定的数量。注意，对于求解来说， @p smoothing_range 是一个相对的公差，并且选择小于1，在这种情况下，我们选择三个数量级，而当只对选定的特征值进行平滑时，它是一个大于1的数字。    
* 从计算的角度来看，只要粗粒度适中，Chebyshev迭代是一个非常有吸引力的粗网格求解器。这是因为Chebyshev方法只执行矩阵-向量乘积和向量更新，这通常比其他迭代方法中涉及的内积更好地并行到具有几万个核心的最大集群规模。前者只涉及（粗）网格中邻居之间的局部通信，而后者则需要在所有处理器上进行全局通信。
* 

* 
* @code
     using SmootherType =
       PreconditionChebyshev<LevelMatrixType,
                             LinearAlgebra::distributed::Vector<float>>;
     mg::SmootherRelaxation<SmootherType,
                            LinearAlgebra::distributed::Vector<float>>
                                                          mg_smoother;
     MGLevelObject<typename SmootherType::AdditionalData> smoother_data;
     smoother_data.resize(0, triangulation.n_global_levels()
* 
- 1);
     for (unsigned int level = 0; level < triangulation.n_global_levels();
          ++level)
       {
         if (level > 0)
           {
             smoother_data[level].smoothing_range     = 15.;
             smoother_data[level].degree              = 5;
             smoother_data[level].eig_cg_n_iterations = 10;
           }
         else
           {
             smoother_data[0].smoothing_range = 1e-3;
             smoother_data[0].degree          = numbers::invalid_unsigned_int;
             smoother_data[0].eig_cg_n_iterations = mg_matrices[0].m();
           }
         mg_matrices[level].compute_diagonal();
         smoother_data[level].preconditioner =
           mg_matrices[level].get_matrix_diagonal_inverse();
       }
     mg_smoother.initialize(mg_matrices, smoother_data);
* 
     MGCoarseGridApplySmoother<LinearAlgebra::distributed::Vector<float>>
       mg_coarse;
     mg_coarse.initialize(mg_smoother);
* 
 @endcode
 
* 下一步是设置悬挂节点情况下所需的接口矩阵。deal.II中的自适应多网格实现了一种叫做局部平滑的方法。这意味着最细级别的平滑只覆盖固定（最细）网格级别所定义的网格的局部部分，而忽略了计算域中终端单元比该级别更粗的部分。随着该方法向更粗的级别发展，越来越多的全局网格将被覆盖。在某个更粗的层次上，整个网格将被覆盖。由于多网格方法中的所有层次矩阵都覆盖了网格中的单一层次，所以在层次矩阵上不会出现悬空节点。在多网格层之间的界面上，在平滑的同时设置同质Dirichlet边界条件。然而，当残差被转移到下一个更粗的层次时，需要考虑到多网格界面的耦合。这是由所谓的界面（或边缘）矩阵来完成的，它计算了被具有同质Dirichlet条件的层次矩阵所遗漏的残差部分。我们参考 @ref mg_paper "Janssen和Kanschat的多网格论文 "以了解更多细节。    
* 对于这些接口矩阵的实现，已经有一个预定义的类 MatrixFreeOperators::MGInterfaceOperator ，它将例程 MatrixFreeOperators::Base::vmult_interface_down() 和 MatrixFreeOperators::Base::vmult_interface_up() 包装在一个带有 @p vmult()和 @p Tvmult() 操作（最初是为矩阵编写的，因此期待这些名字）的新类里。请注意，vmult_interface_down是在多网格V周期的限制阶段使用的，而vmult_interface_up是在延长阶段使用。    
* 一旦接口矩阵被创建，我们就完全类似于 step-16 来设置其余的多重网格预处理基础设施，以获得一个可以应用于矩阵的 @p preconditioner 对象。
* 

* 
* @code
     mg::Matrix<LinearAlgebra::distributed::Vector<float>> mg_matrix(
       mg_matrices);
* 
     MGLevelObject<MatrixFreeOperators::MGInterfaceOperator<LevelMatrixType>>
       mg_interface_matrices;
     mg_interface_matrices.resize(0, triangulation.n_global_levels()
* 
- 1);
     for (unsigned int level = 0; level < triangulation.n_global_levels();
          ++level)
       mg_interface_matrices[level].initialize(mg_matrices[level]);
     mg::Matrix<LinearAlgebra::distributed::Vector<float>> mg_interface(
       mg_interface_matrices);
* 
     Multigrid<LinearAlgebra::distributed::Vector<float>> mg(
       mg_matrix, mg_coarse, mg_transfer, mg_smoother, mg_smoother);
     mg.set_edge_matrices(mg_interface, mg_interface);
* 
     PreconditionMG<dim,
                    LinearAlgebra::distributed::Vector<float>,
                    MGTransferMatrixFree<dim, float>>
       preconditioner(dof_handler, mg, mg_transfer);
* 
 @endcode
 
* 多网格程序的设置非常简单，与 step-16 相比，在求解过程中看不出有什么不同。所有的魔法都隐藏在 LaplaceOperator::vmult 操作的实现背后。请注意，我们通过标准输出打印出求解时间和累积的设置时间，也就是说，在任何情况下，而设置操作的详细时间只有在构造函数中的detail_times标志被改变的情况下才会打印。
* 

* 
*  

* 
* @code
     SolverControl solver_control(100, 1e-12 system_rhs.l2_norm());
     SolverCG<LinearAlgebra::distributed::Vector<double>> cg(solver_control);
     setup_time += time.wall_time();
     time_details << "MG build smoother time     (CPU/wall) " << time.cpu_time()
                  << "s/" << time.wall_time() << "s\n";
     pcout << "Total setup time               (wall) " << setup_time << "s\n";
* 
     time.reset();
     time.start();
     constraints.set_zero(solution);
     cg.solve(system_matrix, solution, system_rhs, preconditioner);
* 
     constraints.distribute(solution);
* 
     pcout << "Time solve (" << solver_control.last_step() << " iterations)"
           << (solver_control.last_step() < 10 ? "  " : " ") << "(CPU/wall) "
           << time.cpu_time() << "s/" << time.wall_time() << "s\n";
   }
* 
 
* 
 @endcode
* 
* <a name="LaplaceProblemoutput_results"></a> <h4>LaplaceProblem::output_results</h4>。
 

* 
* 这里是数据输出，是  step-5  的简化版本。我们对细化过程中产生的每个网格使用标准的VTU（=压缩的VTK）输出。此外，我们还使用了一种针对速度而不是磁盘使用量进行优化的压缩算法。默认设置（针对磁盘使用进行优化）使得保存输出的时间是运行线性求解器的4倍，而设置 DataOutBase::VtkFlags::compression_level 到 DataOutBase::VtkFlags::best_speed 则将其降低到只有线性求解的四分之一的时间。  
* 当网格过大时，我们会禁用输出。这个程序的一个变种已经在几十万个MPI行列上运行，网格单元多达1000亿个，经典的可视化工具无法直接访问。
* 

* 
* @code
   template <int dim>
   void LaplaceProblem<dim>::output_results(const unsigned int cycle) const
   {
     Timer time;
     if (triangulation.n_global_active_cells() > 1000000)
       return;
* 
     DataOut<dim> data_out;
* 
     solution.update_ghost_values();
     data_out.attach_dof_handler(dof_handler);
     data_out.add_data_vector(solution, "solution");
     data_out.build_patches(mapping);
* 
     DataOutBase::VtkFlags flags;
     flags.compression_level = DataOutBase::VtkFlags::best_speed;
     data_out.set_flags(flags);
     data_out.write_vtu_with_pvtu_record(
       "./", "solution", cycle, MPI_COMM_WORLD, 3);
* 
     time_details << "Time write output          (CPU/wall) " << time.cpu_time()
                  << "s/" << time.wall_time() << "s\n";
   }
* 
 
* 
 @endcode
* 
* <a name="LaplaceProblemrun"></a> <h4>LaplaceProblem::run</h4>
 

* 
* 运行该程序的函数与  step-16  中的函数非常相似。与2D相比，我们在3D中做了一些细化步骤，但仅此而已。  
* 在我们运行程序之前，我们输出一些关于检测到的矢量化水平的信息，正如介绍中所讨论的那样。
* 

* 
* @code
   template <int dim>
   void LaplaceProblem<dim>::run()
   {
     {
       const unsigned int n_vect_doubles = VectorizedArray<double>::size();
       const unsigned int n_vect_bits    = 8 sizeof(double) n_vect_doubles;
* 
       pcout << "Vectorization over " << n_vect_doubles
             << " doubles = " << n_vect_bits << " bits ("
             << Utilities::System::get_current_vectorization_level() << ")"
             << std::endl;
     }
* 
     for (unsigned int cycle = 0; cycle < 9
* 
- dim; ++cycle)
       {
         pcout << "Cycle " << cycle << std::endl;
* 
         if (cycle == 0)
           {
             GridGenerator::hyper_cube(triangulation, 0., 1.);
             triangulation.refine_global(3
* 
- dim);
           }
         triangulation.refine_global(1);
         setup_system();
         assemble_rhs();
         solve();
         output_results(cycle);
         pcout << std::endl;
       };
   }
 } // namespace Step37
* 
 
* 
 @endcode
* 
* <a name="Thecodemaincodefunction"></a> <h3>The <code>main</code> function</h3>.
 

* 
* 除了我们根据 step-40 设置了MPI框架外，主函数中没有任何意外。
* 

* 
* @code
 int main(int argc, charargv[])
 {
   try
     {
       using namespace Step37;
* 
       Utilities::MPI::MPI_InitFinalize mpi_init(argc, argv, 1);
* 
       LaplaceProblem<dimension> laplace_problem;
       laplace_problem.run();
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
* 
   return 0;
 }
 @endcode
* <a name="Results"></a><h1>Results</h1> 。
* 

* <a name="Programoutput"></a><h3>Program output</h3>。
 

* 由于这个例子解决的是与 step-5 相同的问题（除了一个不同的系数），所以没有什么可说的解决方案。但我们还是展示了一张图片，通过等高线和体积渲染来说明解决方案的大小。
*  <img src="https://www.dealii.org/images/steps/developer/step-37.solution.png" alt="">  
当我们在二维上运行这个程序时，对于二次（ $Q_2$ ）元素，我们得到以下输出（当在释放模式下在一个核心上运行时）： *更感兴趣的是评估多网格求解器的某些方面。
* @code
Vectorization over 2 doubles = 128 bits (SSE2)
Cycle 0
Number of degrees of freedom: 81
Total setup time               (wall) 0.00159788s
Time solve (6 iterations)  (CPU/wall) 0.000951s/0.000951052s
* 
Cycle 1
Number of degrees of freedom: 289
Total setup time               (wall) 0.00114608s
Time solve (6 iterations)  (CPU/wall) 0.000935s/0.000934839s
* 
Cycle 2
Number of degrees of freedom: 1089
Total setup time               (wall) 0.00244665s
Time solve (6 iterations)  (CPU/wall) 0.00207s/0.002069s
* 
Cycle 3
Number of degrees of freedom: 4225
Total setup time               (wall) 0.00678205s
Time solve (6 iterations)  (CPU/wall) 0.005616s/0.00561595s
* 
Cycle 4
Number of degrees of freedom: 16641
Total setup time               (wall) 0.0241671s
Time solve (6 iterations)  (CPU/wall) 0.019543s/0.0195441s
* 
Cycle 5
Number of degrees of freedom: 66049
Total setup time               (wall) 0.0967851s
Time solve (6 iterations)  (CPU/wall) 0.07457s/0.0745709s
* 
Cycle 6
Number of degrees of freedom: 263169
Total setup time               (wall) 0.346374s
Time solve (6 iterations)  (CPU/wall) 0.260042s/0.265033s
@endcode
* 
* 如同在 step-16 中，我们看到CG迭代的数量在自由度增加的情况下保持不变。恒定的迭代次数（加上最佳的计算特性）意味着计算时间随着问题大小从一个周期到下一个周期的四倍而翻倍增长。该代码在存储方面也非常有效。大约2-4百万度的自由度适合于1GB的内存，也见下面的MPI结果。一个有趣的事实是，尽管没有建立矩阵，但解决一个线性系统比设置要便宜（大约一半的时间花在 DoFHandler::distribute_dofs() 和 DoFHandler::distribute_mg_dofs() 调用上）。这表明这种方法的效率很高，但也表明deal.II数据结构的设置相当昂贵，设置成本必须在几次系统求解中摊销。
* 如果我们在三个空间维度上运行该程序，则变化不大。由于我们使用统一的网格细化，我们得到八倍的元素和大约八倍的自由度的每个周期。
* @code
Vectorization over 2 doubles = 128 bits (SSE2)
Cycle 0
Number of degrees of freedom: 125
Total setup time               (wall) 0.00231099s
Time solve (6 iterations)  (CPU/wall) 0.000692s/0.000922918s
* 
Cycle 1
Number of degrees of freedom: 729
Total setup time               (wall) 0.00289083s
Time solve (6 iterations)  (CPU/wall) 0.001534s/0.0024128s
* 
Cycle 2
Number of degrees of freedom: 4913
Total setup time               (wall) 0.0143182s
Time solve (6 iterations)  (CPU/wall) 0.010785s/0.0107841s
* 
Cycle 3
Number of degrees of freedom: 35937
Total setup time               (wall) 0.087064s
Time solve (6 iterations)  (CPU/wall) 0.063522s/0.06545s
* 
Cycle 4
Number of degrees of freedom: 274625
Total setup time               (wall) 0.596306s
Time solve (6 iterations)  (CPU/wall) 0.427757s/0.431765s
* 
Cycle 5
Number of degrees of freedom: 2146689
Total setup time               (wall) 4.96491s
Time solve (6 iterations)  (CPU/wall) 3.53126s/3.56142s
@endcode
* 
* 既然如此简单，我们来看看如果我们增加多项式的度数会发生什么。当在三维中选择四度，即在 $\mathcal Q_4$ 元素上，通过改变程序顶部的<code>const unsigned intdegree_finite_element=4;</code>一行，我们得到以下的程序输出。
* @code
Vectorization over 2 doubles = 128 bits (SSE2)
Cycle 0
Number of degrees of freedom: 729
Total setup time               (wall) 0.00633097s
Time solve (6 iterations)  (CPU/wall) 0.002829s/0.00379395s
* 
Cycle 1
Number of degrees of freedom: 4913
Total setup time               (wall) 0.0174279s
Time solve (6 iterations)  (CPU/wall) 0.012255s/0.012254s
* 
Cycle 2
Number of degrees of freedom: 35937
Total setup time               (wall) 0.082655s
Time solve (6 iterations)  (CPU/wall) 0.052362s/0.0523629s
* 
Cycle 3
Number of degrees of freedom: 274625
Total setup time               (wall) 0.507943s
Time solve (6 iterations)  (CPU/wall) 0.341811s/0.345788s
* 
Cycle 4
Number of degrees of freedom: 2146689
Total setup time               (wall) 3.46251s
Time solve (7 iterations)  (CPU/wall) 3.29638s/3.3265s
* 
Cycle 5
Number of degrees of freedom: 16974593
Total setup time               (wall) 27.8989s
Time solve (7 iterations)  (CPU/wall) 26.3705s/27.1077s
@endcode
* 
* 由于某个网格上的 $\mathcal Q_4$ 元素对应于一半网格大小上的 $\mathcal Q_2$ 元素，我们可以比较第四周期使用四度多项式和第五周期使用二次多项式的运行时间，两者都是210万自由度。令人惊讶的是，尽管多用了一次线性迭代， $\mathcal Q_4$ 元素的求解器实际上比四次方的情况略快。高阶多项式同样快，甚至比低阶多项式更快，这是通过和因子化进行无矩阵算子评估的主要优势之一，见<a
href="http://dx.doi.org/10.1016/j.compfluid.2012.04.012">matrix-free
paper</a>。这与基于矩阵的方法有根本的不同，后者随着多项式度数的增加和耦合的密集，每个未知数的成本也越来越高。
* 此外，高阶的设置也会变得便宜一些，这是因为需要设置的元素较少。
* 最后，让我们看一下度数为8的时间，这相当于低阶方法的另一轮网格细化。
* @code
Vectorization over 2 doubles = 128 bits (SSE2)
Cycle 0
Number of degrees of freedom: 4913
Total setup time               (wall) 0.0842004s
Time solve (8 iterations)  (CPU/wall) 0.019296s/0.0192959s
* 
Cycle 1
Number of degrees of freedom: 35937
Total setup time               (wall) 0.327048s
Time solve (8 iterations)  (CPU/wall) 0.07517s/0.075999s
* 
Cycle 2
Number of degrees of freedom: 274625
Total setup time               (wall) 2.12335s
Time solve (8 iterations)  (CPU/wall) 0.448739s/0.453698s
* 
Cycle 3
Number of degrees of freedom: 2146689
Total setup time               (wall) 16.1743s
Time solve (8 iterations)  (CPU/wall) 3.95003s/3.97717s
* 
Cycle 4
Number of degrees of freedom: 16974593
Total setup time               (wall) 130.8s
Time solve (8 iterations)  (CPU/wall) 31.0316s/31.767s
@endcode
* 
* 在这里，初始化似乎比以前慢了很多，这主要是由于矩阵对角线的计算，它实际上是在每个单元上计算一个729 x 729的矩阵，并丢弃除对角线以外的所有东西。然而，解算时间又非常接近四分法的情况，表明理论上预期的随着多项式程度的增加而出现的线性增长几乎完全被更好的计算特性所抵消，而且高阶方法在几个单元上的自由度份额较小，增加了评估的复杂性。
*<a name="Comparisonwithasparsematrix"></a><h3>Comparison with a sparse matrix</h3>
* 

* 为了了解无矩阵实现的能力，我们通过测量问题初始化的计算时间（分布自由度、设置和装配矩阵、设置多网格结构），以及无矩阵变体和基于稀疏矩阵的变体的实际解法，对上述三维例子的性能与基于稀疏矩阵的变体进行比较。如上所示，我们将预处理程序建立在浮点数上，而实际的矩阵和向量建立在双数上。测试在英特尔Corei7-5500U笔记本处理器上运行（两个核心，支持<a
href="http://en.wikipedia.org/wiki/Advanced_Vector_Extensions">AVX</a>，即用一条CPU指令可以完成对双数的四次操作，这在FEE评估中被大量使用），优化模式，以及两个MPI等级。
*  <table align="center" class="doxtable">
  <tr>
    <th>&nbsp;</th>
    <th colspan="2">Sparse matrix</th>
    <th colspan="2">Matrix-free implementation</th>
  </tr>
  <tr>
    <th>n_dofs</th>
    <th>Setup + assemble</th>
    <th>&nbsp;Solve&nbsp;</th>
    <th>Setup + assemble</th>
    <th>&nbsp;Solve&nbsp;</th>
  </tr>
  <tr>
    <td align="right">125</td>
    <td align="center">0.0042s</td>
    <td align="center">0.0012s</td>
    <td align="center">0.0022s</td>
    <td align="center">0.00095s</td>
  </tr>
  <tr>
    <td align="right">729</td>
    <td align="center">0.012s</td>
    <td align="center">0.0040s</td>
    <td align="center">0.0027s</td>
    <td align="center">0.0021s</td>
  </tr>
  <tr>
    <td align="right">4,913</td>
    <td align="center">0.082s</td>
    <td align="center">0.012s</td>
    <td align="center">0.011s</td>
    <td align="center">0.0057s</td>
  </tr>
  <tr>
    <td align="right">35,937</td>
    <td align="center">0.73s</td>
    <td align="center">0.13s</td>
    <td align="center">0.048s</td>
    <td align="center">0.040s</td>
  </tr>
  <tr>
    <td align="right">274,625</td>
    <td align="center">5.43s</td>
    <td align="center">1.01s</td>
    <td align="center">0.33s</td>
    <td align="center">0.25s</td>
  </tr>
  <tr>
    <td align="right">2,146,689</td>
    <td align="center">43.8s</td>
    <td align="center">8.24s</td>
    <td align="center">2.42s</td>
    <td align="center">2.06s</td>
  </tr>
</table>  
* 该表清楚地表明，无矩阵实现的求解器速度是原来的两倍多，而在初始化成本方面，速度是原来的六倍多。由于问题的大小被放大了8倍，我们注意到时间通常也上升了8倍（因为求解器的迭代次数恒定为6）。主要的偏差是在5k到36k自由度的稀疏矩阵中，时间增加了12倍。这是处理器中的(L3)缓存不能再容纳矩阵-向量乘积所需的所有数据的阈值，所有的矩阵元素必须从主内存中获取。
* 当然，这种情况不一定适用于所有情况，因为有些问题，对矩阵项的了解可以使解算器的效果更好（如当系数的变化比上面的例子更强烈时就会发生）。此外，这也取决于计算机系统。目前的系统具有良好的内存性能，因此稀疏矩阵的性能相当好。尽管如此，对于本例中使用的<i>Q</i><sub>2</sub>元素，无矩阵的实现已经给出了一个很好的速度。这一点对于时间依赖性或非线性问题尤其明显，在这些问题中，疏散矩阵需要一次又一次地被重新组合，这在这个类别中变得更加容易。当然，由于products有更好的复杂性，当元素的阶数增加时，该方法会获得越来越大的优势（无矩阵实现的成本是4<i>d</i><sup>2</sup><i>p</i>每个自由度，而稀疏矩阵的成本是2<i>p<sup>d</sup></i>，所以在3D中阶数4和更高时它会赢）。
*<a name="ResultsforlargescaleparallelcomputationsonSuperMUC"></a><h3> Results for large-scale parallel computations on SuperMUC</h3>
* 

* 正如介绍和代码中的注释所解释的，这个程序可以用MPI并行运行。事实证明，几何多网格方案工作得非常好，可以扩展到非常大的机器。据作者所知，这里显示的几何多网格结果是截至2016年底用deal.II进行的最大计算，在<a
href="https://www.lrz.de/services/compute/supermuc/systemdescription/">complete
SuperMUC Phase 1</a>的147456个核心上运行。超过1000个核心的可扩展性的要素是，没有任何依赖于全局问题大小的数据结构在单个处理器上保持其完整性，并且通信不是太频繁，以避免遇到网络的延迟问题。 对于用迭代求解器求解的PDEs，通信延迟往往是限制性因素，而不是网络的吞吐量。以SuperMUC系统为例，两个处理器之间的点对点延迟在1e-6到1e-5秒之间，这取决于MPI网络的远近。这一类的矩阵-向量积 @p LaplaceOperator 涉及几个点对点的通信步骤，与每个核上的计算交错进行。矩阵-向量乘积的延迟约为1e-4秒。全局通信，例如一个 @p MPI_Allreduce 操作，在MPInetwork的所有等级上累积每个等级的一个数字之和，其延迟为1e-4秒。这个程序中使用的多网格V型循环也是全局通信的一种形式。想一想发生在单个处理器上的粗略的网格解算。在开始之前，它积累了来自所有处理器的贡献。当完成后，粗网格解决方案被转移到更细的层次，在那里越来越多的处理器帮助进行平滑，直到细网格。从本质上讲，这是在网络中的处理器上的一个树状模式，由网格控制。与 @p MPI_Allreduce 操作不同的是，多网格V型循环是根据MPI网络中的实际链路来优化还原树，而多网格V型循环则是根据网格的划分来进行的。因此，我们不能期望有同样的优化效果。此外，多网格循环并不是简单地在细化树上走来走去，而是在做平滑时在每一层上进行通信。换句话说，多网格中的全局通信更具有挑战性，并且与提供较少优化机会的网格有关。测得的V-循环的延迟在6e-3和2e-2秒之间，即与60到200个MPI_Allreduce操作相同。
* 下图显示了在 $\mathcal Q_3$ 元素上进行的缩放实验。沿着这条线，问题的大小随着核数的增加而保持不变。当内核数量增加一倍时，人们期望计算时间减少一半，灰色虚线表示。结果显示，在达到0.1秒左右的绝对时间之前，该实现几乎显示了理想的行为。解算器的容差被设定为解算器进行了五次迭代。这种绘制数据的方式是该算法的<b>strong scaling</b>。当我们进入非常大的核数时，曲线会提前变平，这是因为SuperMUC的通信网络，较远的处理器之间的通信速度稍慢。
*  <img src="https://www.dealii.org/images/steps/developer/step-37.scaling_strong.png" alt="">  
* 此外，该图还包含了<b>weak scaling</b>的结果，列出了当处理器核心和元素的数量以同样的速度增加时，算法的表现。在这种情况下，我们希望计算时间保持不变。在算法上，CG的迭代次数恒定在5次，所以我们在这方面做得很好。图中的线条是这样排列的：每个数据系列中的左上角代表每个处理器的相同大小，即131,072个元素（或每个核心约3.5百万自由度）。表示理想的强标度的灰色线条相隔8个相同的系数。结果再次表明，扩展性几乎是理想的。从288个核到147456个核的并行效率约为75%，每个核的局部问题大小为750,000自由度，在288个核上需要1.0秒，在2304个核上需要1.03秒，在18000个核上需要1.19秒，在147000个核上需要1.35秒。这些算法也达到了非常高的处理器利用率。在147k核上的最大计算量在SuperMUC上达到约1.7 PFLOPs/s，其中算术峰值为3.2 PFLOPs/s。对于一个迭代式PDE求解器来说，这是一个非常高的数字，而且通常只有密集线性代数才会达到明显的数字。稀疏线性代数被限制在这个数值的十分之一。
* 正如在介绍中提到的，无矩阵方法减少了数据结构的内存消耗。除了由于较少的内存传输而带来的更高的性能外，这些算法还允许非常大的问题在内存中得到解决。下图显示了当我们增加问题大小时的计算时间，直到计算耗尽内存的上限。我们对1k核、8k核和65k核进行了计算，发现问题的大小几乎可以在两个数量级上进行理想的扩展。这张图中显示的最大的计算涉及2920亿（ $2.92 \cdot 10^{11}$ ）个自由度。在147k核的DG计算中，上述算法也被运行，涉及多达5490亿（2^39）个自由度。
*  <img src="https://www.dealii.org/images/steps/developer/step-37.scaling_size.png" alt="">  
* 最后，我们注意到，在对上述大规模系统进行测试的同时，deal.II中的多网格算法的改进也被开发出来了。最初的版本包含了基于MGSmootherPrecondition的次优代码，其中一些MPI_Allreduce命令（检查所有向量条目是否为零）在每一级的平滑操作上进行，这只有在65k核以上才变得明显。然而，下面的图片显示，改进已经在较小的规模上得到了回报，这里显示的是对 $\mathcal Q_5$ 元素在多达14336个核心上的计算。
*  <img src="https://www.dealii.org/images/steps/developer/step-37.scaling_oldnew.png" alt="">  
* 

* <a name="Adaptivity"></a><h3> Adaptivity</h3>。
* 

* 正如代码中所解释的，这里介绍的算法是为运行在自适应细化的网格上而准备的。如果只有部分网格被细化，多网格循环将以局部平滑的方式运行，并在细化程度不同的界面上施加迪里切条件，通过 MatrixFreeOperators::Base 类进行平滑。由于自由度在层次上的分配方式，将层次单元的所有者与第一个下级活动单元的所有者联系起来，在MPI中不同的处理器之间可能存在不平衡，这限制了可扩展性，约为2-5倍。
*<a name="Possibilitiesforextensions"></a><h3> Possibilities for extensions</h3>
* 

* <a name="Kellyerrorestimator"></a><h4> Kelly error estimator </h4>.
* 

* 对于泊松方程，我们可以使用KellyErrorEstimator类中实现的Kelly误差指标。为了评估误差指标中的跳跃项，每个MPI进程都需要知道本地相关的DoFs.然而 MatrixFree::initialize_dof_vector()  ]函数只用一些本地相关的自由度初始化向量。向量中提供的鬼魂指数是一个严格的集合，只有那些在单元积分中被触及的指数（包括约束条件的解决）。 ]，如下图所示。
* @code
IndexSet locally_relevant_dofs;
DoFTools::extract_locally_relevant_dofs(dof_handler, locally_relevant_dofs);
LinearAlgebra::distributed::Vector<double> copy_vec(solution);
solution.reinit(dof_handler.locally_owned_dofs(),
                locally_relevant_dofs,
                triangulation.get_communicator());
solution.copy_locally_owned_data_from(copy_vec);
constraints.distribute(solution);
solution.update_ghost_values();
@endcode
 
* <a name="Sharedmemoryparallelization"></a><h4> Shared-memory parallelization</h4> 。
 

* 这个程序只用MPI来并行化。作为一种选择，MatrixFreeloop也可以在混合模式下发布，例如，在一个集群的节点上使用MPI并行化，在一个节点的共享内存区域内通过Intel TBB使用线程。要使用这个方法，需要在主函数的MPI_InitFinalize数据结构中设置线程数，并设置 MatrixFree::AdditionalData::tasks_parallel_scheme topartition_color来实际进行并行的循环。这个用例在  step-48  中进行了讨论。
* <a name="InhomogeneousDirichletboundaryconditions"></a><h4> Inhomogeneous Dirichlet boundary conditions </h4> 。
* 

* 所介绍的程序假定了同质的Dirichlet边界条件。当进入非均质条件时，情况就有点复杂了。为了了解如何实现这样的设置，让我们首先回顾一下这些条件是如何在数学公式中出现的，以及它们是如何在基于矩阵的变体中实现的。从本质上讲，非均质迪里希特条件将解中的一些节点值设定为给定值，而不是通过变分原理来确定它们，@f{eqnarray*}
u_h(\mathbf{x}) = \sum_{i\in \mathcal N} \varphi_i(\mathbf{x}) u_i =
\sum_{i\in \mathcal N \setminus \mathcal N_D} \varphi_i(\mathbf{x}) u_i +
\sum_{i\in \mathcal N_D} \varphi_i(\mathbf{x}) g_i,
@f} 。
*其中 $u_i$ 表示解决方案的节点值， $\mathcal N$ 表示所有节点的集合。集合 $\mathcal N_D\subset \mathcal N$ 是受Dirichlet边界条件约束的节点子集，其中解决方案被迫等于 $u_i = g_i = g(\mathbf{x}_i)$ ，作为Dirichlet约束节点点 $i\in \mathcal
N_D$ 上的边界值的插值。然后我们把这个解的表示插入到弱的形式中，例如上面显示的拉普拉斯，并把已知量移到右边：@f{eqnarray*}
(\nabla \varphi_i, \nabla u_h)_\Omega &=& (\varphi_i, f)_\Omega \quad \Rightarrow \\
\sum_{j\in \mathcal N \setminus \mathcal N_D}(\nabla \varphi_i,\nabla \varphi_j)_\Omega \, u_j &=&
(\varphi_i, f)_\Omega
* 
-\sum_{j\in \mathcal N_D} (\nabla \varphi_i,\nabla\varphi_j)_\Omega\, g_j.
@f} 。
* 在这个公式中，方程对所有与迪里希特条件约束的节点无关的基函数 $\varphi_i$ 和 $i\in N \setminus \mathcal N_D$ 进行检验。
* 在deal.II的实现中，右侧的积分 $(\nabla \varphi_i,\nabla \varphi_j)_\Omega$ 已经包含在我们在每个单元上组装的局部矩阵贡献中。当使用 AffineConstraints::distribute_local_to_global() 时，如 step-6 和 step-7 教程程序中首次描述的那样，我们可以通过将本地矩阵的列<i>j</i>和行<i>i</i>相乘来说明同质约束的贡献<i>j</i>。 ]的局部矩阵根据积分 $(\varphi_i,
\varphi_j)_\Omega$ 乘以不均匀性，然后从全局右侧向量的位置<i>i</i>中减去所得到的结果，也见 @ref
constraints 模块。实质上，我们使用了一些从方程左手边消除的积分来最终确定右手边的贡献。当首先将所有条目写进左手边的矩阵，然后通过 MatrixTools::apply_boundary_values(). 消除矩阵的行和列时，也会涉及类似的数学。
* 原则上，属于受限自由度的成分可以从线性系统中消除，因为它们不携带任何信息。在实践中，在deal.II中，我们始终保持线性系统的大小不变，以避免处理两种不同的编号系统，并避免对两种不同的索引集产生混淆。为了确保线性系统在不向约束行添加任何东西时不会变得奇异，我们会在矩阵对角线上添加与实际条目无关的假条目。
* 在无矩阵方法中，我们需要采取不同的方法，因为 @p LaplaceOperator类代表了<b>homogeneous</b>算子的矩阵-向量乘积（最后一个公式的左侧）。 传递给 MatrixFree::reinit() 的AffineConstraints对象是否包含不均匀约束并不重要， MatrixFree::cell_loop() 调用将只解决约束的均匀部分，只要它代表一个<b>linear</b>算子。
* 在我们的无矩阵代码中，非均质条件的贡献最后的右手边计算与矩阵算子完全脱钩，由上述不同的函数处理。因此，我们需要明确地生成进入右手边的数据，而不是使用矩阵装配的副产品。由于我们已经知道如何在向量上应用运算符，我们可以尝试对一个向量使用这些设施，在那里我们只设置Dirichlet值。
* @code
  // interpolate boundary values on vector solution
  std::map<types::global_dof_index, double> boundary_values;
  VectorTools::interpolate_boundary_values(mapping,
                                           dof_handler,
                                           0,
                                           BoundaryValueFunction<dim>(),
                                           boundary_values);
  for (const std::pair<const types::global_dof_index, double> &pair : boundary_values)
    if (solution.locally_owned_elements().is_element(pair.first))
      solution(pair.first) = pair.second;
@endcode
* 或者说，如果我们已经将不均匀约束填入AffineConstraints对象中。
* @code
  solution = 0;
  constraints.distribute(solution);
@endcode
* 
* 然后我们可以将向量 @p solution 传递给 @p  LaplaceOperator::vmult_add() 函数，并将新的贡献添加到 @p system_rhs向量中，该向量在 @p LaplaceProblem::assemble_rhs() 函数中被填充。然而，这个想法并不奏效，因为vmult()函数中使用的 FEEvaluation::read_dof_values() 调用假设所有约束条件的值都是同质的（否则运算符就不是线性运算符，而是仿射运算符）。为了同时检索同质性的值，我们可以选择以下两种策略之一。
*<a name="UseFEEvaluationread_dof_values_plaintoavoidresolvingconstraints"></a><h5> Use FEEvaluation::read_dof_values_plain() to avoid resolving constraints </h5>
* 

* FEEvaluation类有一个设施，正是解决了这个要求。对于非均质的Dirichlet值，我们确实希望在从向量 @p solution. 中读取数据时跳过对均质（Dirichlet）约束的隐式施加。例如，我们可以扩展 @p  LaplaceProblem::assemble_rhs() 函数来处理非均质的Dirichlet值，如下所示，假设Dirichlet值已被插值到对象 @p constraints: 中 
* @code
template <int dim>
void LaplaceProblem<dim>::assemble_rhs()
{
  solution = 0;
  constraints.distribute(solution);
  solution.update_ghost_values();
  system_rhs = 0;
* 
  const Table<2, VectorizedArray<double>> &coefficient = system_matrix.get_coefficient();
  FEEvaluation<dim, degree_finite_element> phi(*system_matrix.get_matrix_free());
  for (unsigned int cell = 0;
       cell < system_matrix.get_matrix_free()->n_cell_batches();
       ++cell)
    {
      phi.reinit(cell);
      phi.read_dof_values_plain(solution);
      phi.evaluate(EvaluationFlags::gradients);
      for (unsigned int q = 0; q < phi.n_q_points; ++q)
        {
          phi.submit_gradient(-coefficient(cell, q) phi.get_gradient(q), q);
          phi.submit_value(make_vectorized_array<double>(1.0), q);
        }
      phi.integrate(EvaluationFlags::values|EvaluationFlags::gradients);
      phi.distribute_local_to_global(system_rhs);
    }
  system_rhs.compress(VectorOperation::add);
}
@endcode
* 
* 在这段代码中，我们用 FEEvaluation::read_dof_values_plain() 代替了用于暂定解向量的 FEEvaluation::read_dof_values() 函数，该函数忽略了所有的约束。由于这种设置，我们必须确保其他约束条件，例如悬挂的节点，已经正确地分布到输入向量中，因为它们没有像 FEEvaluation::read_dof_values_plain(). 中那样被解决。 在循环中，我们然后评估拉普拉斯，并用 @p LaplaceOperator 类中的 FEEvaluation::submit_gradient() 重复二次导数的调用，但将符号调换，因为我们想根据上面的公式减去右侧向量中的迪里希条件的贡献。当我们调用 FEEvaluation::integrate() 调用时，我们将关于值槽和第一导数槽的两个参数都设置为真，以说明在正交点的循环中增加的这两个条件。一旦右手边组装完毕，我们就继续求解同质问题的线性系统，例如涉及到一个变量 @p solution_update. 在求解之后，我们可以将 @p solution_update 添加到包含最终（非同质）解决方案的 @p solution 向量。
* 请注意，拉普拉斯的负号与我们需要建立右手边的强制力的正号一起，是一个更普遍的概念。我们所实施的只不过是牛顿的非线性频率方法，但应用于线性系统。我们根据迪里切特边界条件对变量 @p solution 进行了初始猜测，并计算了一个残差 $r = f
* 
- Au_0$ 。然后对线性系统进行求解 $\Delta u = A^{-1} (f-Au)$ ，最后计算出 $u = u_0 + \Delta u$ 。对于线性系统，我们显然在一次迭代后就能得到精确的解。如果我们想将代码扩展到非线性问题，我们会将 @p assemble_rhs() 函数命名为一个更具描述性的名字，如 @p  assemble_residual()，计算残差的（弱）形式，而 @p LaplaceOperator::apply_add() 函数将得到残差相对于解变量的线性化。
*<a name="UseLaplaceOperatorwithasecondAffineConstraintsobjectwithoutDirichletconditions"></a><h5> Use LaplaceOperator with a second AffineConstraints object without Dirichlet conditions </h5>
* 

* 第二种方法是重新使用 @p  LaplaceOperator::apply_add() 函数来获得右手边，即添加第二个LaplaceOperator，跳过Dirichlet约束。为了做到这一点，我们初始化第二个MatrixFreeobject，它没有任何边界值约束。这个 @p matrix_free 对象然后被传递给一个 @p LaplaceOperator 类实例 @p inhomogeneous_operator，它只用于创建右手边。
* @code
template <int dim>
void LaplaceProblem<dim>::assemble_rhs()
{
  system_rhs = 0;
  AffineConstraints<double> no_constraints;
  no_constraints.close();
  LaplaceOperator<dim, degree_finite_element, double> inhomogeneous_operator;
* 
  typename MatrixFree<dim, double>::AdditionalData additional_data;
  additional_data.mapping_update_flags =
    (update_gradients | update_JxW_values | update_quadrature_points);
  std::shared_ptr<MatrixFree<dim, double>> matrix_free(
    new MatrixFree<dim, double>());
  matrix_free->reinit(dof_handler,
                      no_constraints,
                      QGauss<1>(fe.degree + 1),
                      additional_data);
  inhomogeneous_operator.initialize(matrix_free);
* 
  solution = 0.0;
  constraints.distribute(solution);
  inhomogeneous_operator.evaluate_coefficient(Coefficient<dim>());
  inhomogeneous_operator.vmult(system_rhs, solution);
  system_rhs=
* 
-1.0;
* 
  FEEvaluation<dim, degree_finite_element> phi(
   inhomogeneous_operator.get_matrix_free());
  for (unsigned int cell = 0;
       cell < inhomogeneous_operator.get_matrix_free()->n_cell_batches();
       ++cell)
    {
      phi.reinit(cell);
      for (unsigned int q = 0; q < phi.n_q_points; ++q)
        phi.submit_value(make_vectorized_array<double>(1.0), q);
      phi.integrate(EvaluationFlags::values);
      phi.distribute_local_to_global(system_rhs);
    }
  system_rhs.compress(VectorOperation::add);
}
@endcode
* 
* 这个技术的一个更复杂的实现可以重用原始MatrixFree对象。这可以通过用多个块初始化MatrixFree对象来实现，其中每个块对应于不同的AffineConstraints对象。这样做需要对LaplaceOperator类进行大量修改，但库中的 MatrixFreeOperators::LaplaceOperator 类可以做到这一点。参见 MatrixFreeOperators::Base 中关于块的讨论，以了解更多关于如何设置块的信息。
* 

* <a name="PlainProg"></a><h1> The plain program</h1>  @include "step-37.cc" 。
* */


