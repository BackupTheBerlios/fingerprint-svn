/*
Miranda IM: the free IM client for Microsoft Windows

Copyright 2000-2006 Miranda ICQ/IM project,
all portions of this codebase are copyrighted to the people
listed in contributors.txt.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

/************************************************************************/
/*  Author: Artem Shpynov aka FYR     mailto:shpynov@nm.ru              */
/*  icons by Angeli-Ka                                                  */
/*  January 12, 2006													*/
/************************************************************************/



/************************************************************************/
/* This file contains data about appropriate MirVer values              */
/************************************************************************/

/*  
*   NOTE: Masks can contain '*' or '?' wild symbols
*   Asterics '*' symbol covers 'empty' symbol too e.g WildCompare("Tst","T*st*"), returns TRUE 
*   In order to handle situation 'at least one any sybol' use '?*' combination:
*   e.g WildCompare("Tst","T?*st*"), returns FALSE, but both WildCompare("Test","T?*st*") and
*   WildCompare("Teeest","T?*st*") return TRUE.
*
*   Function is 'dirt' case insensitive (it is ignore 5th bit (0x20) so it is no difference
*   beetween some symbols. But it is faster than valid converting to uppercase.
*
*   Mask can contain several submasks. In this case each submask (including first)
*   should start from '|' e.g: "|first*submask|second*mask".
*
*   ORDER OF RECORDS IS IMPORTANT: system search first suitable mask and returns it.
*   e.g. if MirVer is "Miranda IM" and first mask is "*im*" and second is "Miranda *" the 
*   result will be client associated with first mask, not second!
*   So in order to avoid such situation, place most generalised masks to latest place.
*
*   In order to get "Unknown" client, last mask should be "?*".
*/

