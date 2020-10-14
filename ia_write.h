#ifndef _IA_WRITE_H
#define _IA_WRITE_H

void immIAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void reg8IAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void reg16IAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void reg32IAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void regIAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void base8IAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void base16IAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void base32IAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void segRegIAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void memIAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void push_spIAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void push_espIAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void pusha_spIAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);
void pusha_espIAWr(IAinstInfoPtr info, IADWORD val, ADDR adr, ADDR adr2);

#endif
