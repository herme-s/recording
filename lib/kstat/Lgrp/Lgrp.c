/*
 * This file was generated automatically by ExtUtils::ParseXS version 3.24 from the
 * contents of Lgrp.xs. Do not edit this file, edit Lgrp.xs instead.
 *
 *    ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "Lgrp.xs"
/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#pragma ident	"%Z%%M%	%I%	%E% SMI"

/*
 * Lgrp.xs contains XS wrappers for the system locality group library
 * liblgrp(3LIB).
 */

#include <sys/errno.h>
#include <sys/lgrp_user.h>

/*
 * On i386 Solaris defines SP, which conflicts with the perl definition of SP
 * We don't need the Solaris one, so get rid of it to avoid warnings.
 */
#undef SP

/* Perl XS includes. */
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

/* Return undef in scalar context and empty list in list context */
#define LGRP_BADVAL() {			\
	if (GIMME_V == G_ARRAY)		\
			XSRETURN_EMPTY;	\
		else			\
			XSRETURN_UNDEF;	\
}

/*
 * Push all values from input array onto the perl return stack.
 */
#define	PUSHARRAY(array, nitems)	\
{					\
	int x;				\
					\
	if (nitems < 0) {		\
		LGRP_BADVAL()		\
	} else if (nitems > 0) {	\
		EXTEND(SP, nitems);	\
		for (x = 0; x < nitems; x++) {	\
			PUSHs(sv_2mortal(newSVnv(array[x])));	\
		}			\
	}				\
}

/*
 * Several constants are not present in the first version of the Lgrp API,
 * we define them here.
 *
 * lgrp_resources() and lgrp_latency_cookie() only appear in API v2. If the
 * module is linked with old version of liblgrp(3LIB) there is no lgrp_resources
 * symbol in the library and perl wrapper returns empty list and sets errno to
 * EINVAL.
 *
 * The lgrp_latency_cookie() is emulated using lgrp_latency().
 */
#if LGRP_VER_CURRENT == 1
#define	LGRP_CONTENT_ALL LGRP_CONTENT_HIERARCHY
#define	LGRP_LAT_CPU_TO_MEM 	0
#define LGRP_RSRC_CPU           0       /* CPU resources */
#define LGRP_RSRC_MEM           1       /* memory resources */

#define LGRP_RESOURCES(c, lgrp, type) \
	{ errno = EINVAL; LGRP_BADVAL(); }

/*
 * Simulate lgrp_latency_cookie() which just fails. This macro is never called
 * and we just define it so that the C compiler will not complain about the
 * missing symbol.
 */
#define	lgrp_latency_cookie(c, f, t, b) (errno = EINVAL, -1)

#else
#define	LGRP_RESOURCES(c, lgrp, type) { \
	int nr;				\
	lgrp_id_t *lgrps;		\
					\
	errno = 0;			\
	nr = lgrp_resources(c, lgrp, NULL, 0, type);	\
	if (nr < 0)			\
		LGRP_BADVAL();		\
	if (GIMME_V == G_SCALAR)	\
		XSRETURN_IV(nr);	\
	if (nr == 0) {			\
		XSRETURN_EMPTY;		\
	} else if (New(0, lgrps, nr, lgrp_id_t) == NULL) {	\
		errno = ENOMEM;		\
		LGRP_BADVAL();		\
	} else {			\
		nr = lgrp_resources(c, lgrp, lgrps, nr, type);	\
		PUSHARRAY(lgrps, nr);	\
		Safefree(lgrps);	\
	}				\
}
#endif

/*
 * Special version of lgrp_latency_cookie(). Use lgrp_latency() for liblgrp V1
 * and lgrp_latency_cookie for V2.
 */
static int
_lgrp_latency_cookie(lgrp_cookie_t cookie, lgrp_id_t from, lgrp_id_t to,
				   int between)
{
	return (LGRP_VER_CURRENT < 2 ?
	    lgrp_latency(from, to) :
	    lgrp_latency_cookie(cookie, from, to, between));
}

/*
 * Most functions in liblgrp return -1 on failure. The perl equivalent returns
 * 'undef' instead. The macro should be call after the RETVAL is set to the
 * return value of the function.
 */
