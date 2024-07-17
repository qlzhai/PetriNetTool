# 1引言

## 1.1 软件名称以及版本信息

软件名称：一种用于Petri网模型分析的软件工具（PNTool）

版本信息：V1.0

## 1.2编写目的

Petri网作为一种常用的形式化工具，用于描述和分析系统中的资源分配、同步和竞争等关键概念。关联矩阵是一种常见的Petri网表示方法，将库所和变迁之间的关系以矩阵的形式呈现。然而，手动分析和评估复杂的Petri网模型往往非常耗时且容易出错。

为了解决这一问题，Petri网软件应运而生，该软件的开发旨在充分利用现代计算机和软件技术的优势，为研究人员、工程师以及学生提供一个高效、直观的分析环境，包括状态空间分析、结构分析、活性分析以及死锁预防等。同时，该软件旨在提升用户对Petri网模型的理解、验证和性能评估的能力。

## 1.3编写环境

c++

visual studio 2019

Qt 6.6.0

## 1.4术语和缩略词

T-invariant T-不变式

P-invariant P-不变式

SMS 严格极小信标

ESMS 基本信标

MTSI 标记/变迁分离实例

TBDP Time based Deadlock Prevention

SRG 符号可达图

# 2 软件概述

## 2.1软件主要功能

(1) 结构特性分析：包括T-invariant和P-invariant分析。

(2) 信标分析：包括信标计算、极小信标计算、严格极小信标计算以及基本信标计算。

(3) 状态空间分析：包括可达图计算、标识分类、MTSI。

(4) 死锁预防：包括基于SMS的死锁预防以及基于ESMS的死锁预防。

(5) TBDP：包括SRG计算、死锁预防条件计算以及部分可达图计算。

## 2.2系统要求

Windows 2003以上系统，内存2GB以上，硬盘 50 GB以上。

3软件使用说明

# 3 软件使用说明

## 3.1新建和打开

用户可以通过新建和打开命令灵活地创建新的Petri网模型或者加载现有的模型，并在图形化界面上方便地输入或编辑相关的数据，对Petri网模型进行信标分析、状态空间分析、结构特性分析、死锁预防等操作。

### 3.1.1新建

用户可以通过图形化界面轻松创建新的Petri网模型。首先用户需要点击“文件”->“新建”进入新建界面（如下图所示），然后通过文本框或者下拉菜单输入库所数量和变迁数量，并通过文本框输入关联矩阵以及初始标记。在新建的过程，用户也可以点击“关闭”命令以取消新建。

<img src="E:\C++Project\PetriNetTool\image\图片1.png" alt="图片1" style="zoom:50%;" />

在输入关联矩阵以及初始标记的过程中，每个数字之间应该以逗号（英文模式下）或者空格分割开。如下图所示。

<img src="E:\C++Project\PetriNetTool\image\图片2.png" alt="图片2" style="zoom:50%;" />

输入完成后，用户可以点击“确认”命令保存输入的数据，保存文件的格式为文本文件（.txt）。该功能还提供了一种输入保护机制。在Petri网模型中，关联矩阵的行数与库所数量相等，关联矩阵的列数与变迁数量相等，且库所数量和变迁数量都不能为0。如果上述关系有一个被破环，软件就会弹出一个提示框（如下图所示）以提示用户输入不合法。

<img src="E:\C++Project\PetriNetTool\image\图片3.png" alt="图片3" style="zoom:50%;" />

### 3.1.2打开

用户也可以通过“文件”->“打开”命令打开之前保存的文件（.txt）或者用户自定义的文件（.txt）。用户自定义的网文件格式应如下图所示，网文件内容因该包括库所数量、变迁数量、关联矩阵以及初始标记。

 <img src="E:\C++Project\PetriNetTool\image\图片4.png" alt="图片4" style="zoom:50%;" />

一旦文件被选中，该软件将读取文本文件中的内容，并将其解析为库所数量、变迁数量、关联矩阵以及初始标记。解析后，软件将自动加载数据，将库所数量、变迁数量、关联矩阵以及初始标记的信息在界面中显示（如下图），以方便用户查看和编辑。

<img src="E:\C++Project\PetriNetTool\image\图片5.png" alt="图片5" style="zoom:50%;" />

需要特别说明的是，在分析Petri网模型时，库所的的下标是从1到m（m为库所数量），变迁的下标是从1到n（n为变迁数量）。以下测试数据均采用上图的输入数据。

