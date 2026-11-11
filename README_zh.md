# android_kernel_xiaomi_dash

[English](README.md)|简体中文

- Linux 内核入口说明：[README](README)
- How do I submit patches to Android Common Kernels：[ACK_PATCH_SUBMISSION](README_ACK_PATCH_SUBMISSION.md)

这是 Redmi Turbo 5 Max（代号 `dash`）的非官方内核仓库，用于个人 ~~LineageOS 23.2 设备适配工程~~ ~~尝尝发哥答辩咸淡~~ 美美把玩。

**先声明**，可能有潜在的严重程度不同的问题，以及不要把这玩意儿刷到 HyperOS 上。

由于牵扯的版权比较多，我已尽可能的尝试整理，不能排除出现版权头、许可证不匹配，以及我冒领版权等情况。

如果你发现某些代码的版权不属于我或者标错了，请直接开 Issue，我看到后会及时处理，非常感谢。

## 配套仓库

构建和设备适配还依赖以下仓库：

- [Kernel build](https://github.com/Content-Creation-Club/android_kernel_xiaomi_dash_build)
- [Bazel MGK rules](https://github.com/Content-Creation-Club/android_kernel_xiaomi_dash_bazel_mgk_rules)
- [MediaTek device modules](https://github.com/Content-Creation-Club/android_kernel_xiaomi_dash_device_modules)
- [MediaTek kernel modules](https://github.com/Content-Creation-Club/android_kernel_xiaomi_dash_mtk_modules)

~~没有直接提供内核成品的必要。~~

## 如何构建

```bash
mkdir -p dash-kernel && cd dash-kernel
repo init -u git@github.com:Content-Creation-Club/android_kernel_xiaomi_dash_build.git -b dash-w-oss --depth=1
repo sync -c -j8
cd kernel/xiaomi/dash
./build.sh
```

## 免责声明

本项目按现状提供，不保证：

- 成功编译
- 启动或稳定运行
- 与任意固件、vendor 或 bootloader 版本兼容
- 不会造成数据丢失、启动失败或设备损坏
- 手机着火，爆炸，丢进天德池，坠落深渊，再起不能

请在理解 Android 启动链、分区结构、内核构建和设备恢复方法后再使用。任何构建、刷写及设备操作风险均由使用者自行承担。

本项目与 Xiaomi、MediaTek、Google 及 LineageOS 项目没有隶属或官方支持关系。

## 补充模块

这些模块均由 Codex / Claude Code: (`gpt-5.6-sol`, `gpt-6-astra`, `gpt-6.1-sol`) / ChatGPT: (`gpt-5.6-pro`) 反复对 `OS3.0.305.0.WPLCNXM` 中的对应产物进行反汇编与逆向分析，或参考小米及其他项目曾经公开过的代码重新实现。

**构建通过说明不了相关模块都能正常用。对，就是这样。自己测能不能用。**

想要下面或更多模块变得好用？自己动手，再PR回来，谢谢。

| 模块 | | |
|---|---|---|
| `nt38771_touch_dash.ko` | `xiaomi_touch_dash.ko` | `xiaomi_spi_tee.ko` |
| `mitee.ko` | `mi_thermal_interface.ko` | `hwid.ko` |
| `debug_ext.ko` | `mi_memory.ko` | `ufs-mediatek-mod-ise.ko` |
| `perf-actuator.ko` | `miicmpfilter.ko` | `xm_power.ko` |
| `simtray.ko` | `crash_module.ko` | `mi_stack.ko` |
| `mi_ubt.ko` | `mi_ubt_test.ko` | `perf_helper.ko` |
| `millet_core.ko` | `millet_hs.ko` | `millet_sig.ko` |
| `millet_pkg.ko` | `binder_gki.ko` | `millet_binder.ko` |
| `millet_oem_cgroup.ko` | `mi_mem_epoll.ko` | `mi_mempool.ko` |
| `sla.ko` | `minet.ko` | `io_monitor.ko` |
| `lb.ko` | `mi_schedule.ko` | `xr-qi.ko` |
| `xr-qs.ko` | `miwill.ko` | `miwill_mode_redudancy.ko` |
| `metis.ko` | `migt.ko` |  |

## 许可证

各文件继续遵循其原有许可证。详细信息见 [COPYING](COPYING) 以及任何适用的许可声明。

如果你喜欢，请查看不叠加于许可证的 [Don't Be A Dick License v1.2](DBAD.md) 与 [The Fuck Around And Find Out License v0.2](FAFOL.md) 的道德使用条件。

别当傻逼，自己折腾，后果自负。
