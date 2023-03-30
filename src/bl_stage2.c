
#include <nrf.h>

#define APP_START 0x13000

void modify_stack_pointer_and_start_app(uint32_t r0_sp, uint32_t r1_pc)
{
    uint32_t z = 0;
    __ASM volatile (  "msr    control, %[z]   \n\t"
                      "msr    psp, %[z]       \n\t"
                      "msr    primask, %[z]   \n\t"
                      "isb                    \n\t"
                      "mov    sp, %[r0_sp]    \n\t"
                      "bx     %[r1_pc]"
                      :
                      :   [z] "l" (z),
                          [r0_sp] "l" (r0_sp),
                          [r1_pc] "l" (r1_pc)
                  );
}

void main(void) {
	SCB->VTOR = APP_START;
	modify_stack_pointer_and_start_app(
		(*(uint32_t *)(APP_START)),
		(*(uint32_t *)(APP_START + 4))
	);
}