## 3.2结构特性分析

T-invariant和P-invariant是Petri模型的两个重要的结构特性且这两个属性均可以由状态方程获得，用户可以点击“结构特性”->“T-invariant”或“P-invariant”对Petri网模型进行结构分析。

### 3.2.1 T-invariant分析

T-invariant 是与变迁（transitions）相关的特性。一个 T-invariant 是一个与变迁（即变迁的启用条件）相关的线性方程组。在 T-invariant 分析中，Petri 网软件会计算并显示所有满足不变性条件的 T-invariant。这些 T-invariant 可以帮助用户了解 Petri 网的结构特点，例如系统的可达性、死锁情况等。一个测试结果如下图所示，这表明图3.4的网模型有两个T-invariant，分别是
$$
J_1=t_1+t_2+t_3+t_4\\
J_2=t_5+t_6+t_7+t_8
$$
<img src="E:\C++Project\PetriNetTool\image\图片6.png" alt="图片6" style="zoom:50%;" />

### 3.2.2 P-invariant分析

P-invariant 是 Petri 网的一个属性，当且仅当线性方程组的解可以保持库所标记的总数量不变。在 P-invariant 分析中，该软件会计算并显示所有满足不变性条件的P-invariant。这些 P-invariant 可以帮助用户了解 Petri 网的结构特点，例如系统的稳定性、进程间的资源分配等。一个测试结果如图下图所示。

<img src="E:\C++Project\PetriNetTool\image\图片7.png" alt="图片7" style="zoom:50%;" />

## 3.3信标计算

信标在Petri网的死锁分析以及活性分析中尤为重要，因为一个信标一旦在某标识下被清空，则在该标识的所有后续标识下此信标总是被清空的。

### 3.3.1信标

用户可以点击“信标分析”->“信标”计算Petri网模型的所有信标。如下图所示。

<img src="E:\C++Project\PetriNetTool\image\图片8.png" alt="图片8" style="zoom:50%;" />

### 3.3.2极小信标

用户可以点击“信标分析”->“极小信标”计算Petri网模型的所有极小信标（如下图）。

<img src="E:\C++Project\PetriNetTool\image\图片9.png" alt="图片9" style="zoom:50%;" />

### 3.3.3严格极小信标

用户可以点击“信标分析”->“严格极小信标”计算Petri网模型的所有严格极小信标。如下图所示。

<img src="E:\C++Project\PetriNetTool\image\图片10.png" alt="图片10" style="zoom:50%;" />

### 3.3.4基本信标

用户可以点击“信标分析”->“基本信标”计算Petri网模型的所有基本信标。如下图所示。

<img src="E:\C++Project\PetriNetTool\image\图片11.png" alt="图片11" style="zoom:50%;" />

## 3.4状态空间分析

### 3.4.1可达图计算

用户可以点击“状态空间分析”->“可达图计算”计算Petri网模型的所有可达标记。软件以可视化的形式显示出所有的可达标记以及死锁标记（如下图所示）。

<img src="E:\C++Project\PetriNetTool\image\图片12.png" alt="图片12" style="zoom:50%;" />

### 3.4.2标识分类

用户可以点击“状态空间分析”->“标记分类”对Petri网模型的所有可达标记分类。标识分类主要是区分出好标记、危险标记、坏标记以及死锁标记（如下图所示）。

<img src="E:\C++Project\PetriNetTool\image\图片13.png" alt="图片13" style="zoom:50%;" />

### 3.4.3 MTSI

用户可以点击“状态空间分析”->“标记分类”计算Petri网模型的所有MTSI。软件以可视化的形式显示出MTSI个数以及所有的MTSI（如下图所示。

<img src="E:\C++Project\PetriNetTool\image\图片14.png" alt="图片14" style="zoom:50%;" />

## 3.5死锁预防

### 3.5.1基于SMS

用户可以点击“死锁预防”->“基于SMS”对Petri网模型采用基于严格极小信标的死锁预防策略进行死锁预防。软件会显示出受控Petri网模型的关联矩阵以及初始标记（如下图所示），其中关联矩阵的前m行是原始Petri网模型的关联矩阵，第m+1行到最后一行是需要添加的控制库所及其相关的弧；初始标记的前m列是原始Petri网模型的初始标记，第m+1列到最后一列是需要添加的控制库所的初始标记。