#define	RETURN_UNDEF_IF_FAIL { if (RETVAL < 0) XSRETURN_UNDEF; }

/*
 * End of C part, start of XS part.
 *
 * The XS code exported to perl is below here.  Note that the XS preprocessor
 * has its own commenting syntax, so all comments from this point on are in
 * that form.
 */

#line 162 "Lgrp.c"
#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#ifndef dVAR
#  define dVAR		dNOOP
#endif


/* This stuff is not part of the API! You have been warned. */
#ifndef PERL_VERSION_DECIMAL
#  define PERL_VERSION_DECIMAL(r,v,s) (r*1000000 + v*1000 + s)
#endif
#ifndef PERL_DECIMAL_VERSION
#  define PERL_DECIMAL_VERSION \
	  PERL_VERSION_DECIMAL(PERL_REVISION,PERL_VERSION,PERL_SUBVERSION)
#endif
#ifndef PERL_VERSION_GE
#  define PERL_VERSION_GE(r,v,s) \
	  (PERL_DECIMAL_VERSION >= PERL_VERSION_DECIMAL(r,v,s))
#endif
#ifndef PERL_VERSION_LE
#  define PERL_VERSION_LE(r,v,s) \
	  (PERL_DECIMAL_VERSION <= PERL_VERSION_DECIMAL(r,v,s))
#endif

/* XS_INTERNAL is the explicit static-linkage variant of the default
 * XS macro.
 *
 * XS_EXTERNAL is the same as XS_INTERNAL except it does not include
 * "STATIC", ie. it exports XSUB symbols. You probably don't want that
 * for anything but the BOOT XSUB.
 *
 * See XSUB.h in core!
 */


/* TODO: This might be compatible further back than 5.10.0. */
#if PERL_VERSION_GE(5, 10, 0) && PERL_VERSION_LE(5, 15, 1)
#  undef XS_EXTERNAL
#  undef XS_INTERNAL
#  if defined(__CYGWIN__) && defined(USE_DYNAMIC_LOADING)
#    define XS_EXTERNAL(name) __declspec(dllexport) XSPROTO(name)
#    define XS_INTERNAL(name) STATIC XSPROTO(name)
#  endif
#  if defined(__SYMBIAN32__)
#    define XS_EXTERNAL(name) EXPORT_C XSPROTO(name)
#    define XS_INTERNAL(name) EXPORT_C STATIC XSPROTO(name)
#  endif
#  ifndef XS_EXTERNAL
#    if defined(HASATTRIBUTE_UNUSED) && !defined(__cplusplus)
#      define XS_EXTERNAL(name) void name(pTHX_ CV* cv __attribute__unused__)
#      define XS_INTERNAL(name) STATIC void name(pTHX_ CV* cv __attribute__unused__)
#    else
#      ifdef __cplusplus
#        define XS_EXTERNAL(name) extern "C" XSPROTO(name)
#        define XS_INTERNAL(name) static XSPROTO(name)
#      else
#        define XS_EXTERNAL(name) XSPROTO(name)
#        define XS_INTERNAL(name) STATIC XSPROTO(name)
#      endif
#    endif
#  endif
#endif

/* perl >= 5.10.0 && perl <= 5.15.1 */


/* The XS_EXTERNAL macro is used for functions that must not be static
 * like the boot XSUB of a module. If perl didn't have an XS_EXTERNAL
 * macro defined, the best we can do is assume XS is the same.
 * Dito for XS_INTERNAL.
 */
#ifndef XS_EXTERNAL
#  define XS_EXTERNAL(name) XS(name)
#endif
#ifndef XS_INTERNAL
#  define XS_INTERNAL(name) XS(name)
#endif

/* Now, finally, after all this mess, we want an ExtUtils::ParseXS
 * internal macro that we're free to redefine for varying linkage due
 * to the EXPORT_XSUB_SYMBOLS XS keyword. This is internal, use
 * XS_EXTERNAL(name) or XS_INTERNAL(name) in your code if you need to!
 */

#undef XS_EUPXS
#if defined(PERL_EUPXS_ALWAYS_EXPORT)
#  define XS_EUPXS(name) XS_EXTERNAL(name)
#else
   /* default to internal */
#  define XS_EUPXS(name) XS_INTERNAL(name)
#endif

