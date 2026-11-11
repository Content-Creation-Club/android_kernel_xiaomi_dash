=================================
Maintaining the dash ACK boundary
=================================

This tree builds an ACK-derived core kernel and a separate MediaTek device
module set. Keep local changes in three groups: boot compatibility, generic
features, and device diagnostics. The existing mixed-build entry points own
that split; moving directories or rebuilding a second workspace is unnecessary.

Compare against ACK without switching branches
=============================================

In the maintained workspace, ``ack/android15-6.6`` is the local Google ACK
reference. Compare effective source changes, rather than counting commits that
may have been merged or reverted::

    git diff --stat ack/android15-6.6 HEAD
    git diff ack/android15-6.6 HEAD -- drivers/ufs/
    git show ack/android15-6.6:drivers/ufs/core/ufshcd.c

Uncommitted source changes are shown separately by ``git diff``. Record the
exact ACK and dash revisions when reporting a numerical comparison.

Boot compatibility
==================

* UFS registers the device WLUN driver from host initialization. LK appends
  ``initcall_blacklist=ufshcd_core_init``, so the standard core initcall cannot
  be the only registration path with the current bootloader.
* ``CONFIG_ANDROID_DSU_AVB_BYPASS`` supplies an orange bootconfig view to PID 1
  until its first exec of ``/system/bin/init``. This is a first-stage AVB policy
  adaptation, described in ``android-dsu-avb.rst``. A ramdisk-fstab replacement
  remains a separate boot experiment; it has not replaced this helper.
* The firmware search path includes ``/odm/firmware`` and ``/vendor/firmware``.
  Preserve device firmware lookup until an alternative path has been verified.

Generic features and tuning
===========================

Zstd 1.5.7, the direct ZRAM backends and ``algorithm_params`` compression-level
interface, THP changes, BBR/FQ defaults, and ThinLTO/AutoFDO are generic feature
choices. Maintain them separately from the reason a particular phone boots.
Dropping one of these features is a behavior change, not repository cleanup.

Keep the existing Zstd context types opaque at the legacy export boundary.
``lib/zstd/zstd_compress_ext.c`` contains the workspace helpers that need private
parameter definitions; ``zstd_compress_module.c`` uses the public wrapper API.
This separation avoids exposing the private compression-context layout through
the old module-version signatures while retaining the extension entry points.
Check the generated symbol CRCs against the chosen ACK baseline after changing
these wrappers; public function spelling alone does not establish compatibility.

Device diagnostics
==================

The core configuration has MTD disabled, while the device-module configuration
builds and ships MTD, block2mtd and mtdoops in the vendor ramdisk. The local
module parameters, Xiaomi pmsg device-tree binding and reboot-log format are
part of that device-side contract.

Most MTK clock, printk, timer, MTE and UFS debugging additions are conditional
and disabled in the current core configuration. If enabling one, check its
module consumers and any private symbols or structure fields together. Do not
infer core Image contents from the device-module configuration alone.

Standard capability policy
==========================

``security/commoncap.c:cap_capable()`` checks ``cap_effective`` when it reaches
the credential's user namespace, matching ACK. The former unconditional
success at this point came from Xiaomi's original public import
``2d28e280ea36``, which did not explain its purpose.

This policy is independent of SELinux, GKI symbol protection and first-stage
AVB adaptation. Validate it by dropping a disposable test process's own
capabilities and checking that a bounding-set change requires CAP_SETPCAP.
Check affected vendor services rather than reinstating a global exception.

Build policy and official GKI replacement
========================================

The current ``.user`` mixed build uses the modified ``kernel-6.6`` as its base,
with symbol trimming and GKI protected-export enforcement disabled. Module CRC
version checks and signature handling still exist. The device configuration
is applied to the module build, not folded wholesale into the core Image.

The local workspace ``device.bazelrc`` enables Kleaf's persistent Kbuild object
directory under ``out/bazel/cache`` in the kernel workspace. It is independent
of the ROM output and its prepared build graph. The retained Bazel output base
and repository cache remain separate layers; source edits reuse Kbuild objects
after the first local-mode build populates them.

The existing ``.ack`` target selects the older ``common-6.6`` debug target; it
does not select an exact official release. Reuse the mixed-build mechanism when
changing the base, but choose the source or prebuilt release explicitly.

Official GKI replacement additionally requires matching module CRCs, permitted
imports and exports, correctly owned GKI modules, and verified boot and power
management behavior. Preserving a small ACK patch set and supporting an
unmodified official GKI binary are separate maintenance targets.