<img src="E:\C++Project\PetriNetTool\image\图片15.png" alt="图片15" style="zoom:50%;" />

### 3.5.2基于ESMS

用户可以点击“死锁预防”->“基于ESMS”对Petri网模型采用基于基本信标的死锁预防策略进行死锁预防。软件会显示出受控Petri网模型的关联矩阵以及初始标记，其中关联矩阵的前m行是原始Petri网模型的关联矩阵，第m+1行到最后一行是需要添加的控制库所及其相关的弧；初始标记的前m列是原始Petri网模型的初始标记，第m+1列到最后一列是需要添加的控制库所的初始标记。

由于采用基本信标预防死锁的方法依赖于原始Petri网模型的初始标记的配置，因此在某些情况下，所输入的Petri网模型可能不适合采用基本信标预防死锁的方法。此时软件会弹出一个提示框（如下图所示），以提醒用户该模型不适合采用基本信标预防死锁。

<img src="E:\C++Project\PetriNetTool\image\图片16.png" alt="图片16" style="zoom:50%;" />

## 3.6 TBDP

### 3.6.1部分可达图

用户可以点击“TBDP”->“部分可达图”求出影响时间Petri网模型中死锁的部分可达图(如下图所示)。

<img src="E:\C++Project\PetriNetTool\image\图片17.png" alt="图片17" style="zoom:50%;" />

### 3.6.2死锁预防条件

用户可以点击“TBDP”->“死锁预防条件”获取时间Petri网模型中的所有死锁预防条件(如下图所示)，这些死锁预防条件是基于部分可达图获取的。

<img src="E:\C++Project\PetriNetTool\image\图片18.png" alt="图片18" style="zoom:50%;" />

### 3.6.2 SRG

用户可以点击“TBDP”->“SRG”计算Petri网模型的符号可达图(如下图所示)。

<img src="E:\C++Project\PetriNetTool\image\图片19.png" alt="图片19" style="zoom:50%;" />

## 3.7其他说明

因为结构分析、信标分析等都是在有模型输入的情况下进行的，因此，该软件提供了输入检测机制。如果用户没有输入网模型，软件会弹出一个提示框（如图3.20所示），提醒用户先打开一个文件。

<img src="E:\C++Project\PetriNetTool\image\图片20.png" alt="图片20" style="zoom:50%;" />

用户可以点击软件右上角的“×”关闭软件，软件会弹出一个提示框（如图3.21所示），再一次跟用户确认是否需要关闭软件。

<img src="E:\C++Project\PetriNetTool\image\图片21.png" alt="图片21" style="zoom:50%;" />

# 4 bug

TBDP模块中所耗费时间过长

TBDP问题中SRG的计算有可能是无限的，导致程序一直处于运行状态，关于SRG是无限的判断后期会加上

TBDP模块中死锁预防条件中需要计算路径，目前采用的是深度优先遍历的方式，复杂度太高

vector容器是有内存限制的，有时候出现内存不足错误

# 5 参考文献

Y. S. Huang, M. D. Jeng, X. L. Xie, and D. H. Chung, “Siphon-based deadlock prevention policy for flexible manufacturing systems,” IEEE Trans. Syst., Man, Cybern. A, Syst. Humans, vol. 36, no. 6, pp. 1248– 1256, 2006.

M. Uzam, “An optimal deadlock prevention policy for flexible manufacturing systems using Petri net models with resources and the theory of regions,” Int. J. Adv. Manuf. Technol., vol. 19, pp. 192–208, 2002.

Z. W. Li and M. C. Zhou, “Elementary siphons of Petri nets and their application to deadlock prevention in flexible manufacturing systems,” IEEE Trans. Syst, Man, Cybern. A, Syst., Humans, vol. 34, no. 1, pp. 38–51, Jan. 2004.

H. Boucheneb, K. Barkaoui, Q. Xing, K. Wang, G. Y. Liu, and Z. W. Li, “Time based deadlock prevention for Petri nets,” Automatica, vol. 137, 2022, Art. no. 110119.

T. Murata, “Petri nets: properties, analysis and applications,” Proc. IEEE, vol. 77, no. 4, pp. 541–580, Apr. 1989.

T. Qin, Y. F. Dong, L. Yin, and Z. W. Li, “Liveness enforcement for production systems modeled by time Petri nets,” Inf. Sci., vol. 648, no. 119564, Nov. 2023.
