/*-
* Copyright (c) 2014 Michihiro NAKAJIMA
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __LIBARCHIVE_BUILD
#error This header is only to be used internally to libarchive.
#endif

#ifndef ARCHIVE_HMAC_PRIVATE_H_INCLUDED
#define ARCHIVE_HMAC_PRIVATE_H_INCLUDED

#ifdef __APPLE__
#include <CommonCrypto/CommonHMAC.h>

typedef	CCHmacContext archive_hmac_sha1_ctx;

#elif defined(_WIN32) && !defined(__CYGWIN__)

typedef int archive_hmac_sha1_ctx;

#elif defined(HAVE_LIBNETTLE)
#include <nettle/hmac.h>

typedef	struct hmac_sha1_ctx archive_hmac_sha1_ctx;

#elif defined(HAVE_LIBCRYPTO)
#include <openssl/hmac.h>

typedef	HMAC_CTX archive_hmac_sha1_ctx;

#endif


/* HMAC */
#define archive_hmac_sha1_init(ctx, key, key_len)\
	__archive_hmac.__hmac_sha1_init(ctx, key, key_len)
#define archive_hmac_sha1_update(ctx, data, data_len)\
	__archive_hmac.__hmac_sha1_update(ctx, data, data_len)
#define archive_hmac_sha1_final(ctx, out, out_len)\
  	__archive_hmac.__hmac_sha1_final(ctx, out, out_len)
#define archive_hmac_sha1_cleanup(ctx)\
	__archive_hmac.__hmac_sha1_cleanup(ctx)


struct archive_hmac {
	/* HMAC */
	int (*__hmac_sha1_init)(archive_hmac_sha1_ctx *, const uint8_t *,
		size_t);
	void (*__hmac_sha1_update)(archive_hmac_sha1_ctx *, const uint8_t *,
		size_t);
	void (*__hmac_sha1_final)(archive_hmac_sha1_ctx *, uint8_t *, size_t *);
	void (*__hmac_sha1_cleanup)(archive_hmac_sha1_ctx *);
};

extern const struct archive_hmac __archive_hmac;
#endif /* ARCHIVE_HMAC_PRIVATE_H_INCLUDED */
