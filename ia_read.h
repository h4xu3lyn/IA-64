#ifndef _IA_READ_H
#define _IA_READ_H

Status immIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
	       ADDR *adr, ADDR *adr2);
Status reg8IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		ADDR *adr, ADDR *adr2);
Status reg16IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		 ADDR *adr, ADDR *adr2);
Status reg32IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		 ADDR *adr, ADDR *adr2);
Status base8IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		 ADDR *adr, ADDR *adr2);
Status base16IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		  ADDR *adr, ADDR *adr2);
Status base32IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		  ADDR *adr, ADDR *adr2);
Status segRegIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		  ADDR *adr, ADDR *adr2);
Status segRegUpdateIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
			ADDR *adr, ADDR *adr2);
Status modrm16_dispIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
			ADDR *adr, ADDR *adr2);
Status load_far_ptr_16IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
			   ADDR *adr, ADDR *adr2);
Status lea16IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		 ADDR *adr, ADDR *adr2);
Status bound16IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		   ADDR *adr, ADDR *adr2);
Status push_spIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		   ADDR *adr, ADDR *adr2);
Status pop_spIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		  ADDR *adr, ADDR *adr2);
Status pusha_spIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		    ADDR *adr, ADDR *adr2);
Status popa_spIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val
		   , ADDR *adr, ADDR *adr2);
Status str_siIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		  ADDR *adr, ADDR *adr2);
Status str_diIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		  ADDR *adr, ADDR *adr2);
Status modrm32_dispIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
			ADDR *adr, ADDR *adr2);
Status load_far_ptr_32IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
			   ADDR *adr, ADDR *adr2);
Status sib_dispIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		    ADDR *adr, ADDR *adr2);
Status load_far_ptr_sibIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
			    ADDR *adr, ADDR *adr2);
Status lea32IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		 ADDR *adr, ADDR *adr2);
Status leaSibIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		  ADDR *adr, ADDR *adr2);
Status bound32IARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		   ADDR *adr, ADDR *adr2);
Status boundSibIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		    ADDR *adr, ADDR *adr2);
Status push_espIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		   ADDR *adr, ADDR *adr2);
Status pop_espIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		   ADDR *adr, ADDR *adr2);
Status pusha_espIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		     ADDR *adr, ADDR *adr2);
Status popa_espIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		    ADDR *adr, ADDR *adr2);
Status str_esiIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		   ADDR *adr, ADDR *adr2);
Status str_ediIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		   ADDR *adr, ADDR *adr2);
Status call_farIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		    ADDR *adr, ADDR *adr2);
Status ret_farIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		   ADDR *adr, ADDR *adr2);
Status xlatIARd(IAinstInfoPtr info, Accesstype acc, IADWORD *val,
		ADDR *adr, ADDR *adr2);

#endif