KN_FP_MASK def_kn_fp_mask[]=
	{	// IconName			          Mask		          Icon caption    	    NULL  ICON_RESOURCE_ID
	{"client_Miranda,ICQJ_BM",  "|Miranda*ICQ v1.3*|Miranda IM*ICQ BM*",    "Miranda IM(ICQJ_BM)",	NULL, IDI_CLIENTMIRANDA_ICQBM,0xFF,6},
	{"client_Miranda,ICQJ",     "Miranda*ICQ v0.3*",    "Miranda IM(ICQJ)",   	NULL, IDI_CLIENTMIRANDA_ICQJ,0xFF,6},
	{"client_Miranda,ICQ_ISee", "Miranda*ICQ v0.4*",    "Miranda IM(ICQ_ISee)",	NULL, IDI_CLIENTMIRANDA_ICQISEE,0xFF,6},
	{"client_Miranda AimOscar", "Miranda*AimOscar*",    "Miranda AimOscar",     NULL, IDI_CLIENTMIRANDA_AIMOSCAR,0xFF,6},
	{"client_Miranda0.4",       "|Miranda*0.4*|Miranda IM 0.3*","Miranda IM 0.4.x-0.3.x", NULL, IDI_CLIENTMIRANDA04,0xFF,6},
	{"client_Miranda0.5",       "Miranda*0.5*",         "Miranda IM 0.5.x",     NULL, IDI_CLIENTMIRANDA05,0xFF,6},
	{"client_Miranda0.6",       "Miranda*0.6*",         "Miranda IM 0.6.x",     NULL, IDI_CLIENTMIRANDA06,0xFF,6},
	{"client_Miranda",          "Miranda*",             "Miranda IM",           NULL, IDI_CLIENTMIRANDA,0xFF,6},

	{"client_Gaim",             "*Gaim*",               "Gaim",                 NULL, IDI_CLIENTGAIM,0xFF,5},
	{"client_Trillian",         "Trillian*",            "Trillian",             NULL, IDI_CLIENTTRILLIAN,0xFF,5},
	{"client_Kopete",           "Kopete*",              "Kopete",               NULL, IDI_CLIENTKOPETE,0xFF,5},
	{"client_GnomeICU",         "GnomeICU*",            "GnomeICU",             NULL, IDI_CLIENTGNOMEICU,0xFF,5},
	{"client_IM2",              "IM2*",                 "IM2",                  NULL, IDI_CLIENTIM2,0xFF,5},
	{"client_alicq",            "alicq*",               "alicq",                NULL, IDI_CLIENTALICQ,0xFF,5},
	{"client_Licq",             "Licq*",                "Licq",                 NULL, IDI_CLIENTLICQ,0xFF,5},
	{"client_SIM",              "SIM*",                 "SIM",                  NULL, IDI_CLIENTSIM,0xFF,5},
	{"client_Qnext",            "QNext*",               "QNext",                NULL, IDI_CLIENTQNEXT,0xFF,5},
	{"client_Easy message",     "Easy Message*",        "Easy Message",         NULL, IDI_EASY_MESSAGE,0xFF,5},
	{"client_MRA",              "Mail.ru Agent*",       "MRA",                  NULL, IDI_CLIENTMRA,0xFF,5},
	{"client_Fire",             "Fire*",                "Fire",                 NULL, IDI_CLIENTFIRE,0xFF,5},
	{"client_Auttm",            "Auttm*",               "Auttm",                NULL, IDI_CLIENTAUTTM,0xFF,5},
	{"client_Proteus",          "Proteus*",             "Proteus",              NULL, IDI_CLIENTPROTEUS,0xFF,5},
	{"client_Instan-t",         "Instan-t*",            "Instan-t",             NULL, IDI_CLIENTINSTAN_T,0xFF,5},
	{"client_Skype v2.x",       "Skype*2*",             "Skype v2.x",           NULL, IDI_CLIENTSKYPE2,0xFF,5},
	{"client_Skype",            "Skype*",               "Skype",                NULL, IDI_CLIENTSKYPE,0xFF,5},
	{"client_Adium X",          "Adium X*",             "Adium X",              NULL, IDI_CLIENTADIUMX,0xFF,5},
	{"client_Meebo",            "Meebo*",               "Meebo",                NULL, IDI_CLIENTMEEBO,0xFF,5},

	{"client_Yahoo v5.x",       "<Yahoo 6*",            "Yahoo 5.x",            NULL, IDI_CLIENTYAHOO5,0xFF,8},
	{"client_Yahoo v6.x",       "Yahoo 6*",             "Yahoo 6.x",            NULL, IDI_CLIENTYAHOO6,0xFF,8},
	{"client_Yahoo v7.x",       "Yahoo 7*",             "Yahoo 7.x",            NULL, IDI_CLIENTYAHOO7,0xFF,8},

	{"client_AimSMS",           "SMS*",                 "Aim SMS",              NULL, IDI_CLIENTAIMSMS,0xFF,3},
	{"client_Aim Triton",       "AIM*Triton*",          "AIM Triton",           NULL, IDI_CLIENTAIMTRITON,0xFF,3},
	{"client_Aim GPRS",         "GPRS*",                "Aim GPRS",             NULL, IDI_CLIENTAIMGPRS,0xFF,3},
	{"client_AIM TOC",          "AIM TOC*",             "AIM TOC",              NULL, IDI_CLIENTAIMTOC,0xFF,3},
	{"client_AIM Express",      "AIM Express*",         "AIM Express",          NULL, IDI_CLIENTAIMEXPRESS,0xFF,3},
	{"client_naim",	            "naim*",                "naim",                 NULL, IDI_CLIENTNAIM,0xFF,3},
	{"client-miniaim",          "miniaim*",             "miniaim",              NULL, IDI_CLIENTMINIAIM,0xFF,3},
	{"client_Aim4",             "AIM*4*",               "AIM v 4.x",            NULL, IDI_CLIENTAIM4,0xFF,3},
	{"client_Aim5",             "AIM*5*",               "AIM v 5.x",            NULL, IDI_CLIENTAIM5,0xFF,3},
	{"client_TerraIM",          "TerraIM*",             "TerraIM",              NULL, IDI_CLIENTTERRAIM,0xFF,3},
	{"client_Aim",              "AIM*",                 "AIM",                  NULL, IDI_CLIENTAIM,0xFF,3},

	{"client_Agile Messenger",  "Agile Messenger*",     "Agile Messenger",      NULL, IDI_CLIENTAGILE,0xFF,4},
	{"client_mobicq",           "mobicq*",              "Mobile ICQ",           NULL, IDI_CLIENTMOBICQ,0xFF,4},
	{"client_Jimm",             "Jimm*",                "Jimm",                 NULL, IDI_CLIENTJIMM,0xFF,4},
	{"client_Colibry",          "Colibry*",             "Colibry",              NULL, IDI_CLIENTCOLIBRY,0xFF,4},
	{"client_Sticq",            "Sticq*",               "Sticq",                NULL, IDI_CLIENTSTICQ,0xFF,4},
	{"client_uIM",              "uIM*",                 "uIM",                  NULL, IDI_CLIENTUIM,0xFF,4},
	{"client_IMPLUS",           "|IMPLUS*|IM+*",        "IMPLUS",               NULL, IDI_CLIENTIMPLUS,0xFF,4},
	{"client_YAMIGO",           "YAMIGO*",              "YAMIGO",               NULL, IDI_CLIENTYAMIGO,0xFF,4},
	{"client_Bombus",           "*Bombus*",             "Bombus",               NULL, IDI_CLIENTBOMBUS, 0xFF,4},
	{"client_mChat",            "mChat*",               "mChat",                NULL, IDI_CLIENTMCHAT, 0xFF,4},
	{"client_PreludeICQ",       "PreludeICQ*",          "PreludeICQ",           NULL, IDI_CLIENTPRELUDEICQ, 0xFF,4},
	{"client_WmIRC",            "*WmIRC*",              "WmIRC",                NULL, IDI_CLIENTWMIRC, 0xFF,4},


	{"client_ICQ for Mac",      "ICQ for Mac*",         "ICQ for Mac",          NULL, IDI_CLIENTICQMAC,0xFF,1},
	{"client_&RQ",              "&RQ*",                 "&RQ",                  NULL, IDI_CLIENTRQ,0xFF,1},
	{"client_QIP",              "QIP*",                 "QIP",                  NULL, IDI_CLIENTQIP,0xFF,1},
	{"client_NICQ",             "NICQ*",                "NICQ",                 NULL, IDI_CLIENTNICQ,0xFF,1},
	{"client_KXicq2",           "KXicq*",               "KXicq2",               NULL, IDI_CLIENTKXICQ2,0xFF,1},
	{"client_ICQ 2000",         "ICQ*2000*",            "ICQ 2000",             NULL, IDI_CLIENTICQ2000,0xFF,1},
	{"client_ICQ 2001b",        "ICQ*2001*",            "ICQ 2001",             NULL, IDI_CLIENTICQ2001,0xFF,1},
	{"client_ICQ 2002",         "ICQ*2002*",            "ICQ 2002/2003a",       NULL, IDI_CLIENTICQ2002,0xFF,1},
	{"client_ICQ 200",          "ICQ*2003*",            "ICQ 2003b",            NULL, IDI_CLIENTICQ2003,0xFF,1},
	{"client_TICQ",             "TICQClient",           "TICQClient",           NULL, IDI_CLIENTTICQ, 0xFF,1},
	{"client_ICat",             "IC@",                  "IC@",                  NULL, IDI_CLIENTICAT, 0xFF,1},
	{"client_R_and_Q",          "R&Q*",                 "R&Q",                  NULL, IDI_CLIENTR_and_Q, 0xFF,1},
	{"client_SmartIcq",         "SmartICQ*",            "SmartICQ",             NULL, IDI_CLIENTSMARTICQ, 0xFF,1},
	{"client_Icq_abv",          "ICQ*Abv*",             "ICQ Lite v5 [ABV]",    NULL, IDI_CLIENTICQ_ABV, 0xFF,1},
	{"client_Icq_netvigator",   "ICQ*Netvigator*",      "ICQ Lite v5 [Netvigator]",NULL, IDI_CLIENTICQ_NETVIGATOR, 0xFF,1},
	{"client_Icq_rambler",      "ICQ*Rambler*",         "ICQ Lite v5 [Rambler]",NULL, IDI_CLIENTICQ_RAMBLER, 0xFF,1},
	{"client_Icq4pocket PC",    "ICQ*pocket*",          "ICQ 4 pocket PC",      NULL, IDI_CLIENTICQ4POCKET, 0xFF,1},
	{"client_ICQ Lite v4",      "ICQ Lite v4*",         "ICQ Lite v4",          NULL, IDI_CLIENTICQLITE4,0xFF,1},
	{"client_ICQ Lite v5.1",    "|ICQ Lite v5.1*|icq5.1*","ICQ Lite v5.1",      NULL, IDI_CLIENTICQLITE51,0xFF,1},
	{"client_ICQ Lite v5",      "|ICQ Lite v5*|icq5*",  "ICQ Lite v5",          NULL, IDI_CLIENTICQLITE5,0xFF,1},
	{"client_ICQ Lite",         "ICQ Lite*",            "ICQ Lite",             NULL, IDI_CLIENTICQLITE,0xFF,1},
	{"client_WebICQ",           "WebICQ*",              "WebICQ",               NULL, IDI_CLIENTWEBICQ,0xFF,1},
	{"client_ICQ2Go!(Flash)",   "ICQ2Go! (Flash)*",     "ICQ2Go![Flash]",       NULL, IDI_CLIENTICQGOF,0xFF,1},
	{"client_ICQ2Go!",          "ICQ2Go!*",             "ICQ2Go![Other]",       NULL, IDI_CLIENTICQGOJ,0xFF,1},
	{"client_CenterICQ",        "*CenterICQ*",          "CenterICQ",            NULL, IDI_CLIENTCENTERICQ,0xFF,5},
	{"client_ICQ 2X",           "ICQ 2.x*",             "ICQ 2.X",              NULL, IDI_CLIENTICQ2X,0xFF,1},
	{"client_mICQ",             "mICQ*",                "mICQ",                 NULL, IDI_CLIENTMICQ,0xFF,1},
	{"client_libicq2000",       "libicq*",              "LibICQ/JIT",           NULL, IDI_CLIENTLIBICQ2000,0xFF,1},
	{"client_StrICQ",           "StrICQ*",              "StrICQ",               NULL, IDI_CLIENTSTRICQ,0xFF,1},
	{"client_vICQ",             "vICQ*",                "vICQ",                 NULL, IDI_CLIENTVICQ,0xFF,1},
	{"client_YSM",              "YSM*",                 "YSM",                  NULL, IDI_CLIENTYSM,0xFF,1},
	{"client_NanoICQ",          "NanoICQ*",             "NanoICQ",              NULL, IDI_CLIENTNANOICQ,0xFF,1},
	{"client_spam bot",         "*spam bot*",           "spam bot",             NULL, IDI_CLIENTSPAMBOT,0xFF,5},

	{"client_Jabber_messenger", "Jabber Messenger*",    "Jabber Messenger",     NULL, IDI_CLIENTJABBER_MESSENGER, 0xFF,2},
	{"client_Jajc",             "*Jajc*",               "Jajc",                 NULL, IDI_CLIENTJAJC,0xFF,2},
	{"client_TKabber",          "*Tkabber*",            "TKabber",              NULL, IDI_CLIENTTKABBER,0xFF,2},
	{"client_Gizmo",            "*Gizmo*",              "Gizmo",                NULL, IDI_CLIENTGIZMO,0xFF,2},
	{"client_GG",               "*Gadu-Gadu*",          "Gadu-Gadu",            NULL, IDI_CLIENTGG,0xFF,2},
	{"client_Exodus",           "*Exodus*",             "Exodus",               NULL, IDI_CLIENTEXODUS, 0xFF,2},
	{"client_Gush",             "*Gush*",               "Gush",                 NULL, IDI_CLIENTGUSH, 0xFF,2},
	{"client_Pandion",          "*Pandion*",            "Pandion",              NULL, IDI_CLIENTPANDION, 0xFF,2},
	{"client_BitlBee",          "*BitlBee",             "BitlBee",              NULL, IDI_CLIENTBITLBEE, 0xFF,2},
	{"client_WTW",              "Smok MK2*@*WTW",       "WTW",                  NULL, IDI_CLIENTWTW, 0xFF,2},
	{"client_Tlen",             "Smok MK2*@*tlen.pl",   "Tlen.pl",              NULL, IDI_CLIENTTLEN, 0xFF,2},
	{"client_Psi",              "*Psi*",                "Psi",                  NULL, IDI_CLIENTPSI,0xFF,2},
	{"client_Gossip",           "*Gossip*",             "Gossip",               NULL, IDI_CLIENTGOSSIP,0xFF,2},
	{"client_Gabber",           "*Gabber*",             "Gabber",               NULL, IDI_CLIENTGABBER,0xFF,2},
	{"client_Nitro",            "*Nitro*",              "Nitro",                NULL, IDI_CLIENTNITRO,0xFF,2},
	{"client_Neos_mt",          "*Neos*",               "Neos mt",              NULL, IDI_CLIENTNEOS_MT,0xFF,2},
	{"client_Jabberwoky",       "Jabberwoky*",          "Jabberwoky",           NULL, IDI_CLIENTJABBERWOCKY,0xFF,2},
	{"client_iChat",            "*iChat*",              "iChat",                NULL, IDI_CLIENTICHAT,0xFF,2},
	{"client_Konnekt",          "*Konnekt.kJabber*",    "Konnekt",              NULL, IDI_CLIENTKONNEKT,0xFF,2},
	{"client_JETI",             "*JETI*",               "JETI",                 NULL, IDI_CLIENTJETI,0xFF,2},
	{"client_Coccinella",       "*Coccinella*",         "Coccinella",           NULL, IDI_CLIENTCOCCINELLA,0xFF,2},
	{"client_GAJIM",            "*GAJIM*",              "GAJIM",                NULL, IDI_CLIENTGAJIM,0xFF,2},
	{"client_GTalk",            "*talk*",              "GTalk",                NULL, IDI_CLIENTGTALK,0xFF,2},
	{"client_Gmail",            "*gmail*",              "Gmail",                NULL, IDI_CLIENTGMAIL,0xFF,2},
	{"client_Conference bot",   "*conference*",         "Conference bot",       NULL, IDI_CLIENTCONFERENCE,0xFF,2},
	{"client_Spik",             "*Spik*",               "Spik",                 NULL, IDI_CLIENTSPIK,0xFF,2},
	{"client_Kadu",             "*kadu*",               "Kadu",                 NULL, IDI_CLIENTKADU,0xFF,2},
	{"client_Imeem",            "*imeem*",              "Imeem",                NULL, IDI_CLIENTIMEEM,0xFF,2},
	{"client_PyICQ-t",          "PyICQ-t*",              "PyICQ-t",             NULL, IDI_CLIENTPYICQT,0xFF,1},

	{"client_webmessenger",     "Webmessenger*",        "Webmessenger",         NULL, IDI_CLIENTWEBMESSENGER,0xFF,7},
	{"client_MSN 8.x",          "MSN 8.*",              "MSN 8.x",              NULL, IDI_CLIENTMSN8,0xFF,7},
   	{"client_MSN 7.x",          "MSN 7.*",              "MSN 7.x",              NULL, IDI_CLIENTMSN7,0xFF,7},
   	{"client_MSN 6.x",          "MSN 6.*",              "MSN 6.x",              NULL, IDI_CLIENTMSN6,0xFF,7},
 	{"client_MSN 4.x-5.x",      "MSN 4.*",              "MSN 4.x-5.x",          NULL, IDI_CLIENTMSN4_5,0xFF,7},
 	
 	{"client_mIRC",             "mIRC*",                "mIRC",                 NULL, IDI_CLIENTMIRC,0xFF,9},
   	{"client_Eggdrop",          "eggdrop*",             "Eggdrop",              NULL, IDI_CLIENTEGGDROP,0xFF,9},		
  	{"client_eMule",            "eMule*",               "eMule",                NULL, IDI_CLIENTEMULE,0xFF,9},	
  	{"client_ZipTorrent",       "ZipTorrent*",          "Zip Torrent",          NULL, IDI_CLIENTZIPTORRENT,0xFF,9},	
  	{"client_PJIRC",            "PJIRC*",               "PJIRC",                NULL, IDI_CLIENTPJIRC,0xFF,9},	
  	{"client_psyBNC",           "psyBNC*",              "psyBNC",               NULL, IDI_CLIENTPSYBNC,0xFF,9},	
  	{"client_irssi",            "irssi*",               "irssi",                NULL, IDI_CLIENTIRSSI,0xFF,9},	
 	{"client_Klient",           "Klient*",              "Klient",               NULL, IDI_CLIENTKLIENT,0xFF,9},	
	{"client_KVIrc",            "KVIrc*",               "KVIrc",                NULL, IDI_CLIENTKVIRC,0xFF,9},	
	{"client_Colloquy",         "Colloquy*",            "Colloquy",             NULL, IDI_CLIENTCOLLOQUY,0xFF,9},	
	{"client_HydraIRC",         "HydraIRC*",            "HydraIRC",             NULL, IDI_CLIENTHYDRAIRC,0xFF,9},	
	{"client_WeeChat",          "*WeeChat*",            "WeeChat",              NULL, IDI_CLIENTWEECHAT,0xFF,9},	
	{"client_XchatGnome",       "xchat*Gnome*",         "Xchat Gnome",          NULL, IDI_CLIENTXCHATGNOME,0xFF,9},	
	{"client_XchatAqua",        "xchat*Aqua*",          "Xchat Aqua",           NULL, IDI_CLIENTXCHATAQUA,0xFF,9},	
	{"client_Chatzilla",        "*Chatzilla*",          "Chatzilla",            NULL, IDI_CLIENTCHATZILLA,0xFF,9},	 
 	{"client_Opera chat",       "*opera*",              "Opera chat",           NULL, IDI_CLIENTOPERA,0xFF,9},	
  	{"client_XChat",            "xchat*",               "XChat",                NULL, IDI_CLIENTXCHAT,0xFF,9},	
	{"client_pIRC",             "pIRC*",                "pIRC",                 NULL, IDI_CLIENTPIRC,0xFF,9},	
	{"client_Bersirc",          "*bersirc*",            "Bersirc",              NULL, IDI_CLIENTBERSIRC,0xFF,9},	
	{"client_IrcN",             "*IrcN*",               "IrcN",                 NULL, IDI_CLIENTIRCN,0xFF,9},	
	{"client_MaxxIM",           "*MaxxIM*",             "MaxxIM",               NULL, IDI_CLIENTMAXXIM,0xFF,5},	
	{"client_Mirabel script",   "*Mirabel*",            "Mirabel script",       NULL, IDI_CLIENTMIRABEL,0xFF,9},	
	{"client_Ninjia",           "*ninjia*",             "Ninjia",               NULL, IDI_CLIENTNINJIA,0xFF,9},	
	{"client-iScript",          "iScript*",             "iScript",              NULL, IDI_CLIENTISCRIPT,0xFF,9},	
	{"client_CGI IRC",          "CGI:IRC*",             "CGI IRC",              NULL, IDI_CLIENTCGIIRC,0xFF,9},	
	{"client_Icechat",          "*Icechat*",            "Icechat",              NULL, IDI_CLIENTICECHAT,0xFF,9},	
	{"client_Konversation",     "*Konversation*",       "Konversation",         NULL, IDI_CLIENTKONVERSATION,0xFF,9},	
	{"client_Babbel",           "*Babbel*",             "Babbel",               NULL, IDI_CLIENTBABBEL,0xFF,9},	
	{"client_AmIRC",            "*AmIRC*",              "AmIRC",                NULL, IDI_CLIENTAMIRC,0xFF,9},	
	{"client_KSirc",            "*KSirc*",              "KSirc",                NULL, IDI_CLIENTKSIRC,0xFF,9},	
	{"client_Virc",             "*Virc*",               "Virc",                 NULL, IDI_CLIENTVIRC,0xFF,9},	
	{"client_Snak",             "*Snak*",               "Snak",                 NULL, IDI_CLIENTSNAK,0xFF,9},	
	{"client_Savirc",           "*Savirc*",             "Savirc",               NULL, IDI_CLIENTSAVIRC,0xFF,9},	
	{"client_Nettalk",          "*Nettalk*",            "Nettalk",              NULL, IDI_CLIENTNETTALK,0xFF,9},	
	{"client_Conversation",     "*Conversation*",       "Conversation",         NULL, IDI_CLIENTCONVERSATION,0xFF,9},	
	{"client_Xirc",             "*Xirc*",               "Xirc",                 NULL, IDI_CLIENTXIRC,0xFF,9},	
  	{"client_eMule mod",        "|*mule*|ePlus*",       "eMule mods",           NULL, IDI_CLIENTMULE,0xFF,9},	
	{"client_irc",              "*irc*",                "any irc",              NULL, IDI_CLIENTIRC,0xFF,9},	
	{"client_Unknown",          "*?*",                  "Unknown",              NULL, IDI_CLIENTUNKNOWN,0xFF,5},
    			// unknown should be allways last
};

#define DEFAULT_KN_FP_MASK_COUNT sizeof(def_kn_fp_mask)/sizeof(def_kn_fp_mask[0])   //should contain the count of records above
