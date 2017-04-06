#include <libdevcore/Common.h>
#include <libethcore/Precompiled.h>

#include <boost/random.hpp>

#include <iostream>
#include <random>

using namespace std;
using namespace dev;
using namespace eth;

namespace
{
	bigint modexp_boost(bigint const& _b, bigint const& _e, bigint const& _m)
	{
		return boost::multiprecision::powm(_b, _e, _m);
	}

	bigint modexp_manual(bigint _b, bigint _e, bigint const& _m)
	{
		bigint result = 1;
		while (_e)
		{
			using boost::multiprecision::limb_type;
			if (static_cast<limb_type>(_e) & 1)	// If exponent is odd.
				result = (result * _b) % _m;
			_b = (_b * _b) % _m;
			_e >>= 1;
		}
		return result;
	}

	u256 modexp_manual256(u256 _base, u256 _exponent)
	{
		using boost::multiprecision::limb_type;
		u256 result = 1;
		while (_exponent)
		{
			if (static_cast<limb_type>(_exponent) & 1)	// If exponent is odd.
				result *= _base;
			_base *= _base;
			_exponent >>= 1;
		}
		return result;
	}

	bigint cost(bigint const& _baseLength, bigint const& _expLength, bigint const& _modLength)
	{
		bigint const maxLength = max(_modLength, _baseLength);

		return maxLength * maxLength * max<bigint>(_expLength, 1) / 20;
	}

	void compareWithManual()
	{

		/*	PrecompiledExecutor exec = PrecompiledRegistrar::executor("modexp");

		bytes in = fromHex(
		"0000000000000000000000000000000000000000000000000000000000000001"
		"0000000000000000000000000000000000000000000000000000000000000020"
		"0000000000000000000000000000000000000000000000000000000000000020"
		"03"
		"fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2e"
		"fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f");

		Timer timer;

		auto res = exec(bytesConstRef(in.data(), in.size()));

		double execTime = timer.elapsed();
		cout << "exec time: " << fixed << setprecision(6) << execTime << '\n';
		*/

		using generator_type = boost::random::independent_bits_engine<std::mt19937, 1024, bigint>;
		generator_type gen;

		Timer timer;

		gen.seed(0x123456);
		double execTime1 = 0;
		for (int i = 0; i < 10000; ++i)
		{
			bigint _b = gen();
			bigint _e = gen();
			bigint _m = gen();
			//		bigint _m{"0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"};

			timer.restart();
			auto res1 = modexp_boost(_b, _e, _m);
			execTime1 += timer.elapsed();
		}

		/*	using generator_type256 = boost::random::independent_bits_engine<std::mt19937, 256, u256>;
		generator_type256 gen256;
		*/
		gen.seed(0x123456);
		double execTime2 = 0;
		for (int i = 0; i < 10000; ++i)
		{
			bigint _b = gen();
			bigint _e = gen();
			bigint _m = gen();
			//		u256 _b = gen256();
			//		u256 _e = gen256();

			timer.restart();
			//		auto res2 = modexp_manual256(_b, _e);
			auto res2 = modexp_manual(_b, _e, _m);
			execTime2 += timer.elapsed();
		}

		cout << "exec time boost: " << fixed << setprecision(6) << execTime1 << " exec time manual: " << fixed << setprecision(6) << execTime2 << '\n';
	}

	bigint rand_bigint(size_t sizeBits)
	{
		using generator_type = boost::random::independent_bits_engine<std::mt19937, 1024, bigint>;
		static generator_type gen;

		return gen() >> (1024 - sizeBits);
	}

	void measureWithGrowingExp(size_t _baseLength, size_t _modLength)
	{
		Timer timer;

		for (int expLength = 256; expLength <= 1024; expLength += 8)
		{
			double execTime = 0;
			for (int i = 0; i < 100; ++i)
			{
				bigint _b = rand_bigint(_baseLength);
				bigint _m = rand_bigint(_modLength);
				bigint _e = rand_bigint(expLength);

				timer.restart();
				auto res2 = modexp_boost(_b, _e, _m);
				execTime += timer.elapsed();
			}
			cout << _baseLength / 8 << "," << _modLength / 8 << "," << expLength / 8 << ',' << cost(_baseLength / 8, expLength / 8, _modLength / 8) << ',' << execTime << "\n";
		}
	}

	void measurePerformanceAgainsCost()
	{
		cout << "baseLength_bytes,modLength_bytes,expLength_bytes,cost_gas,time_sec_per_100ops\n";

		measureWithGrowingExp(256, 256);
		measureWithGrowingExp(512, 512);
		measureWithGrowingExp(1024, 1024);

		measureWithGrowingExp(256, 512);
		measureWithGrowingExp(256, 1024);

		measureWithGrowingExp(512, 256);
		measureWithGrowingExp(1024, 256);
	}
}

int main(int argc, char** argv)
{
	measurePerformanceAgainsCost();

	return 0;
}
