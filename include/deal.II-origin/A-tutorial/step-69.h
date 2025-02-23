/**
@page step_69 The step-69 tutorial program
This tutorial depends on step-33, step-40.

@htmlonly
<table class="tutorial" width="50%">
<tr><th colspan="2"><b><small>Table of contents</small></b></th></tr>
<tr><td width="50%" valign="top">
<ol>
  <li> <a href="#Intro" class=bold>Introduction</a>
    <ul>
        <li><a href="#Eulersequationsofgasdynamics">Euler's equations of gas dynamics</a>
      <ul>
        <li><a href="#Solutiontheory">Solution theory</a>
        <li><a href="#Variationalversuscollocationtypediscretizations">Variational versus collocation-type discretizations</a>
      </ul>
        <li><a href="#Descriptionofthescheme">Description of the scheme </a>
        <li><a href="#Stableboundaryconditionsandconservationproperties">Stable boundary conditions and conservation properties.</a>
    </ul>
  <li> <a href="#CommProg" class=bold>The commented program</a>
    <ul>
        <li><a href="#Includefiles">Include files</a>
        <li><a href="#Classtemplatedeclarations">Class template declarations</a>
      <ul>
        <li><a href="#ThecodeDiscretizationcodeclass">The <code>Discretization</code> class</a>
        <li><a href="#ThecodeOfflineDatacodeclass">The <code>OfflineData</code> class</a>
        <li><a href="#ThecodeProblemDescriptioncodeclass">The <code>ProblemDescription</code> class</a>
        <li><a href="#ThecodeInitialValuescodeclass">The <code>InitialValues</code> class</a>
        <li><a href="#ThecodeTimeSteppingcodeclass">The <code>%TimeStepping</code> class</a>
        <li><a href="#ThecodeSchlierenPostprocessorcodeclass">The <code>SchlierenPostprocessor</code> class</a>
        <li><a href="#ThecodeMainLoopcodeclass">The <code>MainLoop</code> class</a>
      </ul>
        <li><a href="#Implementation">Implementation</a>
      <ul>
        <li><a href="#Gridgenerationsetupofdatastructures">Grid generation, setup of data structures</a>
        <li><a href="#Assemblyofofflinematrices">Assembly of offline matrices</a>
        <li><a href="#Translationtolocalindexranges">Translation to local index ranges</a>
        <li><a href="#EquationofstateandapproximateRiemannsolver">Equation of state and approximate Riemann solver</a>
        <li><a href="#Initialvalues">Initial values</a>
        <li><a href="#TheForwardEulerstep">The Forward Euler step</a>
        <li><a href="#Schlierenpostprocessing">Schlieren postprocessing</a>
        <li><a href="#Themainloop">The main loop</a>
      <ul>
        <li><a href="#Resume">Resume</a>
        <li><a href="#Outputandcheckpointing">Output and checkpointing</a>
      </ul>
      </ul>
      </ul>
</ol></td><td width="50%" valign="top"><ol>
  <li value="3"> <a href="#Results" class=bold>Results</a>
    <ul>
        <li><a href="#Possibilitiesforextensions">Possibilities for extensions</a>
    </ul>
  <li> <a href="#PlainProg" class=bold>The plain program</a>
</ol> </td> </tr> </table>
@endhtmlonly
<i>
  This program was contributed by Matthias Maier (Texas A&M University),
  and Ignacio Tomas (Sandia National Laboratories$^{\!\dagger}$).
</i>

$^\dagger$<em>Sandia National Laboratories is a multimission laboratory
managed and operated by National Technology & Engineering Solutions of Sandia,
LLC, a wholly owned subsidiary of Honeywell International Inc., for the U.S.
Department of Energy's National Nuclear Security Administration under contract
DE-NA0003525. This document describes objective technical results and analysis.
Any subjective views or opinions that might be expressed in the paper do not
necessarily represent the views of the U.S. Department of Energy or the United
States Government.</em>

@note This tutorial step implements a first-order accurate <i>guaranteed
maximum wavespeed method</i> based on a first-order <i>graph viscosity</i>
for solving Euler's equations of gas dynamics @cite GuermondPopov2016. As
such it is presented primarily for educational purposes. For actual
research computations you might want to consider exploring a corresponding
<a href="https://github.com/conservation-laws/ryujin">high-performance
implementation of a second-order accurate scheme</a> that uses <i>convex
limiting</i> techniques, and strong stability-preserving (SSP) time
integration, see @cite GuermondEtAl2018
(<a href="https://conservation-laws.43-1.org/">website</a>).

@dealiiTutorialDOI{10.5281/zenodo.3698223,https://zenodo.org/badge/DOI/10.5281/zenodo.3698223.svg}

<a name="Intro"></a>
<a name="Introduction"></a><h1>Introduction</h1>


This tutorial presents a first-order scheme for solving compressible
Euler's equations that is based on three ingredients: a
<i>collocation</i>-type discretization of Euler's equations in the context
of finite elements; a graph-viscosity stabilization based on a
<i>guaranteed</i> upper bound of the local wave speed; and explicit
time-stepping. As such, the ideas and techniques presented in this tutorial
step are drastically different from those used in step-33, which focuses on
the use of automatic differentiation. From a programming perspective this
tutorial will focus on a number of techniques found in large-scale
computations: hybrid thread-MPI parallelization; efficient local numbering
of degrees of freedom; concurrent post-processing and write-out of results
using worker threads; as well as checkpointing and restart.

It should be noted that first-order schemes in the context of hyperbolic
conservation laws require prohibitively many degrees of freedom to resolve
certain key features of the simulated fluid, and thus, typically only serve
as elementary building blocks in higher-order schemes
@cite GuermondEtAl2018. However, we hope that the reader still finds the
tutorial step to be a good starting point (in particular with respect to
the programming techniques) before jumping into full research codes such as
the second-order scheme discussed in @cite GuermondEtAl2018.


<a name="eulerequations"></a>
<a name="Eulersequationsofgasdynamics"></a><h3>Euler's equations of gas dynamics</h3>


The compressible Euler's equations of gas dynamics are written in
conservative form as follows:
@f{align}
\mathbf{u}_t + \text{div} \, \mathbb{f}(\mathbf{u}) = \boldsymbol{0} ,
@f}
where $\mathbf{u}(\textbf{x},t):\mathbb{R}^{d} \times \mathbb{R}
\rightarrow \mathbb{R}^{d+2}$, and $\mathbb{f}(\mathbf{u}):\mathbb{R}^{d+2}
\rightarrow \mathbb{R}^{(d+2) \times d}$, and $d \geq 1$ is the space
dimension. We say that $\mathbf{u} \in \mathbb{R}^{d+2}$ is the state and
$\mathbb{f}(\mathbf{u}) \in  \mathbb{R}^{(d+2) \times d}$ is the flux of
the system. In the case of Euler's equations the state is given by
$\textbf{u} = [\rho, \textbf{m},E]^{\top}$: where $\rho \in \mathbb{R}^+$
denotes the density, $\textbf{m} \in \mathbb{R}^d$ is the momentum, and $E
\in \mathbb{R}^+$ is the total energy of the system. The flux of the system
$\mathbb{f}(\mathbf{u})$ is defined as
@f{align*}
\mathbb{f}(\textbf{u})
=
\begin{bmatrix}
  \textbf{m}^\top \\
  \rho^{-1} \textbf{m} \otimes \textbf{m} + \mathbb{I} p\\
  \tfrac{\textbf{m}^\top}{\rho} (E + p)
\end{bmatrix},
@f}
where $\mathbb{I} \in \mathbb{R}^{d \times d}$ is the identity matrix and
$\otimes$ denotes the tensor product. Here, we have introduced the pressure
$p$ that, in general, is defined by a closed-form equation of state.
In this tutorial we limit the discussion to the class of polytropic
ideal gases for which the pressure is given by
@f{align*}
p = p(\textbf{u}) := (\gamma -1) \Big(E -
\tfrac{|\textbf{m}|^2}{2\,\rho}
\Big),
@f}
where the factor $\gamma \in (1,5/3]$ denotes the <a
href="https://en.wikipedia.org/wiki/Heat_capacity_ratio">ratio of specific
heats</a>.


<a name="Solutiontheory"></a><h4>Solution theory</h4>


Hyperbolic conservation laws, such as
@f{align*}
\mathbf{u}_t + \text{div} \, \mathbb{f}(\mathbf{u}) = \boldsymbol{0},
@f}
pose a significant challenge with respect to solution theory. An evident
observation is that rewriting the equation in variational form and testing with
the solution itself does not lead to an energy estimate because the pairing
$\langle \text{div} \, \mathbb{f}(\mathbf{u}), \mathbf{u}\rangle$ (understood as
the $L^2(\Omega)$ inner product or duality pairing) is not guaranteed to be
non-negative. Notions such as energy-stability or $L^2(\Omega)$-stability are
(in general) meaningless in this context.

Historically, the most fruitful step taken in order to deepen the
understanding of hyperbolic conservation laws was to assume that the
solution is formally defined as $\mathbf{u} := \lim_{\epsilon \rightarrow
0^+} \mathbf{u}^{\epsilon}$ where $\mathbf{u}^{\epsilon}$ is the solution
of the parabolic regularization
@f{align}
\mathbf{u}_t^{\epsilon} + \text{div} \, \mathbb{f}(\mathbf{u}^{\epsilon})
- {\epsilon} \Delta \mathbf{u}^{\epsilon} = 0.
@f}
Such solutions, which are understood as the solution recovered in the
zero-viscosity limit, are often referred to as <i>viscosity solutions</i>.
(This is, because physically $\epsilon$ can be understood as related to the viscosity of the
fluid, i.e., a quantity that indicates the amount of friction neighboring gas particles moving at
different speeds exert on each other. The Euler equations themselves are derived under
the assumption of no friction, but can physically be expected to describe the limiting
case of vanishing friction or viscosity.)
Global existence and uniqueness of such solutions is an open issue.
However, we know at least that if such viscosity solutions exists they have
to satisfy the constraint $\textbf{u}(\mathbf{x},t) \in \mathcal{B}$ for
all $\mathbf{x} \in \Omega$ and $t \geq 0$ where
@f{align}
  \mathcal{B} = \big\{ \textbf{u} =
  [\rho, \textbf{m},E]^{\top} \in \mathbb{R}^{d+2} \, \big |
  \
  \rho > 0 \, ,
  \
  \ E - \tfrac{|\textbf{m}|^2}{2 \rho} > 0 \, ,
  \
  s(\mathbf{u}) \geq \min_{x \in \Omega} s(\mathbf{u}_0(\mathbf{x}))
  \big\}.
@f}
Here, $s(\mathbf{u})$ denotes the specific entropy
@f{align}
  s(\mathbf{u}) = \ln \Big(\frac{p(\mathbf{u})}{\rho^{\gamma}}\Big).
@f}
We will refer to $\mathcal{B}$ as the invariant set of Euler's equations.
In other words, a state $\mathbf{u}(\mathbf{x},t)\in\mathcal{B}$ obeys
positivity of the density, positivity of the internal energy, and a local
minimum principle on the specific entropy. This condition is a simplified
version of a class of pointwise stability constraints satisfied by the
exact (viscosity) solution. By pointwise we mean that the constraint has to
be satisfied at every point of the domain, not just in an averaged
(integral, or high order moments) sense.

In context of a numerical approximation, a violation of such a constraint
has dire consequences: it almost surely leads to catastrophic failure of
the numerical scheme, loss of hyperbolicity, and overall, loss of
well-posedness of the (discrete) problem. It would also mean that we have computed
something that can not be interpreted physically. (For example, what are we to make
of a computed solution with a negative density?) In the following we will
formulate a scheme that ensures that the discrete approximation of
$\mathbf{u}(\mathbf{x},t)$ remains in $\mathcal{B}$.


<a name="Variationalversuscollocationtypediscretizations"></a><h4>Variational versus collocation-type discretizations</h4>


Following Step-9, Step-12, Step-33, and Step-67, at this point it might look
tempting to base a discretization of Euler's equations on a (semi-discrete)
variational formulation:
@f{align*}
  (\partial_t\mathbf{u}_{h},\textbf{v}_h)_{L^2(\Omega)}
  - ( \mathbb{f}(\mathbf{u}_{h}) ,\text{grad} \, \textbf{v}_{h})_{L^2(\Omega)}
  + s_h(\mathbf{u}_{h},\textbf{v}_h)_{L^2(\Omega)} = \boldsymbol{0}
  \quad\forall \textbf{v}_h \in \mathbb{V}_h.
@f}
Here, $\mathbb{V}_h$ is an appropriate finite element space, and
$s_h(\cdot,\cdot)_{L^2(\Omega)}$ is some linear stabilization method
(possibly complemented with some ad-hoc shock-capturing technique, see for
instance Chapter 5 of @cite GuermondErn2004 and references therein). Most
time-dependent discretization approaches described in the deal.II tutorials
are based on such a (semi-discrete) variational approach. Fundamentally,
from an analysis perspective, variational discretizations are conceived
to provide some notion of global (integral) stability, meaning an
estimate of the form
@f{align*}
  |\!|\!| \mathbf{u}_{h}(t) |\!|\!| \leq |\!|\!| \mathbf{u}_{h}(0) |\!|\!|
@f}
holds true, where $|\!|\!| \cdot |\!|\!| $ could represent the
$L^2(\Omega)$-norm or, more generally, some discrete (possibly mesh
dependent) energy-norm. Variational discretizations of hyperbolic
conservation laws have been very popular since the mid eighties, in
particular combined with SUPG-type stabilization and/or upwinding
techniques (see the early work of @cite Brooks1982 and @cite Johnson1986). They
have proven to be some of the best approaches for simulations in the subsonic
shockless regime and similarly benign situations.

<!-- In particular, tutorial Step-67 focuses on Euler's equation of gas
dynamics in the subsonic regime using dG techniques. -->

However, in the transonic and supersonic regimes, and shock-hydrodynamics
applications the use of variational schemes might be questionable. In fact,
at the time of this writing, most shock-hydrodynamics codes are still
firmly grounded on finite volume methods. The main reason for failure of
variational schemes in such extreme regimes is the lack of pointwise
stability. This stems from the fact that <i>a priori</i> bounds on
integrated quantities (e.g. integrals of moments) have in general no
implications on pointwise properties of the solution. While some of these
problems might be alleviated by the (perpetual) chase of the right shock
capturing scheme, finite difference-like and finite volume schemes still
have an edge in many regards.

In this tutorial step we therefore depart from variational schemes. We will
present a completely algebraic formulation (with the flavor of a
collocation-type scheme) that preserves constraints pointwise, i.e.,
@f{align*}
  \textbf{u}_h(\mathbf{x}_i,t) \in \mathcal{B}
  \;\text{at every node}\;\mathbf{x}_i\;\text{of the mesh}.
@f}
Contrary to finite difference/volume schemes, the scheme implemented in
this step maximizes the use of finite element software infrastructure,
works on any mesh, in any space dimension, and is theoretically guaranteed
to always work, all the time, no exception. This illustrates that deal.II
can be used far beyond the context of variational schemes in Hilbert spaces
and that a large number of classes, modules and namespaces from deal.II can
be adapted for such a purpose.


<a name="Descriptionofthescheme"></a><h3>Description of the scheme </h3>


Let $\mathbb{V}_h$ be scalar-valued finite dimensional space spanned by a
basis $\{\phi_i\}_{i \in \mathcal{V}}$ where: $\phi_i:\Omega \rightarrow
\mathbb{R}$ and $\mathcal{V}$ is the set of all indices (nonnegative
integers) identifying each scalar Degree of Freedom (DOF) in the mesh.
Therefore a scalar finite element functional $u_h \in \mathbb{V}_h$ can
be written as $u_h = \sum_{i \in \mathcal{V}} U_i \phi_i$ with $U_i \in
\mathbb{R}$. We introduce the notation for vector-valued approximation
spaces $\pmb{\mathbb{V}}_h := \{\mathbb{V}_h\}^{d+2}$. Let $\mathbf{u}_h
\in \pmb{\mathbb{V}}_h$, then it can be written as $\mathbf{u}_h = \sum_{i
\in \mathcal{V}} \mathbf{U}_i \phi_i$ where $\mathbf{U}_i \in
\mathbb{R}^{d+2}$ and $\phi_i$ is a scalar-valued shape function.

@note We purposely refrain from using vector-valued finite element
spaces in our notation. Vector-valued finite element spaces
are natural for variational formulations of PDE systems (e.g. Navier-Stokes).
In such context, the interactions that have to be computed describe
<i>interactions between DOFs</i>: with proper renumbering of the
vector-valued DoFHandler (i.e. initialized with an FESystem) it is possible
to compute the block-matrices (required in order to advance the solution)
with relative ease. However, the interactions that have to be computed in
the context of time-explicit collocation-type schemes (such as finite
differences and/or the scheme presented in this tutorial) can be
better described as <i>interactions between nodes</i> (not between DOFs).
In addition, in our case we do not solve a linear equation in order to
advance the solution. This leaves very little reason to use vector-valued
finite element spaces both in theory and/or practice.

We will use the usual Lagrange finite elements: let $\{\mathbf{x}_i\}_{i \in
\mathcal{V}}$ denote the set of all support points (see @ref GlossSupport "this
glossary entry"), where $\mathbf{x}_i \in \mathbb{R}^d$. Then each index $i \in
\mathcal{V}$ uniquely identifies a support point $\mathbf{x}_i$, as well as a
scalar-valued shape function $\phi_i$. With this notation at hand we can define
the (explicit time stepping) scheme as:
@f{align*}{
  m_i \frac{\mathbf{U}_i^{n+1} - \mathbf{U}_i^{n}}{\tau}
  + \sum_{j \in \mathcal{I}(i)} \mathbb{f}(\mathbf{U}_j^{n})\cdot
  \mathbf{c}_{ij} - \sum_{j \in \mathcal{I}(i)}
  d_{ij} \mathbf{U}_j^{n} = \boldsymbol{0} \, ,
@f}
where
  - $m_i \dealcoloneq \int_{\Omega} \phi_i \, \mathrm{d}\mathbf{x}$
    is the lumped mass matrix
  - $\tau$ is the time step size
  - $\mathbf{c}_{ij} \dealcoloneq \int_{\Omega} \nabla\phi_j\phi_i \,
    \mathrm{d}\mathbf{x}$ (note that $\mathbf{c}_{ij}\in \mathbb{R}^d$)
    is a vector-valued matrix that was used to approximate the divergence
    of the flux in a weak sense.
  - $\mathcal{I}(i) \dealcoloneq \{j \in \mathcal{V} \ | \ \mathbf{c}_{ij}
    \not \equiv \boldsymbol{0}\} \cup \{i\}$ is the adjacency list
    containing all degrees of freedom coupling to the index $i$. In other
    words $\mathcal{I}(i)$ contains all nonzero column indices for row
    index i. $\mathcal{I}(i)$ will also be called a "stencil".
  - $\mathbb{f}(\mathbf{U}_j^{n})$ is the flux $\mathbb{f}$ of the
    hyperbolic system evaluated for the state $\mathbf{U}_j^{n}$ associated
    with support point $\mathbf{x}_j$.
  - $d_{ij} \dealcoloneq \max \{ \lambda_{\text{max}}
    (\mathbf{U}_i^{n},\mathbf{U}_j^{n}, \textbf{n}_{ij}),
    \lambda_{\text{max}} (\mathbf{U}_j^{n}, \mathbf{U}_i^{n},
    \textbf{n}_{ji}) \} \|\mathbf{c}_{ij}\|$ if $i \not = j$ is the so
    called <i>graph viscosity</i>. The graph viscosity serves as a
    stabilization term, it is somewhat the discrete counterpart of
    $\epsilon \Delta \mathbf{u}$ that appears in the notion of viscosity
    solution described above. We will base our construction of $d_{ij}$ on
    an estimate of the maximal local wavespeed $\lambda_{\text{max}}$ that
    will be explained in detail in a moment.
  - the diagonal entries of the viscosity matrix are defined as
    $d_{ii} = - \sum_{j \in \mathcal{I}(i)\backslash \{i\}} d_{ij}$.
  - $\textbf{n}_{ij} = \frac{\mathbf{c}_{ij}}{ \|\mathbf{c}_{ij}\| }$ is a
    normalization of the $\textbf{c}_{ij}$ matrix that enters the
    approximate Riemann solver with which we compute an the approximations
    $\lambda_{\text{max}}$ on the local wavespeed. (This will be explained
    further down below).

The definition of $\lambda_{\text{max}} (\mathbf{U},\mathbf{V},
\textbf{n})$ is far from trivial and we will postpone the precise
definition in order to focus first on some algorithmic and implementation
questions. We note that
  - $m_i$ and $\mathbf{c}_{ij}$ do not evolve in time (provided we keep the
    discretization fixed). It thus makes sense to assemble these
    matrices/vectors once in a so called <i>offline computation</i> and reuse
    them in every time step. They are part of what we are going to call
    off-line data.
  - At every time step we have to evaluate $\mathbb{f}(\mathbf{U}_j^{n})$ and
    $d_{ij} \dealcoloneq \max \{ \lambda_{\text{max}}
    (\mathbf{U}_i^{n},\mathbf{U}_j^{n}, \textbf{n}_{ij}),
    \lambda_{\text{max}} (\mathbf{U}_j^{n}, \mathbf{U}_i^{n},
    \textbf{n}_{ji}) \} \|\mathbf{c}_{ij}\| $, which will
    constitute the bulk of the computational cost.

Consider the following pseudo-code, illustrating a possible straight
forward strategy for computing the solution $\textbf{U}^{n+1}$ at a new
time $t_{n+1} = t_n + \tau_n$ given a known state $\textbf{U}^{n}$ at time
$t_n$:
@f{align*}
&\textbf{for } i \in \mathcal{V} \\
&\ \ \ \  \{\mathbf{c}_{ij}\}_{j \in \mathcal{I}(i)} \leftarrow
\mathtt{gather\_cij\_vectors} (\textbf{c}, \mathcal{I}(i)) \\
&\ \ \ \ \{\textbf{U}_j^n\}_{j \in \mathcal{I}(i)} \leftarrow
\mathtt{gather\_state\_vectors} (\textbf{U}^n, \mathcal{I}(i)) \\
&\ \ \ \ \ \textbf{U}_i^{n+1} \leftarrow \mathbf{U}_i^{n} \\
&\ \ \ \ \textbf{for } j \in \mathcal{I}(i)\backslash\{i\} \\
&\ \ \ \ \ \ \ \  \texttt{compute } d_{ij} \\
&\ \ \ \ \ \ \ \  \texttt{compute } \mathbb{f}(\mathbf{U}_j^{n}) \\
&\ \ \ \ \ \ \ \  \textbf{U}_i^{n+1} \leftarrow \textbf{U}_i^{n+1} - \frac{\tau_n}{m_i}
 \mathbb{f}(\mathbf{U}_j^{n})\cdot \mathbf{c}_{ij} + d_{ij} \mathbf{U}_j^{n} \\
&\ \ \ \ \textbf{end} \\
&\ \ \ \ \mathtt{scatter\_updated\_state} (\textbf{U}_i^{n+1}) \\
&\textbf{end}
@f}

We note here that:
- This "assembly" does not require any form of quadrature or cell-loops.
- Here $\textbf{c}$ and $\textbf{U}^n$ are a global matrix and a global vector
containing all the vectors $\mathbf{c}_{ij}$ and all the states
$\mathbf{U}_j^n$ respectively.
- $\mathtt{gather\_cij\_vectors}$, $\mathtt{gather\_state\_vectors}$, and
$\mathtt{scatter\_updated\_state}$ are hypothetical implementations that
either collect (from) or write (into) global matrices and vectors.
- If we assume a Cartesian mesh in two space
dimensions, first-order polynomial space $\mathbb{Q}^1$, and that
$\mathbf{x}_i$ is an interior node (i.e. $\mathbf{x}_i$ is not on the boundary
of the domain) then: $\{\textbf{U}_j^n\}_{j \in \mathcal{I}(i)}$ should contain
nine state vector elements (i.e. all the states in the patch/macro element
associated to the shape function $\phi_i$). This is one of the major
differences with the usual cell-based loop where the gather functionality
(encoded in FEValuesBase<dim, spacedim>.get_function_values() in the case
of deal.II) only collects values for the local cell (just a subset of the
patch).

The actual implementation will deviate from above code in one key aspect:
the time-step size $\tau$ has to be chosen subject to a CFL condition
@f{align*}
  \tau_n = c_{\text{cfl}}\,\min_{
  i\in\mathcal{V}}\left(\frac{m_i}{-2\,d_{ii}^{n}}\right),
@f}
where $0<c_{\text{cfl}}\le1$ is a chosen constant. This will require to
compute all $d_{ij}$ in a separate step prior to actually performing above
update. The core principle remains unchanged, though: we do not loop over
cells but rather over all edges of the sparsity graph.

@note It is not uncommon to encounter such fully-algebraic schemes (i.e.
no bilinear forms, no cell loops, and no quadrature) outside of the finite
element community in the wider CFD community. There is a rich history of
application of this kind of schemes, also called <i>edge-based</i> or
<i>graph-based</i> finite element schemes (see for instance
@cite Rainald2008 for a historical overview). However, it is important to
highlight that the algebraic structure of the scheme (presented in this
tutorial) and the node-loops are not just a performance gimmick. Actually, the
structure of this scheme was born out of theoretical necessity: the proof of
pointwise stability of the scheme hinges on the specific algebraic structure of
the scheme. In addition, it is not possible to compute the algebraic
viscosities $d_{ij}$ using cell-loops since they depend nonlinearly on
information that spans more than one cell (superposition does not hold: adding
contributions from separate cells does not lead to the right result).

<a name="Stableboundaryconditionsandconservationproperties"></a><h3>Stable boundary conditions and conservation properties.</h3>


In the example considered in this tutorial step we use three different types of
boundary conditions: essential-like boundary conditions (we prescribe a
state at the left boundary of our domain), outflow boundary conditions
(also called "do-nothing" boundary conditions) at the right boundary of the
domain, and "reflecting" boundary conditions $\mathbf{m} \cdot
\boldsymbol{\nu} = 0$ (also called "slip" boundary conditions) at the top,
bottom, and surface of the obstacle. We will not discuss much about
essential and "do-nothing" boundary conditions since their implementation
is relatively easy and the reader will be able to pick-up the
implementation directly from the (documented) source code. In this portion
of the introduction we will focus only on the "reflecting" boundary
conditions which are somewhat more tricky.

@note At the time of this writing (early 2020) it is not unreasonable to say
that both analysis and implementation of stable boundary conditions for
hyperbolic systems of conservation laws is an open issue. For the case of
variational formulations, stable boundary conditions are those leading to a
well-posed (coercive) bilinear form. But for general hyperbolic
systems of conservation laws (and for the algebraic formulation used in this
tutorial) coercivity has no applicability and/or meaning as a notion of
stability. In this tutorial step we will use preservation of the invariant set
as our main notion of stability which (at the very least) guarantees
well-posedness of the discrete problem.

For the case of the reflecting boundary conditions we will proceed as follows:
- For every time step advance in time satisfying no boundary condition at all.
- Let $\partial\Omega^r$ be the portion of the boundary where we want to
  enforce reflecting boundary conditions. At the end of the time step we enforce
  reflecting boundary conditions strongly in a post-processing step where we
  execute the projection
    @f{align*}
    \mathbf{m}_i \dealcoloneq \mathbf{m}_i - (\widehat{\boldsymbol{\nu}}_i
    \cdot \mathbf{m}_i)  \widehat{\boldsymbol{\nu}}_i \ \
    \text{where} \ \
    \widehat{\boldsymbol{\nu}}_i \dealcoloneq
    \frac{\int_{\partial\Omega} \phi_i \widehat{\boldsymbol{\nu}} \,
    \, \mathrm{d}\mathbf{s}}{\big|\int_{\partial\Omega} \phi_i
    \widehat{\boldsymbol{\nu}} \, \mathrm{d}\mathbf{s}\big|}
    \ \ \text{for all }\mathbf{x}_i \in \partial\Omega^r
    \ \ \ \ \boldsymbol{(1)}
    @f}
  that removes the normal component of $\mathbf{m}$. This is a somewhat
  naive idea that preserves a few fundamental properties of the PDE as we
  explain below.

This is approach is usually called "explicit treatment of boundary conditions".
The well seasoned finite element person might find this approach questionable.
No doubt, when solving parabolic, or elliptic equations, we typically enforce
essential (Dirichlet-like) boundary conditions by making them part of the
approximation space $\mathbb{V}$, and treat natural (e.g. Neumann) boundary
conditions as part of the variational formulation. We also know that explicit
treatment of boundary conditions (in the context of parabolic PDEs) almost
surely leads to catastrophic consequences. However, in the context of nonlinear
hyperbolic equations we have that:
- It is relatively easy to prove that (for the case of reflecting boundary
conditions) explicit treatment of boundary conditions is not only conservative
but also guarantees preservation of the property $\mathbf{U}_i \in \mathcal{B}$
for all $i \in \mathcal{V}$ (well-posedness). This is perhaps the most
important reason to use explicit enforcement of boundary conditions.
- To the best of our knowledge: we are not aware of any mathematical result
proving that it is possible to guarantee the property $\mathbf{U}_i \in
\mathcal{B}$ for all $i \in \mathcal{V}$ when using either direct enforcement of
boundary conditions into the approximation space, or weak enforcement using the
Nitsche penalty method (which is for example widely used in discontinuous
Galerkin schemes). In addition, some of these traditional ideas lead to quite
restrictive time step constraints.
- There is enough numerical evidence suggesting that explicit treatment of
Dirichlet-like boundary conditions is stable under CFL conditions and does not
introduce any loss in accuracy.

If $\mathbf{u}_t + \text{div} \, \mathbb{f}(\mathbf{u}) = \boldsymbol{0}$
represents Euler's equation with reflecting boundary conditions on the entirety
of the boundary (i.e. $\partial\Omega^r \equiv \partial\Omega$) and we
integrate in space and time $\int_{\Omega}\int_{t_1}^{t_2}$ we would obtain
@f{align*}
\int_{\Omega} \rho(\mathbf{x},t_2) \, \mathrm{d}\mathbf{x} =
\int_{\Omega} \rho(\mathbf{x},t_1) \, \mathrm{d}\mathbf{x} \ , \ \
\int_{\Omega} \mathbf{m}(\mathbf{x},t_2) \, \mathrm{d}\mathbf{x}
+ \int_{t_1}^{t_2} \! \int_{\partial\Omega} p \boldsymbol{\nu} \,
\mathrm{d}\mathbf{s} \mathrm{d}t =
\int_{\Omega} \mathbf{m}(\mathbf{x},t_1) \,
\mathrm{d}\mathbf{x} \ , \ \
\int_{\Omega} E(\mathbf{x},t_2) \, \mathrm{d}\mathbf{x} =
\int_{\Omega} E(\mathbf{x},t_1) \, \mathrm{d}\mathbf{x} \ \ \ \
\boldsymbol{(2)}
@f}
Note that momentum is NOT a conserved quantity (interaction with walls leads to
momentum gain/loss): however $\mathbf{m}$ has to satisfy a momentum balance.
Even though we will not use reflecting boundary conditions in the entirety of
the domain, we would like to know that our implementation of reflecting
boundary conditions is consistent with the conservation properties mentioned
above. In particular, if we use the projection $\boldsymbol{(1)}$ in the
entirety of the domain the following discrete mass-balance can be guaranteed:
@f{align*}
\sum_{i \in \mathcal{V}} m_i \rho_i^{n+1} =
\sum_{i \in \mathcal{V}} m_i \rho_i^{n} \ , \ \
\sum_{i \in \mathcal{V}} m_i \mathbf{m}_i^{n+1}
+ \tau_n \int_{\partial\Omega} \Big(\sum_{i \in \mathcal{V}} p_i^{n} \phi_i\Big)
\widehat{\boldsymbol{\nu}} \mathrm{d}\mathbf{s} =
\sum_{i \in \mathcal{V}} m_i \mathbf{m}_i^{n} \ , \ \
\sum_{i \in \mathcal{V}} m_i E_i^{n+1} = \sum_{i \in \mathcal{V}} m_i
E_i^{n} \ \ \ \
\boldsymbol{(3)}
@f}
where $p_i$ is the pressure at the nodes that lie at the boundary. Clearly
$\boldsymbol{(3)}$ is the discrete counterpart of $\boldsymbol{(2)}$. The
proof of identity $\boldsymbol{(3)}$ is omitted, but we briefly mention that
it hinges on the definition of the <i>nodal normal</i>
$\widehat{\boldsymbol{\nu}}_i$ provided in $\boldsymbol{(1)}$. We also note that
this enforcement of reflecting boundary conditions is different from the one
originally advanced in @cite GuermondEtAl2018.


 <a name="CommProg"></a>
 <h1> The commented program</h1>
 
 
 <a name="Includefiles"></a> 
 <h3>Include files</h3>
 

 
 The set of include files is quite standard. The most intriguing part is
 the fact that we will rely solely on deal.II data structures for MPI
 parallelization, in particular parallel::distributed::Triangulation and
 LinearAlgebra::distributed::Vector included through
 <code>distributed/tria.h</code> and
 <code>lac/la_parallel_vector.h</code>. Instead of a Trilinos, or PETSc
 specific matrix class, we will use a non-distributed
 dealii::SparseMatrix (<code>lac/sparse_matrix.h</code>) to store the local
 part of the $\mathbf{c}_{ij}$, $\mathbf{n}_{ij}$ and $d_{ij}$ matrices.
 
 @code
 #include <deal.II/base/conditional_ostream.h>
 #include <deal.II/base/parallel.h>
 #include <deal.II/base/parameter_acceptor.h>
 #include <deal.II/base/partitioner.h>
 #include <deal.II/base/quadrature.h>
 #include <deal.II/base/timer.h>
 #include <deal.II/base/work_stream.h>
 
 #include <deal.II/distributed/tria.h>
 
 #include <deal.II/dofs/dof_handler.h>
 #include <deal.II/dofs/dof_renumbering.h>
 #include <deal.II/dofs/dof_tools.h>
 
 #include <deal.II/fe/fe.h>
 #include <deal.II/fe/fe_q.h>
 #include <deal.II/fe/fe_values.h>
 #include <deal.II/fe/mapping.h>
 #include <deal.II/fe/mapping_q.h>
 
 #include <deal.II/grid/grid_generator.h>
 #include <deal.II/grid/manifold_lib.h>
 
 #include <deal.II/lac/dynamic_sparsity_pattern.h>
 #include <deal.II/lac/la_parallel_vector.h>
 #include <deal.II/lac/sparse_matrix.h>
 #include <deal.II/lac/sparse_matrix.templates.h>
 #include <deal.II/lac/vector.h>
 
 #include <deal.II/meshworker/scratch_data.h>
 
 #include <deal.II/numerics/data_out.h>
 #include <deal.II/numerics/vector_tools.h>
 
 @endcode
 
 In addition to above deal.II specific includes, we also include four
 boost headers. The first two are for binary archives that we will use
 for implementing a check-pointing and restart mechanism.
 
 @code
 #include <boost/archive/binary_iarchive.hpp>
 #include <boost/archive/binary_oarchive.hpp>
 
 @endcode
 
 The last two header files are for creating custom iterator ranges
 over integer intervals.
 
 @code
 #include <deal.II/base/std_cxx20/iota_view.h>
 #include <boost/range/iterator_range.hpp>
 
 @endcode
 
 For std::isnan, std::isinf, std::ifstream, std::async, and std::future
 
 @code
 #include <cmath>
 #include <fstream>
 #include <future>
 
 
 @endcode
 
 
 <a name="Classtemplatedeclarations"></a> 
 <h3>Class template declarations</h3>
 

 
 We begin our actual implementation by declaring all classes with their
 data structures and methods upfront. In contrast to previous example
 steps we use a more fine-grained encapsulation of concepts, data
 structures, and parameters into individual classes. A single class thus
 usually centers around either a single data structure (such as the
 Triangulation) in the <code>Discretization</code> class, or a single
 method (such as the <code>make_one_step()</code> function of the
 <code>%TimeStepping</code> class). We typically declare parameter variables
 and scratch data object `private` and make methods and data structures
 used by other classes `public`.
 

 
 @note A cleaner approach would be to guard access to all data
 structures by <a
 href="https://en.wikipedia.org/wiki/Mutator_method">getter/setter
 functions</a>. For the sake of brevity, we refrain from that approach,
 though.
 

 
 We also note that the vast majority of classes is derived from
 ParameterAcceptor. This facilitates the population of all the global
 parameters into a single (global) ParameterHandler. More explanations
 about the use of inheritance from ParameterAcceptor as a global
 subscription mechanism can be found in step-60.
 
 @code
 namespace Step69
 {
   using namespace dealii;
 
 @endcode
 
 We start with defining a number of types::boundary_id constants used
 throughout the tutorial step. This allows us to refer to boundary
 types by a mnemonic (such as <code>do_nothing</code>) rather than a
 numerical value.
 

 
 
 @code
   namespace Boundaries
   {
     constexpr types::boundary_id do_nothing = 0;
     constexpr types::boundary_id free_slip  = 1;
     constexpr types::boundary_id dirichlet  = 2;
   } // namespace Boundaries
 
 @endcode
 
 
 <a name="ThecodeDiscretizationcodeclass"></a> 
 <h4>The <code>Discretization</code> class</h4>
   

 
 The class <code>Discretization</code> contains all data structures
 concerning the mesh (triangulation) and discretization (mapping,
 finite element, quadrature) of the problem. As mentioned, we use
 the ParameterAcceptor class to automatically populate problem-specific
 parameters, such as the geometry information
 (<code>length</code>, etc.) or the refinement level
 (<code>refinement</code>) from a parameter file. This requires us to
 split the initialization of data structures into two functions: We
 initialize everything that does not depend on parameters in the
 constructor, and defer the creation of the mesh to the
 <code>setup()</code> method that can be called once all parameters are
 read in via ParameterAcceptor::initialize().
 
 @code
   template <int dim>
   class Discretization : public ParameterAcceptor
   {
   public:
     Discretization(const MPI_Comm     mpi_communicator,
                    TimerOutput &      computing_timer,
                    const std::string &subsection = "Discretization");
 
     void setup();
 
     const MPI_Comm mpi_communicator;
 
     parallel::distributed::Triangulation<dim> triangulation;
 
     const MappingQ<dim>   mapping;
     const FE_Q<dim>       finite_element;
     const QGauss<dim>     quadrature;
     const QGauss<dim - 1> face_quadrature;
 
   private:
     TimerOutput &computing_timer;
 
     double length;
     double height;
     double disk_position;
     double disk_diameter;
 
     unsigned int refinement;
   };
 
 @endcode
 
 
 <a name="ThecodeOfflineDatacodeclass"></a> 
 <h4>The <code>OfflineData</code> class</h4>
   

 
 The class <code>OfflineData</code> contains pretty much all components
 of the discretization that do not evolve in time, in particular, the
 DoFHandler, SparsityPattern, boundary maps, the lumped mass matrix,
 $\mathbf{c}_{ij}$ and $\mathbf{n}_{ij}$ matrices. Here, the term
 <i>offline</i> refers to the fact that all the class
 members of <code>OfflineData</code> have well-defined values
 independent of the current time step. This means that they can be
 initialized ahead of time (at <i>time step zero</i>) and are not meant
 to be modified at any later time step. For instance, the
 sparsity pattern should not change as we advance in time (we are not
 doing any form of adaptivity in space). Similarly, the entries of the
 lumped mass matrix should not be modified as we advance in time
 either.
   

 
 We also compute and store a <code>boundary_normal_map</code> that
 contains a map from a global index of type types::global_dof_index of
 a boundary degree of freedom to a tuple consisting of a normal vector,
 the boundary id, and the position associated with the degree of
 freedom. We have to compute and store this geometric
 information in this class because we won't have access to geometric
 (or cell-based) information later on in the algebraic loops over the
 sparsity pattern.
   

 
 @note Even though this class currently does not have any parameters
 that could be read in from a parameter file we nevertheless derive
 from ParameterAcceptor and follow the same idiom of providing a
 <code>setup()</code> (and <code>assemble()</code>) method as for the
 class Discretization.
 
 @code
   template <int dim>
   class OfflineData : public ParameterAcceptor
   {
   public:
     using BoundaryNormalMap =
       std::map<types::global_dof_index,
                std::tuple<Tensor<1, dim>, types::boundary_id, Point<dim>>>;
 
     OfflineData(const MPI_Comm             mpi_communicator,
                 TimerOutput &              computing_timer,
                 const Discretization<dim> &discretization,
                 const std::string &        subsection = "OfflineData");
 
     void setup();
     void assemble();
 
     DoFHandler<dim> dof_handler;
 
     std::shared_ptr<const Utilities::MPI::Partitioner> partitioner;
 
     unsigned int n_locally_owned;
     unsigned int n_locally_relevant;
 
     SparsityPattern sparsity_pattern;
 
     BoundaryNormalMap boundary_normal_map;
 
     SparseMatrix<double>                  lumped_mass_matrix;
     std::array<SparseMatrix<double>, dim> cij_matrix;
     std::array<SparseMatrix<double>, dim> nij_matrix;
     SparseMatrix<double>                  norm_matrix;
 
   private:
     const MPI_Comm mpi_communicator;
     TimerOutput &  computing_timer;
 
     SmartPointer<const Discretization<dim>> discretization;
   };
 
 @endcode
 
 
 <a name="ThecodeProblemDescriptioncodeclass"></a> 
 <h4>The <code>ProblemDescription</code> class</h4>
   

 
 The member functions of this class are utility functions and data
 structures specific to Euler's equations:
 - The type alias <code>state_type</code> is used for the states
 $\mathbf{U}_i^n$
 - The type alias <code>flux_type</code> is used for the fluxes
 $\mathbb{f}(\mathbf{U}_j^n)$.
 - The <code>momentum</code> function extracts $\textbf{m}$
 out of the state vector $[\rho,\textbf{m},E]$ and stores it in a
 <code>Tensor<1, dim></code>.
 - The <code>internal_energy</code> function computes $E -
 \frac{|\textbf{m}|^2}{2\rho}$ from a given state vector
 $[\rho,\textbf{m},E]$.
   

 
 The purpose of the class members <code>component_names</code>,
 <code>pressure</code>, and <code>speed_of_sound</code> is evident from
 their names. We also provide a function
 <code>compute_lambda_max()</code>, that computes the wave speed
 estimate mentioned above,
 $\lambda_{max}(\mathbf{U},\mathbf{V},\mathbf{n})$, which is used in
 the computation of the $d_{ij}$ matrix.
   

 
 @note The <code>DEAL_II_ALWAYS_INLINE</code> macro expands to a
 (compiler specific) pragma that ensures that the corresponding
 function defined in this class is always inlined, i.e., the function
 body is put in place for every invocation of the function, and no call
 (and code indirection) is generated. This is stronger than the
 <code>inline</code> keyword, which is more or less a (mild) suggestion
 to the compiler that the programmer thinks it would be beneficial to
 inline the function. <code>DEAL_II_ALWAYS_INLINE</code> should only be
 used rarely and with caution in situations such as this one, where we
 actually know (due to benchmarking) that inlining the function in
 question improves performance.
   

 
 Finally, we observe that this is the only class in this tutorial step
 that is tied to a particular "physics" or "hyperbolic conservation
 law" (in this case Euler's equations). All the other classes are
 primarily "discretization" classes, very much agnostic of the
 particular physics being solved.
 
 @code
   template <int dim>
   class ProblemDescription
   {
   public:
     static constexpr unsigned int problem_dimension = 2 + dim;
 
     using state_type = Tensor<1, problem_dimension>;
     using flux_type  = Tensor<1, problem_dimension, Tensor<1, dim>>;
 
     const static std::array<std::string, problem_dimension> component_names;
 
     static constexpr double gamma = 7. / 5.;
 
     static DEAL_II_ALWAYS_INLINE inline Tensor<1, dim>
     momentum(const state_type &U);
 
     static DEAL_II_ALWAYS_INLINE inline double
     internal_energy(const state_type &U);
 
     static DEAL_II_ALWAYS_INLINE inline double pressure(const state_type &U);
 
     static DEAL_II_ALWAYS_INLINE inline double
     speed_of_sound(const state_type &U);
 
     static DEAL_II_ALWAYS_INLINE inline flux_type flux(const state_type &U);
 
     static DEAL_II_ALWAYS_INLINE inline double
     compute_lambda_max(const state_type &    U_i,
                        const state_type &    U_j,
                        const Tensor<1, dim> &n_ij);
   };
 
 @endcode
 
 
 <a name="ThecodeInitialValuescodeclass"></a> 
 <h4>The <code>InitialValues</code> class</h4>
   

 
 The class <code>InitialValues</code>'s only public data attribute is a
 std::function <code>initial_state</code> that computes the initial
 state of a given point and time. This function is used for populating
 the initial flow field as well as setting Dirichlet boundary
 conditions (at inflow boundaries) explicitly in every time step.
   

 
 For the purpose of this example step
 we simply implement a homogeneous uniform flow field for which the
 direction and a 1D primitive state (density, velocity, pressure) are
 read from the parameter file.
   

 
 It would be desirable to initialize the class in a single shot:
 initialize/set the parameters and define the class members that
 depend on these default parameters. However, since we do not know the
 actual values for the parameters, this would be sort of
 meaningless and unsafe in general (we would like to have mechanisms to
 check the consistency of the input parameters). Instead of defining
 another <code>setup()</code> method to be called (by-hand) after the
 call to ParameterAcceptor::initialize() we provide an
 "implementation" for the class member
 <code>parse_parameters_call_back()</code> which is automatically
 called when invoking ParameterAcceptor::initialize() for every class
 that inherits from ParameterAceptor.
 
 @code
   template <int dim>
   class InitialValues : public ParameterAcceptor
   {
   public:
     using state_type = typename ProblemDescription<dim>::state_type;
 
     InitialValues(const std::string &subsection = "InitialValues");
 
     std::function<state_type(const Point<dim> &point, double t)> initial_state;
 
   private:
 @endcode
 
 We declare a private callback function that will be wired up to the
 ParameterAcceptor::parse_parameters_call_back signal.
 
 @code
     void parse_parameters_callback();
 
     Tensor<1, dim> initial_direction;
     Tensor<1, 3>   initial_1d_state;
   };
 
 @endcode
 
 
 <a name="ThecodeTimeSteppingcodeclass"></a> 
 <h4>The <code>%TimeStepping</code> class</h4>
   

 
 With the <code>OfflineData</code> and <code>ProblemDescription</code>
 classes at hand we can now implement the explicit time-stepping scheme
 that was introduced in the discussion above. The main method of the
 <code>%TimeStepping</code> class is <code>make_one_step(vector_type &U,
 double t)</code> that takes a reference to a state vector
 <code>U</code> and a time point <code>t</code> (as input arguments)
 computes the updated solution, stores it in the vector
 <code>temp</code>, swaps its contents with the vector <code>U</code>,
 and returns the chosen step-size $\tau$.
   

 
 The other important method is <code>prepare()</code> which primarily
 sets the proper partition and sparsity pattern for the temporary
 vector <code>temp</code> and the matrix <code>dij_matrix</code>
 respectively.
 
 @code
   template <int dim>
   class TimeStepping : public ParameterAcceptor
   {
   public:
     static constexpr unsigned int problem_dimension =
       ProblemDescription<dim>::problem_dimension;
 
     using state_type = typename ProblemDescription<dim>::state_type;
     using flux_type  = typename ProblemDescription<dim>::flux_type;
 
     using vector_type =
       std::array<LinearAlgebra::distributed::Vector<double>, problem_dimension>;
 
     TimeStepping(const MPI_Comm            mpi_communicator,
                  TimerOutput &             computing_timer,
                  const OfflineData<dim> &  offline_data,
                  const InitialValues<dim> &initial_values,
                  const std::string &       subsection = "TimeStepping");
 
     void prepare();
 
     double make_one_step(vector_type &U, double t);
 
   private:
     const MPI_Comm mpi_communicator;
     TimerOutput &  computing_timer;
 
     SmartPointer<const OfflineData<dim>>   offline_data;
     SmartPointer<const InitialValues<dim>> initial_values;
 
     SparseMatrix<double> dij_matrix;
 
     vector_type temporary_vector;
 
     double cfl_update;
   };
 
 @endcode
 
 
 <a name="ThecodeSchlierenPostprocessorcodeclass"></a> 
 <h4>The <code>SchlierenPostprocessor</code> class</h4>
   

 
 At its core, the Schlieren class implements the class member
 <code>compute_schlieren()</code>. The main purpose of this class member
 is to compute an auxiliary finite element field
 <code>schlieren</code>, that is defined at each node by
 \f[ \text{schlieren}[i] = e^{\beta \frac{ |\nabla r_i|
 - \min_j |\nabla r_j| }{\max_j |\nabla r_j| - \min_j |\nabla r_j| } }, \f]
 where $r$ can in principle be any scalar quantity. In practice
 though, the density is a natural candidate, viz. $r \dealcoloneq \rho$.
 <a href="https://en.wikipedia.org/wiki/Schlieren">Schlieren</a>
 postprocessing is a standard method for enhancing the contrast of a
 visualization inspired by actual experimental X-ray and shadowgraphy
 techniques of visualization. (See step-67 for another example where we
 create a Schlieren plot.)
 
 @code
   template <int dim>
   class SchlierenPostprocessor : public ParameterAcceptor
   {
   public:
     static constexpr unsigned int problem_dimension =
       ProblemDescription<dim>::problem_dimension;
 
     using state_type = typename ProblemDescription<dim>::state_type;
 
     using vector_type =
       std::array<LinearAlgebra::distributed::Vector<double>, problem_dimension>;
 
     SchlierenPostprocessor(
       const MPI_Comm          mpi_communicator,
       TimerOutput &           computing_timer,
       const OfflineData<dim> &offline_data,
       const std::string &     subsection = "SchlierenPostprocessor");
 
     void prepare();
 
     void compute_schlieren(const vector_type &U);
 
     LinearAlgebra::distributed::Vector<double> schlieren;
 
   private:
     const MPI_Comm mpi_communicator;
     TimerOutput &  computing_timer;
 
     SmartPointer<const OfflineData<dim>> offline_data;
 
     Vector<double> r;
 
     unsigned int schlieren_index;
     double       schlieren_beta;
   };
 
 @endcode
 
 
 <a name="ThecodeMainLoopcodeclass"></a> 
 <h4>The <code>MainLoop</code> class</h4>
   

 
 Now, all that is left to do is to chain the methods implemented in the
 <code>%TimeStepping</code>, <code>InitialValues</code>, and
 <code>SchlierenPostprocessor</code> classes together. We do this in a
 separate class <code>MainLoop</code> that contains an object of every
 class and again reads in a number of parameters with the help of the
 ParameterAcceptor class.
 
 @code
   template <int dim>
   class MainLoop : public ParameterAcceptor
   {
   public:
     using vector_type = typename TimeStepping<dim>::vector_type;
 
     MainLoop(const MPI_Comm mpi_communnicator);
 
     void run();
 
   private:
     vector_type interpolate_initial_values(const double t = 0);
 
     void output(const vector_type &U,
                 const std::string &name,
                 double             t,
                 unsigned int       cycle,
                 bool               checkpoint = false);
 
     const MPI_Comm     mpi_communicator;
     std::ostringstream timer_output;
     TimerOutput        computing_timer;
 
     ConditionalOStream pcout;
 
     std::string base_name;
     double      t_final;
     double      output_granularity;
 
     bool asynchronous_writeback;
 
     bool resume;
 
     Discretization<dim>         discretization;
     OfflineData<dim>            offline_data;
     InitialValues<dim>          initial_values;
     TimeStepping<dim>           time_stepping;
     SchlierenPostprocessor<dim> schlieren_postprocessor;
 
     vector_type output_vector;
 
     std::future<void> background_thread_state;
   };
 
 @endcode
 
 
 <a name="Implementation"></a> 
 <h3>Implementation</h3>
 

 
 
 <a name="Gridgenerationsetupofdatastructures"></a> 
 <h4>Grid generation, setup of data structures</h4>
 

 
 The first major task at hand is the typical triplet of grid
 generation, setup of data structures, and assembly. A notable novelty
 in this example step is the use of the ParameterAcceptor class that we
 use to populate parameter values: we first initialize the
 ParameterAcceptor class by calling its constructor with a string
 <code>subsection</code> denoting the correct subsection in the
 parameter file. Then, in the constructor body every parameter value is
 initialized to a sensible default value and registered with the
 ParameterAcceptor class with a call to
 ParameterAcceptor::add_parameter().
 
 @code
   template <int dim>
   Discretization<dim>::Discretization(const MPI_Comm     mpi_communicator,
                                       TimerOutput &      computing_timer,
                                       const std::string &subsection)
     : ParameterAcceptor(subsection)
     , mpi_communicator(mpi_communicator)
     , triangulation(mpi_communicator)
     , mapping(1)
     , finite_element(1)
     , quadrature(3)
     , face_quadrature(3)
     , computing_timer(computing_timer)
   {
     length = 4.;
     add_parameter("length", length, "Length of computational domain");
 
     height = 2.;
     add_parameter("height", height, "Height of computational domain");
 
     disk_position = 0.6;
     add_parameter("object position",
                   disk_position,
                   "x position of immersed disk center point");
 
     disk_diameter = 0.5;
     add_parameter("object diameter",
                   disk_diameter,
                   "Diameter of immersed disk");
 
     refinement = 5;
     add_parameter("refinement",
                   refinement,
                   "Number of refinement steps of the geometry");
   }
 
 @endcode
 
 Note that in the previous constructor we only passed the MPI
 communicator to the <code>triangulation</code> but we still have not
 initialized the underlying geometry/mesh. As mentioned earlier, we
 have to postpone this task to the <code>setup()</code> function that
 gets called after the ParameterAcceptor::initialize() function has
 populated all parameter variables with the final values read from the
 parameter file.
   

 
 The <code>setup()</code> function is the last class member that has to
 be implemented. It creates the actual triangulation that is a
 benchmark configuration consisting of a channel with a disk obstacle, see
 @cite GuermondEtAl2018. We construct the geometry by modifying the
 mesh generated by GridGenerator::hyper_cube_with_cylindrical_hole().
 We refer to step-49, step-53, and step-54 for an overview how to
 create advanced meshes.
 We first create 4 temporary (non distributed) coarse triangulations
 that we stitch together with the GridGenerator::merge_triangulation()
 function. We center the disk at $(0,0)$ with a diameter of
 <code>disk_diameter</code>. The lower left corner of the channel has
 coordinates (<code>-disk_position</code>, <code>-height/2</code>) and
 the upper right corner has (<code>length-disk_position</code>,
 <code>height/2</code>).
 
 @code
   template <int dim>
   void Discretization<dim>::setup()
   {
     TimerOutput::Scope scope(computing_timer, "discretization - setup");
 
     triangulation.clear();
 
     Triangulation<dim> tria1, tria2, tria3, tria4, tria5, tria6;
 
     GridGenerator::hyper_cube_with_cylindrical_hole(
       tria1, disk_diameter / 2., disk_diameter, 0.5, 1, false);
 
     GridGenerator::subdivided_hyper_rectangle(
       tria2,
       {2, 1},
       Point<2>(-disk_diameter, disk_diameter),
       Point<2>(disk_diameter, height / 2.));
 
     GridGenerator::subdivided_hyper_rectangle(
       tria3,
       {2, 1},
       Point<2>(-disk_diameter, -disk_diameter),
       Point<2>(disk_diameter, -height / 2.));
 
     GridGenerator::subdivided_hyper_rectangle(
       tria4,
       {6, 2},
       Point<2>(disk_diameter, -disk_diameter),
       Point<2>(length - disk_position, disk_diameter));
 
     GridGenerator::subdivided_hyper_rectangle(
       tria5,
       {6, 1},
       Point<2>(disk_diameter, disk_diameter),
       Point<2>(length - disk_position, height / 2.));
 
     GridGenerator::subdivided_hyper_rectangle(
       tria6,
       {6, 1},
       Point<2>(disk_diameter, -height / 2.),
       Point<2>(length - disk_position, -disk_diameter));
 
     GridGenerator::merge_triangulations(
       {&tria1, &tria2, &tria3, &tria4, &tria5, &tria6},
       triangulation,
       1.e-12,
       true);
 
     triangulation.set_manifold(0, PolarManifold<2>(Point<2>()));
 
 @endcode
 
 We have to fix up the left edge that is currently located at
 $x=-$<code>disk_diameter</code> and has to be shifted to
 $x=-$<code>disk_position</code>. As a last step the boundary has to
 be colorized with <code>Boundaries::do_nothing</code> on the right,
 <code>dirichlet</code> on the left and <code>free_slip</code> on the
 upper and lower outer boundaries and the obstacle.
 

 
 
 @code
     for (const auto &cell : triangulation.active_cell_iterators())
       {
         for (const auto v : cell->vertex_indices())
           {
             if (cell->vertex(v)[0] <= -disk_diameter + 1.e-6)
               cell->vertex(v)[0] = -disk_position;
           }
       }
 
     for (const auto &cell : triangulation.active_cell_iterators())
       {
         for (const auto f : cell->face_indices())
           {
             const auto face = cell->face(f);
 
             if (face->at_boundary())
               {
                 const auto center = face->center();
 
                 if (center[0] > length - disk_position - 1.e-6)
                   face->set_boundary_id(Boundaries::do_nothing);
                 else if (center[0] < -disk_position + 1.e-6)
                   face->set_boundary_id(Boundaries::dirichlet);
                 else
                   face->set_boundary_id(Boundaries::free_slip);
               }
           }
       }
 
     triangulation.refine_global(refinement);
   }
 
 @endcode
 
 
 <a name="Assemblyofofflinematrices"></a> 
 <h4>Assembly of offline matrices</h4>
 

 
 Not much is done in the constructor of <code>OfflineData</code> other
 than initializing the corresponding class members in the
 initialization list.
 
 @code
   template <int dim>
   OfflineData<dim>::OfflineData(const MPI_Comm             mpi_communicator,
                                 TimerOutput &              computing_timer,
                                 const Discretization<dim> &discretization,
                                 const std::string &        subsection)
     : ParameterAcceptor(subsection)
     , dof_handler(discretization.triangulation)
     , mpi_communicator(mpi_communicator)
     , computing_timer(computing_timer)
     , discretization(&discretization)
   {}
 
 @endcode
 
 Now we can initialize the DoFHandler, extract the IndexSet objects for
 locally owned and locally relevant DOFs, and initialize a
 Utilities::MPI::Partitioner object that is needed for distributed
 vectors.
 
 @code
   template <int dim>
   void OfflineData<dim>::setup()
   {
     IndexSet locally_owned;
     IndexSet locally_relevant;
 
     {
       TimerOutput::Scope scope(computing_timer,
                                "offline_data - distribute dofs");
 
       dof_handler.distribute_dofs(discretization->finite_element);
 
       locally_owned   = dof_handler.locally_owned_dofs();
       n_locally_owned = locally_owned.n_elements();
 
       DoFTools::extract_locally_relevant_dofs(dof_handler, locally_relevant);
       n_locally_relevant = locally_relevant.n_elements();
 
       partitioner =
         std::make_shared<Utilities::MPI::Partitioner>(locally_owned,
                                                       locally_relevant,
                                                       mpi_communicator);
     }
 
 @endcode
 
 
 <a name="Translationtolocalindexranges"></a> 
 <h4>Translation to local index ranges</h4>
 

 
 We are now in a position to create the sparsity pattern for our
 matrices. There are quite a few peculiarities that need a detailed
 explanation. We avoid using a distributed matrix class (as for
 example provided by Trilinos or PETSc) and instead rely on deal.II's
 own SparseMatrix object to store the local part of all matrices.
 This design decision is motivated by the fact that (a) we actually
 never perform a matrix-vector multiplication, and (b) we can always
 assemble the local part of a matrix exclusively on a given MPI
 rank. Instead, we will compute nonlinear updates while iterating
 over (the local part) of a connectivity stencil; a task for which
 deal.II's own SparsityPattern is specifically optimized for.
     

 
 This design consideration has a caveat, though. What makes the
 deal.II SparseMatrix class fast is the <a
 href="https://en.wikipedia.org/wiki/Sparse_matrix">compressed row
 storage (CSR)</a> used in the SparsityPattern (see @ref Sparsity).
 This, unfortunately, does not play nicely with a global distributed
 index range because a sparsity pattern with CSR cannot contain
 "holes" in the index range. The distributed matrices offered by
 deal.II avoid this by translating from a global index range into a
 contiguous local index range. But this is precisely the type of
 index manipulation we want to avoid in our iteration over the
 stencil because it creates a measurable overhead.
     

 
 The Utilities::MPI::Partitioner class already implements the translation
 from a global index range to a contiguous local (per MPI rank) index
 range: we don't have to reinvent the wheel. We just need to use that
 translation capability (once and only once) in order to create a
 "local" sparsity pattern for the contiguous index range
 $[0,$<code>n_locally_relevant</code>$)$. That capability can be
 invoked by the Utilities::MPI::Partitioner::global_to_local() function.
 Once the sparsity pattern is created using local indices, all that
 is left to do is to ensure that (when implementing our scatter and
 gather auxiliary functions) we always access elements of a
 distributed vector by a call to
 LinearAlgebra::distributed::Vector::local_element(). This way we
 avoid index translations altogether and operate exclusively with
 local indices.
 

 
 
 @code
     {
       TimerOutput::Scope scope(
         computing_timer,
         "offline_data - create sparsity pattern and set up matrices");
 
 @endcode
 
 We have to create the "local" sparsity pattern by hand. We
 therefore loop over all locally owned and ghosted cells (see @ref
 GlossArtificialCell) and extract the (global)
 <code>dof_indices</code> associated with the cell DOFs and renumber
 them using <code>partitioner->global_to_local(index)</code>.
       

 
 @note In the case of a locally owned dof, such renumbering consist
 of applying a shift (i.e. we subtract an offset) such that now they
 will become a number in the integer interval
 $[0,$<code>n_locally_owned</code>$)$. However, in the case of a
 ghosted dof (i.e. not locally owned) the situation is quite
 different, since the global indices associated with ghosted DOFs will
 not be (in general) a contiguous set of integers.
 

 
 
 @code
       DynamicSparsityPattern dsp(n_locally_relevant, n_locally_relevant);
 
       const auto dofs_per_cell =
         discretization->finite_element.n_dofs_per_cell();
       std::vector<types::global_dof_index> dof_indices(dofs_per_cell);
 
       for (const auto &cell : dof_handler.active_cell_iterators())
         {
           if (cell->is_artificial())
             continue;
 
           // We transform the set of global dof indices on the cell to the corresponding "local" index range on the MPI process: 
           cell->get_dof_indices(dof_indices);
           std::transform(dof_indices.begin(),
                          dof_indices.end(),
                          dof_indices.begin(),
                          [&](types::global_dof_index index) {
                            return partitioner->global_to_local(index);
                          });
 
           // And simply add, for each dof, a coupling to all other "local" dofs on the cell: 
           for (const auto dof : dof_indices)
             dsp.add_entries(dof, dof_indices.begin(), dof_indices.end());
         }
 
       sparsity_pattern.copy_from(dsp);
 
       lumped_mass_matrix.reinit(sparsity_pattern);
       norm_matrix.reinit(sparsity_pattern);
       for (auto &matrix : cij_matrix)
         matrix.reinit(sparsity_pattern);
       for (auto &matrix : nij_matrix)
         matrix.reinit(sparsity_pattern);
     }
   }
 
 @endcode
 
 This concludes the setup of the DoFHandler and SparseMatrix objects.
 Next, we have to assemble various matrices. We define a number of
 helper functions and data structures in an anonymous namespace.
 

 
 
 @code
   namespace
   {
 @endcode
 
 <code>CopyData</code> class that will be used to assemble the
 offline data matrices using WorkStream. It acts as a container: it
 is just a struct where WorkStream stores the local cell
 contributions. Note that it also contains a class member
 <code>local_boundary_normal_map</code> used to store the local
 contributions required to compute the normals at the boundary.
 

 
 
 @code
     template <int dim>
     struct CopyData
     {
       bool                                         is_artificial;
       std::vector<types::global_dof_index>         local_dof_indices;
       typename OfflineData<dim>::BoundaryNormalMap local_boundary_normal_map;
       FullMatrix<double>                           cell_lumped_mass_matrix;
       std::array<FullMatrix<double>, dim>          cell_cij_matrix;
     };
 
 @endcode
 
 Next we introduce a number of helper functions that are all
 concerned about reading and writing matrix and vector entries. They
 are mainly motivated by providing slightly more efficient code and
 <a href="https://en.wikipedia.org/wiki/Syntactic_sugar"> syntactic
 sugar</a> for otherwise somewhat tedious code.
 

 
 The first function we introduce, <code>get_entry()</code>, will be
 used to read the value stored at the entry pointed by a
 SparsityPattern iterator <code>it</code> of <code>matrix</code>. The
 function works around a small deficiency in the SparseMatrix
 interface: The SparsityPattern is concerned with all index
 operations of the sparse matrix stored in CRS format. As such the
 iterator already knows the global index of the corresponding matrix
 entry in the low-level vector stored in the SparseMatrix object. Due
 to the lack of an interface in the SparseMatrix for accessing the
 element directly with a SparsityPattern iterator, we unfortunately
 have to create a temporary SparseMatrix iterator. We simply hide
 this in the <code>get_entry()</code> function.
 

 
 
 @code
     template <typename IteratorType>
     DEAL_II_ALWAYS_INLINE inline SparseMatrix<double>::value_type
     get_entry(const SparseMatrix<double> &matrix, const IteratorType &it)
     {
       const SparseMatrix<double>::const_iterator matrix_iterator(
         &matrix, it->global_index());
       return matrix_iterator->value();
     }
 
 @endcode
 
 The <code>set_entry()</code> helper is the inverse operation of
 <code>get_value()</code>: Given an iterator and a value, it sets the
 entry pointed to by the iterator in the matrix.
 

 
 
 @code
     template <typename IteratorType>
     DEAL_II_ALWAYS_INLINE inline void
     set_entry(SparseMatrix<double> &           matrix,
               const IteratorType &             it,
               SparseMatrix<double>::value_type value)
     {
       SparseMatrix<double>::iterator matrix_iterator(&matrix,
                                                      it->global_index());
       matrix_iterator->value() = value;
     }
 
 @endcode
 
 <code>gather_get_entry()</code>: we note that $\mathbf{c}_{ij} \in
 \mathbb{R}^d$. If $d=2$ then $\mathbf{c}_{ij} =
 [\mathbf{c}_{ij}^1,\mathbf{c}_{ij}^2]^\top$. Which basically implies
 that we need one matrix per space dimension to store the
 $\mathbf{c}_{ij}$ vectors. Similar observation follows for the
 matrix $\mathbf{n}_{ij}$. The purpose of
 <code>gather_get_entry()</code> is to retrieve those entries and store
 them into a <code>Tensor<1, dim></code> for our convenience.
 

 
 
 @code
     template <std::size_t k, typename IteratorType>
     DEAL_II_ALWAYS_INLINE inline Tensor<1, k>
     gather_get_entry(const std::array<SparseMatrix<double>, k> &c_ij,
                      const IteratorType                         it)
     {
       Tensor<1, k> result;
       for (unsigned int j = 0; j < k; ++j)
         result[j] = get_entry(c_ij[j], it);
       return result;
     }
 
 @endcode
 
 <code>gather()</code> (first interface): this first function
 signature, having three input arguments, will be used to retrieve
 the individual components <code>(i,l)</code> of a matrix. The
 functionality of <code>gather_get_entry()</code> and
 <code>gather()</code> is very much the same, but their context is
 different: the function <code>gather()</code> does not rely on an
 iterator (that actually knows the value pointed to) but rather on the
 indices <code>(i,l)</code> of the entry in order to retrieve its
 actual value. We should expect <code>gather()</code> to be slightly
 more expensive than <code>gather_get_entry()</code>. The use of
 <code>gather()</code> will be limited to the task of computing the
 algebraic viscosity $d_{ij}$ in the particular case that when
 both $i$ and $j$ lie at the boundary.
     

 
 @note The reader should be aware that accessing an arbitrary
 <code>(i,l)</code> entry of a matrix (say for instance Trilinos or PETSc
 matrices) is in general unacceptably expensive. Here is where we might
 want to keep an eye on complexity: we want this operation to have
 constant complexity, which is the case of the current implementation
 using deal.II matrices.
 

 
 
 @code
     template <std::size_t k>
     DEAL_II_ALWAYS_INLINE inline Tensor<1, k>
     gather(const std::array<SparseMatrix<double>, k> &n_ij,
            const unsigned int                         i,
            const unsigned int                         j)
     {
       Tensor<1, k> result;
       for (unsigned int l = 0; l < k; ++l)
         result[l] = n_ij[l](i, j);
       return result;
     }
 
 @endcode
 
 <code>gather()</code> (second interface): this second function
 signature having two input arguments will be used to gather the
 state at a node <code>i</code> and return it as a
 <code>Tensor<1,problem_dimension></code> for our convenience.
 

 
 
 @code
     template <std::size_t k>
     DEAL_II_ALWAYS_INLINE inline Tensor<1, k>
     gather(const std::array<LinearAlgebra::distributed::Vector<double>, k> &U,
            const unsigned int                                               i)
     {
       Tensor<1, k> result;
       for (unsigned int j = 0; j < k; ++j)
         result[j] = U[j].local_element(i);
       return result;
     }
 
 @endcode
 
 <code>scatter()</code>: this function has three input arguments, the
 first one is meant to be a "global object" (say a locally owned or
 locally relevant vector), the second argument which could be a
 <code>Tensor<1,problem_dimension></code>, and the last argument
 which represents a index of the global object. This function will be
 primarily used to write the updated nodal values, stored as
 <code>Tensor<1,problem_dimension></code>, into the global objects.
 

 
 
 @code
     template <std::size_t k, int k2>
     DEAL_II_ALWAYS_INLINE inline void
     scatter(std::array<LinearAlgebra::distributed::Vector<double>, k> &U,
             const Tensor<1, k2> &                                      tensor,
             const unsigned int                                         i)
     {
       static_assert(k == k2,
                     "The dimensions of the input arguments must agree");
       for (unsigned int j = 0; j < k; ++j)
         U[j].local_element(i) = tensor[j];
     }
   } // namespace
 
 @endcode
 
 We are now in a position to assemble all matrices stored in
 <code>OfflineData</code>: the lumped mass entries $m_i$, the
 vector-valued matrices $\mathbf{c}_{ij}$ and $\mathbf{n}_{ij} =
 \frac{\mathbf{c}_{ij}}{|\mathbf{c}_{ij}|}$, and the boundary normals
 $\boldsymbol{\nu}_i$.
   

 
 In order to exploit thread parallelization we use the WorkStream approach
 detailed in the @ref threads "Parallel computing with multiple processors"
 accessing shared memory. As customary this requires
 definition of
 - Scratch data (i.e. input info required to carry out computations): in
 this case it is <code>scratch_data</code>.
 - The worker: in our case this is the <code>local_assemble_system()</code>
 function that
 actually computes the local (i.e. current cell) contributions from the
 scratch data.
 - A copy data: a struct that contains all the local assembly
 contributions, in this case <code>CopyData<dim>()</code>.
 - A copy data routine: in this case it is
 <code>copy_local_to_global()</code> in charge of actually coping these
 local contributions into the global objects (matrices and/or vectors)
   

 
 Most of the following lines are spent in the definition of the worker
 <code>local_assemble_system()</code> and the copy data routine
 <code>copy_local_to_global()</code>. There is not much to say about the
 WorkStream framework since the vast majority of ideas are reasonably
 well-documented in step-9, step-13 and step-32 among others.
   

 
 Finally, assuming that $\mathbf{x}_i$ is a support point at the boundary,
 the (nodal) normals are defined as:
   

 
 @f{align*}
 \widehat{\boldsymbol{\nu}}_i \dealcoloneq
 \frac{\int_{\partial\Omega} \phi_i \widehat{\boldsymbol{\nu}} \,
 \, \mathrm{d}\mathbf{s}}{\big|\int_{\partial\Omega} \phi_i
 \widehat{\boldsymbol{\nu}} \, \mathrm{d}\mathbf{s}\big|}
 @f}
   

 
 We will compute the numerator of this expression first and store it in
 <code>OfflineData<dim>::BoundaryNormalMap</code>. We will normalize these
 vectors in a posterior loop.
 

 
 
 @code
   template <int dim>
   void OfflineData<dim>::assemble()
   {
     lumped_mass_matrix = 0.;
     norm_matrix        = 0.;
     for (auto &matrix : cij_matrix)
       matrix = 0.;
     for (auto &matrix : nij_matrix)
       matrix = 0.;
 
     unsigned int dofs_per_cell =
       discretization->finite_element.n_dofs_per_cell();
     unsigned int n_q_points = discretization->quadrature.size();
 
 @endcode
 
 What follows is the initialization of the scratch data required by
 WorkStream
 

 
 
 @code
     MeshWorker::ScratchData<dim> scratch_data(
       discretization->mapping,
       discretization->finite_element,
       discretization->quadrature,
       update_values | update_gradients | update_quadrature_points |
         update_JxW_values,
       discretization->face_quadrature,
       update_normal_vectors | update_values | update_JxW_values);
 
     {
       TimerOutput::Scope scope(
         computing_timer,
         "offline_data - assemble lumped mass matrix, and c_ij");
 
       const auto local_assemble_system = 
         [&](const typename DoFHandler<dim>::cell_iterator &cell,
             MeshWorker::ScratchData<dim> &                 scratch,
             CopyData<dim> &                                copy) {
           copy.is_artificial = cell->is_artificial();
           if (copy.is_artificial)
             return;
 
           copy.local_boundary_normal_map.clear();
           copy.cell_lumped_mass_matrix.reinit(dofs_per_cell, dofs_per_cell);
           for (auto &matrix : copy.cell_cij_matrix)
             matrix.reinit(dofs_per_cell, dofs_per_cell);
 
           const auto &fe_values = scratch.reinit(cell);
 
           copy.local_dof_indices.resize(dofs_per_cell);
           cell->get_dof_indices(copy.local_dof_indices);
 
           std::transform(copy.local_dof_indices.begin(),
                          copy.local_dof_indices.end(),
                          copy.local_dof_indices.begin(),
                          [&](types::global_dof_index index) {
                            return partitioner->global_to_local(index);
                          });
 
 @endcode
 
 We compute the local contributions for the lumped mass matrix
 entries $m_i$ and and vectors $c_{ij}$ in the usual fashion:
 
 @code
           for (unsigned int q_point = 0; q_point < n_q_points; ++q_point)
             {
               const auto JxW = fe_values.JxW(q_point);
 
               for (unsigned int j = 0; j < dofs_per_cell; ++j)
                 {
                   const auto value_JxW =
                     fe_values.shape_value(j, q_point) * JxW;
                   const auto grad_JxW = fe_values.shape_grad(j, q_point) * JxW;
 
                   copy.cell_lumped_mass_matrix(j, j) += value_JxW;
 
                   for (unsigned int i = 0; i < dofs_per_cell; ++i)
                     {
                       const auto value = fe_values.shape_value(i, q_point);
                       for (unsigned int d = 0; d < dim; ++d)
                         copy.cell_cij_matrix[d](i, j) += value * grad_JxW[d];
 
                     } // i 
                 }     // j 
             }         // q 
 
 @endcode
 
 Now we have to compute the boundary normals. Note that the
 following loop does not do much unless the element has faces on
 the boundary of the domain.
 
 @code
           for (const auto f : cell->face_indices())
             {
               const auto face = cell->face(f);
               const auto id   = face->boundary_id();
 
               if (!face->at_boundary())
                 continue;
 
               const auto &fe_face_values = scratch.reinit(cell, f);
 
               const unsigned int n_face_q_points =
                 fe_face_values.get_quadrature().size();
 
               for (unsigned int j = 0; j < dofs_per_cell; ++j)
                 {
                   if (!discretization->finite_element.has_support_on_face(j, f))
                     continue;
 
 @endcode
 
 Note that "normal" will only represent the contributions
 from one of the faces in the support of the shape
 function phi_j. So we cannot normalize this local
 contribution right here, we have to take it "as is",
 store it and pass it to the copy data routine. The
 proper normalization requires an additional loop on
 nodes. This is done in the copy function below.
 
 @code
                   Tensor<1, dim> normal;
                   if (id == Boundaries::free_slip)
                     {
                       for (unsigned int q = 0; q < n_face_q_points; ++q)
                         normal += fe_face_values.normal_vector(q) *
                                   fe_face_values.shape_value(j, q);
                     }
 
                   const auto index = copy.local_dof_indices[j];
 
                   Point<dim> position;
                   for (const auto v : cell->vertex_indices())
                     if (cell->vertex_dof_index(v, 0) ==
                         partitioner->local_to_global(index))
                       {
                         position = cell->vertex(v);
                         break;
                       }
 
                   const auto old_id =
                     std::get<1>(copy.local_boundary_normal_map[index]);
                   copy.local_boundary_normal_map[index] =
                     std::make_tuple(normal, std::max(old_id, id), position);
                 }
             }
         };
 
 @endcode
 
 Last, we provide a copy_local_to_global function as required for
 the WorkStream
 
 @code
       const auto copy_local_to_global = [&](const CopyData<dim> &copy) {
         if (copy.is_artificial)
           return;
 
         for (const auto &it : copy.local_boundary_normal_map)
           {
             std::get<0>(boundary_normal_map[it.first]) +=
               std::get<0>(it.second);
             std::get<1>(boundary_normal_map[it.first]) =
               std::max(std::get<1>(boundary_normal_map[it.first]),
                        std::get<1>(it.second));
             std::get<2>(boundary_normal_map[it.first]) = std::get<2>(it.second);
           }
 
         lumped_mass_matrix.add(copy.local_dof_indices,
                                copy.cell_lumped_mass_matrix);
 
         for (int k = 0; k < dim; ++k)
           {
             cij_matrix[k].add(copy.local_dof_indices, copy.cell_cij_matrix[k]);
             nij_matrix[k].add(copy.local_dof_indices, copy.cell_cij_matrix[k]);
           }
       };
 
       WorkStream::run(dof_handler.begin_active(),
                       dof_handler.end(),
                       local_assemble_system,
                       copy_local_to_global,
                       scratch_data,
                       CopyData<dim>());
     }
 
 @endcode
 
 At this point in time we are done with the computation of $m_i$ and
 $\mathbf{c}_{ij}$, but so far the matrix <code>nij_matrix</code>
 contains just a copy of the matrix <code>cij_matrix</code>.
 That's not what we really want: we have to normalize its entries. In
 addition, we have not filled the entries of the matrix
 <code>norm_matrix</code>  and the vectors stored in the map
 <code>OfflineData<dim>::BoundaryNormalMap</code> are not normalized.
     

 
 In principle, this is just offline data, it doesn't make much sense
 to over-optimize their computation, since their cost will get amortized
 over the many time steps that we are going to use. However,
 computing/storing the entries of the matrix
 <code>norm_matrix</code> and the normalization of <code>nij_matrix</code>
 are perfect to illustrate thread-parallel node-loops:
 - we want to visit every node $i$ in the mesh/sparsity graph,
 - and for every such node we want to visit to every $j$ such that
 $\mathbf{c}_{ij} \not \equiv 0$.
     

 
 From an algebraic point of view, this is equivalent to: visiting
 every row in the matrix and for each one of these rows execute a loop on
 the columns. Node-loops is a core theme of this tutorial step (see
 the pseudo-code in the introduction) that will repeat over and over
 again. That's why this is the right time to introduce them.
     

 
 We have the thread parallelization capability
 parallel::apply_to_subranges() that is somehow more general than the
 WorkStream framework. In particular, parallel::apply_to_subranges() can
 be used for our node-loops. This functionality requires four input
 arguments which we explain in detail (for the specific case of our
 thread-parallel node loops):
 - The iterator <code>indices.begin()</code> points to a row index.
 - The iterator <code>indices.end()</code> points to a numerically higher
 row index.
 - The function <code>on_subranges(i1,i2)</code> (where <code>i1</code>
 and <code>i2</code> define a sub-range within the range spanned by
 the end and begin iterators defined in the two previous bullets)
 applies an operation to every iterator in such subrange. We may as
 well call <code>on_subranges</code> the "worker".
 - Grainsize: minimum number of iterators (in this case representing
 rows) processed by each thread. We decided for a minimum of 4096
 rows.
     

 
 A minor caveat here is that the iterators <code>indices.begin()</code>
 and <code>indices.end()</code> supplied to
 parallel::apply_to_subranges() have to be random access iterators:
 internally, parallel::apply_to_subranges() will break the range
 defined by the <code>indices.begin()</code> and
 <code>indices.end()</code> iterators into subranges (we want to be
 able to read any entry in those subranges with constant complexity).
 In order to provide such iterators we resort to
 std_cxx20::ranges::iota_view.
     

 
 The bulk of the following piece of code is spent defining
 the "worker" <code>on_subranges</code>: i.e. the  operation applied at
 each row of the sub-range. Given a fixed <code>row_index</code>
 we want to visit every column/entry in such row. In order to execute
 such columns-loops we use
 <a href="http://www.cplusplus.com/reference/algorithm/for_each/">
 std::for_each</a>
 from the standard library, where:
 - <code>sparsity_pattern.begin(row_index)</code>
 gives us an iterator starting at the first column of the row,
 - <code>sparsity_pattern.end(row_index)</code> is an iterator pointing
 at the last column of the row,
 - the last argument required by `std::for_each` is the operation
 applied at each nonzero entry (a lambda expression in this case)
 of such row.
     

 
 We note that, parallel::apply_to_subranges() will operate on
 disjoint sets of rows (the subranges) and our goal is to write into
 these rows. Because of the simple nature of the operations we want
 to carry out (computation and storage of normals, and normalization
 of the $\mathbf{c}_{ij}$ of entries) threads cannot conflict
 attempting to write the same entry (we do not need a scheduler).
 
 @code
     {
       TimerOutput::Scope scope(computing_timer,
                                "offline_data - compute |c_ij|, and n_ij");
 
       const std_cxx20::ranges::iota_view<unsigned int, unsigned int> indices(
         0, n_locally_relevant);
 
       const auto on_subranges = 
         [&](const auto i1, const auto i2) {
           for (const auto row_index :
                std_cxx20::ranges::iota_view<unsigned int, unsigned int>(*i1,
                                                                         *i2))
             {
 @endcode
 
 First column-loop: we compute and store the entries of the
 matrix norm_matrix and write normalized entries into the
 matrix nij_matrix:
 
 @code
               std::for_each(
                 sparsity_pattern.begin(row_index),
                 sparsity_pattern.end(row_index),
                 [&](const dealii::SparsityPatternIterators::Accessor &jt) {
                   const auto   c_ij = gather_get_entry(cij_matrix, &jt);
                   const double norm = c_ij.norm();
 
                   set_entry(norm_matrix, &jt, norm);
                   for (unsigned int j = 0; j < dim; ++j)
                     set_entry(nij_matrix[j], &jt, c_ij[j] / norm);
                 });
             }
         };
 
       parallel::apply_to_subranges(indices.begin(),
                                    indices.end(),
                                    on_subranges,
                                    4096);
 
 @endcode
 
 Finally, we normalize the vectors stored in
 <code>OfflineData<dim>::BoundaryNormalMap</code>. This operation has
 not been thread parallelized as it would neither illustrate any
 important concept nor lead to any noticeable speed gain.
 
 @code
       for (auto &it : boundary_normal_map)
         {
           auto &normal = std::get<0>(it.second);
           normal /= (normal.norm() + std::numeric_limits<double>::epsilon());
         }
     }
   }
 
 @endcode
 
 At this point we are very much done with anything related to offline data.
 

 
 
 <a name="EquationofstateandapproximateRiemannsolver"></a> 
 <h4>Equation of state and approximate Riemann solver</h4>
 

 
 In this section we describe the implementation of the class members of
 the <code>ProblemDescription</code> class. Most of the code here is
 specific to the compressible Euler's equations with an ideal gas law.
 If we wanted to re-purpose step-69 for a different conservation law
 (say for: instance the shallow water equation) most of the
 implementation of this class would have to change. But most of the
 other classes (in particular those defining loop structures) would
 remain unchanged.
   

 
 We start by implementing a number of small member functions for
 computing <code>momentum</code>, <code>internal_energy</code>,
 <code>pressure</code>, <code>speed_of_sound</code>, and the flux
 <code>f</code> of the system. The functionality of each one of these
 functions is self-explanatory from their names.
 

 
 
 @code
   template <int dim>
   DEAL_II_ALWAYS_INLINE inline Tensor<1, dim>
   ProblemDescription<dim>::momentum(const state_type &U)
   {
     Tensor<1, dim> result;
     std::copy_n(&U[1], dim, &result[0]);
     return result;
   }
 
   template <int dim>
   DEAL_II_ALWAYS_INLINE inline double
   ProblemDescription<dim>::internal_energy(const state_type &U)
   {
     const double &rho = U[0];
     const auto    m   = momentum(U);
     const double &E   = U[dim + 1];
     return E - 0.5 * m.norm_square() / rho;
   }
 
   template <int dim>
   DEAL_II_ALWAYS_INLINE inline double
   ProblemDescription<dim>::pressure(const state_type &U)
   {
     return (gamma - 1.) * internal_energy(U);
   }
 
   template <int dim>
   DEAL_II_ALWAYS_INLINE inline double
   ProblemDescription<dim>::speed_of_sound(const state_type &U)
   {
     const double &rho = U[0];
     const double  p   = pressure(U);
 
     return std::sqrt(gamma * p / rho);
   }
 
   template <int dim>
   DEAL_II_ALWAYS_INLINE inline typename ProblemDescription<dim>::flux_type
   ProblemDescription<dim>::flux(const state_type &U)
   {
     const double &rho = U[0];
     const auto    m   = momentum(U);
     const auto    p   = pressure(U);
     const double &E   = U[dim + 1];
 
     flux_type result;
 
     result[0] = m;
     for (unsigned int i = 0; i < dim; ++i)
       {
         result[1 + i] = m * m[i] / rho;
         result[1 + i][i] += p;
       }
     result[dim + 1] = m / rho * (E + p);
 
     return result;
   }
 
 @endcode
 
 Now we discuss the computation of $\lambda_{\text{max}}
 (\mathbf{U}_i^{n},\mathbf{U}_j^{n}, \textbf{n}_{ij})$. The analysis
 and derivation of sharp upper-bounds of maximum wavespeeds of Riemann
 problems is a very technical endeavor and we cannot include an
 advanced discussion about it in this tutorial. In this portion of the
 documentation we will limit ourselves to sketch the main functionality
 of our implementation functions and point to specific academic
 references in order to help the (interested) reader trace the
 source (and proper mathematical justification) of these ideas.
   

 
 In general, obtaining a sharp guaranteed upper-bound on the maximum
 wavespeed requires solving a quite expensive scalar nonlinear problem.
 This is typically done with an iterative solver. In order to simplify
 the presentation in this example step we decided not to include such
 an iterative scheme. Instead, we will just use an initial guess as a
 guess for an upper bound on the maximum wavespeed. More precisely,
 equations (2.11) (3.7), (3.8) and (4.3) of @cite GuermondPopov2016b
 are enough to define a guaranteed upper bound on the maximum
 wavespeed. This estimate is returned by a call to the function
 <code>lambda_max_two_rarefaction()</code>. At its core the
 construction of such an upper bound uses the so-called two-rarefaction
 approximation for the intermediate pressure $p^*$, see for instance
 Equation (4.46), page 128 in @cite Toro2009.
   

 
 The estimate returned by <code>lambda_max_two_rarefaction()</code> is
 guaranteed to be an upper bound, it is in general quite sharp, and
 overall sufficient for our purposes. However, for some specific
 situations (in particular when one of states is close to vacuum
 conditions) such an estimate will be overly pessimistic. That's why we
 used a second estimate to avoid this degeneracy that will be invoked
 by a call to the function <code>lambda_max_expansion()</code>. The most
 important function here is <code>compute_lambda_max()</code> which
 takes the minimum between the estimates returned by
 <code>lambda_max_two_rarefaction()</code> and
 <code>lambda_max_expansion()</code>.
   

 
 We start again by defining a couple of helper functions:
   

 
 The first function takes a state <code>U</code> and a unit vector
 <code>n_ij</code> and computes the <i>projected</i> 1D state in
 direction of the unit vector.
 
 @code
   namespace
   {
     template <int dim>
     DEAL_II_ALWAYS_INLINE inline std::array<double, 4> riemann_data_from_state(
       const typename ProblemDescription<dim>::state_type U,
       const Tensor<1, dim> &                             n_ij)
     {
       Tensor<1, 3> projected_U;
       projected_U[0] = U[0];
 
 @endcode
 
 For this, we have to change the momentum to $\textbf{m}\cdot
 n_{ij}$ and have to subtract the kinetic energy of the
 perpendicular part from the total energy:
 
 @code
       const auto m   = ProblemDescription<dim>::momentum(U);
       projected_U[1] = n_ij * m;
 
       const auto perpendicular_m = m - projected_U[1] * n_ij;
       projected_U[2] = U[1 + dim] - 0.5 * perpendicular_m.norm_square() / U[0];
 
 @endcode
 
 We return the 1D state in <i>primitive</i> variables instead of
 conserved quantities. The return array consists of density $\rho$,
 velocity $u$, pressure $p$ and local speed of sound $a$:
 

 
 
 @code
       return {{projected_U[0],
                projected_U[1] / projected_U[0],
                ProblemDescription<1>::pressure(projected_U),
                ProblemDescription<1>::speed_of_sound(projected_U)}};
     }
 
 @endcode
 
 At this point we also define two small functions that return the
 positive and negative part of a double.
 

 
 
 @code
     DEAL_II_ALWAYS_INLINE inline double positive_part(const double number)
     {
       return std::max(number, 0.);
     }
 
 
     DEAL_II_ALWAYS_INLINE inline double negative_part(const double number)
     {
       return -std::min(number, 0.);
     }
 
 @endcode
 
 Next, we need two local wavenumbers that are defined in terms of a
 primitive state $[\rho, u, p, a]$ and a given pressure $p^\ast$
 @cite GuermondPopov2016  Eqn. (3.7):
 @f{align*}
 \lambda^- = u - a\,\sqrt{1 + \frac{\gamma+1}{2\gamma}
 \left(\frac{p^\ast-p}{p}\right)_+}
 @f}
 Here, the $(\cdot)_{+}$ denotes the positive part of the given
 argument.
 

 
 
 @code
     DEAL_II_ALWAYS_INLINE inline double
     lambda1_minus(const std::array<double, 4> &riemann_data,
                   const double                 p_star)
     {
       // Implements formula (3.7) in Guermond-Popov-2016 
 
       constexpr double gamma = ProblemDescription<1>::gamma;
       const auto       u     = riemann_data[1];
       const auto       p     = riemann_data[2];
       const auto       a     = riemann_data[3];
 
       const double factor = (gamma + 1.0) / 2.0 / gamma;
       const double tmp    = positive_part((p_star - p) / p);
       return u - a * std::sqrt(1.0 + factor * tmp);
     }
 
 @endcode
 
 Analougously @cite GuermondPopov2016 Eqn. (3.8):
 @f{align*}
 \lambda^+ = u + a\,\sqrt{1 + \frac{\gamma+1}{2\gamma}
 \left(\frac{p^\ast-p}{p}\right)_+}
 @f}
 

 
 
 @code
     DEAL_II_ALWAYS_INLINE inline double
     lambda3_plus(const std::array<double, 4> &riemann_data, const double p_star)
     {
       // Implements formula (3.8) in Guermond-Popov-2016 
 
       constexpr double gamma = ProblemDescription<1>::gamma;
       const auto       u     = riemann_data[1];
       const auto       p     = riemann_data[2];
       const auto       a     = riemann_data[3];
 
       const double factor = (gamma + 1.0) / 2.0 / gamma;
       const double tmp    = positive_part((p_star - p) / p);
       return u + a * std::sqrt(1.0 + factor * tmp);
     }
 
 @endcode
 
 All that is left to do is to compute the maximum of $\lambda^-$ and
 $\lambda^+$ computed from the left and right primitive state
 (@cite GuermondPopov2016 Eqn. (2.11)), where $p^\ast$ is given by
 @cite GuermondPopov2016 Eqn (4.3):
 

 
 
 @code
     DEAL_II_ALWAYS_INLINE inline double
     lambda_max_two_rarefaction(const std::array<double, 4> &riemann_data_i,
                                const std::array<double, 4> &riemann_data_j)
     {
       constexpr double gamma = ProblemDescription<1>::gamma;
       const auto       u_i   = riemann_data_i[1];
       const auto       p_i   = riemann_data_i[2];
       const auto       a_i   = riemann_data_i[3];
       const auto       u_j   = riemann_data_j[1];
       const auto       p_j   = riemann_data_j[2];
       const auto       a_j   = riemann_data_j[3];
 
       const double numerator = a_i + a_j - (gamma - 1.) / 2. * (u_j - u_i);
 
       const double denominator =
         a_i * std::pow(p_i / p_j, -1. * (gamma - 1.) / 2. / gamma) + a_j * 1.;
 
       // Formula (4.3) in Guermond-Popov-2016 
 
       const double p_star =
         p_j * std::pow(numerator / denominator, 2. * gamma / (gamma - 1));
 
       const double lambda1 = lambda1_minus(riemann_data_i, p_star);
       const double lambda3 = lambda3_plus(riemann_data_j, p_star);
 
       // Formula (2.11) in Guermond-Popov-2016 
 
       return std::max(positive_part(lambda3), negative_part(lambda1));
     }
 
 @endcode
 
 We compute the second upper bound of the maximal wavespeed that is, in
 general, not as sharp as the two-rarefaction estimate. But it will
 save the day in the context of near vacuum conditions when the
 two-rarefaction approximation might attain extreme values:
 @f{align*}
 \lambda_{\text{exp}} = \max(u_i,u_j) + 5. \max(a_i, a_j).
 @f}
 @note The constant 5.0 multiplying the maximum of the sound speeds
 is <i>neither</i> an ad-hoc constant, <i>nor</i> a tuning parameter.
 It defines an upper bound for any $\gamma \in [0,5/3]$. Do not play
 with it!
 

 
 
 @code
     DEAL_II_ALWAYS_INLINE inline double
     lambda_max_expansion(const std::array<double, 4> &riemann_data_i,
                          const std::array<double, 4> &riemann_data_j)
     {
       const auto u_i = riemann_data_i[1];
       const auto a_i = riemann_data_i[3];
       const auto u_j = riemann_data_j[1];
       const auto a_j = riemann_data_j[3];
 
       return std::max(std::abs(u_i), std::abs(u_j)) + 5. * std::max(a_i, a_j);
     }
   } // namespace
 
 @endcode
 
 The following is the main function that we are going to call in order to
 compute $\lambda_{\text{max}} (\mathbf{U}_i^{n},\mathbf{U}_j^{n},
 \textbf{n}_{ij})$. We simply compute both maximal wavespeed estimates
 and return the minimum.
 

 
 
 @code
   template <int dim>
   DEAL_II_ALWAYS_INLINE inline double
   ProblemDescription<dim>::compute_lambda_max(const state_type &    U_i,
                                               const state_type &    U_j,
                                               const Tensor<1, dim> &n_ij)
   {
     const auto riemann_data_i = riemann_data_from_state(U_i, n_ij);
     const auto riemann_data_j = riemann_data_from_state(U_j, n_ij);
 
     const double lambda_1 =
       lambda_max_two_rarefaction(riemann_data_i, riemann_data_j);
 
     const double lambda_2 =
       lambda_max_expansion(riemann_data_i, riemann_data_j);
 
     return std::min(lambda_1, lambda_2);
   }
 
 @endcode
 
 We conclude this section by defining static arrays
 <code>component_names</code> that contain strings describing the
 component names of our state vector. We have template specializations
 for dimensions one, two and three, that are used later in DataOut for
 naming the corresponding components:
 

 
 
 @code
   template <>
   const std::array<std::string, 3> ProblemDescription<1>::component_names{
     {"rho", "m", "E"}};
 
   template <>
   const std::array<std::string, 4> ProblemDescription<2>::component_names{
     {"rho", "m_1", "m_2", "E"}};
 
   template <>
   const std::array<std::string, 5> ProblemDescription<3>::component_names{
     {"rho", "m_1", "m_2", "m_3", "E"}};
 
 @endcode
 
 
 <a name="Initialvalues"></a> 
 <h4>Initial values</h4>
 

 
 The last preparatory step, before we discuss the implementation of the
 forward Euler scheme, is to briefly implement the `InitialValues` class.
   

 
 In the constructor we initialize all parameters with default values,
 declare all parameters for the `ParameterAcceptor` class and connect the
 <code>parse_parameters_call_back</code> slot to the respective signal.
   

 
 The <code>parse_parameters_call_back</code> slot will be invoked from
 ParameterAceptor after the call to ParameterAcceptor::initialize(). In
 that regard, its use is appropriate for situations where the
 parameters have to be postprocessed (in some sense) or some
 consistency condition between the parameters has to be checked.
 

 
 
 @code
   template <int dim>
   InitialValues<dim>::InitialValues(const std::string &subsection)
     : ParameterAcceptor(subsection)
   {
     // We wire up the slot InitialValues<dim>::parse_parameters_callback to the ParameterAcceptor::parse_parameters_call_back signal: 
     ParameterAcceptor::parse_parameters_call_back.connect(
       std::bind(&InitialValues<dim>::parse_parameters_callback, this));
 
     initial_direction[0] = 1.;
     add_parameter("initial direction",
                   initial_direction,
                   "Initial direction of the uniform flow field");
 
     initial_1d_state[0] = ProblemDescription<dim>::gamma;
     initial_1d_state[1] = 3.;
     initial_1d_state[2] = 1.;
     add_parameter("initial 1d state",
                   initial_1d_state,
                   "Initial 1d state (rho, u, p) of the uniform flow field");
   }
 
 @endcode
 
 So far the constructor of <code>InitialValues</code> has defined
 default values for the two private members
 <code>initial_direction</code> and <code>initial_1d_state</code> and
 added them to the parameter list. But we have not defined an
 implementation of the only public member that we really care about,
 which is <code>initial_state()</code> (the function that we are going to
 call to actually evaluate the initial solution at the mesh nodes). At
 the top of the function, we have to ensure that the provided initial
 direction is not the zero vector.
   

 
 @note As commented, we could have avoided using the method
 <code>parse_parameters_call_back </code> and defined a class member
 <code>setup()</code> in order to define the implementation of
 <code>initial_state()</code>. But for illustrative purposes we want to
 document a different way here and use the call back signal from
 ParameterAcceptor.
 

 
 
 @code
   template <int dim>
   void InitialValues<dim>::parse_parameters_callback()
   {
     AssertThrow(initial_direction.norm() != 0.,
                 ExcMessage(
                   "Initial shock front direction is set to the zero vector."));
     initial_direction /= initial_direction.norm();
 
 @endcode
 
 Next, we implement the <code>initial_state</code> function object
 with a lambda function computing a uniform flow field. For this we
 have to translate a given primitive 1d state (density $\rho$,
 velocity $u$, and pressure $p$) into a conserved n-dimensional state
 (density $\rho$, momentum $\mathbf{m}$, and total energy $E$).
 

 
 
 @code
     initial_state = [this](const Point<dim> & //！改point/, double //!改t/) {
       const double            rho   = initial_1d_state[0];
       const double            u     = initial_1d_state[1];
       const double            p     = initial_1d_state[2];
       static constexpr double gamma = ProblemDescription<dim>::gamma;
 
       state_type state;
 
       state[0] = rho;
       for (unsigned int i = 0; i < dim; ++i)
         state[1 + i] = rho * u * initial_direction[i];
 
       state[dim + 1] = p / (gamma - 1.) + 0.5 * rho * u * u;
 
       return state;
     };
   }
 
 @endcode
 
 
 <a name="TheForwardEulerstep"></a> 
 <h4>The Forward Euler step</h4>
 

 
 The constructor of the <code>%TimeStepping</code> class does not contain
 any surprising code:
 

 
 
 @code
   template <int dim>
   TimeStepping<dim>::TimeStepping(
     const MPI_Comm            mpi_communicator,
     TimerOutput &             computing_timer,
     const OfflineData<dim> &  offline_data,
     const InitialValues<dim> &initial_values,
     const std::string &       subsection //= "TimeStepping" ！改)
     : ParameterAcceptor(subsection)
     , mpi_communicator(mpi_communicator)
     , computing_timer(computing_timer)
     , offline_data(&offline_data)
     , initial_values(&initial_values)
   {
     cfl_update = 0.80;
     add_parameter("cfl update",
                   cfl_update,
                   "Relative CFL constant used for update");
   }
 
 @endcode
 
 In the class member <code>prepare()</code> we initialize the temporary
 vector <code>temp</code> and the matrix <code>dij_matrix</code>. The
 vector <code>temp</code> will be used to store the solution update
 temporarily before its contents is swapped with the old vector.
 

 
 
 @code
   template <int dim>
   void TimeStepping<dim>::prepare()
   {
     TimerOutput::Scope scope(computing_timer,
                              "time_stepping - prepare scratch space");
 
     for (auto &it : temporary_vector)
       it.reinit(offline_data->partitioner);
 
     dij_matrix.reinit(offline_data->sparsity_pattern);
   }
 
 @endcode
 
 It is now time to implement the forward Euler step. Given a (writable
 reference) to the old state <code>U</code> at time $t$ we update the
 state <code>U</code> in place and return the chosen time-step size. We
 first declare a number of read-only references to various different
 variables and data structures. We do this is mainly to have shorter
 variable names (e.g., <code>sparsity</code> instead of
 <code>offline_data->sparsity_pattern</code>).
 

 
 
 @code
   template <int dim>
   double TimeStepping<dim>::make_one_step(vector_type &U, double t)
   {
     const auto &n_locally_owned    = offline_data->n_locally_owned;
     const auto &n_locally_relevant = offline_data->n_locally_relevant;
 
     const std_cxx20::ranges::iota_view<unsigned int, unsigned int>
       indices_owned(0, n_locally_owned);
     const std_cxx20::ranges::iota_view<unsigned int, unsigned int>
       indices_relevant(0, n_locally_relevant);
 
     const auto &sparsity = offline_data->sparsity_pattern;
 
     const auto &lumped_mass_matrix = offline_data->lumped_mass_matrix;
     const auto &norm_matrix        = offline_data->norm_matrix;
     const auto &nij_matrix         = offline_data->nij_matrix;
     const auto &cij_matrix         = offline_data->cij_matrix;
 
     const auto &boundary_normal_map = offline_data->boundary_normal_map;
 
 @endcode
 
 <b>Step 1</b>: Computing the $d_{ij}$ graph viscosity matrix.
     

 
 It is important to highlight that the viscosity matrix has to be
 symmetric, i.e., $d_{ij} = d_{ji}$. In this regard we note here that
 $\int_{\Omega} \nabla \phi_j \phi_i \, \mathrm{d}\mathbf{x}= -
 \int_{\Omega} \nabla \phi_i \phi_j \, \mathrm{d}\mathbf{x}$ (or
 equivalently $\mathbf{c}_{ij} = - \mathbf{c}_{ji}$) provided either
 $\mathbf{x}_i$ or $\mathbf{x}_j$ is a support point located away
 from the boundary. In this case we can check that
 $\lambda_{\text{max}} (\mathbf{U}_i^{n}, \mathbf{U}_j^{n},
 \textbf{n}_{ij}) = \lambda_{\text{max}} (\mathbf{U}_j^{n},
 \mathbf{U}_i^{n},\textbf{n}_{ji})$ by construction, which guarantees
 the property $d_{ij} = d_{ji}$.
     

 
 However, if both support points $\mathbf{x}_i$ or $\mathbf{x}_j$
 happen to lie on the boundary, then, the equalities $\mathbf{c}_{ij} =
 - \mathbf{c}_{ji}$ and $\lambda_{\text{max}} (\mathbf{U}_i^{n},
 \mathbf{U}_j^{n}, \textbf{n}_{ij}) = \lambda_{\text{max}}
 (\mathbf{U}_j^{n}, \mathbf{U}_i^{n}, \textbf{n}_{ji})$ do not
 necessarily hold true. The only mathematically safe solution for this
 dilemma is to compute both of them $d_{ij}$ and $d_{ji}$ and
 take the maximum.
     

 
 Overall, the computation of $d_{ij}$ is quite expensive. In
 order to save some computing time we exploit the fact that the viscosity
 matrix has to be symmetric (as mentioned above): we only compute
 the upper-triangular entries of $d_{ij}$ and copy the
 corresponding entries to the lower-triangular counterpart.
     

 
 We use again parallel::apply_to_subranges() for thread-parallel for
 loops. Pretty much all the ideas for parallel traversal that we
 introduced when discussing the assembly of the matrix
 <code>norm_matrix</code> and the normalization of
 <code>nij_matrix</code> above are used here again.
     

 
 We define again a "worker" function <code>on_subranges</code> that
 computes the viscosity $d_{ij}$ for a subrange [i1, i2) of column
 indices:
 
 @code
     {
       TimerOutput::Scope scope(computing_timer,
                                "time_stepping - 1 compute d_ij");
 
       const auto on_subranges = 
         [&](const auto i1, const auto i2) {
           for (const auto i :
                std_cxx20::ranges::iota_view<unsigned int, unsigned int>(*i1,
                                                                         *i2))
             {
               const auto U_i = gather(U, i);
 
 @endcode
 
 For a given column index i we iterate over the columns of the
 sparsity pattern from <code>sparsity.begin(i)</code> to
 <code>sparsity.end(i)</code>:
 
 @code
               for (auto jt = sparsity.begin(i); jt != sparsity.end(i); ++jt)
                 {
                   const auto j = jt->column();
 
 @endcode
 
 We only compute $d_{ij}$ if $j < i$ (upper triangular
 entries) and later copy the values over to $d_{ji}$.
 
 @code
                   if (j >= i)
                     continue;
 
                   const auto U_j = gather(U, j);
 
                   const auto   n_ij = gather_get_entry(nij_matrix, jt);
                   const double norm = get_entry(norm_matrix, jt);
 
                   const auto lambda_max =
                     ProblemDescription<dim>::compute_lambda_max(U_i, U_j, n_ij);
 
                   double d = norm * lambda_max;
 
 @endcode
 
 If both support points happen to be at the boundary we
 have to compute $d_{ji}$ as well and then take
 $\max(d_{ij},d_{ji})$. After this we can finally set the
 upper triangular and lower triangular entries.
 
 @code
                   if (boundary_normal_map.count(i) != 0 &&
                       boundary_normal_map.count(j) != 0)
                     {
                       const auto n_ji = gather(nij_matrix, j, i);
                       const auto lambda_max_2 =
                         ProblemDescription<dim>::compute_lambda_max(U_j,
                                                                     U_i,
                                                                     n_ji);
                       const double norm_2 = norm_matrix(j, i);
 
                       d = std::max(d, norm_2 * lambda_max_2);
                     }
 
                   set_entry(dij_matrix, jt, d);
                   dij_matrix(j, i) = d;
                 }
             }
         };
 
       parallel::apply_to_subranges(indices_relevant.begin(),
                                    indices_relevant.end(),
                                    on_subranges,
                                    4096);
     }
 
 @endcode
 
 <b>Step 2</b>: Compute diagonal entries $d_{ii}$ and
 $\tau_{\text{max}}$.
 

 
 So far we have computed all off-diagonal entries of the matrix
 <code>dij_matrix</code>. We still have to fill its diagonal entries
 defined as $d_{ii}^n = - \sum_{j \in \mathcal{I}(i)\backslash \{i\}}
 d_{ij}^n$. We use again parallel::apply_to_subranges() for this
 purpose. While computing the $d_{ii}$s we also determine the
 largest admissible time-step, which is defined as
 \f[
 \tau_n \dealcoloneq c_{\text{cfl}}\,\min_{i\in\mathcal{V}}
 \left(\frac{m_i}{-2\,d_{ii}^{n}}\right) \, .
 \f]
 Note that the operation $\min_{i \in \mathcal{V}}$ is intrinsically
 global, it operates on all nodes: first we have to take the minimum
 over all threads (of a given node) and then we have to take the
 minimum over all MPI processes. In the current implementation:
 - We store  <code>tau_max</code> (per node) as
 <a
 href="http://www.cplusplus.com/reference/atomic/atomic/"><code>std::atomic<double></code></a>.
 The internal implementation of <code>std::atomic</code> will take
 care of guarding any possible race condition when more than one
 thread attempts to read and/or write <code>tau_max</code> at the
 same time.
 - In order to take the minimum over all MPI process we use the utility
 function <code>Utilities::MPI::min</code>.
 

 
 
 @code
     std::atomic<double> tau_max{std::numeric_limits<double>::infinity()};
 
     {
       TimerOutput::Scope scope(computing_timer,
                                "time_stepping - 2 compute d_ii, and tau_max");
 
 @endcode
 
 on_subranges() will be executed on every thread individually. The
 variable <code>tau_max_on_subrange</code> is thus stored thread
 locally.
 

 
 
 @code
       const auto on_subranges = 
         [&](const auto i1, const auto i2) {
           double tau_max_on_subrange = std::numeric_limits<double>::infinity();
 
           for (const auto i :
                std_cxx20::ranges::iota_view<unsigned int, unsigned int>(*i1,
                                                                         *i2))
             {
               double d_sum = 0.;
 
               for (auto jt = sparsity.begin(i); jt != sparsity.end(i); ++jt)
                 {
                   const auto j = jt->column();
 
                   if (j == i)
                     continue;
 
                   d_sum -= get_entry(dij_matrix, jt);
                 }
 
 @endcode
 
 We store the negative sum of the d_ij entries at the
 diagonal position
 
 @code
               dij_matrix.diag_element(i) = d_sum;
 @endcode
 
 and compute the maximal local time-step size
 <code>tau</code>:
 
 @code
               const double mass   = lumped_mass_matrix.diag_element(i);
               const double tau    = cfl_update * mass / (-2. * d_sum);
               tau_max_on_subrange = std::min(tau_max_on_subrange, tau);
             }
 
 @endcode
 
 <code>tau_max_on_subrange</code> contains the largest possible
 time-step size computed for the (thread local) subrange. At this
 point we have to synchronize the value over all threads. This is
 were we use the <a
 href="http://www.cplusplus.com/reference/atomic/atomic/"><code>std::atomic<double></code></a>
 <i>compare exchange</i> update mechanism:
 
 @code
           double current_tau_max = tau_max.load();
           while (current_tau_max > tau_max_on_subrange &&
                  !tau_max.compare_exchange_weak(current_tau_max,
                                                 tau_max_on_subrange))
             ;
         };
 
       parallel::apply_to_subranges(indices_relevant.begin(),
                                    indices_relevant.end(),
                                    on_subranges,
                                    4096);
 
 @endcode
 
 After all threads have finished we can simply synchronize the
 value over all MPI processes:
 

 
 
 @code
       tau_max.store(Utilities::MPI::min(tau_max.load(), mpi_communicator));
 
 @endcode
 
 This is a good point to verify that the computed
 <code>tau_max</code> is indeed a valid floating point number.
 
 @code
       AssertThrow(
         !std::isnan(tau_max.load()) && !std::isinf(tau_max.load()) &&
           tau_max.load() > 0.,
         ExcMessage(
           "I'm sorry, Dave. I'm afraid I can't do that. - We crashed."));
     }
 
 @endcode
 
 <b>Step 3</b>: Perform update.
 

 
 At this point, we have computed all viscosity coefficients $d_{ij}$
 and we know the maximal admissible time-step size
 $\tau_{\text{max}}$. This means we can now compute the update:
     

 
 \f[
 \mathbf{U}_i^{n+1} = \mathbf{U}_i^{n} - \frac{\tau_{\text{max}} }{m_i}
 \sum_{j \in \mathcal{I}(i)} (\mathbb{f}(\mathbf{U}_j^{n}) -
 \mathbb{f}(\mathbf{U}_i^{n})) \cdot \mathbf{c}_{ij} - d_{ij}
 (\mathbf{U}_j^{n} - \mathbf{U}_i^{n})
 \f]
     

 
 This update formula is slightly different from what was discussed in
 the introduction (in the pseudo-code). However, it can be shown that
 both equations are algebraically equivalent (they will produce the
 same numerical values). We favor this second formula since it has
 natural cancellation properties that might help avoid numerical
 artifacts.
 

 
 
 @code
     {
       TimerOutput::Scope scope(computing_timer,
                                "time_stepping - 3 perform update");
 
       const auto on_subranges = 
         [&](const auto i1, const auto i2) {
           for (const auto i : boost::make_iterator_range(i1, i2))
             {
               Assert(i < n_locally_owned, ExcInternalError());
 
               const auto U_i = gather(U, i);
 
               const auto   f_i = ProblemDescription<dim>::flux(U_i);
               const double m_i = lumped_mass_matrix.diag_element(i);
 
               auto U_i_new = U_i;
 
               for (auto jt = sparsity.begin(i); jt != sparsity.end(i); ++jt)
                 {
                   const auto j = jt->column();
 
                   const auto U_j = gather(U, j);
                   const auto f_j = ProblemDescription<dim>::flux(U_j);
 
                   const auto c_ij = gather_get_entry(cij_matrix, jt);
                   const auto d_ij = get_entry(dij_matrix, jt);
 
                   for (unsigned int k = 0; k < problem_dimension; ++k)
                     {
                       U_i_new[k] +=
                         tau_max / m_i *
                         (-(f_j[k] - f_i[k]) * c_ij + d_ij * (U_j[k] - U_i[k]));
                     }
                 }
 
               scatter(temporary_vector, U_i_new, i);
             }
         };
 
       parallel::apply_to_subranges(indices_owned.begin(),
                                    indices_owned.end(),
                                    on_subranges,
                                    4096);
     }
 
 @endcode
 
 <b>Step 4</b>: Fix up boundary states.
 

 
 As a last step in the Forward Euler method, we have to fix up all
 boundary states. As discussed in the intro we
 - advance in time satisfying no boundary condition at all,
 - at the end of the time step enforce boundary conditions strongly
 in a post-processing step.
     

 
 Here, we compute the correction
 \f[
 \mathbf{m}_i \dealcoloneq \mathbf{m}_i - (\boldsymbol{\nu}_i \cdot
 \mathbf{m}_i) \boldsymbol{\nu}_i,
 \f]
 which removes the normal component of $\mathbf{m}$.
 

 
 
 @code
     {
       TimerOutput::Scope scope(computing_timer,
                                "time_stepping - 4 fix boundary states");
 
       for (auto it : boundary_normal_map)
         {
           const auto i = it.first;
 
 @endcode
 
 We only iterate over the locally owned subset:
 
 @code
           if (i >= n_locally_owned)
             continue;
 
           const auto &normal   = std::get<0>(it.second);
           const auto &id       = std::get<1>(it.second);
           const auto &position = std::get<2>(it.second);
 
           auto U_i = gather(temporary_vector, i);
 
 @endcode
 
 On free slip boundaries we remove the normal component of the
 momentum:
 
 @code
           if (id == Boundaries::free_slip)
             {
               auto m = ProblemDescription<dim>::momentum(U_i);
               m -= (m * normal) * normal;
               for (unsigned int k = 0; k < dim; ++k)
                 U_i[k + 1] = m[k];
             }
 
 @endcode
 
 On Dirichlet boundaries we enforce initial conditions
 strongly:
 
 @code
           else if (id == Boundaries::dirichlet)
             {
               U_i = initial_values->initial_state(position, t + tau_max);
             }
 
           scatter(temporary_vector, U_i, i);
         }
     }
 
 @endcode
 
 <b>Step 5</b>: We now update the ghost layer over all MPI ranks,
 swap the temporary vector with the solution vector <code>U</code>
 (that will get returned by reference) and return the chosen
 time-step size $\tau_{\text{max}}$:
 

 
 
 @code
     for (auto &it : temporary_vector)
       it.update_ghost_values();
 
     U.swap(temporary_vector);
 
     return tau_max;
   }
 
 @endcode
 
 
 <a name="Schlierenpostprocessing"></a> 
 <h4>Schlieren postprocessing</h4>
   

 
 At various intervals we will output the current state <code>U</code>
 of the solution together with a so-called Schlieren plot.
 The constructor of the <code>SchlierenPostprocessor</code> class again
 contains no surprises. We simply supply default values to and register
 two parameters:
 - schlieren_beta:
 is an ad-hoc positive amplification factor in order to enhance the
 contrast in the visualization. Its actual value is a matter of
 taste.
 - schlieren_index: is an integer indicating which component of the
 state $[\rho, \mathbf{m},E]$ are we going to use in order to generate
 the visualization.
 

 
 
 @code
   template <int dim>
   SchlierenPostprocessor<dim>::SchlierenPostprocessor(
     const MPI_Comm          mpi_communicator,
     TimerOutput &           computing_timer,
     const OfflineData<dim> &offline_data,
     const std::string &     subsection //= "SchlierenPostprocessor" ！改)
     : ParameterAcceptor(subsection)
     , mpi_communicator(mpi_communicator)
     , computing_timer(computing_timer)
     , offline_data(&offline_data)
   {
     schlieren_beta = 10.;
     add_parameter("schlieren beta",
                   schlieren_beta,
                   "Beta factor used in Schlieren-type postprocessor");
 
     schlieren_index = 0;
     add_parameter("schlieren index",
                   schlieren_index,
                   "Use the corresponding component of the state vector for the "
                   "schlieren plot");
   }
 
 @endcode
 
 Again, the <code>prepare()</code> function initializes two temporary
 the vectors (<code>r</code> and <code>schlieren</code>).
 

 
 
 @code
   template <int dim>
   void SchlierenPostprocessor<dim>::prepare()
   {
     TimerOutput::Scope scope(computing_timer,
                              "schlieren_postprocessor - prepare scratch space");
 
     r.reinit(offline_data->n_locally_relevant);
     schlieren.reinit(offline_data->partitioner);
   }
 
 @endcode
 
 We now discuss the implementation of the class member
 <code>SchlierenPostprocessor<dim>::compute_schlieren()</code>, which
 basically takes a component of the state vector <code>U</code> and
 computes the Schlieren indicator for such component (the formula of the
 Schlieren indicator can be found just before the declaration of the class
 <code>SchlierenPostprocessor</code>). We start by noting
 that this formula requires the "nodal gradients" $\nabla r_j$.
 However, nodal values of gradients are not defined for $\mathcal{C}^0$
 finite element functions. More generally, pointwise values of
 gradients are not defined for $W^{1,p}(\Omega)$ functions. The
 simplest technique we can use to recover gradients at nodes is
 weighted-averaging i.e.
   

 
 \f[ \nabla r_j \dealcoloneq \frac{1}{\int_{S_i} \omega_i(\mathbf{x}) \,
 \mathrm{d}\mathbf{x}}
 \int_{S_i} r_h(\mathbf{x}) \omega_i(\mathbf{x}) \, \mathrm{d}\mathbf{x}
 \ \ \ \ \ \mathbf{(*)} \f]
   

 
 where $S_i$ is the support of the shape function $\phi_i$, and
 $\omega_i(\mathbf{x})$ is the weight. The weight could be any
 positive function such as
 $\omega_i(\mathbf{x}) \equiv 1$ (that would allow us to recover the usual
 notion of mean value). But as usual, the goal is to reuse the off-line
 data as much as possible. In this sense, the most natural
 choice of weight is $\omega_i = \phi_i$. Inserting this choice of
 weight and the expansion $r_h(\mathbf{x}) = \sum_{j \in \mathcal{V}}
 r_j \phi_j(\mathbf{x})$ into $\mathbf{(*)}$ we get :
   

 
 \f[ \nabla r_j \dealcoloneq \frac{1}{m_i} \sum_{j \in \mathcal{I}(i)} r_j
 \mathbf{c}_{ij} \ \ \ \ \ \mathbf{(**)} \, . \f]
   

 
 Using this last formula we can recover averaged nodal gradients without
 resorting to any form of quadrature. This idea aligns quite well with
 the whole spirit of edge-based schemes (or algebraic schemes) where
 we want to operate on matrices and vectors as directly as
 it could be possible avoiding by all means assembly of bilinear
 forms, cell-loops, quadrature, or any other
 intermediate construct/operation between the input arguments (the state
 from the previous time-step) and the actual matrices and vectors
 required to compute the update.
   

 
 The second thing to note is that we have to compute global minimum and
 maximum $\max_j |\nabla r_j|$ and $\min_j |\nabla r_j|$. Following the
 same ideas used to compute the time step size in the class member
 <code>%TimeStepping\<dim>::%step()</code> we define $\max_j |\nabla r_j|$
 and $\min_j |\nabla r_j|$ as atomic doubles in order to resolve any
 conflicts between threads. As usual, we use
 <code>Utilities::MPI::max()</code> and
 <code>Utilities::MPI::min()</code> to find the global maximum/minimum
 among all MPI processes.
   

 
 Finally, it is not possible to compute the Schlieren indicator in a single
 loop over all nodes. The entire operation requires two loops over nodes:
   

 
 - The first loop computes $|\nabla r_i|$ for all $i \in \mathcal{V}$ in
 the mesh, and the bounds $\max_j |\nabla r_j|$ and
 $\min_j |\nabla r_j|$.
 - The second loop finally computes the Schlieren indicator using the
 formula
   

 
 \f[ \text{schlieren}[i] = e^{\beta \frac{ |\nabla r_i|
 - \min_j |\nabla r_j| }{\max_j |\nabla r_j| - \min_j |\nabla r_j| } }
 \, . \f]
   

 
 This means that we will have to define two workers
 <code>on_subranges</code> for each one of these stages.
 

 
 
 @code
   template <int dim>
   void SchlierenPostprocessor<dim>::compute_schlieren(const vector_type &U)
   {
     TimerOutput::Scope scope(
       computing_timer, "schlieren_postprocessor - compute schlieren plot");
 
     const auto &sparsity            = offline_data->sparsity_pattern;
     const auto &lumped_mass_matrix  = offline_data->lumped_mass_matrix;
     const auto &cij_matrix          = offline_data->cij_matrix;
     const auto &boundary_normal_map = offline_data->boundary_normal_map;
     const auto &n_locally_owned     = offline_data->n_locally_owned;
 
     const auto indices =
       std_cxx20::ranges::iota_view<unsigned int, unsigned int>(0,
                                                                n_locally_owned);
 
 @endcode
 
 We define the r_i_max and r_i_min in the current MPI process as
 atomic doubles in order to avoid race conditions between threads:
 
 @code
     std::atomic<double> r_i_max{0.};
     std::atomic<double> r_i_min{std::numeric_limits<double>::infinity()};
 
 @endcode
 
 First loop: compute the averaged gradient at each node and the
 global maxima and minima of the gradients.
 
 @code
     {
       const auto on_subranges = 
         [&](const auto i1, const auto i2) {
           double r_i_max_on_subrange = 0.;
           double r_i_min_on_subrange = std::numeric_limits<double>::infinity();
 
           for (const auto i : boost::make_iterator_range(i1, i2))
             {
               Assert(i < n_locally_owned, ExcInternalError());
 
               Tensor<1, dim> r_i;
 
               for (auto jt = sparsity.begin(i); jt != sparsity.end(i); ++jt)
                 {
                   const auto j = jt->column();
 
                   if (i == j)
                     continue;
 
                   const auto U_js = U[schlieren_index].local_element(j);
                   const auto c_ij = gather_get_entry(cij_matrix, jt);
                   r_i += c_ij * U_js;
                 }
 
 @endcode
 
 We fix up the gradient r_i at free slip boundaries similarly to
 how we fixed up boundary states in the forward Euler step.
 This avoids sharp, artificial gradients in the Schlieren
 plot at free slip boundaries and is a purely cosmetic choice.
 

 
 
 @code
               const auto bnm_it = boundary_normal_map.find(i);
               if (bnm_it != boundary_normal_map.end())
                 {
                   const auto &normal = std::get<0>(bnm_it->second);
                   const auto &id     = std::get<1>(bnm_it->second);
 
                   if (id == Boundaries::free_slip)
                     r_i -= 1. * (r_i * normal) * normal;
                   else
                     r_i = 0.;
                 }
 
 @endcode
 
 We remind the reader that we are not interested in the nodal
 gradients per se. We only want their norms in order to
 compute the Schlieren indicator (weighted with the lumped
 mass matrix $m_i$):
 
 @code
               const double m_i    = lumped_mass_matrix.diag_element(i);
               r[i]                = r_i.norm() / m_i;
               r_i_max_on_subrange = std::max(r_i_max_on_subrange, r[i]);
               r_i_min_on_subrange = std::min(r_i_min_on_subrange, r[i]);
             }
 
 @endcode
 
 We compare the current_r_i_max and current_r_i_min (in the
 current subrange) with r_i_max and r_i_min (for the current MPI
 process) and update them if necessary:
 

 
 
 @code
           double current_r_i_max = r_i_max.load();
           while (current_r_i_max < r_i_max_on_subrange &&
                  !r_i_max.compare_exchange_weak(current_r_i_max,
                                                 r_i_max_on_subrange))
             ;
 
           double current_r_i_min = r_i_min.load();
           while (current_r_i_min > r_i_min_on_subrange &&
                  !r_i_min.compare_exchange_weak(current_r_i_min,
                                                 r_i_min_on_subrange))
             ;
         };
 
       parallel::apply_to_subranges(indices.begin(),
                                    indices.end(),
                                    on_subranges,
                                    4096);
     }
 
 @endcode
 
 And synchronize <code>r_i_max</code> and <code>r_i_min</code> over
 all MPI processes.
 

 
 
 @code
     r_i_max.store(Utilities::MPI::max(r_i_max.load(), mpi_communicator));
     r_i_min.store(Utilities::MPI::min(r_i_min.load(), mpi_communicator));
 
 @endcode
 
 Second loop: we now have the vector <code>r</code> and the scalars
 <code>r_i_max</code> and <code>r_i_min</code> at our disposal. We
 are thus in a position to actually compute the Schlieren indicator.
 

 
 
 @code
     {
       const auto on_subranges = 
         [&](const auto i1, const auto i2) {
           for (const auto i : boost::make_iterator_range(i1, i2))
             {
               Assert(i < n_locally_owned, ExcInternalError());
 
               schlieren.local_element(i) =
                 1. - std::exp(-schlieren_beta * (r[i] - r_i_min) /
                               (r_i_max - r_i_min));
             }
         };
 
       parallel::apply_to_subranges(indices.begin(),
                                    indices.end(),
                                    on_subranges,
                                    4096);
     }
 
 @endcode
 
 And finally, exchange ghost elements.
 
 @code
     schlieren.update_ghost_values();
   }
 
 @endcode
 
 
 <a name="Themainloop"></a> 
 <h4>The main loop</h4>
   

 
 With all classes implemented it is time to create an instance of
 <code>Discretization<dim></code>, <code>OfflineData<dim></code>,
 <code>InitialValues<dim></code>, <code>%TimeStepping\<dim></code>, and
 <code>SchlierenPostprocessor<dim></code>, and run the forward Euler
 step in a loop.
   

 
 In the constructor of <code>MainLoop<dim></code> we now initialize an
 instance of all classes, and declare a number of parameters
 controlling output. Most notable, we declare a boolean parameter
 <code>resume</code> that will control whether the program attempts to
 restart from an interrupted computation, or not.
 

 
 
 @code
   template <int dim>
   MainLoop<dim>::MainLoop(const MPI_Comm mpi_communicator)
     : ParameterAcceptor("A - MainLoop")
     , mpi_communicator(mpi_communicator)
     , computing_timer(mpi_communicator,
                       timer_output,
                       TimerOutput::never,
                       TimerOutput::cpu_and_wall_times)
     , pcout(std::cout, Utilities::MPI::this_mpi_process(mpi_communicator) == 0)
     , discretization(mpi_communicator, computing_timer, "B - Discretization")
     , offline_data(mpi_communicator,
                    computing_timer,
                    discretization,
                    "C - OfflineData")
     , initial_values("D - InitialValues")
     , time_stepping(mpi_communicator,
                     computing_timer,
                     offline_data,
                     initial_values,
                     "E - TimeStepping")
     , schlieren_postprocessor(mpi_communicator,
                               computing_timer,
                               offline_data,
                               "F - SchlierenPostprocessor")
   {
     base_name = "test";
     add_parameter("basename", base_name, "Base name for all output files");
 
     t_final = 4.;
     add_parameter("final time", t_final, "Final time");
 
     output_granularity = 0.02;
     add_parameter("output granularity",
                   output_granularity,
                   "time interval for output");
 
     asynchronous_writeback = true;
     add_parameter("asynchronous writeback",
                   asynchronous_writeback,
                   "Write out solution in a background thread performing IO");
 
     resume = false;
     add_parameter("resume", resume, "Resume an interrupted computation.");
   }
 
 @endcode
 
 We start by implementing a helper function <code>print_head()</code>
 in an anonymous namespace that is used to output messages in the
 terminal with some nice formatting.
 

 
 
 @code
   namespace
   {
     void print_head(ConditionalOStream &pcout,
                     const std::string & header,
                     const std::string & secondary = "")
     {
       const auto header_size   = header.size();
       const auto padded_header = std::string((34 - header_size) / 2, ' ') +
                                  header +
                                  std::string((35 - header_size) / 2, ' ');
 
       const auto secondary_size = secondary.size();
       const auto padded_secondary =
         std::string((34 - secondary_size) / 2, ' ') + secondary +
         std::string((35 - secondary_size) / 2, ' ');
 
       // clang-format off 
       pcout << std::endl;
       pcout << "    ####################################################" << std::endl;
       pcout << "    #########                                  #########" << std::endl;
       pcout << "    #########"     <<  padded_header   <<     "#########" << std::endl;
       pcout << "    #########"     << padded_secondary <<     "#########" << std::endl;
       pcout << "    #########                                  #########" << std::endl;
       pcout << "    ####################################################" << std::endl;
       pcout << std::endl;
       // clang-format on 
     }
   } // namespace
 
 @endcode
 
 With <code>print_head</code> in place it is now time to implement the
 <code>MainLoop<dim>::run()</code> that contains the main loop of our
 program.
 

 
 
 @code
   template <int dim>
   void MainLoop<dim>::run()
   {
 @endcode
 
 We start by reading in parameters and initializing all objects. We
 note here that the call to ParameterAcceptor::initialize reads in
 all parameters from the parameter file (whose name is given as a
 string argument). ParameterAcceptor handles a global
 ParameterHandler that is initialized with subsections and parameter
 declarations for all class instances that are derived from
 ParameterAceptor. The call to initialize enters the subsection for
 each each derived class, and sets all variables that were added
 using ParameterAcceptor::add_parameter()
 

 
 
 @code
     pcout << "Reading parameters and allocating objects... " << std::flush;
 
     ParameterAcceptor::initialize("step-69.prm");
     pcout << "done" << std::endl;
 
 @endcode
 
 Next we create the triangulation, assemble all matrices, set up
 scratch space, and initialize the DataOut<dim> object:
 

 
 
 @code
     {
       print_head(pcout, "create triangulation");
       discretization.setup();
 
       pcout << "Number of active cells:       "
             << discretization.triangulation.n_global_active_cells()
             << std::endl;
 
       print_head(pcout, "compute offline data");
       offline_data.setup();
       offline_data.assemble();
 
       pcout << "Number of degrees of freedom: "
             << offline_data.dof_handler.n_dofs() << std::endl;
 
       print_head(pcout, "set up time step");
       time_stepping.prepare();
       schlieren_postprocessor.prepare();
     }
 
 @endcode
 
 We will store the current time and state in the variable
 <code>t</code> and vector <code>U</code>:
 

 
 
 @code
     double       t            = 0.;
     unsigned int output_cycle = 0;
 
     print_head(pcout, "interpolate initial values");
     vector_type U = interpolate_initial_values();
 
 @endcode
 
 
 <a name="Resume"></a> 
 <h5>Resume</h5>
     

 
 By default the boolean <code>resume</code> is set to false, i.e. the
 following code snippet is not run. However, if
 <code>resume==true</code> we indicate that we have indeed an
 interrupted computation and the program shall restart by reading in
 an old state consisting of <code>t</code>,
 <code>output_cycle</code>, and <code>U</code> from a checkpoint
 file. These checkpoint files will be created in the
 <code>output()</code> routine discussed below.
 

 
 
 @code
     if (resume)
       {
         print_head(pcout, "restore interrupted computation");
 
         const unsigned int i =
           discretization.triangulation.locally_owned_subdomain();
 
         const std::string name = base_name + "-checkpoint-" +
                                  Utilities::int_to_string(i, 4) + ".archive";
         std::ifstream file(name, std::ios::binary);
 
 @endcode
 
 We use a <code>boost::archive</code> to store and read in the
 contents the checkpointed state.
 

 
 
 @code
         boost::archive::binary_iarchive ia(file);
         ia >> t >> output_cycle;
 
         for (auto &it1 : U)
           {
 @endcode
 
 <code>it1</code> iterates over all components of the state
 vector <code>U</code>. We read in every entry of the
 component in sequence and update the ghost layer afterwards:
 
 @code
             for (auto &it2 : it1)
               ia >> it2;
             it1.update_ghost_values();
           }
       }
 
 @endcode
 
 With either the initial state set up, or an interrupted state
 restored it is time to enter the main loop:
 

 
 
 @code
     output(U, base_name, t, output_cycle++);
 
     print_head(pcout, "enter main loop");
 
     for (unsigned int cycle = 1; t < t_final; ++cycle)
       {
 @endcode
 
 We first print an informative status message
 

 
 
 @code
         std::ostringstream head;
         std::ostringstream secondary;
 
         head << "Cycle  " << Utilities::int_to_string(cycle, 6) << "  (" 
              << std::fixed << std::setprecision(1) << t / t_final * 100  
              << "%)";
         secondary << "at time t = " << std::setprecision(8) << std::fixed << t;
 
         print_head(pcout, head.str(), secondary.str());
 
 @endcode
 
 and then perform a single forward Euler step. Note that the
 state vector <code>U</code> is updated in place and that
 <code>time_stepping.make_one_step()</code> returns the chosen step
 size.
 

 
 
 @code
         t += time_stepping.make_one_step(U, t);
 
 @endcode
 
 Post processing, generating output and writing out the current
 state is a CPU and IO intensive task that we cannot afford to do
 every time step - in particular with explicit time stepping. We
 thus only schedule output by calling the <code>output()</code>
 function if we are past a threshold set by
 <code>output_granularity</code>.
 

 
 
 @code
         if (t > output_cycle * output_granularity)
           {
             output(U, base_name, t, output_cycle, true);
             ++output_cycle;
           }
       }
 
 @endcode
 
 We wait for any remaining background output thread to finish before
 printing a summary and exiting.
 
 @code
     if (background_thread_state.valid())
       background_thread_state.wait();
 
     computing_timer.print_summary();
     pcout << timer_output.str() << std::endl;
   }
 
 @endcode
 
 The <code>interpolate_initial_values</code> takes an initial time "t"
 as input argument and populates a state vector <code>U</code> with the
 help of the <code>InitialValues<dim>::initial_state</code> object.
 

 
 
 @code
   template <int dim>
   typename MainLoop<dim>::vector_type
   MainLoop<dim>::interpolate_initial_values(const double t)
   {
     pcout << "MainLoop<dim>::interpolate_initial_values(t = " << t << ")"
           << std::endl;
     TimerOutput::Scope scope(computing_timer,
                              "main_loop - setup scratch space");
 
     vector_type U;
 
     for (auto &it : U)
       it.reinit(offline_data.partitioner);
 
     constexpr auto problem_dimension =
       ProblemDescription<dim>::problem_dimension;
 
 @endcode
 
 The function signature of
 <code>InitialValues<dim>::initial_state</code> is not quite right
 for VectorTools::interpolate(). We work around this issue by, first,
 creating a lambda function that for a given position <code>x</code>
 returns just the value of the <code>i</code>th component. This
 lambda in turn is converted to a dealii::Function with the help of
 the ScalarFunctionFromFunctionObject wrapper.
 

 
 
 @code
     for (unsigned int i = 0; i < problem_dimension; ++i)
       VectorTools::interpolate(offline_data.dof_handler,
                                ScalarFunctionFromFunctionObject<dim, double>(
                                  [&](const Point<dim> &x) {
                                    return initial_values.initial_state(x, t)[i];
                                  }),
                                U[i]);
 
     for (auto &it : U)
       it.update_ghost_values();
 
     return U;
   }
 
 @endcode
 
 
 <a name="Outputandcheckpointing"></a> 
 <h5>Output and checkpointing</h5>
   

 
 Writing out the final vtk files is quite an IO intensive task that can
 stall the main loop for a while. In order to avoid this we use an <a
 href="https://en.wikipedia.org/wiki/Asynchronous_I/O">asynchronous
 IO</a> strategy by creating a background thread that will perform IO
 while the main loop is allowed to continue. In order for this to work
 we have to be mindful of two things:
 - Before running the <code>output_worker</code> thread, we have to create
 a copy of the state vector <code>U</code>. We store it in the
 vector <code>output_vector</code>.
 - We have to avoid any MPI communication in the background thread,
 otherwise the program might deadlock. This implies that we have to
 run the postprocessing outside of the worker thread.
 

 
 
 @code
   template <int dim>
   void MainLoop<dim>::output(const typename MainLoop<dim>::vector_type &U,
                              const std::string &                        name,
                              const double                               t,
                              const unsigned int                         cycle,
                              const bool checkpoint)
   {
     pcout << "MainLoop<dim>::output(t = " << t
           << ", checkpoint = " << checkpoint << ")" << std::endl;
 
 @endcode
 
 If the asynchronous writeback option is set we launch a background
 thread performing all the slow IO to disc. In that case we have to
 make sure that the background thread actually finished running. If
 not, we have to wait to for it to finish. We launch said background
 thread with <a
 href="https://en.cppreference.com/w/cpp/thread/async"><code>std::async()</code></a>
 that returns a <a
 href="https://en.cppreference.com/w/cpp/thread/future"><code>std::future</code></a>
 object. This <code>std::future</code> object contains the return
 value of the function, which is in our case simply
 <code>void</code>.
 

 
 
 @code
     if (background_thread_state.valid())
       {
         TimerOutput::Scope timer(computing_timer, "main_loop - stalled output");
         background_thread_state.wait();
       }
 
     constexpr auto problem_dimension =
       ProblemDescription<dim>::problem_dimension;
 
 @endcode
 
 At this point we make a copy of the state vector, run the schlieren
 postprocessor, and run DataOut<dim>::build_patches() The actual
 output code is standard: We create a DataOut instance, attach all
 data vectors we want to output and call
 DataOut<dim>::build_patches(). There is one twist, however. In order
 to perform asynchronous IO on a background thread we create the
 DataOut<dim> object as a shared pointer that we pass on to the
 worker thread to ensure that once we exit this function and the
 worker thread finishes the DataOut<dim> object gets destroyed again.
 

 
 
 @code
     for (unsigned int i = 0; i < problem_dimension; ++i)
       {
         output_vector[i] = U[i];
         output_vector[i].update_ghost_values();
       }
 
     schlieren_postprocessor.compute_schlieren(output_vector);
 
     auto data_out = std::make_shared<DataOut<dim>>();
 
     data_out->attach_dof_handler(offline_data.dof_handler);
 
     const auto &component_names = ProblemDescription<dim>::component_names;
 
     for (unsigned int i = 0; i < problem_dimension; ++i)
       data_out->add_data_vector(output_vector[i], component_names[i]);
 
     data_out->add_data_vector(schlieren_postprocessor.schlieren,
                               "schlieren_plot");
 
     data_out->build_patches(discretization.mapping,
                             discretization.finite_element.degree - 1);
 
 @endcode
 
 Next we create a lambda function for the background thread. We <a
 href="https://en.cppreference.com/w/cpp/language/lambda">capture</a>
 the <code>this</code> pointer as well as most of the arguments of
 the output function by value so that we have access to them inside
 the lambda function.
 
 @code
     const auto output_worker = [this, name, t, cycle, checkpoint, data_out]() {
       if (checkpoint)
         {
 @endcode
 
 We checkpoint the current state by doing the precise inverse
 operation to what we discussed for the <a href="Resume">resume
 logic</a>:
 

 
 
 @code
           const unsigned int i =
             discretization.triangulation.locally_owned_subdomain();
           std::string filename =
             name + "-checkpoint-" + Utilities::int_to_string(i, 4) + ".archive";
 
           std::ofstream file(filename, std::ios::binary | std::ios::trunc);
 
           boost::archive::binary_oarchive oa(file);
           oa << t << cycle;
           for (const auto &it1 : output_vector)
             for (const auto &it2 : it1)
               oa << it2;
         }
 
       DataOutBase::VtkFlags flags(t,
                                   cycle,
                                   true,
                                   DataOutBase::VtkFlags::best_speed);
       data_out->set_flags(flags);
 
       data_out->write_vtu_with_pvtu_record(
         "", name + "-solution", cycle, mpi_communicator, 6);
     };
 
 @endcode
 
 If the asynchronous writeback option is set we launch a new
 background thread with the help of
 <a
 href="https://en.cppreference.com/w/cpp/thread/async"><code>std::async</code></a>
 function. The function returns a <a
 href="https://en.cppreference.com/w/cpp/thread/future"><code>std::future</code></a>
 object that we can use to query the status of the background thread.
 At this point we can return from the <code>output()</code> function
 and resume with the time stepping in the main loop - the thread will
 run in the background.
 
 @code
     if (asynchronous_writeback)
       {
         background_thread_state = std::async(std::launch::async, output_worker);
       }
     else
       {
         output_worker();
       }
   }
 
 } // namespace Step69
 
 @endcode
 
 And finally, the main function.
 

 
 
 @code
 int main(int argc, char *argv[])
 {
   try
     {
       constexpr int dim = 2;
 
       using namespace dealii;
       using namespace Step69;
 
       Utilities::MPI::MPI_InitFinalize mpi_initialization(argc, argv);
 
       MPI_Comm      mpi_communicator(MPI_COMM_WORLD);
       MainLoop<dim> main_loop(mpi_communicator);
 
       main_loop.run();
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
 }
 @endcode
<a name="Results"></a>
<a name="Results"></a><h1>Results</h1>


Running the program with default parameters in release mode takes about 1
minute on a 4 core machine (with hyperthreading):
@verbatim
# mpirun -np 4 ./step-69 | tee output
Reading parameters and allocating objects... done

    ####################################################
    #########                                  #########
    #########       create triangulation       #########
    #########                                  #########
    ####################################################

Number of active cells:       36864

    ####################################################
    #########                                  #########
    #########       compute offline data       #########
    #########                                  #########
    ####################################################

Number of degrees of freedom: 37376

    ####################################################
    #########                                  #########
    #########         set up time step         #########
    #########                                  #########
    ####################################################

    ####################################################
    #########                                  #########
    #########    interpolate initial values    #########
    #########                                  #########
    #########                                  #########
    ####################################################

TimeLoop<dim>::interpolate_initial_values(t = 0)
TimeLoop<dim>::output(t = 0, checkpoint = 0)

    ####################################################
    #########                                  #########
    #########         enter main loop          #########
    #########                                  #########
    #########                                  #########
    ####################################################

    ####################################################
    #########                                  #########
    #########      Cycle  000001  (0.0%)       #########
    #########      at time t = 0.00000000      #########
    #########                                  #########
    ####################################################

[...]

    ####################################################
    #########                                  #########
    #########     Cycle  007553  (100.0%)      #########
    #########      at time t = 3.99984036      #########
    #########                                  #########
    ####################################################

TimeLoop<dim>::output(t = 4.00038, checkpoint = 1)

+------------------------------------------------------------------------+------------+------------+
| Total CPU time elapsed since start                                     |       357s |            |
|                                                                        |            |            |
| Section                                                    | no. calls |  CPU time  | % of total |
+------------------------------------------------------------+-----------+------------+------------+
| discretization - setup                                     |         1 |     0.113s |         0% |
| offline_data - assemble lumped mass matrix, and c_ij       |         1 |     0.167s |         0% |
| offline_data - compute |c_ij|, and n_ij                    |         1 |   0.00255s |         0% |
| offline_data - create sparsity pattern and set up matrices |         1 |    0.0224s |         0% |
| offline_data - distribute dofs                             |         1 |    0.0617s |         0% |
| offline_data - fix slip boundary c_ij                      |         1 |    0.0329s |         0% |
| schlieren_postprocessor - compute schlieren plot           |       201 |     0.811s |      0.23% |
| schlieren_postprocessor - prepare scratch space            |         1 |   7.6e-05s |         0% |
| time_loop - setup scratch space                            |         1 |     0.127s |         0% |
| time_loop - stalled output                                 |       200 |  0.000685s |         0% |
| time_step - 1 compute d_ij                                 |      7553 |       240s |        67% |
| time_step - 2 compute d_ii, and tau_max                    |      7553 |      11.5s |       3.2% |
| time_step - 3 perform update                               |      7553 |       101s |        28% |
| time_step - 4 fix boundary states                          |      7553 |     0.724s |       0.2% |
| time_step - prepare scratch space                          |         1 |   0.00245s |         0% |
+------------------------------------------------------------+-----------+------------+------------+
@endverbatim

One thing that becomes evident is the fact that the program spends two
thirds of the execution time computing the graph viscosity d_ij and about a
third of the execution time in performing the update, where computing the
flux $f(U)$ is the expensive operation. The preset default resolution is
about 37k gridpoints, which amounts to about 148k spatial degrees of
freedom in 2D. An animated schlieren plot of the solution looks as follows:

<img src="https://www.dealii.org/images/steps/developer/step-69.coarse.gif" alt="" height="300">

It is evident that 37k gridpoints for the first-order method is nowhere
near the resolution needed to resolve any flow features. For comparison,
here is a "reference" computation with a second-order method and about 9.5M
gridpoints (<a href="https://github.com/conservation-laws/ryujin">github
project page</a>):

<img src="https://www.dealii.org/images/steps/developer/step-69.2nd-order.t400.jpg" alt="" height="300">

So, we give the first-order method a second chance and run it with about
2.4M gridpoints on a small compute server:

@verbatim
# mpirun -np 16 ./step-69 | tee output

[...]

    ####################################################
    #########                                  #########
    #########     Cycle  070216  (100.0%)      #########
    #########      at time t = 3.99999231      #########
    #########                                  #########
    ####################################################

TimeLoop<dim>::output(t = 4.00006, checkpoint = 1)

[...]

+------------------------------------------------------------------------+------------+------------+
| Total wallclock time elapsed since start                               |  6.75e+03s |            |
|                                                                        |            |            |
| Section                                                    | no. calls |  wall time | % of total |
+------------------------------------------------------------+-----------+------------+------------+
| discretization - setup                                     |         1 |      1.97s |         0% |
| offline_data - assemble lumped mass matrix, and c_ij       |         1 |      1.19s |         0% |
| offline_data - compute |c_ij|, and n_ij                    |         1 |    0.0172s |         0% |
| offline_data - create sparsity pattern and set up matrices |         1 |     0.413s |         0% |
| offline_data - distribute dofs                             |         1 |      1.05s |         0% |
| offline_data - fix slip boundary c_ij                      |         1 |     0.252s |         0% |
| schlieren_postprocessor - compute schlieren plot           |       201 |      1.82s |         0% |
| schlieren_postprocessor - prepare scratch space            |         1 |  0.000497s |         0% |
| time_loop - setup scratch space                            |         1 |      1.45s |         0% |
| time_loop - stalled output                                 |       200 |   0.00342s |         0% |
| time_step - 1 compute d_ij                                 |     70216 |  4.38e+03s |        65% |
| time_step - 2 compute d_ii, and tau_max                    |     70216 |       419s |       6.2% |
| time_step - 3 perform update                               |     70216 |  1.87e+03s |        28% |
| time_step - 4 fix boundary states                          |     70216 |        24s |      0.36% |
| time_step - prepare scratch space                          |         1 |    0.0227s |         0% |
+------------------------------------------------------------+-----------+------------+------------+
@endverbatim

And with the following result:

<img src="https://www.dealii.org/images/steps/developer/step-69.fine.gif" alt="" height="300">

That's substantially better, although of course at the price of having run
the code for roughly 2 hours on 16 cores.



<a name="extensions"></a>
<a name="Possibilitiesforextensions"></a><h3>Possibilities for extensions</h3>


The program showcased here is really only first-order accurate, as
discussed above. The pictures above illustrate how much diffusion that
introduces and how far the solution is from one that actually resolves
the features we care about.

This can be fixed, but it would exceed what a *tutorial* is about.
Nevertheless, it is worth showing what one can achieve by adding a
second-order scheme. For example, here is a video computed with <a
href=https://conservation-laws.43-1.org/>the following research code</a>
that shows (with a different color scheme) a 2d simulation that corresponds
to the cases shown above:

@htmlonly
<p align="center">
  <iframe width="560" height="315" src="https://www.youtube.com/embed/xIwJZlsXpZ4"
   frameborder="0"
   allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture"
   allowfullscreen></iframe>
 </p>
@endhtmlonly

This simulation was done with 38 million degrees of freedom
(continuous $Q_1$ finite elements) per component of the solution
vector. The exquisite detail of the solution is remarkable for these
kinds of simulations, including in the sub-sonic region behind the
obstacle.

One can also with relative ease further extend this to the 3d case:

@htmlonly
<p align="center">
  <iframe width="560" height="315" src="https://www.youtube.com/embed/vBCRAF_c8m8"
   frameborder="0"
   allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture"
   allowfullscreen></iframe>
 </p>
@endhtmlonly

Solving this becomes expensive, however: The simulation was done with
1,817 million degrees of freedom (continuous $Q_1$ finite elements)
per component (for a total of 9.09 billion spatial degrees of freedom)
and ran on 30,720 MPI ranks. The code achieved an average througput of
969M grid points per second (0.04M gridpoints per second per CPU). The
front and back wall show a "Schlieren plot": the magnitude of the
gradient of the density on an exponential scale from white (low) to
black (high). All other cutplanes and the surface of the obstacle show
the magnitude of the vorticity on a white (low) - yellow (medium) -
red (high) scale. (The scales of the individual cutplanes have been
adjusted for a nicer visualization.)


<a name="PlainProg"></a>
<h1> The plain program</h1>
@include "step-69.cc"
*/
