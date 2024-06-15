#include <device/SPI/spi.hpp>
#include <eduardino_defines.hpp>

const u8 SPI_c::TxRx(cu8 b) {
	const u8 toggle = usiwm0 + usics1 + usiclk + usitc;
	USIDR = b;
	USISR = usioif;

	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();

	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();
	USICR= toggle;//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();//Nop();

	return USIDR;}

void SPI_c::begin() {
	spi_clk_pin.oupinLo();
	spi_mosi_pin.oupinLo();
	spi_miso_pin.inpin();}