#ifndef PERL_ARGS_ASSERT_CROAK_XS_USAGE
#define PERL_ARGS_ASSERT_CROAK_XS_USAGE assert(cv); assert(params)

/* prototype to pass -Wmissing-prototypes */
STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params);

STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params)
{
    const GV *const gv = CvGV(cv);

    PERL_ARGS_ASSERT_CROAK_XS_USAGE;

    if (gv) {
        const char *const gvname = GvNAME(gv);
        const HV *const stash = GvSTASH(gv);
        const char *const hvname = stash ? HvNAME(stash) : NULL;

        if (hvname)
            Perl_croak(aTHX_ "Usage: %s::%s(%s)", hvname, gvname, params);
        else
            Perl_croak(aTHX_ "Usage: %s(%s)", gvname, params);
    } else {
        /* Pants. I don't think that it should be possible to get here. */
        Perl_croak(aTHX_ "Usage: CODE(0x%"UVxf")(%s)", PTR2UV(cv), params);
    }
}
#undef  PERL_ARGS_ASSERT_CROAK_XS_USAGE

#ifdef PERL_IMPLICIT_CONTEXT
#define croak_xs_usage(a,b)    S_croak_xs_usage(aTHX_ a,b)
#else
#define croak_xs_usage        S_croak_xs_usage
#endif

#endif

/* NOTE: the prototype of newXSproto() is different in versions of perls,
 * so we define a portable version of newXSproto()
 */
#ifdef newXS_flags
#define newXSproto_portable(name, c_impl, file, proto) newXS_flags(name, c_impl, file, proto, 0)
#else
#define newXSproto_portable(name, c_impl, file, proto) (PL_Sv=(SV*)newXS(name, c_impl, file), sv_setpv(PL_Sv, proto), (CV*)PL_Sv)
#endif /* !defined(newXS_flags) */

#line 304 "Lgrp.c"

XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_init); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_init)
{
    dVAR; dXSARGS;
    if (items < 0 || items > 1)
       croak_xs_usage(cv,  "view= LGRP_VIEW_OS");
    {
	lgrp_cookie_t	RETVAL;
	dXSTARG;
	lgrp_view_t	view;

	if (items < 1)
	    view = LGRP_VIEW_OS;
	else {
	    view = (lgrp_view_t)SvUV(ST(0))
;
	}

	RETVAL = lgrp_init(view);
#line 202 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
#line 327 "Lgrp.c"
	XSprePUSH; PUSHu((UV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_view); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_view)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "cookie");
    {
	lgrp_cookie_t	cookie = (lgrp_cookie_t)SvUV(ST(0))
;
	lgrp_view_t	RETVAL;
	dXSTARG;

	RETVAL = lgrp_view(cookie);
#line 208 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
#line 349 "Lgrp.c"
	XSprePUSH; PUSHu((UV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_affinity_get); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_affinity_get)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "idtype, id, lgrp");
    {
	idtype_t	idtype = (idtype_t)SvIV(ST(0))
;
	id_t	id = (id_t)SvIV(ST(1))
;
	lgrp_id_t	lgrp = (lgrp_id_t)SvIV(ST(2))
;
	lgrp_affinity_t	RETVAL;
	dXSTARG;

	RETVAL = lgrp_affinity_get(idtype, id, lgrp);
#line 216 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
#line 375 "Lgrp.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_affinity_set); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_affinity_set)
{
    dVAR; dXSARGS;
    if (items != 4)
       croak_xs_usage(cv,  "idtype, id, lgrp, affinity");
    {
	idtype_t	idtype = (idtype_t)SvIV(ST(0))
;
	id_t	id = (id_t)SvIV(ST(1))
;
	lgrp_id_t	lgrp = (lgrp_id_t)SvIV(ST(2))
;
	lgrp_affinity_t	affinity = (lgrp_affinity_t)SvIV(ST(3))
;
	int	RETVAL;
	dXSTARG;

	RETVAL = lgrp_affinity_set(idtype, id, lgrp, affinity);
#line 225 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
	XSRETURN_YES;
#line 404 "Lgrp.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_cookie_stale); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_cookie_stale)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "cookie");
    {
	lgrp_cookie_t	cookie = (lgrp_cookie_t)SvUV(ST(0))
;
	int	RETVAL;
	dXSTARG;

	RETVAL = lgrp_cookie_stale(cookie);
#line 232 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
#line 426 "Lgrp.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_fini); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_fini)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "cookie");
    {
	lgrp_cookie_t	cookie = (lgrp_cookie_t)SvUV(ST(0))
;
	int	RETVAL;
	dXSTARG;

	RETVAL = lgrp_fini(cookie);
#line 238 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
	XSRETURN_YES;
#line 449 "Lgrp.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_home); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_home)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "idtype, id");
    {
	idtype_t	idtype = (idtype_t)SvIV(ST(0))
;
	id_t	id = (id_t)SvIV(ST(1))
;
	lgrp_id_t	RETVAL;
	dXSTARG;

	RETVAL = lgrp_home(idtype, id);
#line 246 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
#line 473 "Lgrp.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_latency); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_latency)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "from, to");
    {
	int	RETVAL;
	dXSTARG;
	lgrp_id_t	from = (lgrp_id_t)SvIV(ST(0))
;
	lgrp_id_t	to = (lgrp_id_t)SvIV(ST(1))
;

	RETVAL = lgrp_latency(from, to);
#line 251 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
#line 497 "Lgrp.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_mem_size); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_mem_size)
{
    dVAR; dXSARGS;
    if (items != 4)
       croak_xs_usage(cv,  "cookie, lgrp, type, content");
    {
	lgrp_cookie_t	cookie = (lgrp_cookie_t)SvUV(ST(0))
;
	lgrp_id_t	lgrp = (lgrp_id_t)SvIV(ST(1))
;
	int	type = (int)SvIV(ST(2))
;
	lgrp_content_t	content = (lgrp_content_t)SvIV(ST(3))
;
	lgrp_mem_size_t	RETVAL;
	dXSTARG;

	RETVAL = lgrp_mem_size(cookie, lgrp, type, content);
#line 260 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
#line 525 "Lgrp.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_nlgrps); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_nlgrps)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "cookie");
    {
	lgrp_cookie_t	cookie = (lgrp_cookie_t)SvUV(ST(0))
;
	int	RETVAL;
	dXSTARG;

	RETVAL = lgrp_nlgrps(cookie);
#line 266 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
#line 547 "Lgrp.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_root); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_root)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "cookie");
    {
	lgrp_cookie_t	cookie = (lgrp_cookie_t)SvUV(ST(0))
;
	lgrp_id_t	RETVAL;
	dXSTARG;

	RETVAL = lgrp_root(cookie);
#line 272 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
#line 569 "Lgrp.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_version); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_version)
{
    dVAR; dXSARGS;
    if (items < 0 || items > 1)
       croak_xs_usage(cv,  "version= LGRP_VER_NONE");
    {
	int	RETVAL;
	dXSTARG;
	int	version;

	if (items < 1)
	    version = LGRP_VER_NONE;
	else {
	    version = (int)SvIV(ST(0))
;
	}

	RETVAL = lgrp_version(version);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_latency_cookie); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_latency_cookie)
{
    dVAR; dXSARGS;
    if (items < 3 || items > 4)
       croak_xs_usage(cv,  "cookie, from, to, between= 0");
    {
	int	RETVAL;
	dXSTARG;
	lgrp_cookie_t	cookie = (lgrp_cookie_t)SvUV(ST(0))
;
	lgrp_id_t	from = (lgrp_id_t)SvIV(ST(1))
;
	lgrp_id_t	to = (lgrp_id_t)SvIV(ST(2))
;
	int	between;

	if (items < 4)
	    between = 0;
	else {
	    between = (int)SvIV(ST(3))
;
	}
#line 284 "Lgrp.xs"
	RETVAL = _lgrp_latency_cookie(cookie, from, to, between);
#line 626 "Lgrp.c"
#line 286 "Lgrp.xs"
	RETURN_UNDEF_IF_FAIL;
#line 629 "Lgrp.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_children); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_children)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "cookie, lgrp");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	lgrp_cookie_t	cookie = (lgrp_cookie_t)SvUV(ST(0))
;
	lgrp_id_t	lgrp = (lgrp_id_t)SvIV(ST(1))
;
#line 310 "Lgrp.xs"
	lgrp_id_t *lgrps;
	int	count;
#line 652 "Lgrp.c"
#line 313 "Lgrp.xs"
	errno = 0;
	if ((count = lgrp_children(cookie, lgrp, NULL, 0)) < 0)
		LGRP_BADVAL();

	if (GIMME_V == G_SCALAR)
		XSRETURN_IV(count);

	if (count > 0) {
		if (New(0, lgrps, count, lgrp_id_t) == NULL) {
			errno = ENOMEM;
			LGRP_BADVAL();
		} else {
			count = lgrp_children(cookie, lgrp, lgrps, count);
			PUSHARRAY(lgrps, count);
			Safefree(lgrps);
		}
	}
#line 671 "Lgrp.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_parents); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_parents)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "cookie, lgrp");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	lgrp_cookie_t	cookie = (lgrp_cookie_t)SvUV(ST(0))
;
	lgrp_id_t	lgrp = (lgrp_id_t)SvIV(ST(1))
;
#line 339 "Lgrp.xs"
	lgrp_id_t *lgrps;
	int count;
#line 694 "Lgrp.c"
#line 342 "Lgrp.xs"
	errno = 0;
	if ((count = lgrp_parents(cookie, lgrp, NULL, 0)) < 0)
		LGRP_BADVAL();

	if (GIMME_V == G_SCALAR)
		XSRETURN_IV(count);

	if (count > 0) {
		if (New(0, lgrps, count, lgrp_id_t) == NULL) {
			errno = ENOMEM;
			LGRP_BADVAL();
		} else {
			count = lgrp_parents(cookie, lgrp, lgrps, count);
			PUSHARRAY(lgrps, count);
			Safefree(lgrps);
		}
	}
#line 713 "Lgrp.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_cpus); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_cpus)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "cookie, lgrp, content");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	lgrp_cookie_t	cookie = (lgrp_cookie_t)SvUV(ST(0))
;
	lgrp_id_t	lgrp = (lgrp_id_t)SvIV(ST(1))
;
	lgrp_content_t	content = (lgrp_content_t)SvIV(ST(2))
;
#line 370 "Lgrp.xs"
	int ncpus;
	processorid_t *cpus;
#line 738 "Lgrp.c"
#line 373 "Lgrp.xs"
	errno = 0;
	if ((ncpus = lgrp_cpus(cookie, lgrp, NULL, 0, content)) < 0)
		LGRP_BADVAL();

	if (GIMME_V == G_SCALAR)
		XSRETURN_IV(ncpus);

	if (ncpus > 0) {
		if (New(0, cpus, ncpus, processorid_t) == NULL) {
			errno = ENOMEM;
			LGRP_BADVAL();
		} else {
			ncpus = lgrp_cpus(cookie, lgrp, cpus, ncpus, content);
			PUSHARRAY(cpus, ncpus);
			Safefree(cpus);
		}
	}
#line 757 "Lgrp.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_resources); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Lgrp_lgrp_resources)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "cookie, lgrp, type");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	lgrp_cookie_t	cookie = (lgrp_cookie_t)SvUV(ST(0))
;
	lgrp_id_t	lgrp = (lgrp_id_t)SvIV(ST(1))
;
	int	type = (int)SvIV(ST(2))
;
#line 397 "Lgrp.xs"
	LGRP_RESOURCES(cookie, lgrp, type);
#line 781 "Lgrp.c"
	PUTBACK;
	return;
    }
}

#ifdef __cplusplus
extern "C"
#endif
XS_EXTERNAL(boot_Sun__Solaris__Lgrp); /* prototype to pass -Wmissing-prototypes */
XS_EXTERNAL(boot_Sun__Solaris__Lgrp)
{
    dVAR; dXSARGS;
#if (PERL_REVISION == 5 && PERL_VERSION < 9)
    char* file = __FILE__;
#else
    const char* file = __FILE__;
#endif

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
#ifdef XS_APIVERSION_BOOTCHECK
    XS_APIVERSION_BOOTCHECK;
#endif
    XS_VERSION_BOOTCHECK;

        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_init", XS_Sun__Solaris__Lgrp_lgrp_init, file, ";$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_view", XS_Sun__Solaris__Lgrp_lgrp_view, file, "$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_affinity_get", XS_Sun__Solaris__Lgrp_lgrp_affinity_get, file, "$$$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_affinity_set", XS_Sun__Solaris__Lgrp_lgrp_affinity_set, file, "$$$$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_cookie_stale", XS_Sun__Solaris__Lgrp_lgrp_cookie_stale, file, "$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_fini", XS_Sun__Solaris__Lgrp_lgrp_fini, file, "$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_home", XS_Sun__Solaris__Lgrp_lgrp_home, file, "$$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_latency", XS_Sun__Solaris__Lgrp_lgrp_latency, file, "$$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_mem_size", XS_Sun__Solaris__Lgrp_lgrp_mem_size, file, "$$$$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_nlgrps", XS_Sun__Solaris__Lgrp_lgrp_nlgrps, file, "$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_root", XS_Sun__Solaris__Lgrp_lgrp_root, file, "$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_version", XS_Sun__Solaris__Lgrp_lgrp_version, file, ";$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_latency_cookie", XS_Sun__Solaris__Lgrp_lgrp_latency_cookie, file, "$$$;$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_children", XS_Sun__Solaris__Lgrp_lgrp_children, file, "$$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_parents", XS_Sun__Solaris__Lgrp_lgrp_parents, file, "$$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_cpus", XS_Sun__Solaris__Lgrp_lgrp_cpus, file, "$$$");
        (void)newXSproto_portable("Sun::Solaris::Lgrp::lgrp_resources", XS_Sun__Solaris__Lgrp_lgrp_resources, file, "$$$");

    /* Initialisation Section */

#line 162 "Lgrp.xs"
	{
	HV *stash;

	stash = gv_stashpv("Sun::Solaris::Lgrp", TRUE);
	newCONSTSUB(stash, "LGRP_AFF_NONE", newSViv(LGRP_AFF_NONE));
	newCONSTSUB(stash, "LGRP_AFF_STRONG", newSViv(LGRP_AFF_STRONG));
	newCONSTSUB(stash, "LGRP_AFF_WEAK", newSViv(LGRP_AFF_WEAK));
	newCONSTSUB(stash, "LGRP_VER_CURRENT", newSViv(LGRP_VER_CURRENT));
	newCONSTSUB(stash, "LGRP_VER_NONE", newSViv(LGRP_VER_NONE));
	newCONSTSUB(stash, "LGRP_NONE", newSViv(LGRP_NONE));
	newCONSTSUB(stash, "LGRP_RSRC_CPU", newSViv(LGRP_RSRC_CPU));
	newCONSTSUB(stash, "LGRP_RSRC_MEM", newSViv(LGRP_RSRC_MEM));
	newCONSTSUB(stash, "LGRP_CONTENT_HIERARCHY",
			newSViv(LGRP_CONTENT_HIERARCHY));
	newCONSTSUB(stash, "LGRP_CONTENT_DIRECT", newSViv(LGRP_CONTENT_DIRECT));
	newCONSTSUB(stash, "LGRP_VIEW_CALLER", newSViv(LGRP_VIEW_CALLER));
	newCONSTSUB(stash, "LGRP_VIEW_OS", newSViv(LGRP_VIEW_OS));
	newCONSTSUB(stash, "LGRP_MEM_SZ_FREE", newSViv(LGRP_MEM_SZ_FREE));
	newCONSTSUB(stash, "LGRP_MEM_SZ_INSTALLED",
			newSViv(LGRP_MEM_SZ_INSTALLED));
	newCONSTSUB(stash, "LGRP_CONTENT_ALL", newSViv(LGRP_CONTENT_ALL));
	newCONSTSUB(stash, "LGRP_LAT_CPU_TO_MEM", newSViv(LGRP_LAT_CPU_TO_MEM));
	newCONSTSUB(stash, "P_PID", newSViv(P_PID));
	newCONSTSUB(stash, "P_LWPID", newSViv(P_LWPID));
	newCONSTSUB(stash, "P_MYID", newSViv(P_MYID));
	}

#line 855 "Lgrp.c"

    /* End of Initialisation Section */

#if (PERL_REVISION == 5 && PERL_VERSION >= 9)
  if (PL_unitcheckav)
       call_list(PL_scopestack_ix, PL_unitcheckav);
#endif
    XSRETURN_YES;
}

