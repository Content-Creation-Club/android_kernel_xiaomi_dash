// SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause
/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under both the BSD-style license (found in the
 * LICENSE file in the root directory of this source tree) and the GPLv2 (found
 * in the COPYING file in the root directory of this source tree).
 * You may select, at your option, one of the above-listed licenses.
 */

#include <linux/module.h>
#include <linux/string.h>
#include <linux/zstd.h>

#include "compress/zstd_compress_internal.h"

/*
 * These helpers need private parameter definitions. Keep them separate from
 * the legacy exports so their context pointers stay opaque to genksyms.
 */
static size_t dummy_external_sequence_producer(
	void *sequenceProducerState,
	ZSTD_Sequence *outSeqs, size_t outSeqsCapacity,
	const void *src, size_t srcSize,
	const void *dict, size_t dictSize,
	int compressionLevel,
	size_t windowSize)
{
	(void)sequenceProducerState;
	(void)outSeqs; (void)outSeqsCapacity;
	(void)src; (void)srcSize;
	(void)dict; (void)dictSize;
	(void)compressionLevel;
	(void)windowSize;
	return ZSTD_SEQUENCE_PRODUCER_ERROR;
}

static void init_cctx_params_from_compress_params(
	ZSTD_CCtx_params *cctx_params,
	const zstd_compression_parameters *compress_params)
{
	ZSTD_parameters zstd_params;
	memset(&zstd_params, 0, sizeof(zstd_params));
	zstd_params.cParams = *compress_params;
	ZSTD_CCtxParams_init_advanced(cctx_params, zstd_params);
}

size_t zstd_cctx_workspace_bound_with_ext_seq_prod(
	const zstd_compression_parameters *compress_params)
{
	ZSTD_CCtx_params cctx_params;
	init_cctx_params_from_compress_params(&cctx_params, compress_params);
	ZSTD_CCtxParams_registerSequenceProducer(&cctx_params, NULL,
					      dummy_external_sequence_producer);
	return ZSTD_estimateCCtxSize_usingCCtxParams(&cctx_params);
}
EXPORT_SYMBOL(zstd_cctx_workspace_bound_with_ext_seq_prod);

size_t zstd_cstream_workspace_bound_with_ext_seq_prod(
	const zstd_compression_parameters *compress_params)
{
	ZSTD_CCtx_params cctx_params;
	init_cctx_params_from_compress_params(&cctx_params, compress_params);
	ZSTD_CCtxParams_registerSequenceProducer(&cctx_params, NULL,
					      dummy_external_sequence_producer);
	return ZSTD_estimateCStreamSize_usingCCtxParams(&cctx_params);
}
EXPORT_SYMBOL(zstd_cstream_workspace_bound_with_ext_seq_prod);
