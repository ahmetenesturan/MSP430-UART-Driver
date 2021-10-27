#include <msp430.h> 

char s[] = "Hello ";
const unsigned int len = 6;
unsigned int pos = 0;

void init_uart();
void init_button();


int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    init_uart();
    init_button();
    __enable_interrupt();

/*
    UCA1CTL1 |= 1; //reset


    UCA1CTL1 |= 0xC0; //smclk
    UCA1BR0 = 8;
    UCA1BR1 = 0;
    UCA1MCTL = UCBRS_6;

    //Peripheral function select
    P4SEL |= BIT4 + BIT5;


    //port mapping
    P4MAP4 = PM_UCA1TXD;
    P4MAP5 = PM_UCA1RXD;


    UCA1CTL1 &= ~1; // out of reset



    P2DIR &= ~BIT1;
    P2OUT |= BIT1;
    P2REN |= BIT1;

    P2IE |= BIT1;
    P2IES |= BIT1;

*/


    while(1)
    {

    }


}

void init_uart()
{
    UCA1CTL1 |= 1; //reset


    UCA1CTL1 |= 0xC0; //smclk
    UCA1BR0 = 8;
    UCA1BR1 = 0;
    UCA1MCTL = UCBRS_6;

    //Peripheral function select
    P4SEL |= BIT4 + BIT5;


    //port mapping
    P4MAP4 = PM_UCA1TXD;
    P4MAP5 = PM_UCA1RXD;


    UCA1CTL1 &= ~1; // out of reset
}

void init_button()
{
    P2DIR &= ~BIT1;
    P2OUT |= BIT1;
    P2REN |= BIT1;

    P2IE |= BIT1;
    P2IES |= BIT1;
}



#pragma vector = PORT2_VECTOR

__interrupt void port2_irq()
{
    pos = 1;
    UCA1IE |= BIT1;
    UCA1IFG &= ~BIT1;
    UCA1TXBUF = s[0];
    P2IFG &= ~BIT1;
}



#pragma vector = USCI_A1_VECTOR

__interrupt void uart_irq()
{
    /*
    if(pos == len)
    {
        UCA1IE &= ~BIT1;
    }
    else
    {
        pos++;
        UCA1TXBUF = s[pos];
    }
    */

    while(pos != len)
    {
        UCA1TXBUF = s[pos];
        pos++;
    }

    UCA1IFG &= ~BIT1;

    UCA1IE &= ~BIT1;


}
