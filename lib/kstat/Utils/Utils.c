/*
 * This file was generated automatically by ExtUtils::ParseXS version 3.24 from the
 * contents of Utils.xs. Do not edit this file, edit Utils.xs instead.
 *
 *    ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "Utils.xs"
/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
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
 * Copyright (c) 1999 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#pragma ident	"%Z%%M%	%I%	%E% SMI"

/*
 * Utils.xs contains XS wrappers for utility functions needed initially by
 * Sun::Solaris::Kstat, but that should prove generally useful as well.
 */

/* Solaris includes */
#include <libgen.h>
#include <libintl.h>

/* Perl XS includes */
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

/*
 * The XS code exported to perl is below here.  Note that the XS preprocessor
 * has its own commenting syntax, so all comments from this point on are in
 * that form.
 */

#line 59 "Utils.c"
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

#line 201 "Utils.c"

XS_EUPXS(XS_Sun__Solaris__Utils_gmatch); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Utils_gmatch)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "str, pattern");
    {
	char *	str = (char *)SvPV_nolen(ST(0))
;
	char *	pattern = (char *)SvPV_nolen(ST(1))
;
	int	RETVAL;
	dXSTARG;

	RETVAL = gmatch(str, pattern);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Utils_gettext); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Utils_gettext)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "msgid");
    {
	char *	msgid = (char *)SvPV_nolen(ST(0))
;
	char *	RETVAL;
	dXSTARG;

	RETVAL = gettext(msgid);
	sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Utils_dcgettext); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Utils_dcgettext)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "domainname, msgid, category");
    {
	char *	domainname = (char *)SvPV_nolen(ST(0))
;
	char *	msgid = (char *)SvPV_nolen(ST(1))
;
	int	category = (int)SvIV(ST(2))
;
	char *	RETVAL;
	dXSTARG;

	RETVAL = dcgettext(domainname, msgid, category);
	sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Utils_dgettext); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Utils_dgettext)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "domainname, msgid");
    {
	char *	domainname = (char *)SvPV_nolen(ST(0))
;
	char *	msgid = (char *)SvPV_nolen(ST(1))
;
	char *	RETVAL;
	dXSTARG;

	RETVAL = dgettext(domainname, msgid);
	sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Utils_textdomain); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Utils_textdomain)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "domain");
    {
	char *	domain = (char *)SvPV_nolen(ST(0))
;
	char *	RETVAL;
	dXSTARG;

	RETVAL = textdomain(domain);
	sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sun__Solaris__Utils_bindtextdomain); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sun__Solaris__Utils_bindtextdomain)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "domain, dirname");
    {
	char *	domain = (char *)SvPV_nolen(ST(0))
;
	char *	dirname = (char *)SvPV_nolen(ST(1))
;
	char *	RETVAL;
	dXSTARG;

	RETVAL = bindtextdomain(domain, dirname);
	sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
    }
    XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS_EXTERNAL(boot_Sun__Solaris__Utils); /* prototype to pass -Wmissing-prototypes */
XS_EXTERNAL(boot_Sun__Solaris__Utils)
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

        (void)newXSproto_portable("Sun::Solaris::Utils::gmatch", XS_Sun__Solaris__Utils_gmatch, file, "$$");
        (void)newXSproto_portable("Sun::Solaris::Utils::gettext", XS_Sun__Solaris__Utils_gettext, file, "$");
        (void)newXSproto_portable("Sun::Solaris::Utils::dcgettext", XS_Sun__Solaris__Utils_dcgettext, file, "$$$");
        (void)newXSproto_portable("Sun::Solaris::Utils::dgettext", XS_Sun__Solaris__Utils_dgettext, file, "$$");
        (void)newXSproto_portable("Sun::Solaris::Utils::textdomain", XS_Sun__Solaris__Utils_textdomain, file, "$");
        (void)newXSproto_portable("Sun::Solaris::Utils::bindtextdomain", XS_Sun__Solaris__Utils_bindtextdomain, file, "$$");
#if (PERL_REVISION == 5 && PERL_VERSION >= 9)
  if (PL_unitcheckav)
       call_list(PL_scopestack_ix, PL_unitcheckav);
#endif
    XSRETURN_YES;
}
