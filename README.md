# Efficiency Step 2

`version 5.1`

`author: yghuang`

## 计算效率

### Usage

1. `make`

2. for local test, prepare a file list and then `./do.sh`

3. for submitting jobs, modify the following in `TemplateXXX.xml`:
    >
    > Line 12, first number (1.0) is DCA cut, and second number (20) is nHitsFit cut
    >
    > Line 25, input file list is the fDst file list

4. do `./preparePro.sh XXXX` and `./preparePbar.sh XXXX` to generate directories

5. `star-submit CsubmitPro.xml` and `star-submit CsubmitPbar.xml`

## Change log

05.04.2024 by yghuang (v5.1):

> 删除了TH1F和TH2F，因为可以直接从TEfficiency里面读出来，没必要单独存

11.03.2024 by yghuang (v5.0):

> 更改了接口，增加运行参数来调整cut
>
> 使用star-submit来提交批处理任务，因为大统计量embedding，之前的hadd之后本地运行的做法不再适用
>
>> 现在需要分别给proton和antiproton交任务，然后merge起来，因为不好处理两个长度不一样的list

14.12.2023 by yghuang (v4.0):

> EffUtil的头文件和实现分开，方便修改之后进行make
>
> 适配了3.0版本的fDst tree的格式

2023 Oct. 16 by yghuang (3.1):

> vz取50

2023 July 22 by yghuang (3.0):

> 现在加入了vz的依赖

2023 Jan. 14 by yghuang (2.2):

> 修正了计算方法。
>
> 增加了在主程序中设置cut的功能，不需要修改头文件。

2023 Jan. 13 by yghuang (2.1):

> 更新了二维的依赖。
>
> 根据一些测试，去掉了acceptance cut。

2023 Jan. 6 by yghuang (2.0):

> 按照新的规范进行重写。

2022 Apr. 1 by yghuang (1.1):

> Reimplement using C++.

2021 September 14 by yghuang (1.0):

> A release version.
