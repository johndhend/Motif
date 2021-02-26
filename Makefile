# $FreeBSD$

PORTNAME=	Motif
DISTVERSION=	2.5.0
CATEGORIES=	x11-wm
MASTER_SITES=	https://github.com/johndhend/Motif/blob/main/

MAINTAINER=	johndhend@icloud.com
COMMENT=	Motif Window Manager and X app dev kit

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYRIGHT.MOTIF

USES_XORG=	x11 xext xt xmu sm ice
USE_LDCONFIG=   yes
MANDIRS=	$(PREFIX)/Motif/man

MAKE_JOBS_UNSAFE= yes

.include <bsd.port.mk>
