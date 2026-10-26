# android_kernel_xiaomi_dash

English|[简体中文](README_zh.md)

- Linux kernel entry point docs: [README](README)
- How do I submit patches to Android Common Kernels: [ACK_PATCH_SUBMISSION](README_ACK_PATCH_SUBMISSION.md)

This is an unofficial kernel tree for the Redmi Turbo 5 Max (codename `dash`), spun up for my personal ~~LineageOS 23.2 bringup~~ ~~suffering through MediaTek's finest hot garbage~~ tinkering pleasure.

**Heads up:** Weird bugs of varying severity may still be lurking around, and **DO NOT flash this directly over HyperOS.**

Due to copyright and licensing being a total minefield, I’ve tried my best to sort things out. Mismatched copyright headers, wrong licenses, or accidental attribution mess-ups might still exist.

If you spot code that belongs to you and isn't properly credited, please open an Issue, and I'll sort it out ASAP.

## Related Repositories

Full builds and device bringups require the following trees:

- [Kernel build](https://github.com/Content-Creation-Club/android_kernel_xiaomi_dash_build)
- [Bazel MGK rules](https://github.com/Content-Creation-Club/android_kernel_xiaomi_dash_bazel_mgk_rules)
- [MediaTek device modules](https://github.com/Content-Creation-Club/android_kernel_xiaomi_dash_device_modules)
- [MediaTek kernel modules](https://github.com/Content-Creation-Club/android_kernel_xiaomi_dash_mtk_modules)

~~No prebuilt boot images provided. Build it yourself.~~

## Build

```bash
mkdir -p dash-kernel && cd dash-kernel
repo init -u git@github.com:Content-Creation-Club/android_kernel_xiaomi_dash_build.git -b dash-w-oss --depth=1
repo sync -c -j8
cd kernel/xiaomi/dash
./build.sh
```

## Disclaimer

**YOUR WARRANTY IS NOW VOID.**

This project is provided **"AS IS"** without warranty of any kind. I do NOT guarantee that it will:

- Compile cleanly on your machine
- Boot, stay alive, or run stably
- Play nice with your specific firmware, vendor blob set, or bootloader revision
- Not cause sudden data loss, bootloops, hard bricks, or thermonuclear war
- Prevent your device from catching fire, exploding, summoning demons, or dying permanently etc.

Only proceed if you actually understand the Android boot chain, partition maps, kernel building, and unbricking/EDL recovery workflows. **Any risk of building, flashing, or bricking your phone rests entirely on you.**

This project is NOT affiliated with or endorsed by Xiaomi, MediaTek, Google, or the LineageOS project.

## Reimplemented / Injected Modules

These modules were reconstructed through iterative disassembly and reverse-engineering of stock binaries from `OS3.0.305.0.WPLCNXM` using Codex/Claude Code(`gpt-5.6-sol`, `gpt-6-astra`, `gpt-6.1-sol`) / ChatGPT (`gpt-5.6-pro`), alongside references to previously published code from Xiaomi and the open-source community.

**"it compiles" does not mean "it works." YES, THIS IS TRUE. CHECK AND TEST YOURSELF.**

If you want those or more modules works better, DIY and send a PR, thank you.

| Modules | | |
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

## Licensing

Individual files remain subject to their original upstream licenses. See [COPYING](COPYING) and any applicable license notices.

In addition (and purely in spirit), please observe the non-legally-binding moral terms of the [Don't Be A Dick License v1.2](DBAD.md) and [The Fuck Around And Find Out License v0.2](FAFOL.md).

**TL;DR:** DON'T BE A DICK, DIY your own stuff, and remember: FUCK AROUND AND FIND OUT.
