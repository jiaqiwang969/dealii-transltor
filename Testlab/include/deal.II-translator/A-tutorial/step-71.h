//include/deal.II-translator/A-tutorial/step-71_0.txt
/**
 * @page step_71 The step-71 tutorial program
 * @htmlonly <table class="tutorial" width="50%"> <tr><th
 * colspan="2"><b><small>Table of contents</small></b><b><small>Table of
 * contents</small></b></th></tr> <tr><td width="50%" valign="top">
 * <ol>
 * <li> <a href="#Intro" class=bold>Introduction</a><a href="#Intro"
 * class=bold>Introduction</a>
 * <ul>
 * <li><a href="#AmotivationWhywouldIusethesetools">A motivation: Why would I
 * use these tools?</a><a href="#AmotivationWhywouldIusethesetools">A
 * motivation: Why would I use these tools?</a>
 * <li><a href="#Theoryformagnetomechanicalmaterials">Theory for
 * magneto-mechanical materials</a><a
 * href="#Theoryformagnetomechanicalmaterials">Theory for magneto-mechanical
 * materials</a>
 * <ul>
 * <li><a href="#Thermodynamicprinciples">Thermodynamic principles</a><a
 * href="#Thermodynamicprinciples">Thermodynamic principles</a>
 * <li><a href="#Constitutivelaws">Constitutive laws</a><a
 * href="#Constitutivelaws">Constitutive laws</a>
 * <ul>
 * <li><a href="#Magnetoelasticconstitutivelaw">Magnetoelastic constitutive
 * law</a><a href="#Magnetoelasticconstitutivelaw">Magnetoelastic constitutive
 * law</a>
 * <li><a href="#Magnetoviscoelasticconstitutivelaw">Magneto-viscoelastic
 * constitutive law</a><a
 * href="#Magnetoviscoelasticconstitutivelaw">Magneto-viscoelastic
 * constitutive law</a>
 * </ul>
 * </ul>
 * <li><a href="#Rheologicalexperiment">Rheological experiment</a><a
 * href="#Rheologicalexperiment">Rheological experiment</a>
 * <li><a href="#Suggestedliterature">Suggested literature</a><a
 * href="#Suggestedliterature">Suggested literature</a>
 * </ul>
 * <li> <a href="#CommProg" class=bold>The commented program</a><a
 * href="#CommProg" class=bold>The commented program</a>
 * <ul>
 * <li><a
 * href="#AnintroductoryexampleThefundamentalsofautomaticandsymbolicdifferentiation">An
 * introductory example: The fundamentals of automatic and symbolic
 * differentiation</a><a
 * href="#AnintroductoryexampleThefundamentalsofautomaticandsymbolicdifferentiation">An
 * introductory example: The fundamentals of automatic and symbolic
 * differentiation</a>
 * <ul>
 * <li><a href="#Ananalyticalfunction">An analytical function</a><a
 * href="#Ananalyticalfunction">An analytical function</a>
 * <li><a href="#Computingderivativesusingautomaticdifferentiation">Computing
 * derivatives using automatic differentiation</a><a
 * href="#Computingderivativesusingautomaticdifferentiation">Computing
 * derivatives using automatic differentiation</a>
 * <li><a
 * href="#Handcalculatedderivativesoftheanalyticalsolution">Hand-calculated
 * derivatives of the analytical solution</a><a
 * href="#Handcalculatedderivativesoftheanalyticalsolution">Hand-calculated
 * derivatives of the analytical solution</a>
 * <li><a href="#Computingderivativesusingsymbolicdifferentiation">Computing
 * derivatives using symbolic differentiation</a><a
 * href="#Computingderivativesusingsymbolicdifferentiation">Computing
 * derivatives using symbolic differentiation</a>
 * <li><a href="#TheSimpleExamplerunfunction">The SimpleExample::run()
 * function</a><a href="#TheSimpleExamplerunfunction">The SimpleExample::run()
 * function</a>
 * </ul>
 * <li><a
 * href="#AmorecomplexexampleUsingautomaticandsymbolicdifferentiationtocomputederivativesatcontinuumpoints">A
 * more complex example: Using automatic and symbolic differentiation to
 * compute derivatives at continuum points</a><a
 * href="#AmorecomplexexampleUsingautomaticandsymbolicdifferentiationtocomputederivativesatcontinuumpoints">A
 * more complex example: Using automatic and symbolic differentiation to
 * compute derivatives at continuum points</a>
 * <ul>
 * <li><a href="#Constitutiveparameters">Constitutive parameters</a><a
 * href="#Constitutiveparameters">Constitutive parameters</a>
 * <li><a href="#ConstitutivelawsBaseclass">Constitutive laws: Base
 * class</a><a href="#ConstitutivelawsBaseclass">Constitutive laws: Base
 * class</a>
 * <li><a
 * href="#Magnetoelasticconstitutivelawusingautomaticdifferentiation">Magnetoelastic
 * constitutive law (using automatic differentiation)</a><a
 * href="#Magnetoelasticconstitutivelawusingautomaticdifferentiation">Magnetoelastic
 * constitutive law (using automatic differentiation)</a>
 * <li><a
 * href="#Magnetoviscoelasticconstitutivelawusingsymbolicalgebraanddifferentiation">Magneto-viscoelastic
 * constitutive law (using symbolic algebra and differentiation)</a><a
 * href="#Magnetoviscoelasticconstitutivelawusingsymbolicalgebraanddifferentiation">Magneto-viscoelastic
 * constitutive law (using symbolic algebra and differentiation)</a>
 * </ul>
 * <li><a
 * href="#AmorecomplexexamplecontinuedParametersandhandderivedmaterialclasses">A
 * more complex example (continued): Parameters and hand-derived material
 * classes</a><a
 * href="#AmorecomplexexamplecontinuedParametersandhandderivedmaterialclasses">A
 * more complex example (continued): Parameters and hand-derived material
 * classes</a>
 * <ul>
 * <li><a href="#Magnetoelasticconstitutivelawhandderived">Magnetoelastic
 * constitutive law (hand-derived)</a><a
 * href="#Magnetoelasticconstitutivelawhandderived">Magnetoelastic
 * constitutive law (hand-derived)</a>
 * <li><a
 * href="#Magnetoviscoelasticconstitutivelawhandderived">Magneto-viscoelastic
 * constitutive law (hand-derived)</a><a
 * href="#Magnetoviscoelasticconstitutivelawhandderived">Magneto-viscoelastic
 * constitutive law (hand-derived)</a>
 * <li><a href="#Rheologicalexperimentparameters">Rheological experiment
 * parameters</a><a href="#Rheologicalexperimentparameters">Rheological
 * experiment parameters</a>
 * <li><a
 * href="#RheologicalexperimentParallelplaterotationalrheometer">Rheological
 * experiment: Parallel plate rotational rheometer</a><a
 * href="#RheologicalexperimentParallelplaterotationalrheometer">Rheological
 * experiment: Parallel plate rotational rheometer</a>
 * <li><a href="#TheCoupledConstitutiveLawsrunfunction">The
 * CoupledConstitutiveLaws::run() function</a><a
 * href="#TheCoupledConstitutiveLawsrunfunction">The
 * CoupledConstitutiveLaws::run() function</a>
 * </ul>
 * <li><a href="#Themainfunction">The main() function</a><a
 * href="#Themainfunction">The main() function</a>
 * </ul>
 * </ol></td><td width="50%" valign="top"><ol>
 * <li value="3"> <a href="#Results" class=bold>Results</a><a href="#Results"
 * class=bold>Results</a>
 * <ul>
 * <li><a href="#Introductoryexample">Introductory example</a><a
 * href="#Introductoryexample">Introductory example</a>
 * <li><a href="#Constitutivemodelling">Constitutive modelling</a><a
 * href="#Constitutivemodelling">Constitutive modelling</a>
 * </ul>
 * <li> <a href="#PlainProg" class=bold>The plain program</a><a
 * href="#PlainProg" class=bold>The plain program</a>
 * </ol> </td> </tr> </table>
 * @endhtmlonly
 * <br>
 * <i>This program was contributed by Jean-Paul Pelteret. </i>   <a
 * name="Introduction"></a><h1>Introduction</h1>
 * 本教程的目的很简单，就是介绍[自动](https://en.wikipedia.org/wiki/Automatic_differentiation)和[符号微分](https://en.wikipedia.org/wiki/Computer_algebra)（分别缩写为AD和SD）的基本原理。人们可以在源代码中描述一个函数
 * $\mathbf f(\mathbf x)$ ，并自动获得导数 $\nabla \mathbf f(\mathbf
 * x)$ （"Jacobian"）、 $\nabla^2 \mathbf f(\mathbf x)$
 * （"Hessian"）等的表示方法，而无需编写额外的代码行。这样做对解决非线性或优化问题很有帮助，因为人们只想在代码中描述非线性方程或目标函数，而不必同时提供它们的导数（对于解决非线性问题的牛顿方法或寻找最小化器来说，这是必要的）。
 * 由于AD和SD工具在某种程度上独立于有限元和边界值问题，本教程将与你之前可能读过的其他教程不同。它将特别关注这些框架是如何工作的，以及它们背后的原理和思想，并将放弃在有限元模拟的直接背景下看待它们。
 * 事实上，我们将研究两组不同的问题，它们的复杂程度大相径庭，但如果框架适当，就有足够的相似性，同样的AD和SD框架可以被利用。通过这些例子，我们的目的是建立起对使用AD和SD工具所需步骤的理解，以及它们之间的区别，并希望能找出它们可以立即用于改进或简化现有代码的地方。
 * 你可能想知道AD和SD是什么，首先。好吧，这个问题很容易回答，但如果没有上下文，就没有很好的洞察力。我们不打算在这个介绍中涉及这个问题，而是将这个问题推迟到第一个介绍性的例子中，在这个例子中我们将列出关键点。作为补充，我们应该提到，这两个框架的核心理论在 @ref
 * auto_symb_diff
 * 模块中得到了广泛的讨论，所以在此无需重复。
 * 由于我们必须选择一些*足够有趣的主题来研究和确定AD和SD可以有效使用的地方，在本教程的后半部分所涉及的主要问题是对一个耦合构成法的建模，特别是磁活性材料（具有滞后效应）。作为介绍的一种手段，在介绍的后面将介绍该类材料的一些基础理论。自然，这不是一个广泛受众感兴趣的领域（甚至不是一类材料）。因此，作者希望预先说明，这个理论和任何后续的推导都不能被认为是本教程的重点。相反，请记住从相对无害的构成法则描述中产生的问题的复杂性，以及我们可能(在边界值问题的背景下)需要从中推导出什么。我们将用这些构成法则在代表连续体点的水平上进行一些计算(所以，仍然在连续体力学领域)，并将产生一些基准结果，我们可以围绕这些结果对计算性能的主题进行最后讨论。
 * 一旦我们有了可以建立进一步概念的基础，我们将看到如何在有限元(而不是连续体)水平上特别利用AD：这是一个在
 * step-72 以及 step-33
 * 中涉及的主题。但在此之前，让我们花点时间想想为什么我们可能要考虑使用这些工具，以及它们可能给你带来什么好处。
 *
 *  <a name="AmotivationWhywouldIusethesetools"></a><h3>A motivation: Why
 * would I use these tools?</h3>
 * 使用AD或SD的主要驱动力通常是，有一些情况需要进行区分，而且这样做有足够的挑战性，使使用外部工具来执行该特定任务的前景具有吸引力。对AD或SD最有用的情况进行了广泛的分类，包括（但可能不限于）以下几种情况。
 *
 * - <b>Rapid prototyping:</b> 对于一类新的问题，你正试图快速实现一个解决方案，并希望去除一些复杂的细节（在数学和代码本身的组织结构方面）。你可能愿意证明任何额外的计算成本是合理的，这将被重组你的代码或修改问题中引入一些复杂的非线性的部分的敏捷性所抵消，只需最小的努力。
 *
 * - <b>Complex problems:</b>很可能有些问题恰好有一个非线性，对线性化或手工制定有极大的挑战。  如果有一个工具为你解决这个挑战，那么在大多数情况下，它是强大的、可靠的和准确的，可能会减轻实现某些问题的痛苦。这方面的例子包括 step-15 ，我们解决的非线性PDE的导数并不难推导，但足够繁琐，人们必须注意用手来做，而且实现牛顿步骤的相应有限元公式需要的不仅仅是实现双线性形式一般需要的几行； step-33 （我们实际上使用AD）是一个更极端的例子。
 *
 * - <b>Verification:</b>对于表现出非线性响应的材料和模拟，准确的而不是只有近似的材料切线（机械工程师对材料定律的导数使用的术语）可能是收敛和发散行为之间的区别，特别是在高外部（或耦合）载荷下。  随着问题复杂性的增加，引入细微的（或者，也许不是那么细微的）错误的机会也在增加，这些错误会产生可预见的负面结果。  此外，通过验证实现是完全正确的，也有很多好处。例如，某些类别的问题已知会表现出不稳定性，因此，当你在非线性求解器（例如牛顿方法）中开始失去二次收敛时，那么这对研究者来说可能不是一个巨大的惊喜。然而，很难（如果不是不可能）区分以下两种收敛行为：一种是你接近不稳定的解时产生的收敛行为，另一种是你在材料或有限元线性化中出现了错误，并因此开始偏离最佳收敛路径。例如，拥有一种验证构成法线性化实现的正确性的方法，也许是你用来捕捉这种错误的唯一有意义的方法，假设你没有其他人来检查你的代码。  值得庆幸的是，通过一些战术性的编程，可以很直接地将代码结构化，以便重复使用，这样你就可以在生产代码中使用相同的类，并直接在例如单元测试框架中验证它们。
 * 这个教程程序将有两个部分。一部分，我们只是用一组简单的例子来介绍deal.II中自动和符号微分支持的基本思想；另一部分，我们将其应用于一个现实的但更复杂的案例。对于后半部分，下一节将提供一些关于磁性机械材料的背景资料。
 *
 * 如果你只想了解什么是AD和SD，你可以跳过这一节，但如果你对如何将AD和SD应用于具体的情况感兴趣，你可能想读完这一节。
 *
 *  <a name="Theoryformagnetomechanicalmaterials"></a><h3>Theory for
 * magneto-mechanical materials</h3> 。   <a
 * name="Thermodynamicprinciples"></a><h4>Thermodynamic principles</h4>
 * 在介绍我们将用来建立磁活性聚合物模型的磁机械耦合材料法之前，我们将首先对这些构成法则必须遵守的突出的热力学进行非常简明的总结。这里总结的理论基础由Truesdell和Toupin
 * @cite Truesdell1960a 以及Coleman和Noll @cite Coleman1963a
 * 详细描述，并遵循Holzapfel @cite Holzapfel2007a 提出的逻辑。
 * 从热力学第一定律开始，并遵循一些技术假设，可以证明动能加内能率与外部资源提供给系统的功率之间的平衡由以下关系给出，该关系等同于左侧（任意）体积 $V$ 中的能量变化率和右侧作用在该体积上的力之和：@f[
 * D_{t} \int\limits_{V} \left[
 *  \frac{1}{2} \rho_{0} \mathbf{v} \cdot \mathbf{v}
 *  + U^{*}_{0} \right] dV
 * = \int\limits_{V} \left[
 * \rho_{0} \mathbf{v} \cdot \mathbf{a}
 * + \mathbf{P}^{\text{tot}} : \dot{\mathbf{F}}
 * + \boldsymbol{\mathbb{H}} \cdot \dot{\boldsymbol{\mathbb{B}}}
 * + \mathbb{E} \cdot \dot{\mathbb{D}}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - D_{t} M^{*}_{0}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \nabla_{0} \cdot \mathbf{Q}
 * + R_{0} \right] dV .
 * @f]这里 $D_{t}$ 代表总时间导数， $\rho_{0}$ 是在拉格朗日参考框架下测量的材料密度， $\mathbf{v}$ 是材料速度， $\mathbf{a}$ 是其加速度， $U^{*}_{0}$ 是每单位参考体积的内能， $\mathbf{P}^{\text{tot}}$ 是总皮奥拉应力张量， $\dot{\mathbf{F}}$  是变形梯度张量的时间速率， $\boldsymbol{\mathbb{H}}$  和  $\boldsymbol{\mathbb{B}}$ 分别是磁场矢量和磁感应强度（或磁通密度）矢量， $\mathbb{E}$ 和 $\mathbb{D}$ 是电场矢量和电位移矢量，以及 $\mathbf{Q}$ 和 $R_{0}$ 材料微分算子 $\nabla_{0} (\bullet) \dealcoloneq \frac{d(\bullet)}{d\mathbf{X}}$ ，其中 $\mathbf{X}$ 是材料位置矢量。随着一些条款的重新排列，引用积分体积的任意性 $V$ ，总的内能密度率 $\dot{E}_{0}$ 可以确定为@f[
 * \dot{E}_{0} = \mathbf{P}^{\text{tot}} : \dot{\mathbf{F}} +
 * \boldsymbol{\mathbb{H}} \cdot \dot{\boldsymbol{\mathbb{B}}} + \mathbb{E}
 * \cdot \dot{\mathbb{D}}
 *
 *
 *
 *
 *
 * - \nabla_{0} \cdot \mathbf{Q} + R_{0} .
 * @f]。总的内能不仅包括由于机械变形（第一项）、热通量和热源（第四项和第五项）而产生的贡献，还包括由于储存在磁场和电场本身的内在能量（分别为第二项和第三项）。
 * 热力学第二定律，也被称为熵不平等原则，告诉我们某些热力学过程是不可逆的。在考虑了总熵和熵的输入率之后，可以得出克劳修斯-杜姆不等式。在局部形式下（以及在物质配置中），这读作@f[
 * \theta \dot{\eta}_{0}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - R_{0}
 * + \nabla_{0} \cdot \mathbf{Q}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \frac{1}{\theta} \nabla_{0} \theta \cdot \mathbf{Q}
 * \geq 0 .
 * @f]量 $\theta$ 是绝对温度， $\eta_{0}$ 代表每单位参考体积的熵值。
 * 用它来代替热力学第一定律结果中的 $R_{0}
 *
 * - \nabla_{0} \cdot \mathbf{Q}$ ，我们现在有了这样的关系@f[
 * \mathbf{P}^{\text{tot}} : \dot{\mathbf{F}}
 * + \boldsymbol{\mathbb{H}} \cdot \dot{\boldsymbol{\mathbb{B}}}
 * + \mathbb{E} \cdot \dot{\mathbb{D}}
 * + \theta \dot{\eta}_{0}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \dot{E}_{0}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \frac{1}{\theta} \nabla_{0} \theta \cdot \mathbf{Q}
 * \geq 0 .
 * @f]，根据傅里叶定律，它告诉我们热量从高温区域流向低温，最后一项总是正的，可以忽略。在等温条件的假设下，电场不会以被认为是不可忽略的方式激发材料，那么这个耗散不等式就会减少为@f[
 * \mathcal{D}_{\text{int}} = \mathbf{P}^{\text{tot}} : \dot{\mathbf{F}} +
 * \boldsymbol{\mathbb{H}} \cdot \dot{\boldsymbol{\mathbb{B}}}
 *
 *
 *
 *
 *
 * - \dot{\psi}^{*}_{0} \left( \mathbf{F}, \boldsymbol{\mathbb{B}} \right)
 * \geq 0 . @f] 。 <a name="Constitutivelaws"></a><h4>Constitutive laws</h4>
 * 。
 *
 * *当考虑到表现出机械耗散行为的材料时，可以证明这可以通过用代表内部变量的额外参数来增加材料自由能密度函数来捕获耗散不等式 @cite Holzapfel1996a  。因此，我们把它写成@f[
 * \mathcal{D}_{\text{int}}
 * = \mathbf{P}^{\text{tot}} : \dot{\mathbf{F}}
 * + \boldsymbol{\mathbb{H}} \cdot \dot{\boldsymbol{\mathbb{B}}}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \dot{\psi}^{*}_{0} \left( \mathbf{F}, \mathbf{F}_{v}^{i}, \boldsymbol{\mathbb{B}} \right)
 * \geq 0 .
 * @f]，其中 $\mathbf{F}_{v}^{i} = \mathbf{F}_{v}^{i} \left( t \right)$ 代表与第i个机械耗散（粘性）机制相关的内部变量（其作用类似于变形梯度的测量）。这是自然的参数化，是所考虑的平衡定律的结果。如果这样一类材料被纳入到有限元模型中，就会发现需要采用某种磁问题的表述，即磁矢量势表述。这有它自己的一套挑战，所以在可能的情况下，更简单的磁标量势公式可能被优先考虑。在这种情况下，磁性问题需要以磁场为参数  $\boldsymbol{\mathbb{H}}$  。为了进行这种重新参数化，我们执行最后的Legendre变换@f[
 * \tilde{\psi}_{0} \left( \mathbf{F}, \mathbf{F}_{v}^{i},
 * \boldsymbol{\mathbb{H}} \right) = \psi^{*}_{0} \left( \mathbf{F},
 * \mathbf{F}_{v}^{i}, \boldsymbol{\mathbb{B}} \right)
 *
 *
 *
 *
 *
 * - \boldsymbol{\mathbb{H}} \cdot \boldsymbol{\mathbb{B}} .
 * @f]。同时，我们可以利用材料框架差异的原则，以便用对称变形量来表达能量密度函数：@f[
 * \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}}
 * \right) = \tilde{\psi}_{0} \left( \mathbf{F}, \mathbf{F}_{v}^{i},
 * \boldsymbol{\mathbb{H}} \right) .
 * @f]这两种变换的结果（撇开相当多的明确和隐藏的细节）使还原耗散质量的最终表达式为@f[
 * \mathcal{D}_{\text{int}} = \mathbf{S}^{\text{tot}} : \frac{1}{2}
 * \dot{\mathbf{C}}
 *
 *
 *
 *
 *
 * - \boldsymbol{\mathbb{B}} \cdot \dot{\boldsymbol{\mathbb{H}}}
 *
 *
 *
 *
 *
 * - \dot{\psi}_{0} \left( \mathbf{C}, \mathbf{C}_{v}^{i},
 * \boldsymbol{\mathbb{H}} \right) \geq 0 . @f]应力量
 * $\mathbf{S}^{\text{tot}}$
 * 被称为Piola-Kirchhoff总应力张量，其能量共轭物 $\mathbf{C} =
 * \mathbf{F}^{T} \cdot \mathbf{F}$ 是右Cauchy-Green变形张量，
 * $\mathbf{C}_{v}^{i} = \mathbf{C}_{v}^{i} \left( t \right)$
 * 是与第i种机械耗散（粘性）机制相关的重新参数化的内部变量。
 * 对能量密度函数的材料速率进行扩展，并对各种条款进行重新排列，结果是表达式@f[
 * \mathcal{D}_{\text{int}}
 * = \left[ \mathbf{S}^{\text{tot}}
 *
 * - 2 \frac{\partial \psi_{0}}{\partial \mathbf{C}} \right] : \frac{1}{2} \dot{\mathbf{C}}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \sum\limits_{i}\left[ 2 \frac{\partial \psi_{0}}{\partial \mathbf{C}_{v}^{i}} \right] : \frac{1}{2} \dot{\mathbf{C}}_{v}^{i}
 * + \left[
 *
 * - \boldsymbol{\mathbb{B}}
 *
 * - \frac{\partial \psi_{0}}{\partial \boldsymbol{\mathbb{H}}} \right] \cdot \dot{\boldsymbol{\mathbb{H}}}
 * \geq 0 .
 * @f]在这一点上，值得注意的是[偏导数](https://en.wikipedia.org/wiki/Partial_derivative)  $\partial \left( \bullet \right)$ 的使用。这是一个重要的细节，对教程中的某个设计选择至关重要。简单提醒一下这意味着什么，多变量函数的偏导返回该函数相对于其中一个变量的导数，同时保持其他变量不变：@f[
 * \frac{\partial f\left(x, y\right)}{\partial x} = \frac{d f\left(x,
 * y\right)}{d x} \Big\vert_{y} .
 * @f]更具体到耗散不等式中的编码（用非常通用的自由能量密度函数
 * $\psi_{0}$
 * ，其参数化有待正式确定），如果一个输入变量是另一个变量的函数，它也被保持不变，连锁规则不会进一步传播，而计算总衍生物将意味着明智地使用连锁规则。通过比较以下两个语句可以更好地理解这一点。
 * @f{align*}
 * \frac{\partial f\left(x, y\left(x\right)\right)}{\partial x}
 * &= \frac{d f\left(x, y\left(x\right)\right)}{d x} \Big\vert_{y} \\
 * \frac{d f\left(x, y\left(x\right)\right)}{d x}
 * &= \frac{d f\left(x, y\left(x\right)\right)}{d x} \Big\vert_{y}
 * + \frac{d f\left(x, y\left(x\right)\right)}{d y} \Big\vert_{x} \frac{d y\left(x\right)}{x} .
 * @f}
 *
 * 回到问题的热力学，我们接下来利用数量 $\dot{\mathbf{C}}$ 和 $\dot{\boldsymbol{\mathbb{H}}}$ 的任意性，通过应用科尔曼-诺尔程序 @cite Coleman1963a ,  @cite Coleman1967a .这导致了动力学共轭数量的识别@f[
 * \mathbf{S}^{\text{tot}}
 * = \mathbf{S}^{\text{tot}} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)
 * \dealcoloneq 2 \frac{\partial \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)}{\partial \mathbf{C}} , \\
 * \boldsymbol{\mathbb{B}}
 * = \boldsymbol{\mathbb{B}} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)
 * \dealcoloneq
 *
 * - \frac{\partial \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)}{\partial \boldsymbol{\mathbb{H}}} .
 * @f]从耗散功率中剩下的项（即与机械耗散机制有关的项）来看，如果假定它们是相互独立的，那么，对于每个机制`i`，@f[
 * \frac{\partial \psi_{0}}{\partial \mathbf{C}_{v}^{i}} :
 * \dot{\mathbf{C}}_{v}^{i} \leq 0 .
 * @f]这一约束必须通过自由能函数的适当选择以及仔细考虑的内部变量的演化规律来满足。
 * 如果在结构模型中没有耗散机制（例如，如果要建模的材料是磁超弹性的），那么自由能密度函数
 * $\psi_{0} = \psi_{0} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)$
 * 就会减少为储存能量密度函数，总应力和磁感应可以简化。
 * @f{align*}{
 * \mathbf{S}^{\text{tot}}
 * = \mathbf{S}^{\text{tot}} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * &\dealcoloneq 2 \frac{d \psi_{0} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)}{d \mathbf{C}} , \\
 * \boldsymbol{\mathbb{B}}
 * = \boldsymbol{\mathbb{B}} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * &\dealcoloneq
 *
 * - \frac{d \psi_{0} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)}{d \boldsymbol{\mathbb{H}}} ,
 * @f}
 * 其中算子 $d$ 表示总导数操作。
 * 为了完整起见，应力张量和磁感应的线性化在四阶总参考弹性张量
 * $\mathcal{H}^{\text{tot}} $ 、二阶磁静力张量 $\mathbb{D}$
 * 和三阶总参考磁弹性耦合张量 $\mathfrak{P}^{\text{tot}}$
 * 中得到体现。无论 $\mathbf{S}^{\text{tot}}$ 和
 * $\boldsymbol{\mathbb{B}}$
 * 的参数化如何，这些量可以通过以下方式计算
 * @f{align*}{
 * \mathcal{H}^{\text{tot}}
 * &= 2 \frac{d \mathbf{S}^{\text{tot}}}{d \mathbf{C}} , \\
 * \mathbb{D}
 * &= \frac{d \boldsymbol{\mathbb{B}}}{d \boldsymbol{\mathbb{H}}} , \\
 * \mathfrak{P}^{\text{tot}}
 * &=
 *
 * - \frac{d \mathbf{S}^{\text{tot}}}{d \boldsymbol{\mathbb{H}}} , \\
 * \left[ \mathfrak{P}^{\text{tot}} \right]^{T}
 * &= 2 \frac{d \boldsymbol{\mathbb{B}}}{d \mathbf{C}} .
 * @f}
 * 对于速率依赖型材料的情况，这扩展为
 * @f{align*}{
 * \mathcal{H}^{\text{tot}} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)
 * &= 4 \frac{d^{2} \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)}{\partial \mathbf{C} \otimes d \mathbf{C}} , \\
 * \mathbb{D} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)
 * &=
 *
 * -\frac{d^{2} \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)}{\partial \boldsymbol{\mathbb{H}} \otimes d \boldsymbol{\mathbb{H}}} , \\
 * \mathfrak{P}^{\text{tot}} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)
 * &=
 *
 * - 2 \frac{d^{2} \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)}{\partial \boldsymbol{\mathbb{H}} \otimes d \mathbf{C}} , \\
 * \left[ \mathfrak{P}^{\text{tot}} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)  \right]^{T}
 * &=
 *
 * - 2 \frac{d^{2} \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v}^{i}, \boldsymbol{\mathbb{H}} \right)}{\partial \mathbf{C} \otimes d \boldsymbol{\mathbb{H}}} ,
 * @f}
 * 而对于与速率无关的材料，线性化为
 * @f{align*}{
 * \mathcal{H}^{\text{tot}} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * &= 4 \frac{d^{2} \psi_{0} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)}{d \mathbf{C} \otimes d \mathbf{C}} , \\
 * \mathbb{D} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * &=
 *
 * -\frac{d^{2} \psi_{0} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)}{d \boldsymbol{\mathbb{H}} \otimes d \boldsymbol{\mathbb{H}}} , \\
 * \mathfrak{P}^{\text{tot}} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * &=
 *
 * - 2 \frac{d^{2} \psi_{0} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)}{d \boldsymbol{\mathbb{H}} \otimes d \mathbf{C}} , \\
 * \left[ \mathfrak{P}^{\text{tot}} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)  \right]^{T}
 * &=
 *
 * - 2 \frac{d^{2} \psi_{0} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)}{d \mathbf{C} \otimes d \boldsymbol{\mathbb{H}}} .
 * @f}
 * 它们之间的细微差别是在计算第一个导数时应用了一个偏导。我们将在后面看到这如何影响这个具体应用中AD与SD的选择。现在，我们将简单地介绍一下本教程中实施的两种具体材料。
 * <a name="Magnetoelasticconstitutivelaw"></a><h5>Magnetoelastic constitutive
 * law</h5>
 *
 * 我们要考虑的第一种材料是受磁-超弹性构成规律支配的材料。这种材料对变形和浸入磁场都有反应，但表现出与时间或历史有关的行为（如通过粘性阻尼或磁滞的耗散，等等）。这种材料的存储能量密度函数*只在（当前）场变量方面进行参数化，而不是它们的时间导数或过去的值。
 * 我们将选择能量密度函数，它既能捕捉到由于变形和磁化而储存在材料中的能量，也能捕捉到储存在磁场本身中的能量，它是@f[
 * \psi_{0} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * = \frac{1}{2} \mu_{e} f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right)
 *  \left[ \text{tr}(\mathbf{C})
 *
 * - d
 *
 * - 2 \ln (\text{det}(\mathbf{F}))
 *  \right]
 * + \lambda_{e} \ln^{2} \left(\text{det}(\mathbf{F}) \right)
 *
 * - \frac{1}{2} \mu_{0} \mu_{r} \text{det}(\mathbf{F})
 *  \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 *  \boldsymbol{\mathbb{H}} \right]
 * @f]与@f[
 * f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right) = 1 + \left[
 * \frac{\mu_{e}^{\infty}}{\mu_{e}}
 *
 * - 1 \right] \tanh \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}} {\left(h_{e}^{\text{sat}}\right)^{2}} \right)
 * @f]，对其而言，变量 $d = \text{tr}(\mathbf{I})$ （ $\mathbf{I}$
 * 是等级2的身份张量）代表空间维度， $\mathbf{F}$
 * 是形变梯度张量。为了给 $\psi_{0}$
 * 的各个组成部分提供一些简要的背景，前两个条款与（超弹性）Neohookean材料的存储能量密度函数非常相似。这里使用的东西和Neohookean材料之间的唯一区别是弹性剪切模量被磁场敏感的饱和函数
 * $f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right)$ 缩放（见 @cite
 * Pelteret2018a
 * ，公式29）。这个函数实际上会使材料在强磁场的存在下变硬。由于它是由一个sigmoid类型的函数控制的，剪切模量将渐进地收敛于指定的饱和剪切模量。还可以证明，
 * $\psi_{0}$
 * 中的最后一项是磁场的储能密度函数（从第一原理推导出来的），由相对渗透率常数缩放。这个定义共同意味着材料是线性磁化的，也就是说，磁化矢量和磁场矢量是一致的。(这在以电流形式表示的磁能中当然不明显，但当磁感应和磁化从
 * $\psi_{0}$ 中导出，并且所有磁场都以 <em> 的电流构型 </em>
 * 表示时，这种相关性就变得很清楚了。)至于磁感应、应力张量和各种材料切线的具体细节，我们将把这些推迟到教程正文中介绍，其中定义了构成法的完整、无辅助的实施。
 * <a name="Magnetoviscoelasticconstitutivelaw"></a><h5>Magneto-viscoelastic
 * constitutive law</h5>
 *
 * 我们将制定的第二个材料是一个具有单一耗散机制`i`的磁-粘弹性材料。
 * @f{align*}{
 * \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v}, \boldsymbol{\mathbb{H}}
 * \right)
 * &= \psi_{0}^{ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * + \psi_{0}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)
 * \\ \psi_{0}^{ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * &= \frac{1}{2} \mu_{e} f_{\mu_{e}^{ME}} \left( \boldsymbol{\mathbb{H}}
 * \right)
 *  \left[ \text{tr}(\mathbf{C})
 *
 * - d
 *
 * - 2 \ln (\text{det}(\mathbf{F}))
 *  \right]
 * + \lambda_{e} \ln^{2} \left(\text{det}(\mathbf{F}) \right)
 *
 * - \frac{1}{2} \mu_{0} \mu_{r} \text{det}(\mathbf{F})
 *  \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 *  \boldsymbol{\mathbb{H}} \right]
 * \\ \psi_{0}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)
 * &= \frac{1}{2} \mu_{v} f_{\mu_{v}^{MVE}} \left( \boldsymbol{\mathbb{H}}
 * \right)
 *  \left[ \mathbf{C}_{v} : \left[
 *    \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 *    \mathbf{C} \right]
 *
 * - d
 *
 * - \ln\left(
 *    \text{det}\left(\mathbf{C}_{v}\right) \right)  \right]
 * @f}
 * 我们将考虑的自由能量密度函数*定义为*@f{align*}{
 * \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v}, \boldsymbol{\mathbb{H}}
 * \right)
 * &= \psi_{0}^{ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * + \psi_{0}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)
 * \\ \psi_{0}^{ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * &= \frac{1}{2} \mu_{e} f_{\mu_{e}^{ME}} \left( \boldsymbol{\mathbb{H}}
 * \right)
 *  \left[ \text{tr}(\mathbf{C})
 *
 * - d
 *
 * - 2 \ln (\text{det}(\mathbf{F}))
 *  \right]
 * + \lambda_{e} \ln^{2} \left(\text{det}(\mathbf{F}) \right)
 *
 * - \frac{1}{2} \mu_{0} \mu_{r} \text{det}(\mathbf{F})
 *  \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 *  \boldsymbol{\mathbb{H}} \right]
 * \\ \psi_{0}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)
 * &= \frac{1}{2} \mu_{v} f_{\mu_{v}^{MVE}} \left( \boldsymbol{\mathbb{H}}
 * \right)
 *  \left[ \mathbf{C}_{v} : \left[
 *    \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 *    \mathbf{C} \right]
 *
 * - d
 *
 * - \ln\left(
 *    \text{det}\left(\mathbf{C}_{v}\right) \right)  \right]
 * @f}，其中@f[
 * f_{\mu_{e}}^{ME} \left( \boldsymbol{\mathbb{H}} \right) = 1 + \left[
 * \frac{\mu_{e}^{\infty}}{\mu_{e}}
 *
 * - 1 \right] \tanh \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}} {\left(h_{e}^{\text{sat}}\right)^{2}} \right)
 * @f]@f[
 * f_{\mu_{v}}^{MVE} \left( \boldsymbol{\mathbb{H}} \right) = 1 + \left[
 * \frac{\mu_{v}^{\infty}}{\mu_{v}}
 *
 * - 1 \right] \tanh \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}} {\left(h_{v}^{\text{sat}}\right)^{2}} \right)
 * @f]和内部粘性变量的演化规律@f[
 * \dot{\mathbf{C}}_{v} \left( \mathbf{C} \right) = \frac{1}{\tau} \left[
 * \left[\left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C}\right]^{-1}
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * - \mathbf{C}_{v} \right]
 * @f]。我们已经选择了能量的磁弹性部分 $\psi_{0}^{ME} \left(
 * \mathbf{C}, \boldsymbol{\mathbb{H}} \right)$
 * 来匹配我们探索的第一个材料模型，所以这部分不需要进一步解释。至于粘性部分
 * $\psi_{0}^{MVE}$
 * ，自由能的这一部分（与粘性变形张量的演化规律一起）取自
 * @cite Linder2011a （通过 @cite Pelteret2018a
 * 中描述的粘性饱和函数进行额外的缩放）。它是在一个热力学上一致的框架中得出的，其核心是对聚合物链在微观尺度上的运动进行建模。
 * 选择隐式一阶逆向差分方案，那么@f[
 * \dot{\mathbf{C}}_{v}
 * \approx \frac{\mathbf{C}_{v}^{(t)}
 *
 * - \mathbf{C}_{v}^{(t-1)}}{\Delta t}
 * = \frac{1}{\tau} \left[
 *    \left[\left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 *      \mathbf{C}\right]^{-1}
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
 * - \mathbf{C}_{v}^{(t)} \right]
 * @f]中的上标 $(t)$ 表示该量是在当前的时间步长上取的， $(t-1)$ 表示在前一时间步长上取的量（即历史变量）。将条款重新排列，使当前时间的所有内部变量量都在方程的左侧，我们得到@f[
 * \mathbf{C}_{v}^{(t)} = \frac{1}{1 + \frac{\Delta t}{\tau_{v}}} \left[
 * \mathbf{C}_{v}^{(t-1)} + \frac{\Delta t}{\tau_{v}}
 * \left[\left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C} \right]^{-1} \right] @f]，与 @cite Linder2011a
 * 方程54相匹配。 <a name="Rheologicalexperiment"></a><h3>Rheological
 * experiment</h3> 。
 *
 * 我们希望对我们制定的材料定律做一些有意义的事情*，因此将它们置于一些机械和磁载荷条件下是有意义的，这些条件在某种程度上代表了在应用或实验室环境中可能发现的一些条件。实现这一目标的方法之一是将这些构成法则嵌入到模拟设备的有限元模型中。但在这个例子中，我们将保持简单（毕竟我们的重点是自动和符号微分概念），并将找到一个简明的方法来忠实地复制一个行业标准的流变学实验，使用负载条件的分析表达。
 * 我们要重现的流变学实验是一个理想化的实验室实验，它被用来描述磁活性聚合物的特性，详细内容见
 * @cite Pelteret2018a （以及 @cite Pelteret2019a
 * ，其中记录了它和真实世界的实验情况）。下面的图片提供了对问题设置的视觉描述。
 * <table align="center" class="tutorial" cellspacing="3" cellpadding="3">
 * <tr> <td align="center"> <img
 * src="https://www.dealii.org/images/steps/developer/step-71.parallel_plate-geometry.png"
 * alt="" height="300"> <p align="center"> The basic functional geometry of
 * the parallel-plate rotational rheometer. The smooth rotor (blue) applies a
 * torque to an experimental sample (red) of radius $r$ and height $H$ while
 * an axially aligned magnetic field generated by a a magneto-rheological
 * device. Although the time-dependent deformation profile of the may be
 * varied, one common experiment would be to subject the material to a
 * harmonic torsional deformation of constant amplitude and frequency
 * $\omega$. </p> </td> <td align="center"> <img
 * src="https://www.dealii.org/images/steps/developer/step-71.parallel_plate-kinematics.png"
 * alt="" height="300"> <p align="center"> Schematic of the kinematics of the
 * problem, assuming no preloading or compression of the sample. A point
 * $\mathbf{P}$ located at azimuth $\Theta$ is displaced to location
 * $\mathbf{p}$ at azimuth $\theta = \Theta + \alpha$. </p> </td> </tr>
 * </table>
 * 假设正在测试的是不可压缩的介质，并且通过样品厚度的变形曲线是线性的，那么在样品内的某个测量点
 * $\mathbf{X}$ 的位移，用径向坐标表示，就是
 * @f{align*}
 * r(\mathbf{X})
 * &= \frac{R(X_{1}, X_{2})}{\sqrt{\lambda_{3}}} , \\
 * \theta(\mathbf{X})
 * & = \Theta(X_{1}, X_{2}) + \underbrace{\tau(t)
 *     \lambda_{3} X_{3}}_{\alpha(X_{3}, t)} , \\
 * z(\mathbf{X})
 * &= \lambda_{3} X_{3}
 * @f}
 * 其中 $R(X_{1}, X_{2})$ 和 $\Theta(X_{1}, X_{2})$ 是在 $\mathbf{X}$
 * 的半径。
 *
 * -和角度为
 *
 * 采样点， $\lambda_{3}$ 是（恒定的）轴向变形， $\tau(t) =
 * \frac{A}{RH} \sin\left(\omega t\right)$
 * 是每单位长度上与时间有关的扭转角，将使用固定振幅
 * $A$ 的无声重复振荡来规定。磁场是轴向排列的，即在
 * $X_{3}$ 方向。
 * 这总结了我们需要全面描述流变样品内任何一点的理想化载荷的一切。我们将设置这样一个问题，即我们在这个样品中
 * "挑选
 * "一个有代表性的点，并使其在恒定的轴向变形（默认为压缩载荷）和恒定的轴向施加的磁场下受到谐波剪切变形的影响。我们将记录这时的应力和磁感应强度，并将数据输出到文件中进行后处理。尽管在这个特定的问题上没有必要，但我们也将计算切线。尽管在这个特定的工作中没有直接使用它们，但为了将构成法嵌入无限元模型（这项工作的一个可能的扩展），需要这些二次导数。因此，我们将利用这个机会，用辅助微分框架来检查我们的手工计算的正确性。
 * <a name="Suggestedliterature"></a><h3>Suggested literature</h3>
 *
 * 除了已经提到的 @ref
 * auto_symb_diff 模块之外，以下是一些更详细讨论的参考文献
 *
 * - 磁力学，以及自动分化框架的某些方面。   @cite Pao1978a  ,  @cite Pelteret2019a  , 和
 *
 * - 使用AD和/或SD的有限元框架的自动化：  @cite Logg2012a  ,  @cite Korelc2016a  。
 * <br>
 *
 *  <a name="CommProg"></a> <h1> The commented program</h1>。
 * 我们首先包括所有必要的deal.II头文件和一些C++相关的文件。这第一个头文件将使我们能够访问一个数据结构，使我们能够在其中存储任意的数据。
 *
 * @code
 * #include <deal.II/algorithms/general_data_storage.h>
 *
 * @endcode
 *
 * 接下来是一些核心类，包括一个提供时间步进的实现。
 *
 * @code
 * #include <deal.II/base/discrete_time.h>
 * #include <deal.II/base/numbers.h>
 * #include <deal.II/base/parameter_acceptor.h>
 * #include <deal.II/base/symmetric_tensor.h>
 * #include <deal.II/base/tensor.h>
 * #include <deal.II/base/timer.h>
 * #include <deal.II/base/utilities.h>
 *
 * @endcode
 *
 * 然后是一些标题，定义了一些有用的坐标变换和运动学关系，在非线性弹性中经常出现。
 *
 * @code
 * #include <deal.II/physics/transformations.h>
 * #include <deal.II/physics/elasticity/kinematics.h>
 * #include <deal.II/physics/elasticity/standard_tensors.h>
 *
 * @endcode
 *
 * 以下两个标头提供了我们进行自动微分所需的所有功能，并使用了deal.II可以利用的符号计算机代数系统。所有自动微分和符号微分包装类的头文件，以及任何需要的辅助数据结构，都被收集在这些统一的头文件中。
 *
 * @code
 * #include <deal.II/differentiation/ad.h>
 * #include <deal.II/differentiation/sd.h>
 *
 * @endcode
 *
 * 包括这个头文件允许我们有能力将输出写入文件流。
 *
 * @code
 * #include <fstream>
 *
 *
 * @endcode
 *
 * 按照惯例，整个教程程序被定义在它自己独特的命名空间内。
 *
 * @code
 * namespace Step71
 * {
 * using namespace dealii;
 *
 * @endcode
 *
 * <a
 * name="AnintroductoryexampleThefundamentalsofautomaticandsymbolicdifferentiation"></a>
 * <h3>An introductory example: The fundamentals of automatic and symbolic
 * differentiation</h3>。
 *
 * 自动和象征性的区分有一些神奇和神秘的特质。尽管在一个项目中使用它们可以因多种原因而受益，但了解如何使用这些框架或如何利用它们的障碍可能会超过试图将它们（可靠地）整合到工作中的开发者的耐心。
 * 尽管作者希望能成功地说明这些工具如何能被集成到有限元建模的工作流程中，但最好还是先退一步，从基础开始。因此，一开始，我们先看看如何使用这两个框架来区分一个
 * "简单
 * "的数学函数，这样就可以牢固地建立和理解基本的操作（包括它们的顺序和功能），并使其复杂程度降到最低。在本教程的第二部分，我们将把这些基本原理付诸实践，并在此基础上进一步发展。
 * 伴随着对使用框架的算法步骤的描述，将有一个简化的观点，即这些框架可能*在后台做什么。这种描述在很大程度上是为了帮助理解，我们鼓励读者查看 @ref
 * auto_symb_diff
 * 模块文档，以获得对这些工具实际工作的更正式描述。
 *
 * <a name="Ananalyticalfunction"></a> <h4>An analytical function</h4>。
 *
 * @code
 * namespace SimpleExample
 * {
 * @endcode
 *
 * 为了使读者相信这些工具在实践中确实有用，让我们选择一个函数，用手计算分析导数并不难。只是它的复杂程度足以让你考虑是否真的要去做这个练习，也可能让你怀疑你是否完全确定你对其导数的计算和实现是正确的。当然，问题的关键在于，函数的微分在某种意义上是相对公式化的，应该是计算机所擅长的。
 *
 * - 如果我们能在现有的软件上建立起理解规则的软件，我们就不必费力地自己去做了。
 * 我们为此选择了双变量三角函数 $f(x,y) =
 * \cos\left(\frac{y}{x}\right)$
 * 。请注意，这个函数是以数字类型为模板的。这样做是因为我们经常（但并不总是）可以使用特殊的自动微分和符号类型作为实值或复值类型的落地替代，然后这些类型将执行一些基本的计算，例如评估一个函数值及其导数。我们将利用这一特性，确保我们只需要定义一次我们的函数，然后就可以在我们希望对其进行微分操作的任何情况下重新使用。
 *
 * @code
 *   template <typename NumberType>
 *   NumberType f(const NumberType &x, const NumberType &y)
 *   {
 *     return std::cos(y / x);
 *   }
 *
 * @endcode
 *
 * 我们没有立即揭示这个函数的导数，而是向前声明返回它们的函数，并将它们的定义推迟到后面。正如函数名称所暗示的，它们分别返回导数
 * $\frac{df(x,y)}{dx}$  。
 *
 * @code
 *   double df_dx(const double x, const double y);
 *
 * @endcode
 *  $\frac{df(x,y)}{dy}$  :
 * @code
 *   double df_dy(const double x, const double y);
 *
 * @endcode
 *  $\frac{d^{2}f(x,y)}{dx^{2}}$  :
 * @code
 *   double d2f_dx_dx(const double x, const double y);
 *
 * @endcode
 *  $\frac{d^{2}f(x,y)}{dx dy}$  :
 * @code
 *   double d2f_dx_dy(const double x, const double y);
 *
 * @endcode
 *  $\frac{d^{2}f(x,y)}{dy dx}$  :
 * @code
 *   double d2f_dy_dx(const double x, const double y);
 *
 * @endcode
 *  最后是 $\frac{d^{2}f(x,y)}{dy^{2}}$  。
 * @code
 *   double d2f_dy_dy(const double x, const double y);
 *
 *
 * @endcode
 *
 * <a name="Computingderivativesusingautomaticdifferentiation"></a>
 * <h4>Computing derivatives using automatic differentiation</h4>。
 * 首先，我们将使用AD作为工具，为我们自动计算导数。我们将用参数`x`和`y`来评估函数，并期望得到的值和所有的导数都能在给定的公差范围内匹配。
 *
 * @code
 *   void
 *   run_and_verify_ad(const double x, const double y, const double tol = 1e-12)
 *   {
 * @endcode
 *
 * 我们的函数 $f(x,y)$
 * 是一个标量值函数，其参数代表代数计算或张量计算中遇到的典型输入变量。由于这个原因，
 * Differentiation::AD::ScalarFunction
 * 类是合适的包装类，可以用来做我们所需要的计算。(作为比较，如果函数参数代表有限元单元的自由度，我们会希望以不同的方式处理它们)。问题的空间维度是不相关的，因为我们没有矢量或张量值的参数需要容纳，所以`dim`模板参数被任意分配为1的值。
 * 第二个模板参数规定了将使用哪个AD框架（deal.II支持几个外部AD框架），以及这个框架提供的基础数字类型将被使用。这个数字类型影响了微分运算的最大顺序，以及用于计算它们的基础算法。鉴于其模板性质，这个选择是一个编译时的决定，因为许多（但不是全部）AD库利用编译时的元编程，以有效的方式实现这些特殊的数字类型。第三个模板参数说明结果类型是什么；在我们的例子中，我们正在处理
 * "双"。
 *
 * @code
 *     constexpr unsigned int                     dim = 1;
 *     constexpr Differentiation::AD::NumberTypes ADTypeCode =
 *       Differentiation::AD::NumberTypes::sacado_dfad_dfad;
 *     using ADHelper =
 *       Differentiation::AD::ScalarFunction<dim, ADTypeCode, double>;
 *
 * @endcode
 *
 * 我们有必要在我们的 @p ADHelper 类中预先登记函数 $f(x,y)$
 * 有多少个参数（我们将称之为
 * "独立变量"）。这些参数是`x`和`y`，所以显然有两个参数。
 *
 * @code
 *     constexpr unsigned int n_independent_variables = 2;
 *
 * @endcode
 *
 * 我们现在有足够的信息来创建和初始化一个辅助类的实例。我们还可以得到具体的数字类型，它将在所有后续的计算中使用。这很有用，因为我们可以从这里开始通过引用这个类型来编写一切，如果我们想改变使用的框架，或者数字类型（例如，如果我们需要更多的差分运算），那么我们只需要调整`ADTypeCode`模板参数。
 *
 * @code
 *     ADHelper ad_helper(n_independent_variables);
 *     using ADNumberType = typename ADHelper::ad_type;
 *
 * @endcode
 * 下一步是在辅助类中注册自变量的数值。这样做是因为函数和它的导数将正好针对这些参数进行评估。由于我们以`{x,y}`的顺序注册它们，变量`x`将被分配到分量号`0`，而`y`将是分量号`1`。
 *
 *
 * - 一个将在接下来几行中使用的细节。
 *
 * @code
 *     ad_helper.register_independent_variables({x, y});
 *
 * @endcode
 *
 * 我们现在要求助手类向我们提供自变量及其自动差异化的表示。这些被称为
 * "敏感变量"，因为从现在开始，我们对组件`独立变量_ad`所做的任何操作都会被AD框架跟踪和记录，并且在我们要求计算它们的导数时，会被考虑。帮助器返回的是一个可自动微分的
 * "向量"，但是我们可以确定，第2个元素代表
 * "x"，第1个元素代表
 * "y"。为了完全确保这些变量的数字类型没有任何歧义，我们给所有的自动微分变量加上`ad'的后缀。
 *
 * @code
 *     const std::vector<ADNumberType> independent_variables_ad =
 *       ad_helper.get_sensitive_variables();
 *     const ADNumberType &x_ad = independent_variables_ad[0];
 *     const ADNumberType &y_ad = independent_variables_ad[1];
 *
 * @endcode
 *
 * 我们可以立即将自变量的敏感表示法传递给我们的模板函数，计算出
 * $f(x,y)$  。这也会返回一个可自动微分的数字。
 *
 * @code
 *     const ADNumberType f_ad = f(x_ad, y_ad);
 *
 * @endcode
 *
 * 所以现在要问的自然是，我们把这些特殊的`x_ad`和`y_ad`变量传递给函数`f`，而不是原来的`double`变量`x`和`y`，实际上计算了什么？换句话说，这一切与我们想要确定的导数的计算有什么关系？或者，更简洁地说。这个返回的`ADNumberType`对象有什么特别之处，使它有能力神奇地返回导数？
 * 从本质上讲，这可以*做的是以下几点。这个特殊的数字可以被看作是一个数据结构，它存储了函数值，以及规定的导数数量。对于一个期望有两个参数的一次可导数，它可能看起来像这样。
 * <div class=CodeFragmentInTutorialComment>
 *
 *
 * @code
 * struct ADNumberType
 * {
 * double value;          // The value of the object
 * double derivatives[2]; // Array of derivatives of the object with
 *                        // respect to x and y
 * };
 * @endcode
 *
 * </div>
 * 对于我们的自变量`x_ad`，`x_ad.value`的起始值将只是它的赋值（即这个变量所代表的实值）。导数`x_ad.derivatives[0]`将被初始化为`1'，因为`x'是第2个自变量和
 * $\frac{d(x)}{dx} = 1$
 * 。导数`x.derivatives[1]`将被初始化为零，因为第一个自变量是`y`和
 * $\frac{d(x)}{dy} = 0$  。
 * 为了使函数导数有意义，我们必须假设这个函数不仅在分析意义上是可微的，而且在评估点`x,y`也是可微的。我们可以利用这两个假设：当我们在数学运算中使用这种数字类型时，AD框架可以*.
 * 重载操作（例如，`%operator+()`, `%operator*()`以及`%sin()`,
 * `%exp()`,
 * 等等），使返回的结果具有预期值。同时，它将通过对被重载的确切函数的了解和对连锁规则的严格应用来计算导数。因此，`%sin()`函数（其参数`a`本身是自变量`x`和`y`的函数）可能*被定义如下。
 * <div class=CodeFragmentInTutorialComment>
 *
 *
 * @code
 * ADNumberType sin(const ADNumberType &a)
 * {
 * ADNumberType output;
 *
 *
 * // For the input argument "a", "a.value" is simply its value.
 * output.value = sin(a.value);
 *
 *
 * // We know that the derivative of sin(a) is cos(a), but we need
 * // to also consider the chain rule and that the input argument
 * // `a` is also differentiable with respect to the original
 * // independent variables `x` and `y`. So `a.derivatives[0]`
 * // and `a.derivatives[1]` respectively represent the partial
 * // derivatives of `a` with respect to its inputs `x` and `y`.
 * output.derivatives[0] = cos(a.value)*a.derivatives[0];
 * output.derivatives[1] = cos(a.value)*a.derivatives[1];
 *
 *
 * return output;
 * }
 * @endcode
 *
 * </div> 所有这些当然也可以用于二阶甚至高阶导数。
 * 所以现在很清楚，通过上述表示方法，"ADNumberType
 * "携带了一些额外的数据，表示可微调函数相对于原始（敏感）自变量的各种导数。因此应该注意到，使用它们会产生计算开销（因为我们在做导数计算时要计算额外的函数），以及存储这些结果的内存开销。因此，规定的微分运算的级数最好保持在最低水平，以限制计算成本。例如，我们可以自己计算一阶导数，然后使用
 * Differentiation::AD::VectorFunction
 * 辅助类来确定依赖函数集合的梯度，这将是原始标量函数的二阶导数。
 * 还值得注意的是，由于链式规则是无差别应用的，我们只看到计算的起点和终点`{x,y}`
 * $\rightarrow$
 * `f(x,y)`，我们永远只能查询到`f`的总导数；部分导数（上例中的`a.导数[0]`和`a.导数[1]`）是中间值，对我们是隐藏的。
 *
 *
 * 好的，既然我们现在至少对`f_ad`所代表的内容和它所编码的内容有了一定的了解，那么让我们把所有的东西都用到实际中去。为了获得那些隐藏的派生结果，我们将最终的结果注册到辅助类中。在这之后，我们不能再改变`f_ad`的值，也不能让这些变化反映在帮助者类返回的结果中。
 *
 * @code
 *     ad_helper.register_dependent_variable(f_ad);
 *
 * @endcode
 *
 * 下一步是提取导数（特别是函数梯度和Hessian）。为此，我们首先创建一些临时的数据结构（结果类型为`double'）来存储导数（注意所有的导数都是一次性返回的，而不是单独返回）...
 *
 * @code
 *     Vector<double>     Df(ad_helper.n_dependent_variables());
 *     FullMatrix<double> D2f(ad_helper.n_dependent_variables(),
 *                            ad_helper.n_independent_variables());
 *
 * @endcode
 *
 * ...
 * 然后我们要求助手类计算这些导数，以及函数值本身。就这样了。我们得到了我们想得到的一切。
 *
 * @code
 *     const double computed_f = ad_helper.compute_value();
 *     ad_helper.compute_gradient(Df);
 *     ad_helper.compute_hessian(D2f);
 *
 * @endcode
 *
 * 我们可以通过与分析解的比较来说服自己，AD框架是正确的。(或者，如果你像作者一样，你会反其道而行之，宁愿验证你对分析解的实现是正确的！)
 *
 * @code
 *     AssertThrow(std::abs(f(x, y)
 *
 * - computed_f) < tol,
 *                 ExcMessage(std::string("Incorrect value computed for f. ") +
 *                            std::string("Hand-calculated value: ") +
 *                            Utilities::to_string(f(x, y)) +
 *                            std::string(" ; ") +
 *                            std::string("Value computed by AD: ") +
 *                            Utilities::to_string(computed_f)));
 *
 * @endcode
 *
 * 因为我们知道自变量的排序，我们知道梯度的哪个分量与哪个导数有关......。
 *
 * @code
 *     const double computed_df_dx = Df[0];
 *     const double computed_df_dy = Df[1];
 *
 *     AssertThrow(std::abs(df_dx(x, y)
 *
 * - computed_df_dx) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for df/dx. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(df_dx(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by AD: ") +
 *                   Utilities::to_string(computed_df_dx)));
 *     AssertThrow(std::abs(df_dy(x, y)
 *
 * - computed_df_dy) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for df/dy. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(df_dy(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by AD: ") +
 *                   Utilities::to_string(computed_df_dy)));
 *
 * @endcode
 *  ......对于Hessian也是如此。
 *
 * @code
 *     const double computed_d2f_dx_dx = D2f[0][0];
 *     const double computed_d2f_dx_dy = D2f[0][1];
 *     const double computed_d2f_dy_dx = D2f[1][0];
 *     const double computed_d2f_dy_dy = D2f[1][1];
 *
 *     AssertThrow(std::abs(d2f_dx_dx(x, y)
 *
 * - computed_d2f_dx_dx) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for d2f/dx_dx. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(d2f_dx_dx(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by AD: ") +
 *                   Utilities::to_string(computed_d2f_dx_dx)));
 *     AssertThrow(std::abs(d2f_dx_dy(x, y)
 *
 * - computed_d2f_dx_dy) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for d2f/dx_dy. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(d2f_dx_dy(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by AD: ") +
 *                   Utilities::to_string(computed_d2f_dx_dy)));
 *     AssertThrow(std::abs(d2f_dy_dx(x, y)
 *
 * - computed_d2f_dy_dx) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for d2f/dy_dx. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(d2f_dy_dx(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by AD: ") +
 *                   Utilities::to_string(computed_d2f_dy_dx)));
 *     AssertThrow(std::abs(d2f_dy_dy(x, y)
 *
 * - computed_d2f_dy_dy) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for d2f/dy_dy. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(d2f_dy_dy(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by AD: ") +
 *                   Utilities::to_string(computed_d2f_dy_dy)));
 *   }
 *
 * @endcode
 * 这真是太好了。在计算这个三角函数的二阶导数时并没有太多的工作。
 *
 *   <a name="Handcalculatedderivativesoftheanalyticalsolution"></a>
 * <h4>Hand-calculated derivatives of the analytical solution</h4>。
 *
 * 因为我们现在知道了让AD框架为我们计算这些导数需要多少
 * "执行工作"，让我们把它与手工计算并在几个独立的函数中实现的导数进行比较。
 *
 *   下面是 $f(x,y) = \cos\left(\frac{y}{x}\right)$
 * 的两个一阶导数。 $\frac{df(x,y)}{dx} = \frac{y}{x^2}
 * \sin\left(\frac{y}{x}\right)$
 * @code
 *   double df_dx(const double x, const double y)
 *   {
 *     Assert(x != 0.0, ExcDivideByZero());
 *     return y std::sin(y / x) / (x x);
 *   }
 *
 * @endcode
 *
 * $\frac{df(x,y)}{dx} =
 *
 * -\frac{1}{x} \sin\left(\frac{y}{x}\right)$
 * @code
 *   double df_dy(const double x, const double y)
 *   {
 *     return
 *
 * -std::sin(y / x) / x;
 *   }
 *
 * @endcode
 *  而这里是 $f(x,y)$ 的四个二阶导数。 $\frac{d^{2}f(x,y)}{dx^{2}}
 * =
 *
 * -\frac{y}{x^4} (2x \sin\left(\frac{y}{x}\right) + y
 * \cos\left(\frac{y}{x}\right))$
 * @code
 *   double d2f_dx_dx(const double x, const double y)
 *   {
 *     return
 *
 * -y (2 x std::sin(y / x) + y std::cos(y / x)) /
 *            (x x x x);
 *   }
 *
 * @endcode
 *  $\frac{d^{2}f(x,y)}{dx dy} = \frac{1}{x^3} (x \sin\left(\frac{y}{x}\right)
 * + y \cos\left(\frac{y}{x}\right))$
 * @code
 *   double d2f_dx_dy(const double x, const double y)
 *   {
 *     return (x std::sin(y / x) + y std::cos(y / x)) / (x x x);
 *   }
 *
 * @endcode
 *
 * $\frac{d^{2}f(x,y)}{dy dx} = \frac{1}{x^3} (x \sin\left(\frac{y}{x}\right)
 * + y \cos\left(\frac{y}{x}\right))$
 * （如预期，基于[施瓦茨定理]（https://en.wikipedia.org/wiki/Symmetry_of_second_derivatives））
 * @code
 *   double d2f_dy_dx(const double x, const double y)
 *   {
 *     return (x std::sin(y / x) + y std::cos(y / x)) / (x x x);
 *   }
 *
 * @endcode
 *
 * $\frac{d^{2}f(x,y)}{dy^{2}} =
 *
 * -\frac{1}{x^2} \cos\left(\frac{y}{x}\right)$
 * @code
 *   double d2f_dy_dy(const double x, const double y)
 *   {
 *     return
 *
 * -(std::cos(y / x)) / (x x);
 *   }
 *
 * @endcode
 *
 * 嗯......上面有很多地方我们可以引入错误，特别是在应用链式规则的时候。虽然它们不是银弹，但至少这些AD框架可以作为一个验证工具，确保我们没有犯任何错误（无论是计算还是实施），从而对我们的结果产生负面影响。
 *
 *
 * 这个例子的重点当然是，我们可能选择了一个相对简单的函数
 * $f(x,y)$
 * ，我们可以手工验证AD框架计算的导数是否正确。但是AD框架并不关心这个函数是否简单。它可能是一个复杂得多的表达式，或者取决于两个以上的变量，它仍然能够计算出导数。
 *
 * 唯一的区别是，我们*不会再想出导数来验证AD框架的正确性。
 *
 *
 *
 * <a name="Computingderivativesusingsymbolicdifferentiation"></a>
 * <h4>Computing derivatives using symbolic differentiation</h4>。
 *
 * 我们现在用符号微分法重复同样的练习。术语 "符号微分
 * "有点误导，因为微分只是计算机代数系统（CAS）（即符号框架）提供的一个工具。然而，在有限元建模和应用的背景下，它是CAS最常见的用途，因此将是我们关注的重点。再次，我们将提供参数值`x`和`y`，用来评估我们的函数
 * $f(x,y) = \cos\left(\frac{y}{x}\right)$
 * 及其导数，以及测试返回结果正确性的公差。
 *
 * @code
 *   void
 *   run_and_verify_sd(const double x, const double y, const double tol = 1e-12)
 *   {
 * @endcode
 *
 * 我们需要做的第一步是形成符号变量，代表我们希望对其进行微分的函数参数。同样，这些将是我们问题的独立变量，因此，从某种意义上说，它们是原始变量，对任何其他变量没有依赖性。我们通过初始化一个符号类型
 * Differentiation::SD::Expression,
 * 来创建这些类型的（独立）变量，这个符号类型是对符号框架所使用的一组类的包装，有一个唯一的标识符。在这种情况下，这个标识符，一个
 * `std::string`, 对于 $x$ 的参数来说就是`"x"`，同样，对于 $y$
 * 的依赖函数的参数来说就是`"y"。像以前一样，我们将用`sd`作为符号变量名称的后缀，这样我们就可以清楚地看到哪些变量是符号性的（而不是数字性的）。
 *
 * @code
 *     const Differentiation::SD::Expression x_sd("x");
 *     const Differentiation::SD::Expression y_sd("y");
 *
 * @endcode
 *
 * 使用计算 $f(x,y)$
 * 的模板化函数，我们可以将这些独立变量作为参数传递给函数。返回的结果将是另一个符号类型，代表用于计算
 * $\cos\left(\frac{y}{x}\right)$  的操作序列。
 *
 * @code
 *     const Differentiation::SD::Expression f_sd = f(x_sd, y_sd);
 *
 * @endcode
 *
 * 在这一点上，打印出表达式`f_sd`是合法的，如果我们这样做的话
 * <div class=CodeFragmentInTutorialComment>
 *
 *
 * @code
 * std::cout << "f(x,y) = " << f_sd << std::endl;
 * @endcode
 *
 * </div>  我们会看到`f(x,y) = cos(y/x)`打印到控制台。
 * 你可能会注意到，我们在构建符号函数`f_sd`时没有考虑到我们可能要如何使用它。与上面的AD方法相比，我们调用`f(x_sd,
 * y_sd)`返回的不是函数`f`在某个特定点上的求值，而实际上是一个通用的、尚未确定的点上的求值的符号表示。这是使符号框架（CAS）不同于自动区分框架的关键点之一。每个变量`x_sd`和`y_sd`，甚至复合依赖函数`f_sd`，在某种意义上分别是数值的
 * "占位符
 * "和运算的组成。事实上，用于组成函数的各个组件也是占位符。操作序列被编码成一个树状的数据结构（概念上类似于[抽象语法树](https://en.wikipedia.org/wiki/Abstract_syntax_tree)）。
 * 一旦我们形成这些数据结构，我们就可以把我们可能想对它们进行的任何操作推迟到以后的某个时间。这些占位符中的每一个都代表了一些东西，但我们有机会在任何方便的时间点上定义或重新定义它们所代表的东西。因此，对于这个特定的问题，我们想把
 * "x "和 "y
 * "与一些*数值（类型尚未确定）联系起来是有道理的，但我们可以在概念上（如果有道理的话）给
 * "y/x "这个比率赋值，而不是单独给 "x "和 "y
 * "这些变量赋值。我们还可以将 "x "或 "y
 * "与其他一些符号函数`g(a,b)`联系起来。这些操作中的任何一个都涉及到对所记录的操作树的操作，以及用其他东西替换树上的突出节点（以及该节点的子树）。这里的关键词是
 * "替换"，事实上，在 Differentiation::SD
 * 名称空间中，有许多函数的名称中都有这个词。
 * 这种能力使该框架完全通用。在有限元模拟的背景下，我们通常会对我们的符号类型进行的操作类型是函数组合、微分、替换（部分或完全）和评估（即符号类型转换为其数字对应物）。但如果你需要，一个CAS的能力往往不止这些。它可以形成函数的反导数（积分），对形成函数的表达式进行简化（例如，用
 * $1$ 替换 $(\sin a)^2 + (\cos a)^2$
 * ；或者，更简单：如果函数做了像`1+2`这样的运算，CAS可以用`3`替换它），等等。变量所代表的表达式*是从函数
 * $f$
 * 的实现方式中得到的，但CAS可以对其进行任何功能的处理。
 * 具体来说，为了计算因果函数相对于各个自变量的一阶导数的符号表示，我们使用
 * Differentiation::SD::Expression::differentiate()
 * 函数，自变量作为其参数。每次调用都会导致CAS通过组成`f_sd'的运算树，并对表达式树的每个节点进行相对于给定符号参数的微分。
 *
 * @code
 *     const Differentiation::SD::Expression df_dx_sd = f_sd.differentiate(x_sd);
 *     const Differentiation::SD::Expression df_dy_sd = f_sd.differentiate(y_sd);
 *
 * @endcode
 *
 * 为了计算二阶导数的符号表示，我们只需对自变量的一阶导数进行微分。所以要计算高阶导数，我们首先需要计算低阶导数。由于调用
 * "differentiate()
 * "的返回类型是一个表达式，我们原则上可以通过将两个调用连在一起，直接从标量上执行双倍微分。但是在这种特殊情况下，这是不需要的，因为我们手头有中间结果）。)
 *
 * @code
 *     const Differentiation::SD::Expression d2f_dx_dx_sd =
 *       df_dx_sd.differentiate(x_sd);
 *     const Differentiation::SD::Expression d2f_dx_dy_sd =
 *       df_dx_sd.differentiate(y_sd);
 *     const Differentiation::SD::Expression d2f_dy_dx_sd =
 *       df_dy_sd.differentiate(x_sd);
 *     const Differentiation::SD::Expression d2f_dy_dy_sd =
 *       df_dy_sd.differentiate(y_sd);
 * @endcode
 *
 * 使用语句 <div class=CodeFragmentInTutorialComment>
 *
 *
 * @code
 * std::cout << "df_dx_sd: " << df_dx_sd << std::endl;
 * std::cout << "df_dy_sd: " << df_dy_sd << std::endl;
 * std::cout << "d2f_dx_dx_sd: " << d2f_dx_dx_sd << std::endl;
 * std::cout << "d2f_dx_dy_sd: " << d2f_dx_dy_sd << std::endl;
 * std::cout << "d2f_dy_dx_sd: " << d2f_dy_dx_sd << std::endl;
 * std::cout << "d2f_dy_dy_sd: " << d2f_dy_dy_sd << std::endl;
 * @endcode
 *
 * </div>
 * 打印由CAS计算的第一和第二导数的表达式，得到以下输出。
 * <div class=CodeFragmentInTutorialComment>
 *
 *
 * @code{.sh}
 * df_dx_sd: y*sin(y/x)/x**2
 * df_dy_sd:
 *
 * -sin(y/x)/x
 * d2f_dx_dx_sd:
 *
 * -y**2*cos(y/x)/x**4
 *
 * - 2*y*sin(y/x)/x**3
 * d2f_dx_dy_sd: sin(y/x)/x**2 + y*cos(y/x)/x**3
 * d2f_dy_dx_sd: sin(y/x)/x**2 + y*cos(y/x)/x**3
 * d2f_dy_dy_sd:
 *
 * -cos(y/x)/x**2
 * @endcode
 *
 * </div>
 * 这与前面介绍的这些导数的分析表达式相比，效果更好。
 *
 *
 * 现在我们已经形成了函数及其导数的符号表达式，我们想用函数的主要参数`x`和`y`的数字值来评估它们。为了达到这个目的，我们构造了一个替代图*，它将符号值映射到它们的数字对应物上。
 *
 * @code
 *     const Differentiation::SD::types::substitution_map substitution_map =
 *       Differentiation::SD::make_substitution_map(
 *         std::pair<Differentiation::SD::Expression, double>{x_sd, x},
 *         std::pair<Differentiation::SD::Expression, double>{y_sd, y});
 *
 * @endcode
 *
 * 这个过程的最后一步是将所有符号变量和操作转换为数值，并产生这个操作的数值结果。为了做到这一点，我们在上面已经提到的步骤中，将替换图与符号变量结合起来。"替换"。
 * 一旦我们把这个替换图传递给CAS，它就会把符号变量的每个实例（或者更一般的，子表达式）替换成它的数值对应物，然后把这些结果在操作树上传播，如果可能的话，简化树上的每个节点。如果运算树被简化为一个单一的值（即我们已经将所有的独立变量替换为它们的数字对应物），那么评估就完成了。
 * 由于C++的强类型特性，我们需要指示CAS将其对结果的表示转换为内在的数据类型（在这里是
 * "double"）。这就是 "评估
 * "步骤，通过模板类型我们定义了这个过程的返回类型。方便的是，如果我们确定我们已经进行了完整的替换，这两个步骤可以一次完成。
 *
 * @code
 *     const double computed_f =
 *       f_sd.substitute_and_evaluate<double>(substitution_map);
 *
 *     AssertThrow(std::abs(f(x, y)
 *
 * - computed_f) < tol,
 *                 ExcMessage(std::string("Incorrect value computed for f. ") +
 *                            std::string("Hand-calculated value: ") +
 *                            Utilities::to_string(f(x, y)) +
 *                            std::string(" ; ") +
 *                            std::string("Value computed by AD: ") +
 *                            Utilities::to_string(computed_f)));
 *
 * @endcode
 *
 * 我们可以对第一个导数做同样的处理......
 *
 * @code
 *     const double computed_df_dx =
 *       df_dx_sd.substitute_and_evaluate<double>(substitution_map);
 *     const double computed_df_dy =
 *       df_dy_sd.substitute_and_evaluate<double>(substitution_map);
 *
 *     AssertThrow(std::abs(df_dx(x, y)
 *
 * - computed_df_dx) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for df/dx. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(df_dx(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by AD: ") +
 *                   Utilities::to_string(computed_df_dx)));
 *     AssertThrow(std::abs(df_dy(x, y)
 *
 * - computed_df_dy) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for df/dy. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(df_dy(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by AD: ") +
 *                   Utilities::to_string(computed_df_dy)));
 *
 * @endcode
 *
 * ...和二阶导数。请注意，我们可以在这些操作中重复使用相同的替换图，因为我们希望对`x`和`y`的相同值评估所有这些函数。修改置换图中的值，就可以得到相同的符号表达式的评估结果，同时给自变量分配不同的值。我们也可以很高兴地让每个变量在一次中代表一个实值，在下一次中代表一个复值。
 *
 * @code
 *     const double computed_d2f_dx_dx =
 *       d2f_dx_dx_sd.substitute_and_evaluate<double>(substitution_map);
 *     const double computed_d2f_dx_dy =
 *       d2f_dx_dy_sd.substitute_and_evaluate<double>(substitution_map);
 *     const double computed_d2f_dy_dx =
 *       d2f_dy_dx_sd.substitute_and_evaluate<double>(substitution_map);
 *     const double computed_d2f_dy_dy =
 *       d2f_dy_dy_sd.substitute_and_evaluate<double>(substitution_map);
 *
 *     AssertThrow(std::abs(d2f_dx_dx(x, y)
 *
 * - computed_d2f_dx_dx) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for d2f/dx_dx. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(d2f_dx_dx(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by SD: ") +
 *                   Utilities::to_string(computed_d2f_dx_dx)));
 *     AssertThrow(std::abs(d2f_dx_dy(x, y)
 *
 * - computed_d2f_dx_dy) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for d2f/dx_dy. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(d2f_dx_dy(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by SD: ") +
 *                   Utilities::to_string(computed_d2f_dx_dy)));
 *     AssertThrow(std::abs(d2f_dy_dx(x, y)
 *
 * - computed_d2f_dy_dx) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for d2f/dy_dx. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(d2f_dy_dx(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by SD: ") +
 *                   Utilities::to_string(computed_d2f_dy_dx)));
 *     AssertThrow(std::abs(d2f_dy_dy(x, y)
 *
 * - computed_d2f_dy_dy) < tol,
 *                 ExcMessage(
 *                   std::string("Incorrect value computed for d2f/dy_dy. ") +
 *                   std::string("Hand-calculated value: ") +
 *                   Utilities::to_string(d2f_dy_dy(x, y)) + std::string(" ; ") +
 *                   std::string("Value computed by SD: ") +
 *                   Utilities::to_string(computed_d2f_dy_dy)));
 *   }
 *
 *
 * @endcode
 *
 * <a name="TheSimpleExamplerunfunction"></a> <h4>The SimpleExample::run()
 * function</h4>。
 *
 * 用来驱动这些初始例子的函数是直接的。我们将任意选择一些值来评估该函数（尽管知道`x
 * =
 * 0`是不允许的），然后将这些值传递给使用AD和SD框架的函数。
 *
 * @code
 *   void run()
 *   {
 *     const double x = 1.23;
 *     const double y = 0.91;
 *
 *     std::cout << "Simple example using automatic differentiation..."
 *               << std::endl;
 *     run_and_verify_ad(x, y);
 *     std::cout << "... all calculations are correct!" << std::endl;
 *
 *     std::cout << "Simple example using symbolic differentiation."
 *               << std::endl;
 *     run_and_verify_sd(x, y);
 *     std::cout << "... all calculations are correct!" << std::endl;
 *   }
 *
 * } // namespace SimpleExample
 *
 *
 * @endcode
 *
 * <a
 * name="AmorecomplexexampleUsingautomaticandsymbolicdifferentiationtocomputederivativesatcontinuumpoints"></a>
 * <h3>A more complex example: Using automatic and symbolic differentiation to
 * compute derivatives at continuum points</h3>。
 *
 * 现在我们已经介绍了自动和符号分化背后的原理，我们将通过制定两个耦合的磁力学构成法将其付诸实施：一个是与速率无关的，另一个是表现出与速率有关的行为。
 * 正如你在介绍中记得的那样，我们将考虑的材料构成法比上面的简单例子要复杂得多。这不仅仅是因为我们将考虑的函数
 * $\psi_{0}$ 的形式，而且特别是因为 $\psi_{0}$
 * 不仅仅取决于两个标量变量，而是取决于一大堆张量*，每个张量都有几个组成部分。在某些情况下，这些是对称*张量，对于这些张量来说，只有一个分量子集实际上是独立的，我们必须考虑计算
 * $\frac{\partial\psi_{0}}{\partial \mathbf{C}}$
 * 这样的导数的实际意义，其中 $\mathbf C$
 * 是一个对称张量。希望这一切将在下面变得清晰。我们也将清楚地看到，用手做这些事情，最好的情况是极其*繁琐*，最差的情况是
 * 乏味*，最糟糕的是，充满了难以发现的错误。
 *
 * @code
 * namespace CoupledConstitutiveLaws
 * {
 * @endcode
 *
 * <a name="Constitutiveparameters"></a> <h4>Constitutive parameters</h4>。
 *
 * 我们首先描述在能量函数的描述中出现的各种材料参数
 * $\psi_{0}$  。
 * ConstitutiveParameters类被用来保存这些数值。所有参数的值（包括构成参数和流变参数）都取自
 * @cite Pelteret2018a
 * ，并给出了产生构成响应的值，该响应大致代表了真实的、实验室制造的磁活性聚合物，当然，这里使用的具体数值对本程序的目的没有影响。
 * 前四个构成参数分别代表
 *
 *
 * - 弹性剪切模量  $\mu_{e}$  。
 *
 *
 * - 磁饱和时的弹性剪切模量  $\mu_{e}^{\infty}$  。
 *
 *
 * - 弹性剪切模量的饱和磁场强度 $h_{e}^{\text{sat}}$  ，以及
 *
 *
 * - 泊松比  $\nu$  。
 *
 * @code
 *   class ConstitutiveParameters : public ParameterAcceptor
 *   {
 *   public:
 *     ConstitutiveParameters();
 *
 *     double mu_e       = 30.0e3;
 *     double mu_e_inf   = 250.0e3;
 *     double mu_e_h_sat = 212.2e3;
 *     double nu_e       = 0.49;
 *
 * @endcode
 *
 * 接下来的四个，只与速率相关的材料有关，是以下的参数
 *
 *
 * - 粘弹性剪切模量  $\mu_{v}$  。
 *
 *
 * - 磁饱和时的粘弹性剪切模量  $\mu_{v}^{\infty}$  。
 *
 *
 * - 粘弹性剪切模量的饱和磁场强度 $h_{v}^{\text{sat}}$  ，以及
 *
 *
 * - 特征松弛时间  $\tau$  。
 *
 * @code
 *     double mu_v       = 20.0e3;
 *     double mu_v_inf   = 35.0e3;
 *     double mu_v_h_sat = 92.84e3;
 *     double tau_v      = 0.6;
 *
 * @endcode
 *
 * 最后一个参数是相对磁导率  $\mu_{r}$  。
 *
 * @code
 *     double mu_r = 6.0;
 *
 *     bool initialized = false;
 *   };
 *
 * @endcode
 *
 * 参数是通过ParameterAcceptor框架初始化的，这在  step-60
 * 中有详细讨论。
 *
 * @code
 *   ConstitutiveParameters::ConstitutiveParameters()
 *     : ParameterAcceptor("/Coupled Constitutive Laws/Constitutive Parameters/")
 *   {
 *     add_parameter("Elastic shear modulus", mu_e);
 *     add_parameter("Elastic shear modulus at magnetic saturation", mu_e_inf);
 *     add_parameter(
 *       "Saturation magnetic field strength for elastic shear modulus",
 *       mu_e_h_sat);
 *     add_parameter("Poisson ratio", nu_e);
 *
 *     add_parameter("Viscoelastic shear modulus", mu_v);
 *     add_parameter("Viscoelastic shear modulus at magnetic saturation",
 *                   mu_v_inf);
 *     add_parameter(
 *       "Saturation magnetic field strength for viscoelastic shear modulus",
 *       mu_v_h_sat);
 *     add_parameter("Characteristic relaxation time", tau_v);
 *
 *     add_parameter("Relative magnetic permeability", mu_r);
 *
 *     parse_parameters_call_back.connect([&]() { initialized = true; });
 *   }
 *
 *
 * @endcode
 *
 * <a name="ConstitutivelawsBaseclass"></a> <h4>Constitutive laws: Base
 * class</h4>。
 *
 * 因为我们将为同一类材料制定两种构成法，所以定义一个基类以确保它们有统一的接口是有意义的。
 * 该类的声明从构造函数开始，它将接受一组构成参数，这些参数与材料定律本身一起决定了材料的响应。
 *
 * @code
 *   template <int dim>
 *   class Coupled_Magnetomechanical_Constitutive_Law_Base
 *   {
 *   public:
 *     Coupled_Magnetomechanical_Constitutive_Law_Base(
 *       const ConstitutiveParameters &constitutive_parameters);
 *
 * @endcode
 *
 * 与其随意计算和返回动力学变量或它们的线性化，我们将在一个方法中计算和存储这些值。然后这些缓存的结果将在请求时返回。我们将把为什么要这样做的精确解释推迟到以后的阶段。现在重要的是看到这个函数接受所有的场变量，即磁场矢量
 * $\boldsymbol{\mathbb{H}}$ 和右Cauchy-Green形变张量 $\mathbf{C}$
 * ，以及时间离散器。除了 @p constitutive_parameters,
 * 之外，这些都是计算材料响应所需的所有基本量。
 *
 * @code
 *     virtual void update_internal_data(const SymmetricTensor<2, dim> &C,
 *                                       const Tensor<1, dim> &         H,
 *                                       const DiscreteTime &time) = 0;
 *
 * @endcode
 *
 * 接下来的几个函数提供了探测材料响应的接口，由于受到施加的变形和磁载荷的影响。
 * 由于材料的类别可以用自由能来表示  $\psi_{0}$
 * ，我们可以计算出...
 *
 * @code
 *     virtual double get_psi() const = 0;
 *
 * @endcode
 *
 * ... 以及两个动力学量。
 *
 *
 * -磁感应矢量 $\boldsymbol{\mathbb{B}}$  ，以及
 *
 *
 * - 总的Piola-Kirchhoff应力张量 $\mathbf{S}^{\text{tot}}$  。
 *
 * @code
 *     virtual Tensor<1, dim> get_B() const = 0;
 *
 *     virtual SymmetricTensor<2, dim> get_S() const = 0;
 *
 * @endcode
 *
 * ......以及动力学量的线性化，它们是
 *
 *
 * - 磁静力切张量  $\mathbb{D}$  。
 *
 *
 * -总的参考磁弹性耦合张量 $\mathfrak{P}^{\text{tot}}$  ，以及
 *
 *
 * - 总的参考弹性正切张量  $\mathcal{H}^{\text{tot}}$  。
 *
 * @code
 *     virtual SymmetricTensor<2, dim> get_DD() const = 0;
 *
 *     virtual Tensor<3, dim> get_PP() const = 0;
 *
 *     virtual SymmetricTensor<4, dim> get_HH() const = 0;
 *
 * @endcode
 *
 * 我们还将定义一个方法，为这个类的实例提供一个机制，在进入下一个时间步长之前做任何额外的任务。同样，这样做的原因将在稍后变得清晰。
 *
 * @code
 *     virtual void update_end_of_timestep()
 *     {}
 *
 * @endcode
 *
 * 在该类的 "保护
 * "部分，我们存储了一个对支配材料响应的构成参数实例的引用。为了方便，我们还定义了一些函数来返回各种构成参数（包括明确定义的，以及计算的）。
 * 与材料的弹性响应有关的参数依次是
 *
 *
 * - 弹性剪切模量。
 *
 *
 * - 饱和磁场下的弹性剪切模量。
 *
 *
 * - 弹性剪切模量的饱和磁场强度。
 *
 *
 * - 泊松比。
 *
 *
 * - Lam&eacute;参数，以及
 *
 *
 * - 体积模量。
 * @code
 *   protected:
 *     const ConstitutiveParameters &constitutive_parameters;
 *
 *     double get_mu_e() const;
 *
 *     double get_mu_e_inf() const;
 *
 *     double get_mu_e_h_sat() const;
 *
 *     double get_nu_e() const;
 *
 *     double get_lambda_e() const;
 *
 *     double get_kappa_e() const;
 *
 * @endcode
 *
 * 与材料的弹性响应有关的参数依次为：。
 *
 *
 * - 粘弹性剪切模量。
 *
 *
 * - 磁饱和时的粘弹性剪切模量。
 *
 *
 * - 粘弹性剪切模量的饱和磁场强度，以及
 *
 *
 * - 特征松弛时间。
 * @code
 *     double get_mu_v() const;
 *
 *     double get_mu_v_inf() const;
 *
 *     double get_mu_v_h_sat() const;
 *
 *     double get_tau_v() const;
 *
 * @endcode
 *
 * 与材料的磁响应有关的参数依次为：。
 *
 *
 * - 相对磁导率，和
 *
 *
 * - 磁导率常数 $\mu_{0}$ （并不是真正的材料常数，而是一个普遍的常数，为了简单起见，我们在这里分组）。
 * 我们还将实现一个函数，从时间离散性中返回时间步长。
 *
 * @code
 *     double get_mu_r() const;
 *
 *     constexpr double get_mu_0() const;
 *     double           get_delta_t(const DiscreteTime &time) const;
 *   };
 *
 *
 *
 * @endcode
 *
 * 在下文中，让我们从实现刚才定义的类的几个相对琐碎的成员函数开始。
 *
 * @code
 *   template <int dim>
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::
 *     Coupled_Magnetomechanical_Constitutive_Law_Base(
 *       const ConstitutiveParameters &constitutive_parameters)
 *     : constitutive_parameters(constitutive_parameters)
 *   {
 *     Assert(get_kappa_e() > 0, ExcInternalError());
 *   }
 *
 *
 *   template <int dim>
 *   double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_mu_e() const
 *   {
 *     return constitutive_parameters.mu_e;
 *   }
 *
 *
 *   template <int dim>
 *   double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_mu_e_inf() const
 *   {
 *     return constitutive_parameters.mu_e_inf;
 *   }
 *
 *
 *   template <int dim>
 *   double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_mu_e_h_sat() const
 *   {
 *     return constitutive_parameters.mu_e_h_sat;
 *   }
 *
 *
 *   template <int dim>
 *   double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_nu_e() const
 *   {
 *     return constitutive_parameters.nu_e;
 *   }
 *
 *
 *   template <int dim>
 *   double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_lambda_e() const
 *   {
 *     return 2.0 get_mu_e() get_nu_e() / (1.0
 *
 * - 2.0 get_nu_e());
 *   }
 *
 *
 *   template <int dim>
 *   double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_kappa_e() const
 *   {
 *     return (2.0 get_mu_e() (1.0 + get_nu_e())) /
 *            (3.0 (1.0
 *
 * - 2.0 get_nu_e()));
 *   }
 *
 *
 *   template <int dim>
 *   double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_mu_v() const
 *   {
 *     return constitutive_parameters.mu_v;
 *   }
 *
 *
 *   template <int dim>
 *   double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_mu_v_inf() const
 *   {
 *     return constitutive_parameters.mu_v_inf;
 *   }
 *
 *
 *   template <int dim>
 *   double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_mu_v_h_sat() const
 *   {
 *     return constitutive_parameters.mu_v_h_sat;
 *   }
 *
 *
 *   template <int dim>
 *   double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_tau_v() const
 *   {
 *     return constitutive_parameters.tau_v;
 *   }
 *
 *
 *   template <int dim>
 *   double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_mu_r() const
 *   {
 *     return constitutive_parameters.mu_r;
 *   }
 *
 *
 *   template <int dim>
 *   constexpr double
 *   Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_mu_0() const
 *   {
 *     return 4.0 numbers::PI 1e-7;
 *   }
 *
 *
 *   template <int dim>
 *   double Coupled_Magnetomechanical_Constitutive_Law_Base<dim>::get_delta_t(
 *     const DiscreteTime &time) const
 *   {
 *     return time.get_previous_step_size();
 *   }
 *
 *
 * @endcode
 *  <a name="Magnetoelasticconstitutivelawusingautomaticdifferentiation"></a>
 * <h4>Magnetoelastic constitutive law (using automatic
 * differentiation)</h4>。
 * 我们将首先考虑一种非耗散性材料，即受磁超弹性构成法则支配的材料，在浸入磁场时表现出僵化。正如介绍中所述，这种材料的储能密度函数可能由@f[
 * \psi_{0} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * = \frac{1}{2} \mu_{e} f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right)
 * \left[ \text{tr}(\mathbf{C})
 *
 * - d
 *
 * - 2 \ln (\text{det}(\mathbf{F}))
 * \right]
 * + \lambda_{e} \ln^{2} \left(\text{det}(\mathbf{F}) \right)
 *
 *
 *
 *
 *
 * - \frac{1}{2} \mu_{0} \mu_{r} \text{det}(\mathbf{F})
 * \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right]
 * @f]与@f[
 * f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right) = 1 + \left[
 * \frac{\mu_{e}^{\infty}}{\mu_{e}}
 *
 * - 1 \right] \tanh \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}} {\left(h_{e}^{\text{sat}}\right)^{2}} \right) .
 * @f]给出。
 * 现在来看看实现这种行为的类。由于我们期望这个类能完全描述一种材料，我们将把它标记为
 * "最终"，这样继承树就在这里终止了。在类的顶部，我们定义了辅助类型，我们将在标量能量密度函数的AD计算中使用它。请注意，我们希望它能返回
 * "double
 * "类型的值。我们还必须指定空间维度的数量，`dim'，以便建立矢量、张量和对称张量场与它们所含分量数量之间的联系。用于ADHelper类的具体的`ADTypeCode`将在实际使用该类的时候作为模板参数提供。
 *
 * @code
 *   template <int dim, Differentiation::AD::NumberTypes ADTypeCode>
 *   class Magnetoelastic_Constitutive_Law_AD final
 *     : public Coupled_Magnetomechanical_Constitutive_Law_Base<dim>
 *   {
 *     using ADHelper =
 *       Differentiation::AD::ScalarFunction<dim, ADTypeCode, double>;
 *     using ADNumberType = typename ADHelper::ad_type;
 *
 *   public:
 *     Magnetoelastic_Constitutive_Law_AD(
 *       const ConstitutiveParameters &constitutive_parameters);
 *
 * @endcode
 *
 * 由于基类的公共接口是纯 "虚拟
 * "的，这里我们将声明这个类将覆盖所有这些基类方法。
 *
 * @code
 *     virtual void update_internal_data(const SymmetricTensor<2, dim> &C,
 *                                       const Tensor<1, dim> &         H,
 *                                       const DiscreteTime &) override;
 *
 *     virtual double get_psi() const override;
 *
 *     virtual Tensor<1, dim> get_B() const override;
 *
 *     virtual SymmetricTensor<2, dim> get_S() const override;
 *
 *     virtual SymmetricTensor<2, dim> get_DD() const override;
 *
 *     virtual Tensor<3, dim> get_PP() const override;
 *
 *     virtual SymmetricTensor<4, dim> get_HH() const override;
 *
 * @endcode
 *
 * 在这个类的`private'部分，我们需要定义一些提取器，这些提取器将帮助我们设置自变量，随后得到与因变量相关的计算值。如果这个类是在有限元问题的背景下使用，那么这些提取器中的每一个都（很可能）与解场的一个分量的梯度有关（在这种情况下，位移和磁标势）。正如你现在可能推断的那样，这里
 * "C "表示右Cauchy-Green张量，"H "表示磁场向量。
 *
 * @code
 *   private:
 *     const FEValuesExtractors::Vector             H_components;
 *     const FEValuesExtractors::SymmetricTensor<2> C_components;
 *
 * @endcode
 *
 * 这是一个自动微分助手的实例，我们将设置它来进行与构成法有关的所有微分计算......
 *
 * @code
 *     ADHelper ad_helper;
 *
 * @endcode
 *
 * ... 以下三个成员变量将存储来自 @p ad_helper. 的输出。 @p
 * ad_helper
 * 一次性返回关于所有场变量的导数，因此我们将保留完整的梯度向量和Hessian矩阵。我们将从中提取我们真正感兴趣的个别条目。
 *
 * @code
 *     double             psi;
 *     Vector<double>     Dpsi;
 *     FullMatrix<double> D2psi;
 *   };
 *
 * @endcode
 *
 * 在设置字段组件提取器时，对于它们的排序方式是完全任意的。但重要的是，这些提取器没有重叠的索引。这些提取器的组件总数定义了
 * @p ad_helper
 * 需要跟踪的独立变量的数量，并且我们将对其进行导数。由此产生的数据结构
 * @p Dpsi 和 @p D2psi 也必须有相应大小。一旦 @p ad_helper
 * 被配置好（它的输入参数是 $\mathbf{C}$ 和
 * $\boldsymbol{\mathbb{H}}$
 * 的组件总数），我们就可以直接询问它使用多少个独立变量。
 *
 * @code
 *   template <int dim, Differentiation::AD::NumberTypes ADTypeCode>
 *   Magnetoelastic_Constitutive_Law_AD<dim, ADTypeCode>::
 *     Magnetoelastic_Constitutive_Law_AD(
 *       const ConstitutiveParameters &constitutive_parameters)
 *     : Coupled_Magnetomechanical_Constitutive_Law_Base<dim>(
 *         constitutive_parameters)
 *     , H_components(0)
 *     , C_components(Tensor<1, dim>::n_independent_components)
 *     , ad_helper(Tensor<1, dim>::n_independent_components +
 *                 SymmetricTensor<2, dim>::n_independent_components)
 *     , psi(0.0)
 *     , Dpsi(ad_helper.n_independent_variables())
 *     , D2psi(ad_helper.n_independent_variables(),
 *             ad_helper.n_independent_variables())
 *   {}
 *
 * @endcode
 *
 * 如前所述，由于自动微分库的工作方式， @p ad_helper
 * 将总是同时返回能量密度函数相对于所有场变量的导数。由于这个原因，在函数`get_B()`、`get_S()`等中计算导数是没有意义的，因为我们会做很多额外的计算，然后直接丢弃。因此，处理这个问题的最好方法是用一个单一的函数调用来完成所有的前期计算，然后我们在需要时提取存储的数据。这就是我们在
 * "update_internal_data()
 * "方法中要做的。由于材料是与速度无关的，我们可以忽略DiscreteTime参数。
 *
 * @code
 *   template <int dim, Differentiation::AD::NumberTypes ADTypeCode>
 *   void
 *   Magnetoelastic_Constitutive_Law_AD<dim, ADTypeCode>::update_internal_data(
 *     const SymmetricTensor<2, dim> &C,
 *     const Tensor<1, dim> &         H,
 *     const DiscreteTime &)
 *   {
 *     Assert(determinant(C) > 0, ExcInternalError());
 *
 * @endcode
 *
 * 因为我们在每个时间步骤中都会重复使用 @p ad_helper
 * 数据结构，所以我们需要在使用前清除它的所有陈旧信息。
 *
 * @code
 *     ad_helper.reset();
 *
 * @endcode
 *
 * 下一步是设置所有字段组件的值。这些定义了
 * "点"，我们将围绕这个点计算函数梯度和它们的线性化。我们之前创建的提取器在
 * @p ad_helper 中提供了字段和注册表之间的关联。
 *
 * - 它们将被反复使用，以确保我们对哪个变量对应于`H'或`C'的哪个分量有正确的解释。
 *
 * @code
 *     ad_helper.register_independent_variable(H, H_components);
 *     ad_helper.register_independent_variable(C, C_components);
 *
 * @endcode
 *
 * 现在我们已经完成了初始设置，我们可以检索我们的场的AD对应物。这些是真正的能量函数的独立变量，对用它们进行的计算是
 * "敏感
 * "的。请注意，AD数被视为一种特殊的数字类型，可以在许多模板化的类中使用（在这个例子中，作为Tensor和SymmetricTensor类的标量类型）。
 *
 * @code
 *     const Tensor<1, dim, ADNumberType> H_ad =
 *       ad_helper.get_sensitive_variables(H_components);
 *     const SymmetricTensor<2, dim, ADNumberType> C_ad =
 *       ad_helper.get_sensitive_variables(C_components);
 *
 * @endcode
 *
 * 我们还可以在许多以标量类型为模板的函数中使用它们。因此，对于我们需要的这些中间值，我们可以进行张量运算和一些数学函数。由此产生的类型也将是一个自动可分的数字，它编码了这些函数中执行的操作。
 *
 * @code
 *     const ADNumberType det_F_ad = std::sqrt(determinant(C_ad));
 *     const SymmetricTensor<2, dim, ADNumberType> C_inv_ad = invert(C_ad);
 *     AssertThrow(det_F_ad > ADNumberType(0.0),
 *                 ExcMessage("Volumetric Jacobian must be positive."));
 *
 * @endcode
 *
 * 接下来我们将计算在磁场影响下导致剪切模量变化（增加）的比例函数......
 *
 * @code
 *     const ADNumberType f_mu_e_ad =
 *       1.0 + (this->get_mu_e_inf() / this->get_mu_e()
 *
 * - 1.0)
 *               std::tanh((2.0 H_ad H_ad) /
 *                         (this->get_mu_e_h_sat() this->get_mu_e_h_sat()));
 *
 * @endcode
 *
 * ...
 * 然后我们就可以定义材料的储能密度函数。我们将在后面看到，这个例子足够复杂，足以保证使用AD来，至少验证一个无辅助的实现。
 *
 * @code
 *     const ADNumberType psi_ad =
 *       0.5 this->get_mu_e() f_mu_e_ad
 *         (trace(C_ad)
 *
 * - dim
 *
 * - 2.0 std::log(det_F_ad))
 *       + this->get_lambda_e() std::log(det_F_ad) std::log(det_F_ad)
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
 *
 *
 *
 *
 * - 0.5 this->get_mu_0() this->get_mu_r() det_F_ad
 *           (H_ad C_inv_ad H_ad);
 *
 * @endcode
 *
 * 储存的能量密度函数实际上是这个问题的因变量，所以作为
 * "配置 "阶段的最后一步，我们用 @p ad_helper. 登记其定义。
 *
 * @code
 *     ad_helper.register_dependent_variable(psi_ad);
 *
 * @endcode
 *
 * 最后，我们可以检索存储的能量密度函数的结果值，以及它相对于输入字段的梯度和Hessian，并将它们缓存起来。
 *
 * @code
 *     psi = ad_helper.compute_value();
 *     ad_helper.compute_gradient(Dpsi);
 *     ad_helper.compute_hessian(D2psi);
 *   }
 *
 * @endcode
 *
 * 下面的几个函数可以查询 $\psi_{0}$
 * 的存储值，并提取梯度向量和Hessian矩阵的所需成分。我们再次利用提取器来表达我们希望检索的总梯度向量和Hessian矩阵的哪些部分。它们只返回能量函数的导数，所以对于我们的动能变量的定义和它们的线性化，还需要进行一些操作来形成所需的结果。
 *
 * @code
 *   template <int dim, Differentiation::AD::NumberTypes ADTypeCode>
 *   double Magnetoelastic_Constitutive_Law_AD<dim, ADTypeCode>::get_psi() const
 *   {
 *     return psi;
 *   }
 *
 *
 *   template <int dim, Differentiation::AD::NumberTypes ADTypeCode>
 *   Tensor<1, dim>
 *   Magnetoelastic_Constitutive_Law_AD<dim, ADTypeCode>::get_B() const
 *   {
 *     const Tensor<1, dim> dpsi_dH =
 *       ad_helper.extract_gradient_component(Dpsi, H_components);
 *     return
 *
 * -dpsi_dH;
 *   }
 *
 *
 *   template <int dim, Differentiation::AD::NumberTypes ADTypeCode>
 *   SymmetricTensor<2, dim>
 *   Magnetoelastic_Constitutive_Law_AD<dim, ADTypeCode>::get_S() const
 *   {
 *     const SymmetricTensor<2, dim> dpsi_dC =
 *       ad_helper.extract_gradient_component(Dpsi, C_components);
 *     return 2.0 dpsi_dC;
 *   }
 *
 *
 *   template <int dim, Differentiation::AD::NumberTypes ADTypeCode>
 *   SymmetricTensor<2, dim>
 *   Magnetoelastic_Constitutive_Law_AD<dim, ADTypeCode>::get_DD() const
 *   {
 *     const Tensor<2, dim> dpsi_dH_dH =
 *       ad_helper.extract_hessian_component(D2psi, H_components, H_components);
 *     return
 *
 * -symmetrize(dpsi_dH_dH);
 *   }
 *
 * @endcode
 *
 * 请注意，对于耦合项来说，提取器参数的顺序特别重要，因为它决定了提取方向性导数的顺序。因此，如果我们在调用`extract_hessian_component()`时颠倒了提取器的顺序，那么我们实际上是在检索
 * $\left[ \mathfrak{P}^{\text{tot}} \right]^{T}$ 的一部分。
 *
 * @code
 *   template <int dim, Differentiation::AD::NumberTypes ADTypeCode>
 *   Tensor<3, dim>
 *   Magnetoelastic_Constitutive_Law_AD<dim, ADTypeCode>::get_PP() const
 *   {
 *     const Tensor<3, dim> dpsi_dC_dH =
 *       ad_helper.extract_hessian_component(D2psi, C_components, H_components);
 *     return
 *
 * -2.0 dpsi_dC_dH;
 *   }
 *
 *
 *   template <int dim, Differentiation::AD::NumberTypes ADTypeCode>
 *   SymmetricTensor<4, dim>
 *   Magnetoelastic_Constitutive_Law_AD<dim, ADTypeCode>::get_HH() const
 *   {
 *     const SymmetricTensor<4, dim> dpsi_dC_dC =
 *       ad_helper.extract_hessian_component(D2psi, C_components, C_components);
 *     return 4.0 dpsi_dC_dC;
 *   }
 *
 *
 * @endcode
 *
 * <a
 * name="Magnetoviscoelasticconstitutivelawusingsymbolicalgebraanddifferentiation"></a>
 * <h4>Magneto-viscoelastic constitutive law (using symbolic algebra and
 * differentiation)</h4>。
 * 我们要考虑的第二个材料定律将是一个代表具有单一耗散机制的磁-粘弹性材料的定律。我们将考虑这样一种材料的自由能密度函数，定义为
 * @f{align*}{
 * \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v}, \boldsymbol{\mathbb{H}}
 * \right)
 * &= \psi_{0}^{ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * + \psi_{0}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)
 * \\ \psi_{0}^{ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * &= \frac{1}{2} \mu_{e} f_{\mu_{e}^{ME}} \left( \boldsymbol{\mathbb{H}}
 * \right)
 * \left[ \text{tr}(\mathbf{C})
 *
 * - d
 *
 * - 2 \ln (\text{det}(\mathbf{F}))
 * \right]
 * + \lambda_{e} \ln^{2} \left(\text{det}(\mathbf{F}) \right)
 *
 *
 *
 *
 *
 * - \frac{1}{2} \mu_{0} \mu_{r} \text{det}(\mathbf{F})
 * \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right]
 * \\ \psi_{0}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)
 * &= \frac{1}{2} \mu_{v} f_{\mu_{v}^{MVE}} \left( \boldsymbol{\mathbb{H}}
 * \right)
 * \left[ \mathbf{C}_{v} : \left[
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C} \right]
 *
 * - d
 *
 * - \ln\left(
 * \text{det}\left(\mathbf{C}_{v}\right) \right)  \right]
 * @f}
 * 与@f[
 * f_{\mu_{e}}^{ME} \left( \boldsymbol{\mathbb{H}} \right)
 * = 1 + \left[ \frac{\mu_{e}^{\infty}}{\mu_{e}}
 *
 * - 1 \right]
 * \tanh \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}}
 * {\left(h_{e}^{\text{sat}}\right)^{2}} \right)
 * @f]@f[
 * f_{\mu_{v}}^{MVE} \left( \boldsymbol{\mathbb{H}} \right) = 1 + \left[
 * \frac{\mu_{v}^{\infty}}{\mu_{v}}
 *
 * - 1 \right] \tanh \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}} {\left(h_{v}^{\text{sat}}\right)^{2}} \right),
 * @f]结合，内部粘性变量@f[
 * \mathbf{C}_{v}^{(t)} = \frac{1}{1 + \frac{\Delta t}{\tau_{v}}} \left[
 * \mathbf{C}_{v}^{(t-1)} + \frac{\Delta t}{\tau_{v}}
 * \left[\left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C} \right]^{-1} \right]
 * @f]的演化规律是用一阶后向差分近似法离散的。
 * 再一次，让我们看看这在一个具体的类中是如何实现的。我们现在将利用SD方法，而不是前一个类中使用的AD框架。为了支持这一点，类的构造函数不仅接受
 * @p constitutive_parameters,
 * ，而且还接受两个额外的变量，这些变量将用于初始化一个
 * Differentiation::SD::BatchOptimizer.
 * 我们将在后面给出更多的背景。
 *
 * @code
 *   template <int dim>
 *   class Magnetoviscoelastic_Constitutive_Law_SD final
 *     : public Coupled_Magnetomechanical_Constitutive_Law_Base<dim>
 *   {
 *   public:
 *     Magnetoviscoelastic_Constitutive_Law_SD(
 *       const ConstitutiveParameters &               constitutive_parameters,
 *       const Differentiation::SD::OptimizerType     optimizer_type,
 *       const Differentiation::SD::OptimizationFlags optimization_flags);
 *
 * @endcode
 *
 * 和自动微分助手一样， Differentiation::SD::BatchOptimizer
 * 将一次性返回一个结果的集合。因此，为了只做一次，我们将利用与之前类似的方法，在`update_internal_data()`函数中做所有昂贵的计算，并将结果缓存起来供层提取。
 *
 * @code
 *     virtual void update_internal_data(const SymmetricTensor<2, dim> &C,
 *                                       const Tensor<1, dim> &         H,
 *                                       const DiscreteTime &time) override;
 *
 *     virtual double get_psi() const override;
 *
 *     virtual Tensor<1, dim> get_B() const override;
 *
 *     virtual SymmetricTensor<2, dim> get_S() const override;
 *
 *     virtual SymmetricTensor<2, dim> get_DD() const override;
 *
 *     virtual Tensor<3, dim> get_PP() const override;
 *
 *     virtual SymmetricTensor<4, dim> get_HH() const override;
 *
 * @endcode
 *
 * 因为我们要处理的是一个与速率有关的材料，所以我们必须在适当的时候更新历史变量。这将是这个函数的目的。
 *
 * @code
 *     virtual void update_end_of_timestep() override;
 *
 * @endcode
 *
 * 在该类的 "私有
 * "部分，我们要跟踪内部的粘性变形，所以下面两个（实值的、非符号的）成员变量分别持有
 *
 *
 * - 内部变量时间步长的值（如果嵌入到非线性求解器框架中，则为牛顿步长），以及
 *
 *
 * - 内部变量在前一个时间段的值。
 * (我们给这些变量贴上 "Q
 * "的标签，以便于识别；在计算的海洋中，不一定容易区分`Cv`或`C_v`与`C`)。
 *
 * @code
 *   private:
 *     SymmetricTensor<2, dim> Q_t;
 *     SymmetricTensor<2, dim> Q_t1;
 *
 * @endcode
 *
 * 因为我们将使用符号类型，所以我们需要定义一些符号变量来与框架一起使用。(它们都以
 * "SD
 * "为后缀，以方便区分符号类型或表达式与实值类型或标量。)这可以在前面做一次（甚至有可能作为
 * "静态
 * "变量），以尽量减少与创建这些变量相关的开销。为了实现通用编程的终极目标，我们甚至可以用符号来描述构成参数，可能*允许一个单一的类实例也可以用不同的输入来重复使用这些值。
 * 这些是代表弹性、粘性和磁性材料参数的符号标量（主要按照它们在
 * @p ConstitutiveParameters
 * 类中出现的相同顺序定义）。我们还存储了一个符号表达式，
 * @p delta_t_sd, ，表示时间步长的大小）。)
 *
 * @code
 *     const Differentiation::SD::Expression mu_e_sd;
 *     const Differentiation::SD::Expression mu_e_inf_sd;
 *     const Differentiation::SD::Expression mu_e_h_sat_sd;
 *     const Differentiation::SD::Expression lambda_e_sd;
 *     const Differentiation::SD::Expression mu_v_sd;
 *     const Differentiation::SD::Expression mu_v_inf_sd;
 *     const Differentiation::SD::Expression mu_v_h_sat_sd;
 *     const Differentiation::SD::Expression tau_v_sd;
 *     const Differentiation::SD::Expression delta_t_sd;
 *     const Differentiation::SD::Expression mu_r_sd;
 *
 * @endcode
 *
 * 接下来我们定义一些代表独立场变量的张量符号变量，在此基础上对能量密度函数进行参数化。
 *
 * @code
 *     const Tensor<1, dim, Differentiation::SD::Expression>          H_sd;
 *     const SymmetricTensor<2, dim, Differentiation::SD::Expression> C_sd;
 *
 * @endcode
 * 同样，我们也有内部粘性变量的符号表示（包括它的当前值和它在前一个时间段的值）。
 *
 * @code
 *     const SymmetricTensor<2, dim, Differentiation::SD::Expression> Q_t_sd;
 *     const SymmetricTensor<2, dim, Differentiation::SD::Expression> Q_t1_sd;
 *
 * @endcode
 *
 * 我们还应该存储从属表达式的定义。虽然我们只计算一次，但我们需要它们从下面声明的
 * @p optimizer
 * 中检索数据。此外，当序列化一个像这样的材料类时（不是作为本教程的一部分），我们要么需要把这些表达式也序列化，要么需要在重新加载时重建它们。
 *
 * @code
 *     Differentiation::SD::Expression                          psi_sd;
 *     Tensor<1, dim, Differentiation::SD::Expression>          B_sd;
 *     SymmetricTensor<2, dim, Differentiation::SD::Expression> S_sd;
 *     SymmetricTensor<2, dim, Differentiation::SD::Expression> BB_sd;
 *     Tensor<3, dim, Differentiation::SD::Expression>          PP_sd;
 *     SymmetricTensor<4, dim, Differentiation::SD::Expression> HH_sd;
 *
 * @endcode
 *
 * 接下来的变量是用于评估从属函数的优化器。更具体地说，它提供了加速评估符号从属表达式的可能性。这是一个重要的工具，因为对冗长表达式的本地评估（不使用加速方法，而是直接对符号表达式进行评估）会非常慢。
 * Differentiation::SD::BatchOptimizer
 * 类提供了一种机制，可以将符号表达式树转化为另一种代码路径，例如，在各种从属表达式之间共享中间结果（意味着这些中间值每次评估只计算一次）和/或使用即时编译器编译代码（从而为评估步骤检索接近原生性能）。
 * 执行这种代码转换在计算上是非常昂贵的，所以我们存储了优化器，使其在每个类实例中只做一次。这也进一步促使我们决定将构成参数本身变成符号化。然后，我们可以在几种材料（当然是相同的能量函数）和潜在的多个连续体点（如果嵌入有限元模拟）中重复使用这个
 * @p optimizer 的单一实例。
 * 正如模板参数所指定的，数值结果将是<tt>double</tt>类型。
 *
 * @code
 *     Differentiation::SD::BatchOptimizer<double> optimizer;
 *
 * @endcode
 *
 * 在评估阶段，我们必须将符号变量映射到它们的实值对应物。下一个方法将提供这个功能。
 * 这个类的最后一个方法将配置 @p optimizer. 。
 *
 * @code
 *     Differentiation::SD::types::substitution_map
 *     make_substitution_map(const SymmetricTensor<2, dim> &C,
 *                           const Tensor<1, dim> &         H,
 *                           const double                   delta_t) const;
 *
 *     void initialize_optimizer();
 *   };
 *
 * @endcode
 *
 * 由于静止变形状态是材料被认为是完全松弛的状态，所以内部粘性变量用身份张量初始化，即
 * $\mathbf{C}_{v} = \mathbf{I}$
 * 。代表构成参数、时间步长、场和内部变量的各种符号变量都有一个唯一的标识符。优化器被传递给两个参数，这两个参数声明了应该应用哪种优化（加速）技术，以及CAS应该采取哪些额外步骤来帮助提高评估期间的性能。
 *
 * @code
 *   template <int dim>
 *   Magnetoviscoelastic_Constitutive_Law_SD<dim>::
 *     Magnetoviscoelastic_Constitutive_Law_SD(
 *       const ConstitutiveParameters &               constitutive_parameters,
 *       const Differentiation::SD::OptimizerType     optimizer_type,
 *       const Differentiation::SD::OptimizationFlags optimization_flags)
 *     : Coupled_Magnetomechanical_Constitutive_Law_Base<dim>(
 *         constitutive_parameters)
 *     , Q_t(Physics::Elasticity::StandardTensors<dim>::I)
 *     , Q_t1(Physics::Elasticity::StandardTensors<dim>::I)
 *     , mu_e_sd("mu_e")
 *     , mu_e_inf_sd("mu_e_inf")
 *     , mu_e_h_sat_sd("mu_e_h_sat")
 *     , lambda_e_sd("lambda_e")
 *     , mu_v_sd("mu_v")
 *     , mu_v_inf_sd("mu_v_inf")
 *     , mu_v_h_sat_sd("mu_v_h_sat")
 *     , tau_v_sd("tau_v")
 *     , delta_t_sd("delta_t")
 *     , mu_r_sd("mu_r")
 *     , H_sd(Differentiation::SD::make_vector_of_symbols<dim>("H"))
 *     , C_sd(Differentiation::SD::make_symmetric_tensor_of_symbols<2, dim>("C"))
 *     , Q_t_sd(
 *         Differentiation::SD::make_symmetric_tensor_of_symbols<2, dim>("Q_t"))
 *     , Q_t1_sd(
 *         Differentiation::SD::make_symmetric_tensor_of_symbols<2, dim>("Q_t1"))
 *     , optimizer(optimizer_type, optimization_flags)
 *   {
 *     initialize_optimizer();
 *   }
 *
 * @endcode
 *
 * 替换图只是将以下所有数据配对在一起。
 *
 *
 * - 构成参数（从基类中检索出的值）。
 *
 *
 * - 时间步长（其值从时间离散器中获取）。
 *
 *
 * - 字段值（其值由调用此 @p Magnetoviscoelastic_Constitutive_Law_SD 实例的外部函数规定），以及
 *
 *
 * - 当前和以前的内部粘性变形（其值存储在该类实例中）。
 *
 * @code
 *   template <int dim>
 *   Differentiation::SD::types::substitution_map
 *   Magnetoviscoelastic_Constitutive_Law_SD<dim>::make_substitution_map(
 *     const SymmetricTensor<2, dim> &C,
 *     const Tensor<1, dim> &         H,
 *     const double                   delta_t) const
 *   {
 *     return Differentiation::SD::make_substitution_map(
 *       std::make_pair(mu_e_sd, this->get_mu_e()),
 *       std::make_pair(mu_e_inf_sd, this->get_mu_e_inf()),
 *       std::make_pair(mu_e_h_sat_sd, this->get_mu_e_h_sat()),
 *       std::make_pair(lambda_e_sd, this->get_lambda_e()),
 *       std::make_pair(mu_v_sd, this->get_mu_v()),
 *       std::make_pair(mu_v_inf_sd, this->get_mu_v_inf()),
 *       std::make_pair(mu_v_h_sat_sd, this->get_mu_v_h_sat()),
 *       std::make_pair(tau_v_sd, this->get_tau_v()),
 *       std::make_pair(delta_t_sd, delta_t),
 *       std::make_pair(mu_r_sd, this->get_mu_r()),
 *       std::make_pair(H_sd, H),
 *       std::make_pair(C_sd, C),
 *       std::make_pair(Q_t_sd, Q_t),
 *       std::make_pair(Q_t1_sd, Q_t1));
 *   }
 *
 * @endcode
 *
 * 由于符号表达式的 "自然 "使用，配置 @p optimizer
 * 的大部分程序看起来与构建自动区分帮助器的程序非常相似。尽管如此，我们还是要再次详细说明这些步骤，以强调这两个框架的不同之处。
 * 该函数从符号编码变形梯度行列式的表达式开始（用右Cauchy-Green变形张量表示，即我们的主要场变量），以及
 * $\mathbf{C}$ 本身的逆。
 *
 * @code
 *   template <int dim>
 *   void Magnetoviscoelastic_Constitutive_Law_SD<dim>::initialize_optimizer()
 *   {
 *     const Differentiation::SD::Expression det_F_sd =
 *       std::sqrt(determinant(C_sd));
 *     const SymmetricTensor<2, dim, Differentiation::SD::Expression> C_inv_sd =
 *       invert(C_sd);
 *
 * @endcode
 *
 * 接下来是自由能密度函数的弹性部分的饱和函数的符号表示，然后是自由能密度函数的磁弹性贡献。这一切与我们之前看到的结构相同。
 *
 * @code
 *     const Differentiation::SD::Expression f_mu_e_sd =
 *       1.0 +
 *       (mu_e_inf_sd / mu_e_sd
 *
 * - 1.0)
 *         std::tanh((2.0 H_sd H_sd) / (mu_e_h_sat_sd mu_e_h_sat_sd));
 *
 *     const Differentiation::SD::Expression psi_ME_sd =
 *       0.5 mu_e_sd f_mu_e_sd
 *         (trace(C_sd)
 *
 * - dim
 *
 * - 2.0 std::log(det_F_sd)) +
 *       lambda_e_sd std::log(det_F_sd) std::log(det_F_sd)
 *
 * -
 *       0.5 this->get_mu_0() mu_r_sd det_F_sd (H_sd C_inv_sd H_sd);
 *
 * @endcode
 * 此外，我们定义了磁-粘弹性对自由能密度函数的贡献。实现这一点所需的第一个成分是一个缩放函数，它将使粘性剪切模量在磁场的影响下发生变化（增加）（见
 * @cite Pelteret2018a
 * ，公式29）。此后，我们可以计算能量密度函数的耗散分量；其表达式见
 * @cite Pelteret2018a （方程28），这是对 @cite Linder2011a
 * （方程46）中制定的能量密度函数的直接扩展。
 *
 * @code
 *     const Differentiation::SD::Expression f_mu_v_sd =
 *       1.0 +
 *       (mu_v_inf_sd / mu_v_sd
 *
 * - 1.0)
 *         std::tanh((2.0 H_sd H_sd) / (mu_v_h_sat_sd mu_v_h_sat_sd));
 *
 *     const Differentiation::SD::Expression psi_MVE_sd =
 *       0.5 mu_v_sd f_mu_v_sd
 *       (Q_t_sd (std::pow(det_F_sd,
 *
 * -2.0 / dim) C_sd)
 *
 * - dim
 *
 * -
 *        std::log(determinant(Q_t_sd)));
 *
 * @endcode
 *
 * 从这些构件中，我们就可以定义材料的总自由能密度函数。
 *
 * @code
 *     psi_sd = psi_ME_sd + psi_MVE_sd;
 *
 * @endcode
 *
 * 目前，对于CAS来说，变量 @p Q_t_sd 似乎是独立于 @p C_sd.
 * 的，我们的张量符号表达式 @p Q_t_sd
 * 只是有一个与之相关的标识符，没有任何东西将其与另一个张量符号表达式
 * @p C_sd. 联系起来。因此，相对于 @p C_sd
 * 的任何导数将忽略这种固有的依赖关系，正如我们从进化规律可以看出，实际上是
 * $\mathbf{C}_{v} = \mathbf{C}_{v} \left( \mathbf{C}, t \right)$
 * 。这意味着相对于  $\mathbf{C}$  推导任何函数  $f =
 * f(\mathbf{C}, \mathbf{Q})$  将返回部分导数  $\frac{\partial
 * f(\mathbf{C}, \mathbf{Q})}{\partial \mathbf{C}} \Big\vert_{\mathbf{Q}}$
 * ，而不是总导数  $\frac{d f(\mathbf{C}, \mathbf{Q}(\mathbf{C}))}{d
 * \mathbf{C}} = \frac{\partial f(\mathbf{C},
 * \mathbf{Q}(\mathbf{C}))}{\partial \mathbf{C}} \Big\vert_{\mathbf{Q}} +
 * \frac{\partial f(\mathbf{C}, \mathbf{Q}(\mathbf{C}))}{\partial \mathbf{Q}}
 * \Big\vert_{\mathbf{C}} : \frac{d \mathbf{Q}(\mathbf{C}))}{d \mathbf{C}}$
 * 。
 * 相比之下，在当前的AD库中，总导数总是被返回。这意味着对于这类材料模型来说，计算出的动力学变量是不正确的，这使得AD成为从能量密度函数推导出（连续点水平）这种耗散性材料的构成法的不正确工具。
 * 正是这种特定的控制水平描述了SD和AD框架之间的一个决定性的区别。在几行中，我们将操纵内部变量
 * @p Q_t_sd 的表达式，使其产生正确的线性化。
 *
 *
 * 但是，首先，我们将计算动能变量的符号表达式，即磁感应矢量和Piola-Kirchhoff应力张量。执行微分的代码相当紧密地模仿了理论中的定义。
 *
 * @code
 *     B_sd =
 *
 * -Differentiation::SD::differentiate(psi_sd, H_sd);
 *     S_sd = 2.0 Differentiation::SD::differentiate(psi_sd, C_sd);
 *
 * @endcode
 *
 * 因为下一步是对上述内容进行线性化，所以现在是告知CAS
 * @p Q_t_sd 对 @p C_sd, 的明确依赖性的适当时机，即说明
 * $\mathbf{C}_{v} = \mathbf{C}_{v} \left( \mathbf{C}, t \right)$
 * 。这意味着未来所有关于 @p C_sd
 * 的微分运算将考虑到这种依赖关系（即计算总导数）。换句话说，我们将转换一些表达式，使它们的内在参数化从
 * $f(\mathbf{C}, \mathbf{Q})$ 变为 $f(\mathbf{C}, \mathbf{Q}(\mathbf{C}))$
 * 。
 * 为了做到这一点，我们考虑时间离散的演化规律。由此，我们有了内部变量在其历史方面的明确表达，以及主要的场变量。这就是它在这个表达式中描述的内容。
 *
 * @code
 *     const SymmetricTensor<2, dim, Differentiation::SD::Expression>
 *       Q_t_sd_explicit =
 *         (1.0 / (1.0 + delta_t_sd / tau_v_sd))
 *         (Q_t1_sd +
 *          (delta_t_sd / tau_v_sd std::pow(det_F_sd, 2.0 / dim) C_inv_sd));
 *
 * @endcode
 *
 * 接下来我们产生一个中间替换图，它将在一个表达式中找到
 * @p Q_t_sd （我们的标识符）的每个实例，并用 @p
 * Q_t_sd_explicit. 中的完整表达式来替换它。
 *
 * @code
 *     const Differentiation::SD::types::substitution_map
 *       substitution_map_explicit = Differentiation::SD::make_substitution_map(
 *         std::make_pair(Q_t_sd, Q_t_sd_explicit));
 *
 * @endcode
 *
 * 我们可以对两个动力学变量进行这种替换，并立即将替换后的结果与场变量进行区分。(如果你愿意，这可以分成两个步骤，中间的结果储存在一个临时变量中。)同样，如果你忽略了替换所产生的
 * "复杂性"，这些使动能变量线性化并产生三个切向张量的调用与理论中所述的非常相似。
 *
 * @code
 *     BB_sd = symmetrize(Differentiation::SD::differentiate(
 *       Differentiation::SD::substitute(B_sd, substitution_map_explicit),
 *       H_sd));
 *     PP_sd =
 *
 * -Differentiation::SD::differentiate(
 *       Differentiation::SD::substitute(S_sd, substitution_map_explicit), H_sd);
 *     HH_sd =
 *       2.0
 *       Differentiation::SD::differentiate(
 *         Differentiation::SD::substitute(S_sd, substitution_map_explicit),
 *         C_sd);
 *
 * @endcode
 *
 * 现在我们需要告诉 @p optimizer
 * 我们需要提供哪些条目的数值，以便它能成功地进行计算。这些基本上是作为
 * @p optimizer
 * 必须评估的所有从属函数的输入参数。它们统称为问题的自变量、历史变量、时间步长和构成参数（因为我们没有将它们硬编码在能量密度函数中）。
 * 所以我们真正想要的是为它提供一个符号集合，可以用这种方式完成。
 * <div class=CodeFragmentInTutorialComment>
 *
 *
 * @code
 * optimizer.register_symbols(Differentiation::SD::make_symbol_map(
 * mu_e_sd, mu_e_inf_sd, mu_e_h_sat_sd, lambda_e_sd,
 * mu_v_sd, mu_v_inf_sd, mu_v_h_sat_sd, tau_v_sd,
 * delta_t_sd, mu_r_sd,
 * H_sd, C_sd,
 * Q_t_sd, Q_t1_sd));
 * @endcode
 *
 * </div>
 * 但这些实际上都已经被编码为替换图的键。这样做还意味着我们需要在两个地方（这里和构建替换图时）管理这些符号，这很烦人，而且如果这个材料类被修改或扩展，可能会出现错误。由于我们此时对数值不感兴趣，所以如果替代图中与每个键项相关的数值被填入无效的数据也没有关系。所以我们将简单地创建一个假的替换图，并从中提取符号。请注意，任何传递给
 * @p optimizer 的替换图都必须至少包含这些符号的条目。
 *
 * @code
 *     optimizer.register_symbols(
 *       Differentiation::SD::Utilities::extract_symbols(
 *         make_substitution_map({}, {}, 0)));
 *
 * @endcode
 *
 * 然后，我们告知优化器我们想要计算哪些数值，在我们的情况下，这包括所有的因变量（即能量密度函数及其各种导数）。
 *
 * @code
 *     optimizer.register_functions(psi_sd, B_sd, S_sd, BB_sd, PP_sd, HH_sd);
 *
 * @endcode
 *
 * 最后一步是最终确定优化器。通过这个调用，它将确定一个等价的代码路径，该路径将一次评估所有的依赖函数，但计算成本比直接评估符号表达式时要低。注意：这是一个昂贵的调用，所以我们希望尽可能少地执行它。我们在我们的类的构造函数中完成了这个任务，实现了每个类实例只被调用一次的目标。
 *
 * @code
 *     optimizer.optimize();
 *   }
 *
 * @endcode
 *
 * 由于 @p optimizer
 * 的配置是在前面完成的，所以每次我们想计算动能变量或它们的线性化（导数）时，要做的事情就很少了。
 *
 * @code
 *   template <int dim>
 *   void Magnetoviscoelastic_Constitutive_Law_SD<dim>::update_internal_data(
 *     const SymmetricTensor<2, dim> &C,
 *     const Tensor<1, dim> &         H,
 *     const DiscreteTime &           time)
 *   {
 * @endcode
 *
 * 为了更新内部历史变量，我们首先需要计算一些基本量，这些量我们之前已经看到了。我们还可以向时间离散器询问用于从上一个时间步长迭代到当前时间步长的时间步长。
 *
 * @code
 *     const double delta_t = this->get_delta_t(time);
 *
 *     const double                  det_F = std::sqrt(determinant(C));
 *     const SymmetricTensor<2, dim> C_inv = invert(C);
 *     AssertThrow(det_F > 0.0,
 *                 ExcMessage("Volumetric Jacobian must be positive."));
 *
 * @endcode
 *
 * 现在我们可以更新（实值）内部粘性变形张量，根据演化规律给出的定义，结合选择的时间离散化方案。
 *
 * @code
 *     Q_t = (1.0 / (1.0 + delta_t / this->get_tau_v()))
 *           (Q_t1 + (delta_t / this->get_tau_v()) std::pow(det_F, 2.0 / dim)
 *                     C_inv);
 *
 * @endcode
 *
 * 接下来，我们向优化器传递我们希望自变量、时间步长和（本调用隐含的）构成参数所代表的数字值。
 *
 * @code
 *     const auto substitution_map = make_substitution_map(C, H, delta_t);
 *
 * @endcode
 *
 * 当进行这个下一个调用时，用于（数字）评估依赖函数的调用路径比字典替换更快。
 *
 * @code
 *     optimizer.substitute(substitution_map);
 *   }
 *
 * @endcode
 *
 * 在调用了`update_internal_data()`之后，从优化器中提取数据就有效了。在进行评估时，我们需要从优化器中提取的数据的确切符号表达式。这意味着我们需要在优化器的生命周期内存储所有因变量的符号表达式（自然，输入变量也是如此）。
 *
 * @code
 *   template <int dim>
 *   double Magnetoviscoelastic_Constitutive_Law_SD<dim>::get_psi() const
 *   {
 *     return optimizer.evaluate(psi_sd);
 *   }
 *
 *
 *   template <int dim>
 *   Tensor<1, dim> Magnetoviscoelastic_Constitutive_Law_SD<dim>::get_B() const
 *   {
 *     return optimizer.evaluate(B_sd);
 *   }
 *
 *
 *   template <int dim>
 *   SymmetricTensor<2, dim>
 *   Magnetoviscoelastic_Constitutive_Law_SD<dim>::get_S() const
 *   {
 *     return optimizer.evaluate(S_sd);
 *   }
 *
 *
 *   template <int dim>
 *   SymmetricTensor<2, dim>
 *   Magnetoviscoelastic_Constitutive_Law_SD<dim>::get_DD() const
 *   {
 *     return optimizer.evaluate(BB_sd);
 *   }
 *
 *
 *   template <int dim>
 *   Tensor<3, dim> Magnetoviscoelastic_Constitutive_Law_SD<dim>::get_PP() const
 *   {
 *     return optimizer.evaluate(PP_sd);
 *   }
 *
 *
 *   template <int dim>
 *   SymmetricTensor<4, dim>
 *   Magnetoviscoelastic_Constitutive_Law_SD<dim>::get_HH() const
 *   {
 *     return optimizer.evaluate(HH_sd);
 *   }
 *
 * @endcode
 *
 * 当在时间上向前移动时，内部变量的 "当前
 * "状态瞬间定义了 "前一个
 * "时间步骤的状态。因此，我们记录历史变量的值，作为下一个时间步骤的
 * "过去值 "使用。
 *
 * @code
 *   template <int dim>
 *   void Magnetoviscoelastic_Constitutive_Law_SD<dim>::update_end_of_timestep()
 *   {
 *     Q_t1 = Q_t;
 *   }
 *
 *
 * @endcode
 *
 * <a
 * name="AmorecomplexexamplecontinuedParametersandhandderivedmaterialclasses"></a>
 * <h3>A more complex example (continued): Parameters and hand-derived
 * material classes</h3>。
 *
 * 现在我们已经看到了AD和SD框架是如何在定义这些构成法则方面做得很轻松的，我们将用手来实现等价的类，以便进行验证，并对框架与本地实现进行一些初步的基准测试。
 * 以作者的理智为代价，下面记录的（希望是准确的）是动能变量及其切线的完整定义，以及一些中间计算。由于构成法则类的结构和设计已经在前面概述过了，我们将略过它，只是在
 * "update_internal_data()
 * "方法的定义中对各阶段的计算进行划分。将导数计算（及其适度表达的变量名）与出现在类描述中的文档定义联系起来应该是很容易的。然而，我们将借此机会介绍两种实现构成法类的不同范式。第二种将比第一种提供更多的灵活性（从而使其更容易扩展，在作者看来），但要牺牲一些性能。
 *
 *   <a name="Magnetoelasticconstitutivelawhandderived"></a>
 * <h4>Magnetoelastic constitutive law (hand-derived)</h4>。
 * 如前所述，从储存的能量来看，对于这种磁弹性材料，定义为@f[
 * \psi_{0} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * = \frac{1}{2} \mu_{e} f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right)
 * \left[ \text{tr}(\mathbf{C})
 *
 * - d
 *
 * - 2 \ln (\text{det}(\mathbf{F}))
 * \right]
 * + \lambda_{e} \ln^{2} \left(\text{det}(\mathbf{F}) \right)
 *
 *
 *
 *
 *
 * - \frac{1}{2} \mu_{0} \mu_{r} \text{det}(\mathbf{F})
 * \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right]
 * @f]与@f[
 * f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right) = 1 + \left[
 * \frac{\mu_{e}^{\infty}}{\mu_{e}}
 *
 * - 1 \right] \tanh \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}} {\left(h_{e}^{\text{sat}}\right)^{2}} \right) , \\
 * \text{det}(\mathbf{F}) = \sqrt{\text{det}(\mathbf{C})}
 * @f]，对应于磁感应矢量和总Piola-Kirchhoff应力张量的第一导数是@f[
 * \boldsymbol{\mathbb{B}} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * \dealcoloneq
 *
 * - \frac{d \psi_{0}}{d \boldsymbol{\mathbb{H}}} =
 *
 * - \frac{1}{2} \mu_{e} \left[ \text{tr}(\mathbf{C})
 *
 * - d
 *
 * - 2 \ln (\text{det}(\mathbf{F})) \right] \frac{d f_{\mu_{e}} \left(
 * \boldsymbol{\mathbb{H}} \right)}{d \boldsymbol{\mathbb{H}}} + \mu_{0}
 * \mu_{r} \text{det}(\mathbf{F}) \left[ \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right] @f] 。
 * @f{align}
 * \mathbf{S}^{\text{tot}} \left( \mathbf{C}, \boldsymbol{\mathbb{H}}
 * \right)
 * \dealcoloneq 2 \frac{d \psi_{0} \left( \mathbf{C},
 * \boldsymbol{\mathbb{H}} \right)}{d \mathbf{C}}
 * &= \mu_{e} f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right)
 * \left[ \frac{d\,\text{tr}(\mathbf{C})}{d \mathbf{C}}
 *
 *
 *
 *
 *
 * - 2 \frac{1}{\text{det}(\mathbf{F})}
 * \frac{d\,\text{det}(\mathbf{F})}{d \mathbf{C}} \right]
 * + 4 \lambda_{e} \ln \left(\text{det}(\mathbf{F}) \right)
 * \frac{1}{\text{det}(\mathbf{F})} \frac{d\,\text{det}(\mathbf{F})}{d
 * \mathbf{C}}
 *
 *
 *
 *
 *
 * - \mu_{0} \mu_{r} \left[
 * \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right] \frac{d\,\text{det}(\mathbf{F})}{d
 * \mathbf{C}} + \text{det}(\mathbf{F}) \frac{d \left[
 * \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}}
 * \right]}{d \mathbf{C}} \right]
 * \\ &= \mu_{e} f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right)
 * \left[ \mathbf{I}
 *
 * - \mathbf{C}^{-1} \right]
 * + 2 \lambda_{e} \ln \left(\text{det}(\mathbf{F}) \right) \mathbf{C}^{-1}
 *
 *
 *
 *
 *
 * - \mu_{0} \mu_{r} \left[
 * \frac{1}{2}  \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1}
 * \cdot \boldsymbol{\mathbb{H}} \right] \text{det}(\mathbf{F})
 * \mathbf{C}^{-1}
 *
 *
 *
 *
 *
 * - \text{det}(\mathbf{F})
 * \left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}} \right] \otimes
 * \left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}} \right]
 * \right]
 * @f}
 * 与 @f[
 * \frac{d f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right)}{d
 * \boldsymbol{\mathbb{H}}}
 * = \left[ \frac{\mu_{e}^{\infty}}{\mu_{e}}
 *
 * - 1 \right]
 * \text{sech}^{2} \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}}
 * {\left(h_{e}^{\text{sat}}\right)^{2}} \right)
 * \left[ \frac{4} {\left(h_{e}^{\text{sat}}\right)^{2}}
 * \boldsymbol{\mathbb{H}} \right]
 * @f] @f[
 * \frac{d\,\text{tr}(\mathbf{C})}{d \mathbf{C}} = \mathbf{I} \quad \text{(the
 * second-order identity tensor)}
 * @f] @f[
 * \frac{d\,\text{det}(\mathbf{F})}{d \mathbf{C}} = \frac{1}{2}
 * \text{det}(\mathbf{F}) \mathbf{C}^{-1}
 * @f] @f[
 * \frac{d C^{-1}_{ab}}{d C_{cd}} =
 *
 * - \text{sym} \left( C^{-1}_{ac} C^{-1}_{bd} \right) =
 *
 * -\frac{1}{2} \left[ C^{-1}_{ac} C^{-1}_{bd} + C^{-1}_{ad} C^{-1}_{bc}
 * \right]
 * @f] @f[
 * \frac{d \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right]}{d \mathbf{C}} =
 *
 * - \left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}} \right] \otimes
 * \left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}} \right] @f]
 * 在上面的一个推导中使用对称算子 $\text{sym} \left( \bullet
 * \right)$ 有助于确保所得到的四阶张量，由于 $\mathbf{C}$
 * 的对称性而持有小的对称性，仍然将二阶对称张量映射到二阶对称张量。参见SymmetricTensor类文档和
 * step-44
 * 的介绍，并进一步解释在四阶张量的背景下对称性的含义。
 * *每个运动学变量相对于其参数的线性化是@f[
 * \mathbb{D} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * = \frac{d \boldsymbol{\mathbb{B}}}{d \boldsymbol{\mathbb{H}}}
 * =
 *
 * - \frac{1}{2} \mu_{e} \left[ \text{tr}(\mathbf{C})
 *
 * - d
 *
 * - 2 \ln
 * (\text{det}(\mathbf{F}))
 * \right] \frac{d^{2} f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}}
 * \right)}{d \boldsymbol{\mathbb{H}} \otimes d \boldsymbol{\mathbb{H}}}
 * + \mu_{0} \mu_{r} \text{det}(\mathbf{F}) \mathbf{C}^{-1}
 * @f]。
 * @f{align}
 * \mathfrak{P}^{\text{tot}} \left( \mathbf{C}, \boldsymbol{\mathbb{H}}
 * \right) =
 *
 * - \frac{d \mathbf{S}^{\text{tot}}}{d \boldsymbol{\mathbb{H}}}
 * &=
 *
 * - \mu_{e}
 * \left[ \frac{d\,\text{tr}(\mathbf{C})}{d \mathbf{C}}
 *
 *
 *
 *
 *
 * - 2 \frac{1}{\text{det}(\mathbf{F})}
 * \frac{d\,\text{det}(\mathbf{F})}{d \mathbf{C}} \right]
 * \otimes \frac{d f_{\mu_{e} \left( \boldsymbol{\mathbb{H}}
 * \right)}}{d \boldsymbol{\mathbb{H}}}
 * + \mu_{0} \mu_{r} \left[
 * \frac{d\,\text{det}(\mathbf{F})}{d \mathbf{C}} \otimes
 * \frac{d \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}}
 * \right]}{d \boldsymbol{\mathbb{H}}} \right]
 * + \text{det}(\mathbf{F})
 * \frac{d^{2} \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1}
 * \cdot \boldsymbol{\mathbb{H}}
 * \right]}{d \mathbf{C} \otimes d \boldsymbol{\mathbb{H}}}
 * \\ &=
 *
 * - \mu_{e}
 * \left[ \mathbf{I}
 *
 * - \mathbf{C}^{-1} \right] \otimes
 * \frac{d f_{\mu_{e} \left( \boldsymbol{\mathbb{H}} \right)}}{d
 * \boldsymbol{\mathbb{H}}}
 * + \mu_{0} \mu_{r} \left[
 * \text{det}(\mathbf{F}) \mathbf{C}^{-1} \otimes
 * \left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}} \right]
 * \right]
 * + \text{det}(\mathbf{F})
 * \frac{d^{2} \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1}
 * \cdot \boldsymbol{\mathbb{H}}
 * \right]}{d \mathbf{C} \otimes \mathbf{C} \boldsymbol{\mathbb{H}}}
 * @f}
 * @f{align}
 * \mathcal{H}^{\text{tot}} \left( \mathbf{C}, \boldsymbol{\mathbb{H}}
 * \right) = 2 \frac{d \mathbf{S}^{\text{tot}}}{d \mathbf{C}}
 * &= 2 \mu_{e} f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right)
 * \left[
 *
 * - \frac{d \mathbf{C}^{-1}}{d \mathbf{C}} \right]
 * + 4 \lambda_{e} \left[ \mathbf{C}^{-1} \otimes \left[
 * \frac{1}{\text{det}(\mathbf{F})} \frac{d \, \text{det}(\mathbf{F})}{d
 * \mathbf{C}} \right] + \ln \left(\text{det}(\mathbf{F}) \right) \frac{d
 * \mathbf{C}^{-1}}{d \mathbf{C}} \right]
 * \\ &- \mu_{0} \mu_{r}  \left[
 * \text{det}(\mathbf{F}) \mathbf{C}^{-1} \otimes \frac{d \left[
 * \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right]}{d \mathbf{C}}
 * + \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right] \mathbf{C}^{-1} \otimes \frac{d \,
 * \text{det}(\mathbf{F})}{d \mathbf{C}}
 * + \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right] \text{det}(\mathbf{F}) \frac{d
 * \mathbf{C}^{-1}}{d \mathbf{C}}
 * \right]
 * \\ &+ 2 \mu_{0} \mu_{r} \left[ \left[
 * \left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}} \right] \otimes
 * \left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}} \right]
 * \right] \otimes \frac{d \, \text{det}(\mathbf{F})}{d \mathbf{C}}
 *
 *
 *
 *
 *
 * - \text{det}(\mathbf{F})
 * \frac{d^{2} \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1}
 * \cdot \boldsymbol{\mathbb{H}}\right]}{d \mathbf{C} \otimes d
 * \mathbf{C}}
 * \right]
 * \\ &= 2 \mu_{e} f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right)
 * \left[
 *
 * - \frac{d \mathbf{C}^{-1}}{d \mathbf{C}} \right]
 * + 4 \lambda_{e} \left[ \frac{1}{2} \mathbf{C}^{-1} \otimes
 * \mathbf{C}^{-1} + \ln \left(\text{det}(\mathbf{F}) \right) \frac{d
 * \mathbf{C}^{-1}}{d \mathbf{C}} \right]
 * \\ &- \mu_{0} \mu_{r}  \left[
 *
 *
 *
 *
 *
 * - \text{det}(\mathbf{F}) \mathbf{C}^{-1} \otimes \left[ \left[
 * \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}} \right] \otimes
 * \left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}} \right] \right]
 * + \frac{1}{2} \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right] \text{det}(\mathbf{F})  \mathbf{C}^{-1}
 * \otimes \mathbf{C}^{-1}
 * + \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right] \text{det}(\mathbf{F}) \frac{d
 * \mathbf{C}^{-1}}{d \mathbf{C}}
 * \right]
 * \\ &+ 2 \mu_{0} \mu_{r} \left[ \frac{1}{2} \text{det}(\mathbf{F}) \left[
 * \left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}} \right] \otimes
 * \left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}} \right]
 * \right] \otimes \mathbf{C}^{-1}
 *
 *
 *
 *
 *
 * - \text{det}(\mathbf{F})
 * \frac{d^{2} \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1}
 * \cdot \boldsymbol{\mathbb{H}}\right]}{d \mathbf{C} \otimes d
 * \mathbf{C}}
 * \right]
 * @f}
 * *与@f[
 * \frac{d^{2} f_{\mu_{e}} \left( \boldsymbol{\mathbb{H}} \right)}{d
 * \boldsymbol{\mathbb{H}} \otimes d \boldsymbol{\mathbb{H}}}
 * =
 *
 * -2 \left[ \frac{\mu_{e}^{\infty}}{\mu_{e}}
 *
 * - 1 \right]
 * \tanh \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}}
 * {\left(h_{e}^{\text{sat}}\right)^{2}} \right)
 * \text{sech}^{2} \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}}
 * {\left(h_{e}^{\text{sat}}\right)^{2}} \right)
 * \left[ \frac{4} {\left(h_{e}^{\text{sat}}\right)^{2}} \mathbf{I}
 * \right]
 * @f] @f[
 * \frac{d \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}} \right]}{d \boldsymbol{\mathbb{H}}} = 2
 * \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}}
 * @f] @f[
 * \frac{d^{2} \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}}\right]}{d \mathbf{C} \otimes d
 * \boldsymbol{\mathbb{H}}} \Rightarrow \frac{d^{2} \left[ \mathbb{H}_{e}
 * C^{-1}_{ef} \mathbb{H}_{f} \right]}{d C_{ab} d \mathbb{H}_{c}} =
 *
 * - C^{-1}_{ac} C^{-1}_{be} \mathbb{H}_{e}
 *
 * - C^{-1}_{ae} \mathbb{H}_{e} C^{-1}_{bc} @f]。
 * @f{align}
 * \frac{d^{2} \left[ \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot
 * \boldsymbol{\mathbb{H}}\right]}{d \mathbf{C} \otimes d \mathbf{C}}
 * &=
 *
 * -\frac{d \left[\left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}}
 * \right] \otimes
 * \left[ \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}}
 * \right]\right]}{d \mathbf{C}}
 * \\ \Rightarrow
 * \frac{d^{2} \left[ \mathbb{H}_{e} C^{-1}_{ef} \mathbb{H}_{f}
 * \right]}{d C_{ab} d C_{cd}}
 * &= \text{sym} \left( C^{-1}_{ae} \mathbb{H}_{e} C^{-1}_{cf}
 * \mathbb{H}_{f} C^{-1}_{bd}
 * + C^{-1}_{ce} \mathbb{H}_{e} C^{-1}_{bf} \mathbb{H}_{f}
 * C^{-1}_{ad} \right)
 * \\ &= \frac{1}{2} \left[
 * C^{-1}_{ae} \mathbb{H}_{e} C^{-1}_{cf} \mathbb{H}_{f} C^{-1}_{bd}
 * + C^{-1}_{ae} \mathbb{H}_{e} C^{-1}_{df} \mathbb{H}_{f} C^{-1}_{bc}
 * + C^{-1}_{ce} \mathbb{H}_{e} C^{-1}_{bf} \mathbb{H}_{f} C^{-1}_{ad}
 * + C^{-1}_{be} \mathbb{H}_{e} C^{-1}_{df} \mathbb{H}_{f} C^{-1}_{ac}
 * \right]
 * @f}
 *
 * 好吧，这很快就升级了
 *
 * - 尽管 $\psi_{0}$ 和 $f_{\mu_e}$ 的定义可能已经给出了一些提示，表明计算动能场和它们的线性化将需要一些努力，但很可能最终定义的复杂性比最初想象的要多一些。了解了我们现在所做的，也许可以说，我们真的不想计算这些函数相对于其参数的一、二次导数
 *
 * 不管我们在微积分课上表现如何，也不管我们是多么优秀的程序员。
 * 在最终实现这些的类方法定义中，我们以稍微不同的方式组成这些计算。一些中间步骤也被保留下来，以便从另一个角度说明如何系统地计算导数。此外，一些计算被分解得更少或更进一步，以重用一些中间值，并希望能帮助读者跟随导数的操作。
 *
 * @code
 *   template <int dim>
 *   class Magnetoelastic_Constitutive_Law final
 *     : public Coupled_Magnetomechanical_Constitutive_Law_Base<dim>
 *   {
 *   public:
 *     Magnetoelastic_Constitutive_Law(
 *       const ConstitutiveParameters &constitutive_parameters);
 *
 *     virtual void update_internal_data(const SymmetricTensor<2, dim> &C,
 *                                       const Tensor<1, dim> &         H,
 *                                       const DiscreteTime &) override;
 *
 *     virtual double get_psi() const override;
 *
 *     virtual Tensor<1, dim> get_B() const override;
 *
 *     virtual SymmetricTensor<2, dim> get_S() const override;
 *
 *     virtual SymmetricTensor<2, dim> get_DD() const override;
 *
 *     virtual Tensor<3, dim> get_PP() const override;
 *
 *     virtual SymmetricTensor<4, dim> get_HH() const override;
 *
 *   private:
 *     double                  psi;
 *     Tensor<1, dim>          B;
 *     SymmetricTensor<2, dim> S;
 *     SymmetricTensor<2, dim> BB;
 *     Tensor<3, dim>          PP;
 *     SymmetricTensor<4, dim> HH;
 *   };
 *
 *
 *   template <int dim>
 *   Magnetoelastic_Constitutive_Law<dim>::Magnetoelastic_Constitutive_Law(
 *     const ConstitutiveParameters &constitutive_parameters)
 *     : Coupled_Magnetomechanical_Constitutive_Law_Base<dim>(
 *         constitutive_parameters)
 *     , psi(0.0)
 *   {}
 *
 * @endcode
 *
 * 对于这个类的更新方法，我们将简单地预先计算一个中间值的集合（用于函数求值、导数计算等），并
 * "手动
 * "安排它们的顺序，以使它们的重复使用最大化。这意味着我们必须自己管理，并决定哪些值必须在其他值之前计算，同时保持代码本身的某种秩序或结构的模样。这很有效，但也许有点乏味。它对类的未来扩展也没有太大的帮助，因为所有这些值都是这个单一方法的局部。
 * 有趣的是，这种预先计算在多个地方使用的中间表达式的基本技术有一个名字：[共同子表达式消除（CSE）]（https://en.wikipedia.org/wiki/Common_subexpression_elimination）。它是计算机代数系统使用的一种策略，当它们被赋予评估类似表达式的任务时，可以减少计算费用。
 *
 * @code
 *   template <int dim>
 *   void Magnetoelastic_Constitutive_Law<dim>::update_internal_data(
 *     const SymmetricTensor<2, dim> &C,
 *     const Tensor<1, dim> &         H,
 *     const DiscreteTime &)
 *   {
 *     const double                  det_F = std::sqrt(determinant(C));
 *     const SymmetricTensor<2, dim> C_inv = invert(C);
 *     AssertThrow(det_F > 0.0,
 *                 ExcMessage("Volumetric Jacobian must be positive."));
 *
 * @endcode
 *
 * 磁弹性能的饱和函数。
 *
 * @code
 *     const double two_h_dot_h_div_h_sat_squ =
 *       (2.0 H H) / (this->get_mu_e_h_sat() this->get_mu_e_h_sat());
 *     const double tanh_two_h_dot_h_div_h_sat_squ =
 *       std::tanh(two_h_dot_h_div_h_sat_squ);
 *
 *     const double f_mu_e =
 *       1.0 + (this->get_mu_e_inf() / this->get_mu_e()
 *
 * - 1.0)
 *               tanh_two_h_dot_h_div_h_sat_squ;
 *
 * @endcode
 *
 * 饱和函数的一阶导数，注意 $\frac{d \tanh(x)}{dx} =
 * \text{sech}^{2}(x)$  。
 *
 * @code
 *     const double dtanh_two_h_dot_h_div_h_sat_squ =
 *       std::pow(1.0 / std::cosh(two_h_dot_h_div_h_sat_squ), 2.0);
 *     const Tensor<1, dim> dtwo_h_dot_h_div_h_sat_squ_dH =
 *       2.0 2.0 / (this->get_mu_e_h_sat() this->get_mu_e_h_sat()) H;
 *
 *     const Tensor<1, dim> df_mu_e_dH =
 *       (this->get_mu_e_inf() / this->get_mu_e()
 *
 * - 1.0)
 *       (dtanh_two_h_dot_h_div_h_sat_squ dtwo_h_dot_h_div_h_sat_squ_dH);
 *
 * @endcode
 *
 * 饱和函数的二阶导数，注意到 $\frac{d \text{sech}^{2}(x)}{dx} =
 *
 * -2 \tanh(x) \text{sech}^{2}(x)$  。
 *
 * @code
 *     const double d2tanh_two_h_dot_h_div_h_sat_squ =
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
 * -2.0 tanh_two_h_dot_h_div_h_sat_squ dtanh_two_h_dot_h_div_h_sat_squ;
 *     const SymmetricTensor<2, dim> d2two_h_dot_h_div_h_sat_squ_dH_dH =
 *       2.0 2.0 / (this->get_mu_e_h_sat() this->get_mu_e_h_sat())
 *       Physics::Elasticity::StandardTensors<dim>::I;
 *
 *     const SymmetricTensor<2, dim> d2f_mu_e_dH_dH =
 *       (this->get_mu_e_inf() / this->get_mu_e()
 *
 * - 1.0)
 *       (d2tanh_two_h_dot_h_div_h_sat_squ
 *          symmetrize(outer_product(dtwo_h_dot_h_div_h_sat_squ_dH,
 *                                   dtwo_h_dot_h_div_h_sat_squ_dH)) +
 *        dtanh_two_h_dot_h_div_h_sat_squ d2two_h_dot_h_div_h_sat_squ_dH_dH);
 *
 * @endcode
 *
 * 一些直接从场/运动学变量中获得的中间量。
 *
 * @code
 *     const double         log_det_F         = std::log(det_F);
 *     const double         tr_C              = trace(C);
 *     const Tensor<1, dim> C_inv_dot_H       = C_inv H;
 *     const double         H_dot_C_inv_dot_H = H C_inv_dot_H;
 *
 * @endcode
 *
 * 中间量的一阶导数。
 *
 * @code
 *     const SymmetricTensor<2, dim> d_tr_C_dC =
 *       Physics::Elasticity::StandardTensors<dim>::I;
 *     const SymmetricTensor<2, dim> ddet_F_dC     = 0.5 det_F C_inv;
 *     const SymmetricTensor<2, dim> dlog_det_F_dC = 0.5 C_inv;
 *
 *     const Tensor<1, dim> dH_dot_C_inv_dot_H_dH = 2.0 C_inv_dot_H;
 *
 *     SymmetricTensor<4, dim> dC_inv_dC;
 *     for (unsigned int A = 0; A < dim; ++A)
 *       for (unsigned int B = A; B < dim; ++B)
 *         for (unsigned int C = 0; C < dim; ++C)
 *           for (unsigned int D = C; D < dim; ++D)
 *             dC_inv_dC[A][B][C][D]
 *
 * -=
 *               0.5 (C_inv[A][C] C_inv[B][D]
 *                      + C_inv[A][D] C_inv[B][C]);
 *
 *     const SymmetricTensor<2, dim> dH_dot_C_inv_dot_H_dC =
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
 * -symmetrize(outer_product(C_inv_dot_H, C_inv_dot_H));
 *
 * @endcode
 *
 * 中间量的二阶导数。
 *
 * @code
 *     const SymmetricTensor<4, dim> d2log_det_F_dC_dC = 0.5 dC_inv_dC;
 *
 *     const SymmetricTensor<4, dim> d2det_F_dC_dC =
 *       0.5 (outer_product(C_inv, ddet_F_dC) + det_F dC_inv_dC);
 *
 *     const SymmetricTensor<2, dim> d2H_dot_C_inv_dot_H_dH_dH = 2.0 C_inv;
 *
 *     Tensor<3, dim> d2H_dot_C_inv_dot_H_dC_dH;
 *     for (unsigned int A = 0; A < dim; ++A)
 *       for (unsigned int B = 0; B < dim; ++B)
 *         for (unsigned int C = 0; C < dim; ++C)
 *           d2H_dot_C_inv_dot_H_dC_dH[A][B][C]
 *
 * -=
 *             C_inv[A][C] C_inv_dot_H[B] +
 *             C_inv_dot_H[A] C_inv[B][C];
 *
 *     SymmetricTensor<4, dim> d2H_dot_C_inv_dot_H_dC_dC;
 *     for (unsigned int A = 0; A < dim; ++A)
 *       for (unsigned int B = A; B < dim; ++B)
 *         for (unsigned int C = 0; C < dim; ++C)
 *           for (unsigned int D = C; D < dim; ++D)
 *             d2H_dot_C_inv_dot_H_dC_dC[A][B][C][D] +=
 *               0.5 (C_inv_dot_H[A] C_inv_dot_H[C] C_inv[B][D] +
 *                      C_inv_dot_H[A] C_inv_dot_H[D] C_inv[B][C] +
 *                      C_inv_dot_H[B] C_inv_dot_H[C] C_inv[A][D] +
 *                      C_inv_dot_H[B] C_inv_dot_H[D] C_inv[A][C]);
 *
 * @endcode
 *
 * 储存的能量密度函数。
 *
 * @code
 *     psi =
 *       (0.5 this->get_mu_e() f_mu_e)
 *         (tr_C
 *
 * - dim
 *
 * - 2.0 std::log(det_F)) +
 *       this->get_lambda_e() (std::log(det_F) std::log(det_F))
 *
 * -
 *       (0.5 this->get_mu_0() this->get_mu_r()) det_F (H C_inv H);
 *
 * @endcode
 *
 * 动能量。
 *
 * @code
 *     B =
 *
 * -(0.5 this->get_mu_e() (tr_C
 *
 * - dim
 *
 * - 2.0 log_det_F))
 *           df_mu_e_dH
 *         + 0.5 this->get_mu_0() this->get_mu_r() det_F
 *             dH_dot_C_inv_dot_H_dH;
 *
 *     S = 2.0 (0.5 this->get_mu_e() f_mu_e)
 *           (d_tr_C_dC
 *
 * - 2.0 dlog_det_F_dC)
 *         + 2.0 this->get_lambda_e() (2.0 log_det_F dlog_det_F_dC)
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
 * - 2.0 (0.5 this->get_mu_0() this->get_mu_r())
 *             (H_dot_C_inv_dot_H ddet_F_dC
 *              + det_F dH_dot_C_inv_dot_H_dC);
 *
 * @endcode
 *
 * 运动量的线性化。
 *
 * @code
 *     BB =
 *
 * -(0.5 this->get_mu_e() (tr_C
 *
 * - dim
 *
 * - 2.0 log_det_F))
 *            d2f_mu_e_dH_dH
 *          + 0.5 this->get_mu_0() this->get_mu_r() det_F
 *              d2H_dot_C_inv_dot_H_dH_dH;
 *
 *     PP =
 *
 * -2.0 (0.5 this->get_mu_e())
 *            outer_product(Tensor<2, dim>(d_tr_C_dC
 *
 * - 2.0 dlog_det_F_dC),
 *                          df_mu_e_dH)
 *          +
 *          2.0 (0.5 this->get_mu_0() this->get_mu_r())
 *            (outer_product(Tensor<2, dim>(ddet_F_dC), dH_dot_C_inv_dot_H_dH)
 *             + det_F d2H_dot_C_inv_dot_H_dC_dH);
 *
 *     HH =
 *       4.0 (0.5 this->get_mu_e() f_mu_e) (-2.0 d2log_det_F_dC_dC)
 *       + 4.0 this->get_lambda_e()
 *           (2.0 outer_product(dlog_det_F_dC, dlog_det_F_dC)
 *            + 2.0 log_det_F d2log_det_F_dC_dC)
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
 * - 4.0 (0.5 this->get_mu_0() this->get_mu_r())
 *           (H_dot_C_inv_dot_H d2det_F_dC_dC
 *            + outer_product(ddet_F_dC, dH_dot_C_inv_dot_H_dC)
 *            + outer_product(dH_dot_C_inv_dot_H_dC, ddet_F_dC)
 *            + det_F d2H_dot_C_inv_dot_H_dC_dC);
 *   }
 *
 *   template <int dim>
 *   double Magnetoelastic_Constitutive_Law<dim>::get_psi() const
 *   {
 *     return psi;
 *   }
 *
 *   template <int dim>
 *   Tensor<1, dim> Magnetoelastic_Constitutive_Law<dim>::get_B() const
 *   {
 *     return B;
 *   }
 *
 *   template <int dim>
 *   SymmetricTensor<2, dim> Magnetoelastic_Constitutive_Law<dim>::get_S() const
 *   {
 *     return S;
 *   }
 *
 *   template <int dim>
 *   SymmetricTensor<2, dim> Magnetoelastic_Constitutive_Law<dim>::get_DD() const
 *   {
 *     return BB;
 *   }
 *
 *   template <int dim>
 *   Tensor<3, dim> Magnetoelastic_Constitutive_Law<dim>::get_PP() const
 *   {
 *     return PP;
 *   }
 *
 *   template <int dim>
 *   SymmetricTensor<4, dim> Magnetoelastic_Constitutive_Law<dim>::get_HH() const
 *   {
 *     return HH;
 *   }
 *
 *
 * @endcode
 *
 * <a name="Magnetoviscoelasticconstitutivelawhandderived"></a>
 * <h4>Magneto-viscoelastic constitutive law (hand-derived)</h4>。
 *
 * 如前所述，我们将考虑的具有一种耗散机制的磁涡流材料的自由能密度函数被定义为@f[
 * \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v}, \boldsymbol{\mathbb{H}}
 * \right)
 * = \psi_{0}^{ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * + \psi_{0}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)
 * @f] @f[
 * \psi_{0}^{ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right) =
 * \frac{1}{2} \mu_{e} f_{\mu_{e}^{ME}} \left( \boldsymbol{\mathbb{H}} \right)
 * \left[ \text{tr}(\mathbf{C})
 *
 * - d
 *
 * - 2 \ln (\text{det}(\mathbf{F})) \right] + \lambda_{e} \ln^{2}
 * \left(\text{det}(\mathbf{F}) \right)
 *
 *
 *
 * - \frac{1}{2} \mu_{0} \mu_{r} \text{det}(\mathbf{F}) \left[
 * \boldsymbol{\mathbb{H}} \cdot \mathbf{C}^{-1} \cdot \boldsymbol{\mathbb{H}}
 * \right]
 * @f] @f[
 * \psi_{0}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v}, \boldsymbol{\mathbb{H}}
 * \right) = \frac{1}{2} \mu_{v} f_{\mu_{v}^{MVE}} \left(
 * \boldsymbol{\mathbb{H}} \right) \left[ \mathbf{C}_{v} : \left[
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}} \mathbf{C}
 * \right]
 *
 * - d
 *
 * - \ln\left( \text{det}\left(\mathbf{C}_{v}\right) \right)  \right]
 * @f]，其中有@f[
 * f_{\mu_{e}}^{ME} \left( \boldsymbol{\mathbb{H}} \right) = 1 + \left[
 * \frac{\mu_{e}^{\infty}}{\mu_{e}}
 *
 * - 1 \right] \tanh \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}} {\left(h_{e}^{\text{sat}}\right)^{2}} \right)
 * @f] @f[
 * f_{\mu_{v}}^{MVE} \left( \boldsymbol{\mathbb{H}} \right) = 1 + \left[
 * \frac{\mu_{v}^{\infty}}{\mu_{v}}
 *
 * - 1 \right] \tanh \left( 2 \frac{\boldsymbol{\mathbb{H}} \cdot
 * \boldsymbol{\mathbb{H}}} {\left(h_{v}^{\text{sat}}\right)^{2}} \right)
 * @f]和演变规律@f[
 * \dot{\mathbf{C}}_{v} \left( \mathbf{C} \right) = \frac{1}{\tau} \left[
 * \left[\left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C}\right]^{-1}
 *
 *
 *
 * - \mathbf{C}_{v} \right] @f]，其本身是以 $\mathbf{C}$
 * 为参数。根据设计，能量 $\psi_{0}^{ME} \left( \mathbf{C},
 * \boldsymbol{\mathbb{H}} \right)$
 * 的磁弹性部分与前面介绍的磁弹性材料的磁弹性部分是相同的。因此，对于源于这部分能量的各种贡献的导数，请参考前面的章节。我们将继续强调来自这些条款的具体贡献，用
 * $ME$
 * 对突出的条款进行上标，而来自磁弹性部分的贡献则用
 * $MVE$ 进行上标。此外，阻尼项的磁饱和函数
 * $f_{\mu_{v}}^{MVE} \left( \boldsymbol{\mathbb{H}} \right)$
 * 与弹性项的形式相同（即 $f_{\mu_{e}}^{ME} \left(
 * \boldsymbol{\mathbb{H}} \right)$
 * ），因此其导数的结构与之前看到的相同；唯一的变化是三个构成参数，现在与粘性剪切模量
 * $\mu_{v}$ 而不是弹性剪切模量 $\mu_{e}$ 相关。
 * 对于这种磁-粘弹性材料，对应于磁感应矢量和总Piola-Kirchhoff应力张量的第一导数是@f[
 * \boldsymbol{\mathbb{B}} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)
 * \dealcoloneq
 *
 * - \frac{\partial \psi_{0} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)}{\partial \boldsymbol{\mathbb{H}}}
 * \Big\vert_{\mathbf{C}, \mathbf{C}_{v}} \equiv
 * \boldsymbol{\mathbb{B}}^{ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}}
 * \right)
 * + \boldsymbol{\mathbb{B}}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right) =
 *
 *
 *
 *
 *
 * - \frac{d \psi_{0}^{ME} \left(
 * \mathbf{C}, \boldsymbol{\mathbb{H}} \right)}{d \boldsymbol{\mathbb{H}}}
 *
 *
 *
 *
 *
 * - \frac{\partial \psi_{0}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)}{\partial \boldsymbol{\mathbb{H}}}
 * @f] @f[
 * \mathbf{S}^{\text{tot}} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right) \dealcoloneq 2 \frac{\partial \psi_{0}
 * \left( \mathbf{C}, \mathbf{C}_{v}, \boldsymbol{\mathbb{H}}
 * \right)}{\partial \mathbf{C}} \Big\vert_{\mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}}} \equiv \mathbf{S}^{\text{tot}, ME} \left(
 * \mathbf{C}, \boldsymbol{\mathbb{H}} \right) + \mathbf{S}^{\text{tot}, MVE}
 * \left( \mathbf{C}, \mathbf{C}_{v}, \boldsymbol{\mathbb{H}} \right) =  2
 * \frac{d \psi_{0}^{ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)}{d
 * \mathbf{C}} + 2 \frac{\partial \psi_{0}^{MVE} \left( \mathbf{C},
 * \mathbf{C}_{v}, \boldsymbol{\mathbb{H}} \right)}{\partial \mathbf{C}}
 * @f]，粘性贡献是@f[
 * \boldsymbol{\mathbb{B}}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right) =
 *
 * - \frac{\partial \psi_{0}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)}{\partial \boldsymbol{\mathbb{H}}}
 * \Big\vert_{\mathbf{C}, \mathbf{C}_{v}} =
 *
 * - \frac{1}{2} \mu_{v} \left[ \mathbf{C}_{v} : \left[
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}} \mathbf{C}
 * \right]
 *
 * - d
 *
 * - \ln\left( \text{det}\left(\mathbf{C}_{v}\right) \right)  \right]
 * \frac{\partial f_{\mu_{v}^{MVE}} \left( \boldsymbol{\mathbb{H}}
 * \right)}{\partial \boldsymbol{\mathbb{H}}}
 * @f] @f[
 * \mathbf{S}^{\text{tot}, MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right) = 2 \frac{\partial \psi_{0}^{MVE} \left(
 * \mathbf{C}, \mathbf{C}_{v}, \boldsymbol{\mathbb{H}} \right)}{\partial
 * \mathbf{C}} \Big\vert_{\mathbf{C}_{v}, \boldsymbol{\mathbb{H}}} = \mu_{v}
 * f_{\mu_{v}^{MVE}} \left( \boldsymbol{\mathbb{H}} \right) \left[  \left[
 * \mathbf{C}_{v} : \mathbf{C} \right] \left[
 *
 * - \frac{1}{d} \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C}^{-1} \right] +
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C}_{v} \right]
 * @f]，而@f[
 * \frac{\partial f_{\mu_{v}^{MVE}} \left( \boldsymbol{\mathbb{H}}
 * \right)}{\partial \boldsymbol{\mathbb{H}}} \equiv \frac{d f_{\mu_{v}^{MVE}}
 * \left( \boldsymbol{\mathbb{H}} \right)}{d \boldsymbol{\mathbb{H}}} .
 * @f]的时间分解进化律，@f[
 * \mathbf{C}_{v}^{(t)} \left( \mathbf{C} \right) = \frac{1}{1 + \frac{\Delta
 * t}{\tau_{v}}} \left[ \mathbf{C}_{v}^{(t-1)} + \frac{\Delta t}{\tau_{v}}
 * \left[\left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C} \right]^{-1} \right]
 * @f]也将决定内部变量相对于场变量的线性化是如何构成。
 * 请注意，为了获得这种耗散材料的磁感应矢量和总Piola-Kirchhoff应力张量的正确*表达式，我们必须严格遵守应用Coleman-Noll程序的结果：我们必须对自由能密度函数进行部分导数*。
 * 的自由能密度函数与场变量的关系。对于我们的非耗散性磁弹性材料，取部分导数或总导数都会有同样的结果，所以之前没有必要提请你注意这一点）。该操作的关键部分是冻结内部变量
 * $\mathbf{C}_{v}^{(t)} \left( \mathbf{C} \right)$ ，同时计算
 * $\psi_{0}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v} \left( \mathbf{C}
 * \right), \boldsymbol{\mathbb{H}} \right)$ 相对于 $\mathbf{C}$
 * 的导数。
 *
 * - 不考虑 $\mathbf{C}_{v}^{(t)}$ 对 $\mathbf{C}$ 的依赖性。当决定使用AD或SD来执行这项任务时，选择是明确的
 *
 * - 只有符号框架提供了这样的机制；如前所述，AD只能返回总导数，所以它不适合这个任务。
 * 总结一下，我们将介绍这种速度依赖的耦合材料的材料切线。两个动力学变量相对于其参数的线性化是@f[
 * \mathbb{D} \left( \mathbf{C}, \mathbf{C}_{v}, \boldsymbol{\mathbb{H}}
 * \right) = \frac{d \boldsymbol{\mathbb{B}}}{d \boldsymbol{\mathbb{H}}}
 * \equiv \mathbb{D}^{ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}} \right)
 * + \mathbb{D}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right) = \frac{d \boldsymbol{\mathbb{B}}^{ME}}{d
 * \boldsymbol{\mathbb{H}}}
 * + \frac{d \boldsymbol{\mathbb{B}}^{MVE}}{d \boldsymbol{\mathbb{H}}}
 * @f] @f[
 * \mathfrak{P}^{\text{tot}} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right) =
 *
 * - \frac{d \mathbf{S}^{\text{tot}}}{d \boldsymbol{\mathbb{H}}} \equiv
 * \mathfrak{P}^{\text{tot}, ME} \left( \mathbf{C}, \boldsymbol{\mathbb{H}}
 * \right) + \mathfrak{P}^{\text{tot}, MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right) =
 *
 * - \frac{d \mathbf{S}^{\text{tot}, ME}}{d \boldsymbol{\mathbb{H}}}
 *
 *
 *
 * - \frac{d \mathbf{S}^{\text{tot}, MVE}}{d \boldsymbol{\mathbb{H}}}
 * @f] @f[
 * \mathcal{H}^{\text{tot}} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right) = 2 \frac{d \mathbf{S}^{\text{tot}}}{d
 * \mathbf{C}} \equiv \mathcal{H}^{\text{tot}, ME} \left( \mathbf{C},
 * \boldsymbol{\mathbb{H}} \right) + \mathcal{H}^{\text{tot}, MVE} \left(
 * \mathbf{C}, \mathbf{C}_{v}, \boldsymbol{\mathbb{H}} \right) = 2 \frac{d
 * \mathbf{S}^{\text{tot}, ME}}{d \mathbf{C}} + 2 \frac{d
 * \mathbf{S}^{\text{tot}, MVE}}{d \mathbf{C}}
 * @f]，其中粘性贡献的切线是@f[
 * \mathbb{D}^{MVE} \left( \mathbf{C}, \mathbf{C}_{v}, \boldsymbol{\mathbb{H}}
 * \right) =
 *
 * - \frac{1}{2} \mu_{v} \left[ \mathbf{C}_{v} : \left[
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}} \mathbf{C}
 * \right]
 *
 * - d
 *
 * - \ln\left( \text{det}\left(\mathbf{C}_{v}\right) \right)  \right]
 * \frac{\partial^{2} f_{\mu_{v}^{MVE}} \left( \boldsymbol{\mathbb{H}}
 * \right)}{\partial \boldsymbol{\mathbb{H}} \otimes d
 * \boldsymbol{\mathbb{H}}}
 * @f] @f[
 * \mathfrak{P}^{\text{tot}, MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right) =
 *
 * - \mu_{v} \left[  \left[ \mathbf{C}_{v} : \mathbf{C} \right] \left[
 *
 * - \frac{1}{d} \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C}^{-1} \right] +
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C}_{v} \right] \otimes \frac{d f_{\mu_{v}^{MVE}} \left(
 * \boldsymbol{\mathbb{H}} \right)}{d \boldsymbol{\mathbb{H}}} @f] 。
 * @f{align}
 * \mathcal{H}^{\text{tot}, MVE} \left( \mathbf{C}, \mathbf{C}_{v},
 * \boldsymbol{\mathbb{H}} \right)
 * &= 2 \mu_{v} f_{\mu_{v}^{MVE}} \left( \boldsymbol{\mathbb{H}} \right)
 * \left[
 *
 * - \frac{1}{d}
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C}^{-1} \right] \otimes
 * \left[ \mathbf{C}_{v} + \mathbf{C} : \frac{d \mathbf{C}_{v}}{d
 * \mathbf{C}} \right]
 * \\ &+ 2 \mu_{v} f_{\mu_{v}^{MVE}} \left( \boldsymbol{\mathbb{H}} \right)
 * \left[ \mathbf{C}_{v} : \mathbf{C} \right]
 * \left[
 * \frac{1}{d^{2}}
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C}^{-1} \otimes \mathbf{C}^{-1}
 *
 *
 *
 *
 *
 * - \frac{1}{d}
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}} \frac{d
 * \mathbf{C}^{-1}}{d \mathbf{C}}
 * \right]
 * \\ &+ 2 \mu_{v} f_{\mu_{v}^{MVE}} \left( \boldsymbol{\mathbb{H}} \right)
 * \left[
 *
 *
 *
 *
 *
 * -\frac{1}{d}
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \mathbf{C}_{v} \otimes \mathbf{C}^{-1}
 * + \left[\text{det}\left(\mathbf{F}\right)\right]^{-\frac{2}{d}}
 * \frac{d \mathbf{C}_{v}}{d \mathbf{C}}
 * \right]
 * @f}
 * *与@f[
 * \frac{\partial^{2} f_{\mu_{v}^{MVE}} \left( \boldsymbol{\mathbb{H}}
 * \right)}{\partial \boldsymbol{\mathbb{H}} \otimes
 * d \boldsymbol{\mathbb{H}}} \equiv \frac{d^{2} f_{\mu_{v}^{MVE}} \left(
 * \boldsymbol{\mathbb{H}} \right)}{d \boldsymbol{\mathbb{H}} \otimes d
 * \boldsymbol{\mathbb{H}}}
 * @f]，从演化规律来看，@f[
 * \frac{d \mathbf{C}_{v}}{d \mathbf{C}} \equiv \frac{d
 * \mathbf{C}_{v}^{(t)}}{d \mathbf{C}} = \frac{\frac{\Delta t}{\tau_{v}} }{1 +
 * \frac{\Delta t}{\tau_{v}}} \left[ \frac{1}{d}
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{\frac{2}{d}}
 * \mathbf{C}^{-1} \otimes \mathbf{C}^{-1} +
 * \left[\text{det}\left(\mathbf{F}\right)\right]^{\frac{2}{d}} \frac{d
 * \mathbf{C}^{-1}}{d \mathbf{C}} \right] . @f]注意，只是
 * $\mathcal{H}^{\text{tot}, MVE}$
 * 的最后一项包含了内部变量的切线。这个特殊演化规律的线性化是线性的。关于非线性演化定律的例子，这种线性化必须以迭代的方式求解，见
 * @cite Koprowski  -Theiss2011a。
 *
 * @code
 *   template <int dim>
 *   class Magnetoviscoelastic_Constitutive_Law final
 *     : public Coupled_Magnetomechanical_Constitutive_Law_Base<dim>
 *   {
 *   public:
 *     Magnetoviscoelastic_Constitutive_Law(
 *       const ConstitutiveParameters &constitutive_parameters);
 *
 *     virtual void update_internal_data(const SymmetricTensor<2, dim> &C,
 *                                       const Tensor<1, dim> &         H,
 *                                       const DiscreteTime &time) override;
 *
 *     virtual double get_psi() const override;
 *
 *     virtual Tensor<1, dim> get_B() const override;
 *
 *     virtual SymmetricTensor<2, dim> get_S() const override;
 *
 *     virtual SymmetricTensor<2, dim> get_DD() const override;
 *
 *     virtual Tensor<3, dim> get_PP() const override;
 *
 *     virtual SymmetricTensor<4, dim> get_HH() const override;
 *
 *     virtual void update_end_of_timestep() override;
 *
 *   private:
 *     SymmetricTensor<2, dim> Q_t;
 *     SymmetricTensor<2, dim> Q_t1;
 *
 *     double                  psi;
 *     Tensor<1, dim>          B;
 *     SymmetricTensor<2, dim> S;
 *     SymmetricTensor<2, dim> BB;
 *     Tensor<3, dim>          PP;
 *     SymmetricTensor<4, dim> HH;
 *
 * @endcode
 *
 * 一个用于存储所有中间计算的数据结构。我们很快就会准确地看到如何利用这一点，使我们实际进行计算的那部分代码变得干净和容易（嗯，至少更容易）遵循和维护。但是现在，我们可以说，它将允许我们把计算中间量的导数的代码部分从使用它们的地方移开。
 *
 * @code
 *     mutable GeneralDataStorage cache;
 *
 * @endcode
 *
 * 接下来的两个函数用于更新字段和内部变量的状态，在我们进行任何详细的计算之前会被调用。
 *
 * @code
 *     void set_primary_variables(const SymmetricTensor<2, dim> &C,
 *                                const Tensor<1, dim> &         H) const;
 *
 *     void update_internal_variable(const DiscreteTime &time);
 *
 * @endcode
 *
 * 该类接口的其余部分专门用于计算自由能密度函数及其所有导数所需的组件的方法。
 *
 *
 * 运动学的，或场的变量。
 *
 * @code
 *     const Tensor<1, dim> &get_H() const;
 *
 *     const SymmetricTensor<2, dim> &get_C() const;
 *
 * @endcode
 *
 * 饱和度函数的一般化表述，所需的构成参数作为参数传递给每个函数。
 *
 * @code
 *     double get_two_h_dot_h_div_h_sat_squ(const double mu_h_sat) const;
 *
 *     double get_tanh_two_h_dot_h_div_h_sat_squ(const double mu_h_sat) const;
 *
 *     double get_f_mu(const double mu,
 *                     const double mu_inf,
 *                     const double mu_h_sat) const;
 *
 * @endcode
 *
 * 饱和度函数的一阶导数的一般化表述，所需的构成参数作为参数传递给每个函数。
 *
 * @code
 *     double get_dtanh_two_h_dot_h_div_h_sat_squ(const double mu_h_sat) const;
 *
 *     Tensor<1, dim>
 *     get_dtwo_h_dot_h_div_h_sat_squ_dH(const double mu_h_sat) const;
 *
 *     Tensor<1, dim> get_df_mu_dH(const double mu,
 *                                 const double mu_inf,
 *                                 const double mu_h_sat) const;
 *
 * @endcode
 *
 * 饱和度函数二阶导数的一般化表述，所需的构成参数作为参数传递给每个函数。
 *
 * @code
 *     double get_d2tanh_two_h_dot_h_div_h_sat_squ(const double mu_h_sat) const;
 *
 *     SymmetricTensor<2, dim>
 *     get_d2two_h_dot_h_div_h_sat_squ_dH_dH(const double mu_h_sat) const;
 *
 *     SymmetricTensor<2, dim> get_d2f_mu_dH_dH(const double mu,
 *                                              const double mu_inf,
 *                                              const double mu_h_sat) const;
 *
 * @endcode
 *
 * 直接从场/运动学变量中获得的中间量。
 *
 * @code
 *     const double &get_det_F() const;
 *
 *     const SymmetricTensor<2, dim> &get_C_inv() const;
 *
 *     const double &get_log_det_F() const;
 *
 *     const double &get_trace_C() const;
 *
 *     const Tensor<1, dim> &get_C_inv_dot_H() const;
 *
 *     const double &get_H_dot_C_inv_dot_H() const;
 *
 * @endcode
 *
 * 中间量的一阶导数。
 *
 * @code
 *     const SymmetricTensor<4, dim> &get_dC_inv_dC() const;
 *
 *     const SymmetricTensor<2, dim> &get_d_tr_C_dC() const;
 *
 *     const SymmetricTensor<2, dim> &get_ddet_F_dC() const;
 *
 *     const SymmetricTensor<2, dim> &get_dlog_det_F_dC() const;
 *
 *     const Tensor<1, dim> &get_dH_dot_C_inv_dot_H_dH() const;
 *
 *     const SymmetricTensor<2, dim> &get_dH_dot_C_inv_dot_H_dC() const;
 *
 * @endcode
 *
 * 内部变量相对于场变量的导数。注意，我们只需要这个内部变量的导数，因为这个变量只是作为动力学变量线性化的一部分而被微分。
 *
 * @code
 *     const SymmetricTensor<4, dim> &
 *     get_dQ_t_dC(const DiscreteTime &time) const;
 *
 * @endcode
 *
 * 中间量的二阶导数。
 *
 * @code
 *     const SymmetricTensor<4, dim> &get_d2log_det_F_dC_dC() const;
 *
 *     const SymmetricTensor<4, dim> &get_d2det_F_dC_dC() const;
 *
 *     const SymmetricTensor<2, dim> &get_d2H_dot_C_inv_dot_H_dH_dH() const;
 *
 *     const Tensor<3, dim> &get_d2H_dot_C_inv_dot_H_dC_dH() const;
 *
 *     const SymmetricTensor<4, dim> &get_d2H_dot_C_inv_dot_H_dC_dC() const;
 *   };
 *
 *
 *   template <int dim>
 *   Magnetoviscoelastic_Constitutive_Law<
 *     dim>::Magnetoviscoelastic_Constitutive_Law(const ConstitutiveParameters
 *                                                  &constitutive_parameters)
 *     : Coupled_Magnetomechanical_Constitutive_Law_Base<dim>(
 *         constitutive_parameters)
 *     , Q_t(Physics::Elasticity::StandardTensors<dim>::I)
 *     , Q_t1(Physics::Elasticity::StandardTensors<dim>::I)
 *     , psi(0.0)
 *   {}
 *
 *
 *   template <int dim>
 *   void Magnetoviscoelastic_Constitutive_Law<dim>::update_internal_data(
 *     const SymmetricTensor<2, dim> &C,
 *     const Tensor<1, dim> &         H,
 *     const DiscreteTime &           time)
 *   {
 * @endcode
 *
 * 记录应用的变形状态以及磁载荷。此后，根据新的变形状态更新内部（粘性）变量。
 *
 * @code
 *     set_primary_variables(C, H);
 *     update_internal_variable(time);
 *
 * @endcode
 *
 * 根据当前磁场获得弹性和粘性饱和函数的值...
 *
 * @code
 *     const double f_mu_e = get_f_mu(this->get_mu_e(),
 *                                    this->get_mu_e_inf(),
 *                                    this->get_mu_e_h_sat());
 *
 *     const double f_mu_v = get_f_mu(this->get_mu_v(),
 *                                    this->get_mu_v_inf(),
 *                                    this->get_mu_v_h_sat());
 *
 * @endcode
 *
 * ...以及它们的第一个导数...
 * @code
 *     const Tensor<1, dim> df_mu_e_dH = get_df_mu_dH(this->get_mu_e(),
 *                                                    this->get_mu_e_inf(),
 *                                                    this->get_mu_e_h_sat());
 *
 *     const Tensor<1, dim> df_mu_v_dH = get_df_mu_dH(this->get_mu_v(),
 *                                                    this->get_mu_v_inf(),
 *                                                    this->get_mu_v_h_sat());
 *
 *
 * @endcode
 *
 * ......和它们的二阶导数。
 *
 * @code
 *     const SymmetricTensor<2, dim> d2f_mu_e_dH_dH =
 *       get_d2f_mu_dH_dH(this->get_mu_e(),
 *                        this->get_mu_e_inf(),
 *                        this->get_mu_e_h_sat());
 *
 *     const SymmetricTensor<2, dim> d2f_mu_v_dH_dH =
 *       get_d2f_mu_dH_dH(this->get_mu_v(),
 *                        this->get_mu_v_inf(),
 *                        this->get_mu_v_h_sat());
 *
 * @endcode
 *
 * 中间量。请注意，由于我们是从一个缓存中获取这些值，而这个缓存的寿命比这个函数调用的寿命长，所以我们可以对结果进行别名，而不是从缓存中复制这个值。
 *
 * @code
 *     const double &                 det_F = get_det_F();
 *     const SymmetricTensor<2, dim> &C_inv = get_C_inv();
 *
 *     const double &log_det_F         = get_log_det_F();
 *     const double &tr_C              = get_trace_C();
 *     const double &H_dot_C_inv_dot_H = get_H_dot_C_inv_dot_H();
 *
 * @endcode
 *
 * 中间值的第一导数，以及内部变量相对于右Cauchy-Green变形张量的那个导数。
 *
 * @code
 *     const SymmetricTensor<2, dim> &d_tr_C_dC     = get_d_tr_C_dC();
 *     const SymmetricTensor<2, dim> &ddet_F_dC     = get_ddet_F_dC();
 *     const SymmetricTensor<2, dim> &dlog_det_F_dC = get_dlog_det_F_dC();
 *
 *     const SymmetricTensor<4, dim> &dQ_t_dC = get_dQ_t_dC(time);
 *
 *     const Tensor<1, dim> &dH_dot_C_inv_dot_H_dH = get_dH_dot_C_inv_dot_H_dH();
 *
 *     const SymmetricTensor<2, dim> &dH_dot_C_inv_dot_H_dC =
 *       get_dH_dot_C_inv_dot_H_dC();
 *
 * @endcode
 *
 * 中间值的二次导数。
 *
 * @code
 *     const SymmetricTensor<4, dim> &d2log_det_F_dC_dC =
 *       get_d2log_det_F_dC_dC();
 *
 *     const SymmetricTensor<4, dim> &d2det_F_dC_dC = get_d2det_F_dC_dC();
 *
 *     const SymmetricTensor<2, dim> &d2H_dot_C_inv_dot_H_dH_dH =
 *       get_d2H_dot_C_inv_dot_H_dH_dH();
 *
 *     const Tensor<3, dim> &d2H_dot_C_inv_dot_H_dC_dH =
 *       get_d2H_dot_C_inv_dot_H_dC_dH();
 *
 *     const SymmetricTensor<4, dim> &d2H_dot_C_inv_dot_H_dC_dC =
 *       get_d2H_dot_C_inv_dot_H_dC_dC();
 *
 * @endcode
 *
 * 由于线性化的定义变得特别冗长，我们将把自由能密度函数分解为三个相加的部分。
 *
 *
 * - 类似 "新胡克 "的术语。
 *
 *
 * - 与速率有关的条款，以及
 *
 *
 * - 类似于储存在磁场中的能量的术语。
 * 为了保持一致，这些贡献中的每一个都将被单独添加到我们想要计算的变量中，其顺序也是如此。
 * 所以，首先这是能量密度函数本身。
 *
 * @code
 *     psi = (0.5 this->get_mu_e() f_mu_e)
 *             (tr_C
 *
 * - dim
 *
 * - 2.0 std::log(det_F)) +
 *           this->get_lambda_e() (std::log(det_F) std::log(det_F));
 *     psi += (0.5 this->get_mu_v() f_mu_v)
 *            (Q_t (std::pow(det_F,
 *
 * -2.0 / dim) C)
 *
 * - dim
 *
 * -
 *             std::log(determinant(Q_t)));
 *     psi
 *
 * -=
 *       (0.5 this->get_mu_0() this->get_mu_r()) det_F (H C_inv H);
 *
 * @endcode
 *
 * ......接着是磁感应矢量和Piola-Kirchhoff应力。
 *
 * @code
 *     B =
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
 * -(0.5 this->get_mu_e() (tr_C
 *
 * - dim
 *
 * - 2.0 log_det_F)) df_mu_e_dH;
 *     B
 *
 * -= (0.5 this->get_mu_v())
 *          (Q_t (std::pow(det_F,
 *
 * -2.0 / dim) C)
 *
 * - dim
 *
 * -
 *           std::log(determinant(Q_t)))
 *          df_mu_v_dH;
 *     B += 0.5 this->get_mu_0() this->get_mu_r() det_F
 *          dH_dot_C_inv_dot_H_dH;
 *
 *     S = 2.0 (0.5 this->get_mu_e() f_mu_e)
 *           (d_tr_C_dC
 *
 * - 2.0 dlog_det_F_dC)
 *         + 2.0 this->get_lambda_e() (2.0 log_det_F dlog_det_F_dC);
 *     S += 2.0 (0.5 this->get_mu_v() f_mu_v)
 *          ((Q_t C)
 *             ((-2.0 / dim) std::pow(det_F,
 *
 * -2.0 / dim
 *
 * - 1.0) ddet_F_dC) +
 *           std::pow(det_F,
 *
 * -2.0 / dim) Q_t);                // dC/dC = II
 *     S
 *
 * -= 2.0 (0.5 this->get_mu_0() this->get_mu_r())
 *          (H_dot_C_inv_dot_H ddet_F_dC
 *           + det_F dH_dot_C_inv_dot_H_dC);
 *
 * @endcode
 *
 * ......最后是由于动能变量的线性化而产生的切线。
 *
 * @code
 *     BB =
 *
 * -(0.5 this->get_mu_e() (tr_C
 *
 * - dim
 *
 * - 2.0 log_det_F))
 *          d2f_mu_e_dH_dH;
 *     BB
 *
 * -= (0.5 this->get_mu_v())
 *           (Q_t (std::pow(det_F,
 *
 * -2.0 / dim) C)
 *
 * - dim
 *
 * -
 *            std::log(determinant(Q_t)))
 *           d2f_mu_v_dH_dH;
 *     BB += 0.5 this->get_mu_0() this->get_mu_r() det_F
 *           d2H_dot_C_inv_dot_H_dH_dH;
 *
 *     PP =
 *
 * -2.0 (0.5 this->get_mu_e())
 *          outer_product(Tensor<2, dim>(d_tr_C_dC
 *
 * - 2.0 dlog_det_F_dC),
 *                        df_mu_e_dH);
 *     PP
 *
 * -= 2.0 (0.5 this->get_mu_v())
 *           outer_product(Tensor<2, dim>((Q_t C)
 *                                          ((-2.0 / dim)
 *                                           std::pow(det_F,
 *
 * -2.0 / dim
 *
 * - 1.0)
 *                                           ddet_F_dC) +
 *                                        std::pow(det_F,
 *
 * -2.0 / dim) Q_t),
 *                         df_mu_v_dH);
 *     PP += 2.0 (0.5 this->get_mu_0() this->get_mu_r())
 *           (outer_product(Tensor<2, dim>(ddet_F_dC), dH_dot_C_inv_dot_H_dH) +
 *            det_F d2H_dot_C_inv_dot_H_dC_dH);
 *
 *     HH =
 *       4.0 (0.5 this->get_mu_e() f_mu_e) (-2.0 d2log_det_F_dC_dC)
 *       + 4.0 this->get_lambda_e()
 *           (2.0 outer_product(dlog_det_F_dC, dlog_det_F_dC)
 *            + 2.0 log_det_F d2log_det_F_dC_dC);
 *     HH += 4.0 (0.5 this->get_mu_v() f_mu_v)
 *           (outer_product((-2.0 / dim) std::pow(det_F,
 *
 * -2.0 / dim
 *
 * - 1.0)
 *                            ddet_F_dC,
 *                          C dQ_t_dC + Q_t) +
 *            (Q_t C)
 *              (outer_product(ddet_F_dC,
 *                             (-2.0 / dim) (-2.0 / dim
 *
 * - 1.0)
 *                               std::pow(det_F,
 *
 * -2.0 / dim
 *
 * - 2.0) ddet_F_dC) +
 *               ((-2.0 / dim) std::pow(det_F,
 *
 * -2.0 / dim
 *
 * - 1.0)
 *                d2det_F_dC_dC)) +
 *            outer_product(Q_t,
 *                          (-2.0 / dim) std::pow(det_F,
 *
 * -2.0 / dim
 *
 * - 1.0)
 *                            ddet_F_dC) +
 *            std::pow(det_F,
 *
 * -2.0 / dim) dQ_t_dC);
 *     HH
 *
 * -= 4.0 (0.5 this->get_mu_0() this->get_mu_r())
 *           (H_dot_C_inv_dot_H d2det_F_dC_dC
 *            + outer_product(ddet_F_dC, dH_dot_C_inv_dot_H_dC)
 *            + outer_product(dH_dot_C_inv_dot_H_dC, ddet_F_dC)
 *            + det_F d2H_dot_C_inv_dot_H_dC_dC);
 *
 *
 * @endcode
 *
 * 现在我们已经用完了存储在缓存中的所有临时变量，我们可以把它清除掉，以释放一些内存。
 *
 * @code
 *     cache.reset();
 *   }
 *
 *   template <int dim>
 *   double Magnetoviscoelastic_Constitutive_Law<dim>::get_psi() const
 *   {
 *     return psi;
 *   }
 *
 *
 *   template <int dim>
 *   Tensor<1, dim> Magnetoviscoelastic_Constitutive_Law<dim>::get_B() const
 *   {
 *     return B;
 *   }
 *
 *
 *   template <int dim>
 *   SymmetricTensor<2, dim>
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_S() const
 *   {
 *     return S;
 *   }
 *
 *
 *   template <int dim>
 *   SymmetricTensor<2, dim>
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_DD() const
 *   {
 *     return BB;
 *   }
 *
 *
 *   template <int dim>
 *   Tensor<3, dim> Magnetoviscoelastic_Constitutive_Law<dim>::get_PP() const
 *   {
 *     return PP;
 *   }
 *
 *
 *   template <int dim>
 *   SymmetricTensor<4, dim>
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_HH() const
 *   {
 *     return HH;
 *   }
 *
 *
 *   template <int dim>
 *   void Magnetoviscoelastic_Constitutive_Law<dim>::update_end_of_timestep()
 *   {
 *     Q_t1 = Q_t;
 *   }
 *
 *
 *   template <int dim>
 *   void Magnetoviscoelastic_Constitutive_Law<dim>::update_internal_variable(
 *     const DiscreteTime &time)
 *   {
 *     const double delta_t = this->get_delta_t(time);
 *
 *     Q_t = (1.0 / (1.0 + delta_t / this->get_tau_v()))
 *           (Q_t1 + (delta_t / this->get_tau_v())
 *                     std::pow(get_det_F(), 2.0 / dim) get_C_inv());
 *   }
 *
 * @endcode
 *
 * 接下来的几个函数实现了饱和度函数的广义表述，以及它的各种导数。
 *
 * @code
 *   template <int dim>
 *   double
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_two_h_dot_h_div_h_sat_squ(
 *     const double mu_h_sat) const
 *   {
 *     const Tensor<1, dim> &H = get_H();
 *     return (2.0 H H) / (mu_h_sat mu_h_sat);
 *   }
 *
 *
 *   template <int dim>
 *   double Magnetoviscoelastic_Constitutive_Law<
 *     dim>::get_tanh_two_h_dot_h_div_h_sat_squ(const double mu_h_sat) const
 *   {
 *     return std::tanh(get_two_h_dot_h_div_h_sat_squ(mu_h_sat));
 *   }
 *
 * @endcode
 *
 * 一个比例函数，它将使剪切模量在磁场的影响下发生变化（增加）。
 *
 * @code
 *   template <int dim>
 *   double Magnetoviscoelastic_Constitutive_Law<dim>::get_f_mu(
 *     const double mu,
 *     const double mu_inf,
 *     const double mu_h_sat) const
 *   {
 *     return 1.0 +
 *            (mu_inf / mu
 *
 * - 1.0) get_tanh_two_h_dot_h_div_h_sat_squ(mu_h_sat);
 *   }
 *
 * @endcode
 *
 * 缩放函数的一阶导数
 *
 * @code
 *   template <int dim>
 *   double Magnetoviscoelastic_Constitutive_Law<
 *     dim>::get_dtanh_two_h_dot_h_div_h_sat_squ(const double mu_h_sat) const
 *   {
 *     return std::pow(1.0 / std::cosh(get_two_h_dot_h_div_h_sat_squ(mu_h_sat)),
 *                     2.0);
 *   }
 *
 *
 *   template <int dim>
 *   Tensor<1, dim> Magnetoviscoelastic_Constitutive_Law<
 *     dim>::get_dtwo_h_dot_h_div_h_sat_squ_dH(const double mu_h_sat) const
 *   {
 *     return 2.0 2.0 / (mu_h_sat mu_h_sat) get_H();
 *   }
 *
 *
 *   template <int dim>
 *   Tensor<1, dim> Magnetoviscoelastic_Constitutive_Law<dim>::get_df_mu_dH(
 *     const double mu,
 *     const double mu_inf,
 *     const double mu_h_sat) const
 *   {
 *     return (mu_inf / mu
 *
 * - 1.0)
 *            (get_dtanh_two_h_dot_h_div_h_sat_squ(mu_h_sat)
 *             get_dtwo_h_dot_h_div_h_sat_squ_dH(mu_h_sat));
 *   }
 *
 *
 *   template <int dim>
 *   double Magnetoviscoelastic_Constitutive_Law<
 *     dim>::get_d2tanh_two_h_dot_h_div_h_sat_squ(const double mu_h_sat) const
 *   {
 *     return
 *
 * -2.0 get_tanh_two_h_dot_h_div_h_sat_squ(mu_h_sat)
 *            get_dtanh_two_h_dot_h_div_h_sat_squ(mu_h_sat);
 *   }
 *
 *
 *   template <int dim>
 *   SymmetricTensor<2, dim> Magnetoviscoelastic_Constitutive_Law<
 *     dim>::get_d2two_h_dot_h_div_h_sat_squ_dH_dH(const double mu_h_sat) const
 *   {
 *     return 2.0 2.0 / (mu_h_sat mu_h_sat)
 *            Physics::Elasticity::StandardTensors<dim>::I;
 *   }
 *
 *
 *   template <int dim>
 *   SymmetricTensor<2, dim>
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_d2f_mu_dH_dH(
 *     const double mu,
 *     const double mu_inf,
 *     const double mu_h_sat) const
 *   {
 *     return (mu_inf / mu
 *
 * - 1.0)
 *            (get_d2tanh_two_h_dot_h_div_h_sat_squ(mu_h_sat)
 *               symmetrize(
 *                 outer_product(get_dtwo_h_dot_h_div_h_sat_squ_dH(mu_h_sat),
 *                               get_dtwo_h_dot_h_div_h_sat_squ_dH(mu_h_sat))) +
 *             get_dtanh_two_h_dot_h_div_h_sat_squ(mu_h_sat)
 *               get_d2two_h_dot_h_div_h_sat_squ_dH_dH(mu_h_sat));
 *   }
 *
 * @endcode
 *
 * 对于我们为这个材料类采用的缓存计算方法，所有计算的根基是场变量，以及不可改变的辅助数据，如构成参数和时间步长等。因此，我们需要以与其他变量不同的方式将它们输入缓存，因为它们是由类本身之外规定的输入。这个函数只是将它们从输入参数中直接添加到缓存中，并检查那里是否有相等的数据（我们希望每个时间步长或牛顿迭代只调用一次`update_internal_data()`方法）。
 *
 * @code
 *   template <int dim>
 *   void Magnetoviscoelastic_Constitutive_Law<dim>::set_primary_variables(
 *     const SymmetricTensor<2, dim> &C,
 *     const Tensor<1, dim> &         H) const
 *   {
 * @endcode
 *
 * 为 $\boldsymbol{\mathbb{H}}$ 设定值。
 *
 * @code
 *     const std::string name_H("H");
 *     Assert(!cache.stores_object_with_name(name_H),
 *            ExcMessage(
 *              "The primary variable has already been added to the cache."));
 *     cache.add_unique_copy(name_H, H);
 *
 * @endcode
 *
 * 为 $\mathbf{C}$ 设定值。
 *
 * @code
 *     const std::string name_C("C");
 *     Assert(!cache.stores_object_with_name(name_C),
 *            ExcMessage(
 *              "The primary variable has already been added to the cache."));
 *     cache.add_unique_copy(name_C, C);
 *   }
 *
 * @endcode
 *
 * 之后，我们可以在任何时间点从缓存中获取它们。
 *
 * @code
 *   template <int dim>
 *   const Tensor<1, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_H() const
 *   {
 *     const std::string name("H");
 *     Assert(cache.stores_object_with_name(name),
 *            ExcMessage("Primary variables must be added to the cache."));
 *     return cache.template get_object_with_name<Tensor<1, dim>>(name);
 *   }
 *
 *   template <int dim>
 *   const SymmetricTensor<2, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_C() const
 *   {
 *     const std::string name("C");
 *     Assert(cache.stores_object_with_name(name),
 *            ExcMessage("Primary variables must be added to the cache."));
 *     return cache.template get_object_with_name<SymmetricTensor<2, dim>>(name);
 *   }
 *
 * @endcode
 *
 * 当我们需要主要变量时，保证它们在缓存中，我们不能从它们中计算出所有的中间值（无论是直接，还是间接）。
 * 如果缓存中还没有存储我们要找的值，那么我们就快速计算，把它存储在缓存中，然后返回刚刚存储在缓存中的值。这样我们就可以把它作为一个引用返回，避免复制对象。同样的道理也适用于复合函数可能依赖的任何值。换句话说，如果在我们目前感兴趣的计算之前有一个依赖链，那么在我们继续使用这些值之前，我们可以保证解决这些依赖关系。尽管从缓存中获取数据是有成本的，但
 * "已解决的依赖关系
 * "的概念可能足够方便，使其值得看一下这个额外的成本。如果这些材料定律被嵌入到有限元框架中，那么额外的成本甚至可能不会被注意到。
 *
 * @code
 *   template <int dim>
 *   const double &Magnetoviscoelastic_Constitutive_Law<dim>::get_det_F() const
 *   {
 *     const std::string name("det_F");
 *     if (cache.stores_object_with_name(name) == false)
 *       {
 *         const double det_F = std::sqrt(determinant(get_C()));
 *         AssertThrow(det_F > 0.0,
 *                     ExcMessage("Volumetric Jacobian must be positive."));
 *         cache.add_unique_copy(name, det_F);
 *       }
 *
 *     return cache.template get_object_with_name<double>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const SymmetricTensor<2, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_C_inv() const
 *   {
 *     const std::string name("C_inv");
 *     if (cache.stores_object_with_name(name) == false)
 *       {
 *         cache.add_unique_copy(name, invert(get_C()));
 *       }
 *
 *     return cache.template get_object_with_name<SymmetricTensor<2, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const double &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_log_det_F() const
 *   {
 *     const std::string name("log(det_F)");
 *     if (cache.stores_object_with_name(name) == false)
 *       cache.add_unique_copy(name, std::log(get_det_F()));
 *
 *     return cache.template get_object_with_name<double>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const double &Magnetoviscoelastic_Constitutive_Law<dim>::get_trace_C() const
 *   {
 *     const std::string name("trace(C)");
 *     if (cache.stores_object_with_name(name) == false)
 *       cache.add_unique_copy(name, trace(get_C()));
 *
 *     return cache.template get_object_with_name<double>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const Tensor<1, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_C_inv_dot_H() const
 *   {
 *     const std::string name("C_inv_dot_H");
 *     if (cache.stores_object_with_name(name) == false)
 *       cache.add_unique_copy(name, get_C_inv() get_H());
 *
 *     return cache.template get_object_with_name<Tensor<1, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const double &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_H_dot_C_inv_dot_H() const
 *   {
 *     const std::string name("H_dot_C_inv_dot_H");
 *     if (cache.stores_object_with_name(name) == false)
 *       cache.add_unique_copy(name, get_H() get_C_inv_dot_H());
 *
 *     return cache.template get_object_with_name<double>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const SymmetricTensor<4, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_dQ_t_dC(
 *     const DiscreteTime &time) const
 *   {
 *     const std::string name("dQ_t_dC");
 *     if (cache.stores_object_with_name(name) == false)
 *       {
 *         const double  delta_t = this->get_delta_t(time);
 *         const double &det_F   = get_det_F();
 *
 *         const SymmetricTensor<4, dim> dQ_t_dC =
 *           (1.0 / (1.0 + delta_t / this->get_tau_v()))
 *           (delta_t / this->get_tau_v())
 *           ((2.0 / dim) std::pow(det_F, 2.0 / dim
 *
 * - 1.0)
 *              outer_product(get_C_inv(), get_ddet_F_dC()) +
 *            std::pow(det_F, 2.0 / dim) get_dC_inv_dC());
 *
 *         cache.add_unique_copy(name, dQ_t_dC);
 *       }
 *
 *     return cache.template get_object_with_name<SymmetricTensor<4, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const SymmetricTensor<4, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_dC_inv_dC() const
 *   {
 *     const std::string name("dC_inv_dC");
 *     if (cache.stores_object_with_name(name) == false)
 *       {
 *         const SymmetricTensor<2, dim> &C_inv = get_C_inv();
 *         SymmetricTensor<4, dim>        dC_inv_dC;
 *
 *         for (unsigned int A = 0; A < dim; ++A)
 *           for (unsigned int B = A; B < dim; ++B)
 *             for (unsigned int C = 0; C < dim; ++C)
 *               for (unsigned int D = C; D < dim; ++D)
 *                 dC_inv_dC[A][B][C][D]
 *
 * -=
 *                   0.5 (C_inv[A][C] C_inv[B][D]
 *                          + C_inv[A][D] C_inv[B][C]);
 *
 *         cache.add_unique_copy(name, dC_inv_dC);
 *       }
 *
 *     return cache.template get_object_with_name<SymmetricTensor<4, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const SymmetricTensor<2, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_d_tr_C_dC() const
 *   {
 *     const std::string name("d_tr_C_dC");
 *     if (cache.stores_object_with_name(name) == false)
 *       cache.add_unique_copy(name,
 *                             Physics::Elasticity::StandardTensors<dim>::I);
 *
 *     return cache.template get_object_with_name<SymmetricTensor<2, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const SymmetricTensor<2, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_ddet_F_dC() const
 *   {
 *     const std::string name("ddet_F_dC");
 *     if (cache.stores_object_with_name(name) == false)
 *       cache.add_unique_copy(name, 0.5 get_det_F() get_C_inv());
 *
 *     return cache.template get_object_with_name<SymmetricTensor<2, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const SymmetricTensor<2, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_dlog_det_F_dC() const
 *   {
 *     const std::string name("dlog_det_F_dC");
 *     if (cache.stores_object_with_name(name) == false)
 *       cache.add_unique_copy(name, 0.5 get_C_inv());
 *
 *     return cache.template get_object_with_name<SymmetricTensor<2, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const Tensor<1, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_dH_dot_C_inv_dot_H_dH() const
 *   {
 *     const std::string name("dH_dot_C_inv_dot_H_dH");
 *     if (cache.stores_object_with_name(name) == false)
 *       cache.add_unique_copy(name, 2.0 get_C_inv_dot_H());
 *
 *     return cache.template get_object_with_name<Tensor<1, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const SymmetricTensor<2, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_dH_dot_C_inv_dot_H_dC() const
 *   {
 *     const std::string name("dH_dot_C_inv_dot_H_dC");
 *     if (cache.stores_object_with_name(name) == false)
 *       {
 *         const Tensor<1, dim> C_inv_dot_H = get_C_inv_dot_H();
 *         cache.add_unique_copy(
 *           name,
 *
 * -symmetrize(outer_product(C_inv_dot_H, C_inv_dot_H)));
 *       }
 *
 *     return cache.template get_object_with_name<SymmetricTensor<2, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const SymmetricTensor<4, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_d2log_det_F_dC_dC() const
 *   {
 *     const std::string name("d2log_det_F_dC_dC");
 *     if (cache.stores_object_with_name(name) == false)
 *       cache.add_unique_copy(name, 0.5 get_dC_inv_dC());
 *
 *     return cache.template get_object_with_name<SymmetricTensor<4, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const SymmetricTensor<4, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_d2det_F_dC_dC() const
 *   {
 *     const std::string name("d2det_F_dC_dC");
 *     if (cache.stores_object_with_name(name) == false)
 *       cache.add_unique_copy(name,
 *                             0.5
 *                               (outer_product(get_C_inv(), get_ddet_F_dC()) +
 *                                get_det_F() get_dC_inv_dC()));
 *
 *     return cache.template get_object_with_name<SymmetricTensor<4, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const SymmetricTensor<2, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_d2H_dot_C_inv_dot_H_dH_dH()
 *     const
 *   {
 *     const std::string name("d2H_dot_C_inv_dot_H_dH_dH");
 *     if (cache.stores_object_with_name(name) == false)
 *       cache.add_unique_copy(name, 2.0 get_C_inv());
 *
 *     return cache.template get_object_with_name<SymmetricTensor<2, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const Tensor<3, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_d2H_dot_C_inv_dot_H_dC_dH()
 *     const
 *   {
 *     const std::string name("d2H_dot_C_inv_dot_H_dC_dH");
 *     if (cache.stores_object_with_name(name) == false)
 *       {
 *         const Tensor<1, dim> &         C_inv_dot_H = get_C_inv_dot_H();
 *         const SymmetricTensor<2, dim> &C_inv       = get_C_inv();
 *
 *         Tensor<3, dim> d2H_dot_C_inv_dot_H_dC_dH;
 *         for (unsigned int A = 0; A < dim; ++A)
 *           for (unsigned int B = 0; B < dim; ++B)
 *             for (unsigned int C = 0; C < dim; ++C)
 *               d2H_dot_C_inv_dot_H_dC_dH[A][B][C]
 *
 * -=
 *                 C_inv[A][C] C_inv_dot_H[B] +
 *                 C_inv_dot_H[A] C_inv[B][C];
 *
 *         cache.add_unique_copy(name, d2H_dot_C_inv_dot_H_dC_dH);
 *       }
 *
 *     return cache.template get_object_with_name<Tensor<3, dim>>(name);
 *   }
 *
 *
 *   template <int dim>
 *   const SymmetricTensor<4, dim> &
 *   Magnetoviscoelastic_Constitutive_Law<dim>::get_d2H_dot_C_inv_dot_H_dC_dC()
 *     const
 *   {
 *     const std::string name("d2H_dot_C_inv_dot_H_dC_dC");
 *     if (cache.stores_object_with_name(name) == false)
 *       {
 *         const Tensor<1, dim> &         C_inv_dot_H = get_C_inv_dot_H();
 *         const SymmetricTensor<2, dim> &C_inv       = get_C_inv();
 *
 *         SymmetricTensor<4, dim> d2H_dot_C_inv_dot_H_dC_dC;
 *         for (unsigned int A = 0; A < dim; ++A)
 *           for (unsigned int B = A; B < dim; ++B)
 *             for (unsigned int C = 0; C < dim; ++C)
 *               for (unsigned int D = C; D < dim; ++D)
 *                 d2H_dot_C_inv_dot_H_dC_dC[A][B][C][D] +=
 *                   0.5 (C_inv_dot_H[A] C_inv_dot_H[C] C_inv[B][D] +
 *                          C_inv_dot_H[A] C_inv_dot_H[D] C_inv[B][C] +
 *                          C_inv_dot_H[B] C_inv_dot_H[C] C_inv[A][D] +
 *                          C_inv_dot_H[B] C_inv_dot_H[D] C_inv[A][C]);
 *
 *         cache.add_unique_copy(name, d2H_dot_C_inv_dot_H_dC_dC);
 *       }
 *
 *     return cache.template get_object_with_name<SymmetricTensor<4, dim>>(name);
 *   }
 *
 * @endcode
 *
 * <a name="Rheologicalexperimentparameters"></a> <h4>Rheological experiment
 * parameters</h4>。
 *
 * @p RheologicalExperimentParameters
 * 类是用来驱动数值实验的，这些实验将在我们已经实现了构成法则的耦合材料上进行。
 *
 * @code
 *   class RheologicalExperimentParameters : public ParameterAcceptor
 *   {
 *   public:
 *     RheologicalExperimentParameters();
 *
 * @endcode
 *
 * 这些是要模拟的流变学试样的尺寸。它们，有效地，定义了我们的虚拟实验的测量点。
 *
 * @code
 *     double sample_radius = 0.01;
 *     double sample_height = 0.001;
 *
 * @endcode
 *
 * 三个稳态载荷参数分别为
 *
 *
 * - 轴向拉伸。
 *
 *
 * - 剪切应变的振幅，以及
 *
 *
 * - 轴向磁场强度。
 *
 * @code
 *     double lambda_2 = 0.95;
 *     double gamma_12 = 0.05;
 *     double H_2      = 60.0e3;
 *
 * @endcode
 *  此外，随时间变化的流变负载条件的参数是
 *
 *
 * - 负载周期的频率。
 *
 *
 * - 负载周期的数量，以及
 *
 *
 * - 每个周期的离散时间步数。
 *
 * @code
 *     double       frequency         = 1.0 / (2.0 numbers::PI);
 *     unsigned int n_cycles          = 5;
 *     unsigned int n_steps_per_cycle = 2500;
 *
 * @endcode
 *
 * 我们还声明了一些不言自明的参数，这些参数与用速率依赖型和速率非依赖型材料进行的实验产生的输出数据有关。
 *
 * @code
 *     bool        output_data_to_file = true;
 *     std::string output_filename_rd =
 *       "experimental_results-rate_dependent.csv";
 *     std::string output_filename_ri =
 *       "experimental_results-rate_independent.csv";
 *
 * @endcode
 *
 * 接下来的几个函数计算实验的时间相关参数...
 *
 * @code
 *     double start_time() const;
 *
 *     double end_time() const;
 *
 *     double delta_t() const;
 *
 * @endcode
 *
 * ......而下面两个则规定了任何时候的机械和磁力负荷......
 *
 * @code
 *     Tensor<1, 3> get_H(const double time) const;
 *
 *     Tensor<2, 3> get_F(const double time) const;
 *
 * @endcode
 *
 * ......而这最后一个是将实验的状态输出到控制台。
 *
 * @code
 *     bool print_status(const int step_number) const;
 *
 *     bool initialized = false;
 *   };
 *
 *
 *
 *   RheologicalExperimentParameters::RheologicalExperimentParameters()
 *     : ParameterAcceptor("/Coupled Constitutive Laws/Rheological Experiment/")
 *   {
 *     add_parameter("Experimental sample radius", sample_radius);
 *     add_parameter("Experimental sample radius", sample_height);
 *
 *     add_parameter("Axial stretch", lambda_2);
 *     add_parameter("Shear strain amplitude", gamma_12);
 *     add_parameter("Axial magnetic field strength", H_2);
 *
 *     add_parameter("Frequency", frequency);
 *     add_parameter("Number of loading cycles", n_cycles);
 *     add_parameter("Discretisation for each cycle", n_steps_per_cycle);
 *
 *     add_parameter("Output experimental results to file", output_data_to_file);
 *     add_parameter("Output file name (rate dependent constitutive law)",
 *                   output_filename_rd);
 *     add_parameter("Output file name (rate independent constitutive law)",
 *                   output_filename_ri);
 *
 *     parse_parameters_call_back.connect([&]()
 *
 * -> void { initialized = true; });
 *   }
 *
 *
 *   double RheologicalExperimentParameters::start_time() const
 *   {
 *     return 0.0;
 *   }
 *
 *
 *   double RheologicalExperimentParameters::end_time() const
 *   {
 *     return n_cycles / frequency;
 *   }
 *
 *
 *   double RheologicalExperimentParameters::delta_t() const
 *   {
 *     return (end_time()
 *
 * - start_time()) / (n_steps_per_cycle n_cycles);
 *   }
 *
 *
 *   bool
 *   RheologicalExperimentParameters::print_status(const int step_number) const
 *   {
 *     return (step_number % (n_cycles n_steps_per_cycle / 100)) == 0;
 *   }
 *
 * @endcode
 *
 * 施加的磁场总是与流变仪转子的旋转轴对齐。
 *
 * @code
 *   Tensor<1, 3> RheologicalExperimentParameters::get_H(const double) const
 *   {
 *     return Tensor<1, 3>({0.0, 0.0, H_2});
 *   }
 *
 * @endcode
 *
 * 应用的变形（梯度）是根据流变仪和样品的几何形状、采样点和实验参数计算出来的。根据介绍中记录的位移曲线，变形梯度可以用直角坐标表示为 @f[
 * \mathbf{F} = \begin{bmatrix}
 * \frac{\cos\left(\alpha\right)}{\sqrt{\lambda_{3}}}
 * &
 *
 * -\frac{\sin\left(\alpha\right)}{\sqrt{\lambda_{3}}}
 * &
 *
 * -\tau R \sqrt{\lambda_{3}} \sin\left(\Theta + \alpha\right)
 * \\  \frac{\sin\left(\alpha\right)}{\sqrt{\lambda_{3}}}
 * & \frac{\cos\left(\alpha\right)}{\sqrt{\lambda_{3}}}
 * &
 *
 * -\tau R \sqrt{\lambda_{3}} \cos\left(\Theta + \alpha\right)
 * \\  0 & 0 & \lambda_{3}
 * \end{bmatrix}
 * @f] 。
 *
 * @code
 *   Tensor<2, 3> RheologicalExperimentParameters::get_F(const double time) const
 *   {
 *     AssertThrow((sample_radius > 0.0 && sample_height > 0.0),
 *                 ExcMessage("Non-physical sample dimensions"));
 *     AssertThrow(lambda_2 > 0.0,
 *                 ExcMessage("Non-physical applied axial stretch"));
 *
 *     const double sqrt_lambda_2     = std::sqrt(lambda_2);
 *     const double inv_sqrt_lambda_2 = 1.0 / sqrt_lambda_2;
 *
 *     const double alpha_max =
 *       std::atan(std::tan(gamma_12) sample_height /
 *                 sample_radius); // Small strain approximation
 *     const double A       = sample_radius alpha_max;
 *     const double w       = 2.0 numbers::PI frequency; // in rad /s
 *     const double gamma_t = A std::sin(w time);
 *     const double tau_t =
 *       gamma_t /
 *       (sample_radius sample_height); // Torsion angle per unit length
 *     const double alpha_t = tau_t lambda_2 sample_height;
 *
 *     Tensor<2, 3> F;
 *     F[0][0] = inv_sqrt_lambda_2 std::cos(alpha_t);
 *     F[0][1] =
 *
 * -inv_sqrt_lambda_2 std::sin(alpha_t);
 *     F[0][2] =
 *
 * -tau_t sample_radius sqrt_lambda_2 std::sin(alpha_t);
 *     F[1][0] = inv_sqrt_lambda_2 std::sin(alpha_t);
 *     F[1][1] = inv_sqrt_lambda_2 std::cos(alpha_t);
 *     F[1][2] = tau_t sample_radius sqrt_lambda_2 std::cos(alpha_t);
 *     F[2][0] = 0.0;
 *     F[2][1] = 0.0;
 *     F[2][2] = lambda_2;
 *
 *     AssertThrow((F[0][0] > 0) && (F[1][1] > 0) && (F[2][2] > 0),
 *                 ExcMessage("Non-physical deformation gradient component."));
 *     AssertThrow(std::abs(determinant(F)
 *
 * - 1.0) < 1e-6,
 *                 ExcMessage("Volumetric Jacobian is not equal to unity."));
 *
 *     return F;
 *   }
 *
 * @endcode
 *
 * <a name="RheologicalexperimentParallelplaterotationalrheometer"></a>
 * <h4>Rheological experiment: Parallel plate rotational rheometer</h4>。
 *
 * 这是驱动数值实验的函数。
 *
 * @code
 *   template <int dim>
 *   void run_rheological_experiment(
 *     const RheologicalExperimentParameters &experimental_parameters,
 *     Coupled_Magnetomechanical_Constitutive_Law_Base<dim>
 *       &material_hand_calculated,
 *     Coupled_Magnetomechanical_Constitutive_Law_Base<dim>
 *       &               material_assisted_computation,
 *     TimerOutput &     timer,
 *     const std::string filename)
 *   {
 * @endcode
 *
 * 我们可以把手工实现的构成法，与用AD或SD得到的结果进行比较。通过这种方式，我们可以验证它们产生了相同的结果（这表明要么两种实现方式都有很大的可能性是正确的，要么就是它们都有相同的缺陷而不正确）。不管怎么说，这对完全自我实现的变体来说是个不错的理智检查，当检测到结果之间的差异时，当然可以作为一种调试策略）。)
 *
 * @code
 *     const auto check_material_class_results =
 *       [](
 *         const Coupled_Magnetomechanical_Constitutive_Law_Base<dim> &to_verify,
 *         const Coupled_Magnetomechanical_Constitutive_Law_Base<dim> &blessed,
 *         const double tol = 1e-6) {
 *         (void)to_verify;
 *         (void)blessed;
 *         (void)tol;
 *
 *         Assert(std::abs(blessed.get_psi()
 *
 * - to_verify.get_psi()) < tol,
 *                ExcMessage("No match for psi. Error: " +
 *                           Utilities::to_string(std::abs(
 *                             blessed.get_psi()
 *
 * - to_verify.get_psi()))));
 *
 *         Assert((blessed.get_B()
 *
 * - to_verify.get_B()).norm() < tol,
 *                ExcMessage("No match for B. Error: " +
 *                           Utilities::to_string(
 *                             (blessed.get_B()
 *
 * - to_verify.get_B()).norm())));
 *         Assert((blessed.get_S()
 *
 * - to_verify.get_S()).norm() < tol,
 *                ExcMessage("No match for S. Error: " +
 *                           Utilities::to_string(
 *                             (blessed.get_S()
 *
 * - to_verify.get_S()).norm())));
 *
 *         Assert((blessed.get_DD()
 *
 * - to_verify.get_DD()).norm() < tol,
 *                ExcMessage("No match for BB. Error: " +
 *                           Utilities::to_string(
 *                             (blessed.get_DD()
 *
 * - to_verify.get_DD()).norm())));
 *         Assert((blessed.get_PP()
 *
 * - to_verify.get_PP()).norm() < tol,
 *                ExcMessage("No match for PP. Error: " +
 *                           Utilities::to_string(
 *                             (blessed.get_PP()
 *
 * - to_verify.get_PP()).norm())));
 *         Assert((blessed.get_HH()
 *
 * - to_verify.get_HH()).norm() < tol,
 *                ExcMessage("No match for HH. Error: " +
 *                           Utilities::to_string(
 *                             (blessed.get_HH()
 *
 * - to_verify.get_HH()).norm())));
 *       };
 *
 * @endcode
 *
 * 我们将把材料的构成响应输出到文件中进行后处理，所以在这里我们声明一个`stream`，它将作为这个输出的缓冲区。我们将使用一个简单的CSV格式来输出结果。
 *
 * @code
 *     std::ostringstream stream;
 *     stream
 *       << "Time;Axial magnetic field strength [A/m];Axial magnetic induction [T];Shear strain [%];Shear stress [Pa]\n";
 *
 * @endcode
 *
 * 使用DiscreteTime类，我们使用一个固定的时间步长来迭代每个时间段。
 *
 * @code
 *     for (DiscreteTime time(experimental_parameters.start_time(),
 *                            experimental_parameters.end_time() +
 *                              experimental_parameters.delta_t(),
 *                            experimental_parameters.delta_t());
 *          time.is_at_end() == false;
 *          time.advance_time())
 *       {
 *         if (experimental_parameters.print_status(time.get_step_number()))
 *           std::cout << "Timestep = " << time.get_step_number()
 *                     << " @ time = " << time.get_current_time() << "s."
 *                     << std::endl;
 *
 * @endcode
 *
 * 我们获取并计算在这个时间步长中应用于材料的负载...
 *
 * @code
 *         const Tensor<1, dim> H =
 *           experimental_parameters.get_H(time.get_current_time());
 *         const Tensor<2, dim> F =
 *           experimental_parameters.get_F(time.get_current_time());
 *         const SymmetricTensor<2, dim> C =
 *           Physics::Elasticity::Kinematics::C(F);
 *
 * @endcode
 *
 * ...然后我们更新材料的状态...
 *
 * @code
 *         {
 *           TimerOutput::Scope timer_section(timer, "Hand calculated");
 *           material_hand_calculated.update_internal_data(C, H, time);
 *           material_hand_calculated.update_end_of_timestep();
 *         }
 *
 *         {
 *           TimerOutput::Scope timer_section(timer, "Assisted computation");
 *           material_assisted_computation.update_internal_data(C, H, time);
 *           material_assisted_computation.update_end_of_timestep();
 *         }
 *
 * @endcode
 *
 * ... 并测试两者之间的差异。
 *
 * @code
 *         check_material_class_results(material_hand_calculated,
 *                                      material_assisted_computation);
 *
 *         if (experimental_parameters.output_data_to_file)
 *           {
 * @endcode
 * 接下来，我们要做的是收集一些结果来进行后处理。所有的数量都是在
 * "当前配置"（而不是
 * "参考配置"，所有由构成法则计算的数量都是在这个框架内）。
 *
 * @code
 *             const Tensor<1, dim> h =
 *               Physics::Transformations::Covariant::push_forward(H, F);
 *             const Tensor<1, dim> b =
 *               Physics::Transformations::Piola::push_forward(
 *                 material_hand_calculated.get_B(), F);
 *             const SymmetricTensor<2, dim> sigma =
 *               Physics::Transformations::Piola::push_forward(
 *                 material_hand_calculated.get_S(), F);
 *             stream << time.get_current_time() << ";" << h[2] << ";" << b[2]
 *                    << ";" << F[1][2] 100.0 << ";" << sigma[1][2] << "\n";
 *           }
 *       }
 *
 * @endcode
 *
 * 最后，我们把应变应力和磁载荷历史输出到文件中。
 *
 * @code
 *     if (experimental_parameters.output_data_to_file)
 *       {
 *         std::ofstream output(filename);
 *         output << stream.str();
 *       }
 *   }
 *
 * @endcode
 *
 * <a name="TheCoupledConstitutiveLawsrunfunction"></a> <h4>The
 * CoupledConstitutiveLaws::run() function</h4>。
 *
 * 这个驱动函数的目的是从文件中读取所有的参数，并在此基础上创建每个构成法则的代表性实例，并调用函数对其进行流变学实验。
 *
 * @code
 *   void run(int argc, charargv[])
 *   {
 *     using namespace dealii;
 *
 *     constexpr unsigned int dim = 3;
 *
 *     const ConstitutiveParameters          constitutive_parameters;
 *     const RheologicalExperimentParameters experimental_parameters;
 *
 *     std::string parameter_file;
 *     if (argc > 1)
 *       parameter_file = argv[1];
 *     else
 *       parameter_file = "parameters.prm";
 *     ParameterAcceptor::initialize(parameter_file, "used_parameters.prm");
 *
 * @endcode
 *
 * 我们通过配置和运行实验开始实际工作，使用我们的速率无关的构成法。这里的自动可微调数类型是硬编码的，但是通过一些巧妙的模板设计，可以在运行时选择使用哪种框架（例如，通过参数文件选择）。我们将同时用完全手工实现的反面材料法进行实验，并检查它与我们的辅助实现的计算结果。
 *
 * @code
 *     {
 *       TimerOutput timer(std::cout,
 *                         TimerOutput::summary,
 *                         TimerOutput::wall_times);
 *       std::cout
 *         << "Coupled magnetoelastic constitutive law using automatic differentiation."
 *         << std::endl;
 *
 *       constexpr Differentiation::AD::NumberTypes ADTypeCode =
 *         Differentiation::AD::NumberTypes::sacado_dfad_dfad;
 *
 *       Magnetoelastic_Constitutive_Law<dim> material(constitutive_parameters);
 *       Magnetoelastic_Constitutive_Law_AD<dim, ADTypeCode> material_ad(
 *         constitutive_parameters);
 *
 *       run_rheological_experiment(experimental_parameters,
 *                                  material,
 *                                  material_ad,
 *                                  timer,
 *                                  experimental_parameters.output_filename_ri);
 *
 *       std::cout << "... all calculations are correct!" << std::endl;
 *     }
 *
 * @endcode
 *
 * 接下来我们对与速率相关的构成法做同样的处理。如果SymEngine被设置为使用LLVM即时编译器，则默认选择最高性能的选项，该编译器（结合一些积极的编译标志）产生所有可用选项中最快的代码评估路径。作为后备措施，所谓的
 * "lambda
 * "优化器（它只需要一个兼容C++11的编译器）将被选中。同时，我们将要求CAS进行普通子表达式的消除，以尽量减少评估过程中使用的中间计算的数量。我们将记录在SD实现的构造器内执行
 * "初始化
 * "步骤所需的时间，因为这是发生上述转换的地方。
 *
 * @code
 *     {
 *       TimerOutput timer(std::cout,
 *                         TimerOutput::summary,
 *                         TimerOutput::wall_times);
 *       std::cout
 *         << "Coupled magneto-viscoelastic constitutive law using symbolic differentiation."
 *         << std::endl;
 *
 * #ifdef DEAL_II_SYMENGINE_WITH_LLVM
 *       std::cout << "Using LLVM optimizer." << std::endl;
 *       constexpr Differentiation::SD::OptimizerType optimizer_type =
 *         Differentiation::SD::OptimizerType::llvm;
 *       constexpr Differentiation::SD::OptimizationFlags optimization_flags =
 *         Differentiation::SD::OptimizationFlags::optimize_all;
 * #else
 *       std::cout << "Using lambda optimizer." << std::endl;
 *       constexpr Differentiation::SD::OptimizerType optimizer_type =
 *         Differentiation::SD::OptimizerType::lambda;
 *       constexpr Differentiation::SD::OptimizationFlags optimization_flags =
 *         Differentiation::SD::OptimizationFlags::optimize_cse;
 * #endif
 *
 *       Magnetoviscoelastic_Constitutive_Law<dim> material(
 *         constitutive_parameters);
 *
 *       timer.enter_subsection("Initialize symbolic CL");
 *       Magnetoviscoelastic_Constitutive_Law_SD<dim> material_sd(
 *         constitutive_parameters, optimizer_type, optimization_flags);
 *       timer.leave_subsection();
 *
 *       run_rheological_experiment(experimental_parameters,
 *                                  material,
 *                                  material_sd,
 *                                  timer,
 *                                  experimental_parameters.output_filename_rd);
 *
 *       std::cout << "... all calculations are correct!" << std::endl;
 *     }
 *   }
 *
 * } // namespace CoupledConstitutiveLaws
 *
 * } // namespace Step71
 *
 *
 * @endcode
 *
 * <a name="Themainfunction"></a> <h3>The main() function</h3>。
 *
 * 主函数只调用两组要执行的例子的驱动函数。
 *
 * @code
 * int main(int argc, charargv[])
 * {
 * Step71::SimpleExample::run();
 * Step71::CoupledConstitutiveLaws::run(argc, argv);
 *
 * return 0;
 * }
 * @endcode
 * <a name="Results"></a><h1>Results</h1> 。   <a
 * name="Introductoryexample"></a><h3>Introductory example</h3>
 * 第一个探索性的例子产生了以下输出。经核实，所有三种实现方式产生的结果是相同的。
 * @code
 * > ./step-71
 * Simple example using automatic differentiation...
 * ... all calculations are correct!
 * Simple example using symbolic differentiation.
 * ... all calculations are correct!
 * @endcode
 *
 * <a name="Constitutivemodelling"></a><h3>Constitutive modelling</h3> 。
 *
 * 为了帮助总结虚拟实验本身的结果，下面是一些图表，显示了材料样品内选定位置的剪切应力，与剪切应变的关系图。这些图表显示了在三种不同磁载荷下的应力-应变曲线，以及（机械）载荷曲线的最后一个周期，当速率依赖型材料达到可重复的（"稳态"）反应时。这些类型的图表通常被称为[Lissajous图]（https://en.wikipedia.org/wiki/Lissajous_curve）。粘弹性材料的曲线所呈现的椭圆面积可以衡量材料耗散的能量大小，其椭圆度表示粘性反应相对于弹性反应的相位变化。
 * <table align="center" class="tutorial" cellspacing="3" cellpadding="3">
 * <tr> <td align="center"> <img
 * src="https://www.dealii.org/images/steps/developer/step-71.lissajous_plot-me.png"
 * alt="" width="400"> <p align="center"> Lissajous plot for the
 * magneto-elastic material. </p> </td> <td align="center"> <img
 * src="https://www.dealii.org/images/steps/developer/step-71.lissajous_plot-mve.png"
 * alt="" width="400"> <p align="center"> Lissajous plot for the
 * magneto-viscoelastic material. </p> </td> </tr> </table>
 * 我们不难看出，磁弹性材料的反应有一条与加载曲线相匹配的卸载曲线。
 *
 * 但在这里可以清楚地注意到，随着施加磁场的增加，曲线的梯度也在增加。沿着这条曲线任何一点的切线都与瞬时剪切模量有关，由于能量密度函数的定义方式，我们预计剪切模量会随着磁场强度的增加而增加。我们观察到磁-粘弹性材料的行为大致相同。由加载-卸载曲线追踪的椭圆的主轴有一个斜率，随着施加更大的磁负荷而增加。同时，材料耗散的能量也越多。
 * 至于代码输出，这是打印到控制台的关于用磁弹性材料进行流变学实验的部分。
 * @code
 * Coupled magnetoelastic constitutive law using automatic differentiation.
 * Timestep = 0 @ time = 0s.
 * Timestep = 125 @ time = 0.314159s.
 * Timestep = 250 @ time = 0.628318s.
 * Timestep = 375 @ time = 0.942477s.
 * ...
 * Timestep = 12250 @ time = 30.7876s.
 * Timestep = 12375 @ time = 31.1018s.
 * Timestep = 12500 @ time = 31.4159s.
 * ... all calculations are correct!
 * @endcode
 *
 * 这部分的输出涉及到用磁弹性材料进行的实验。
 * @code
 * Coupled magneto-viscoelastic constitutive law using symbolic differentiation.
 * Using LLVM optimizer.
 * Timestep = 0 @ time = 0s.
 * Timestep = 125 @ time = 0.314159s.
 * Timestep = 250 @ time = 0.628318s.
 * Timestep = 375 @ time = 0.942477s.
 * ...
 * Timestep = 12250 @ time = 30.7876s.
 * Timestep = 12375 @ time = 31.1018s.
 * Timestep = 12500 @ time = 31.4159s.
 * ... all calculations are correct!
 * @endcode
 *
 * 计时器的输出也被发送到控制台，因此我们可以比较进行手工计算和辅助计算所需的时间，并对使用AD和SD框架的开销有一些了解。以下是使用AD框架的磁弹性实验的时间，基于Trilinos库的Sacado组件。
 * @code
 * +---------------------------------------------+------------+------------+
 * | Total wallclock time elapsed since start    |       3.2s |            |
 * |                                             |            |            |
 * | Section                         | no. calls |  wall time | % of total |
 * +---------------------------------+-----------+------------+------------+
 * | Assisted computation            |     12501 |      3.02s |        95% |
 * | Hand calculated                 |     12501 |    0.0464s |       1.5% |
 * +---------------------------------+-----------+------------+------------+
 * @endcode
 * 关于使用自动微分进行的计算（作为提醒，这是使用Sacadolibrary结合动态前向自动微分类型进行的两级微分），我们注意到，辅助计算需要大约
 * $65 \times$
 * 的时间来计算所需的数量。这看起来确实是一个相当大的开销，但是，正如介绍中提到的，这是否可以接受完全是主观的，并且取决于具体情况：你是否更看重计算机的时间，而不是人的时间来做必要的导数手工计算，验证其正确性，实现它们，并验证实现的正确性？如果你开发的研究代码只会在相对较少的实验中运行，你可能更看重自己的时间。如果你开发的生产代码将在10,000核的集群上反复运行几个小时，你的考虑可能就不一样了。无论如何，AD方法的一个很好的特点是，当函数和类在标量类型上建模时，有
 * "滴入 "能力。这意味着开始使用它只需要最小的努力。
 * 与此相反，使用实时（JIT）编译的符号代数实现的磁涡弹材料的时间表明，在初始化过程中付出一些不可忽视的代价，计算本身的执行效率要高得多。
 * @code
 * +---------------------------------------------+------------+------------+
 * | Total wallclock time elapsed since start    |      1.34s |            |
 * |                                             |            |            |
 * | Section                         | no. calls |  wall time | % of total |
 * +---------------------------------+-----------+------------+------------+
 * | Assisted computation            |     12501 |     0.376s |        28% |
 * | Hand calculated                 |     12501 |     0.368s |        27% |
 * | Initialize symbolic CL          |         1 |     0.466s |        35% |
 * +---------------------------------+-----------+------------+------------+
 * @endcode
 * 由于初始化阶段很可能只需要在每个线程中执行一次，这个初始的昂贵阶段可以通过重复使用单个
 * Differentiation::SD::BatchOptimizer
 * 实例来抵消。尽管磁弹性构成法与磁弹性构成法相比，有更多的条款需要计算，但它在执行动能变量和切线的计算方面仍然快了一个数量级。而且，与使用缓存方案的手工计算变量相比，计算时间几乎相等。因此，尽管使用符号框架需要在如何实现和操作符号表达方面进行范式转换，但它可以提供AD框架所缺乏的良好性能和灵活性。
 * 关于数据缓存的问题，事实上，与使用中间值进行的数值实验相比，磁弹性材料实现的价值缓存所增加的成本是在
 * "update_internal_data() "中花费的时间 $6\times$
 * 。下面是删除缓存数据结构后，为 "手工计算
 * "变体提取的时间比较的样本输出。
 * @code
 * +---------------------------------------------+------------+------------+
 * | Total wallclock time elapsed since start    |      1.01s |            |
 * |                                             |            |            |
 * | Section                         | no. calls |  wall time | % of total |
 * +---------------------------------+-----------+------------+------------+
 * | Assisted computation            |     12501 |     0.361s |        36% |
 * | Hand calculated                 |     12501 |    0.0562s |       5.6% |
 * | Initialize symbolic CL          |         1 |     0.469s |        47% |
 * +---------------------------------+-----------+------------+------------+
 * @endcode
 * 通过一些小的调整，我们可以很容易地测试批量优化器的不同优化方案。因此，让我们比较一下与
 * "LLVM
 * "批处理优化器设置相关的计算费用和其他选择。以下是
 * "lambda "优化方法的时间报告（保留使用CSE）。
 * @code
 * +---------------------------------------------+------------+------------+
 * | Total wallclock time elapsed since start    |      3.87s |            |
 * |                                             |            |            |
 * | Section                         | no. calls |  wall time | % of total |
 * +---------------------------------+-----------+------------+------------+
 * | Assisted computation            |     12501 |      3.12s |        81% |
 * | Hand calculated                 |     12501 |     0.394s |        10% |
 * | Initialize symbolic CL          |         1 |     0.209s |       5.4% |
 * +---------------------------------+-----------+------------+------------+
 * @endcode
 * 这里的主要观察是，与 "LLVM "方法相比，在 "辅助计算
 * "部分花费的时间要多出一个数量级。 最后，我们将测试
 * "字典
 * "替换与CSE的结合情况。字典替换只是在CAS框架内做了所有的评估，而没有对底层数据结构进行转换。在这种情况下，只有使用缓存中间结果的CSE才能提供任何
 * "加速"。考虑到这一点，下面是这个选择的结果。
 * @code
 * +---------------------------------------------+------------+------------+
 * | Total wallclock time elapsed since start    |  1.54e+03s |            |
 * |                                             |            |            |
 * | Section                         | no. calls |  wall time | % of total |
 * +---------------------------------+-----------+------------+------------+
 * | Assisted computation            |     12501 |  1.54e+03s |     1e+02% |
 * | Hand calculated                 |     12501 |     0.563s |         0% |
 * | Initialize symbolic CL          |         1 |     0.184s |         0% |
 * +---------------------------------+-----------+------------+------------+
 * @endcode
 * 不用说，与其他两种方法相比，这些结果花了不少时间来产生。字典
 * "替换方法也许只适用于简单的表达式，或者当调用的数量足够少的时候。
 * <a name="SowhichframeworkshouldIuse"></a><h1>So, which framework should I
 * use?</h1>
 *
 * 也许你已经相信这些工具有一些优点，并且可以对你有直接的帮助或用途。现在明显的问题是使用哪一个。特别是在连续点层面上，你将使用这些框架来计算构成法则的导数，我们可以说以下几点。
 *
 * - 自动微分可能是进入辅助微分世界的最简单的切入点。
 *
 * - 鉴于构成框架有足够的通用实现，自动微分通常可以用来替代内在的标量类型，然后可以利用辅助类来计算一阶（以及可能的高阶）导数，只需付出最小的努力。
 *
 * 作为对上述观点的限定，作为一个 "落入式替代
 * "并不意味着你必须对这些数字所通过的算法不产生争议。有可能不经意间进行的操作，在进行区分时，会返回一个不正确的结果。
 * 所以这绝对是一个人应该注意的事情。
 * 一个具体的例子。当计算一个张量的特征值时，如果该张量是对角线的，那么得到结果的捷径就是直接返回对角线条目（从输入张量中提取的）。就计算特征值本身而言，这是完全正确的，但是不通过算法来计算非对角线张量的特征值会产生意想不到的副作用，即特征值看起来（对AD框架而言）是完全相互脱钩的，它们的交叉敏感度没有被编码在返回的结果中。在进行微分时，导数张量的许多条目将被丢失。为了解决这个问题，我们必须确保使用标准的特征值求解算法，这样返回的特征值对彼此的敏感度就会在结果中得到编码。
 *
 * - 涉及AD数字类型的计算可能很昂贵。随着微分运算顺序的增加，费用也会增加（有时是相当大的）。这可能会被周围操作的计算复杂性所缓解（例如线性求解），但最终还是要看具体问题。
 *
 * - AD被限制在只需要总导数的情况下。如果一个微分操作需要相对于自变量的偏导，那么使用它是不合适的。
 *
 * - 每个AD库都有自己的怪癖（说起来很悲哀，但根据作者的经验，是真的），所以可能需要一些试验和错误来找到合适的库和选择AD数来满足你的目的。这些 "怪癖 "的原因往往归结于库背后的整体理念（数据结构、模板元编程的使用等）以及导数计算的数学实现（例如，使用对数函数改变基础的结果操作可能限制了输入值的域
 *
 * - 当然，所有的细节都是对用户隐藏的）。)  此外，一个库可能比另一个库能更快地计算出所需的结果，所以在这方面进行一些初步探索可能是有益的。
 *
 * - 符号微分（嗯，一般来说，使用CAS）提供了最灵活的框架，可以进行辅助计算。
 *
 * - SD框架可以做AD框架所能做的一切，还有一个好处是可以对某些操作和运算的时间进行低级控制。
 *
 * - 表达式评估的加速是可能的，与一些手工实现相比，有可能导致SD框架接近原生的性能（当然，这种比较取决于整个程序设计），但代价是初始优化调用。
 *
 * - 巧妙地使用 Differentiation::SD::BatchOptimizer 可以最大限度地减少优化依赖表达式的昂贵调用的费用。  可以对 Differentiation::SD::BatchOptimizer 进行序列化，往往（但不一定）这个昂贵的调用可以做一次，然后在以后的模拟中重复使用。
 *
 * - 例如，如果两个或更多的材料法只因其材料参数而不同，那么只要这些材料参数被认为是象征性的，就可以在它们之间共享一个批量优化器。这意味着你可以 "区分一次，在许多情况下评估"。
 *
 * - SD框架可以部分地被用作标量类型的 "直接替换"，但是人们（至少）必须在它周围增加一些框架来执行值替换步骤，将符号类型转换为它们的数字对应物。
 *
 * - 在一些专门的算法中可能无法使用SD数字。  例如，如果一个算法的退出点或代码分支是基于（符号）输入参数应该采取的一些具体的数值，那么显然这是不可行的。我们要么重新实现专门针对SD数字类型的算法（有点不方便，但经常是可能的，因为 Differentiation::SD::Expression 类支持条件反射），要么必须使用创造性的手段来解决这个具体问题（例如，引入一个符号表达式来表示这个算法返回的结果，如果在要使用它的上下文中是合理的，也许可以声明它是一个[符号函数]（https://dealii.org/developer/doxygen/deal.II/namespaceDifferentiation_1_1SD.html#a876041f6048705c7a8ad0855cdb1bd7a）。这以后可以用它的数值来替代，如果声明为符号函数，那么它的递延导数也可以作为替代的结果纳入计算中。)
 *
 * - 使用SD的最大缺点是，使用它需要一个范式的转变，人们必须以不同的方式来构建大多数问题，以便利用它的最大优势。仔细考虑如何使用和重用数据结构也是让它有效工作的关键）。这可能意味着，人们需要对它进行一番玩耍，并建立起对典型操作顺序的理解，以及每一步在操作基础数据方面的具体作用。如果人们有时间和意愿这样做，那么使用这个工具的好处可能是巨大的。
 * <a name="Possibilitiesforextension"></a><h1>Possibilities for
 * extension</h1>
 *
 *  有几个合乎逻辑的方法可以扩展这个程序。
 *
 * - 也许最明显的扩展是实现和测试其他构成模型。  这仍然可以在磁-机械耦合问题的范围内进行，也许可以考虑替代能量函数的 "Neo-Hookean "型弹性部分，改变耗散能量的构成规律（及其相关的演化规律），或者包括磁滞效应或这些材料试图模拟的复合聚合物的破坏模型。
 *
 * - 当然，所实现的模型可以被修改或完全替换为专注于物理学其他方面的模型，如电活性聚合物、生物力学材料、弹塑性介质等。
 *
 * - 为粘弹性演化规律实施不同的时间分层方案。
 *
 * - 与其直接从能量密度函数推导出一切，不如使用 Differentiation::AD::VectorFunction 来直接线性化动力学量。  这将意味着只需要一个一次微分的自动微分的数字类型，而且肯定会大大改善性能。  这种方法也为耗散材料提供了机会，比如这里考虑的磁涡弹材料，可以与AD结合起来实现。这是因为线性化调用了因变量相对于场变量的总导数，这正是AD框架所能提供的。
 *
 * - 研究使用其他可自动微分的数字类型和框架（如ADOL-C）。由于每个AD库都有自己的实现，选择使用哪个库可能会导致性能的提高，而且在最不幸的情况下，计算会更加稳定。至少可以说，对于deal.II支持的AD库，结果的准确性应该基本不受这个决定的影响。
 *
 * - 在有限元模拟中嵌入这些构成法之一。
 * 用较少的精力，可以考虑重新编写非线性问题求解器，比如在
 * step-15
 * 中实现的使用AD或SDapproaches来计算牛顿矩阵的问题。事实上，这在
 * step-72 中已经完成。
 *
* <a name="PlainProg"></a><h1> The plain program</h1> @include "step-71.cc"  。
 *
 */


