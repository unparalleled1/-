#ifndef __MATRIXKEY_H
#define __MATRIXKEY_H
/*	
 *	R1->PA1		R2->PA2		R3->PC4		R4->PA3
 *  C1->PG11	C2->PC1		C3->PA7		C4->PC5
 */
void Matrix_ssKey_Pin_Init(void);
unsigned char Matrix_Key_Scan(void);
#endif
