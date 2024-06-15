#pragma once
#include "pinout.hpp"
#include <avr/io.h>

class SPI_c {
	public:
		_inline_ void repeatTx(u16 n, const u8 b= 0xFF){
			while( n-- ) {
				TxRx(b);}}

		_inline_ u8 last() {return USIDR;}
		const u8 TxRx(cu8 b);
		void begin();

		_inline_ auto & operator<<(const auto & data) {
		Txs((u8*)(&data), sizeof(data));
		return mSelf;}

		_inline_ auto & operator>>(auto & data) {
		Rxs((u8*)(&data), sizeof(data));
		return mSelf;}

		_inline_ void Rxs(u8 * data, const size_t sz) {
		for( u8 i= 0; i < (sz); i++ ) {
			(data)[i] = Rx();}}

		_inline_ void Txs(u8 * data, const size_t sz) {
		for( u8 i= 0; i < (sz); i++ ) {
			Tx(data[i]);};}

	protected:
		void Tx(const u8 b) {
			TxRx(b);}

		const u8 Rx(){
			return TxRx(0xFF);}
};

static SPI_c spi0;

