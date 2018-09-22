#pragma once
#include "common.h"

class StockProblems {
public:
	// 121. Best Time to Buy and Sell Stock
	// condition: buy and sell once
	int maxProfit_once(vector<int>& prices) {
		int n = (int)prices.size();
		if (n == 0) return 0;
		int ans = 0;
		int min_price = prices[0];
		for (int i = 0; i < n; ++i) {
			min_price = min(min_price, prices[i]);
			ans = max(ans, prices[i] - min_price);
		}
		return ans;
	}


	// 122. Best Time to Buy and Sell Stock II
	// condition: buy and sell multiple times, can in the same day
	int maxProfit_infinite_times(vector<int>& prices) {
		if (prices.size() < 2) return 0;
		int sum = 0;
		for (int i = 1; i < prices.size(); ++i) {
			int diff = prices[i] - prices[i - 1];
			if (diff > 0) sum += diff;
		}
		return sum;
	}


	// 123. Best Time to Buy and Sell Stock III
	// condition: buy and sell m times (m = 2)
	int maxProfit_m_times(vector<int>& prices) {
		int n = (int)prices.size();
		if (n == 0) return 0;
		const int m = 2;

		// l[i][j] local indicates the i day, j transaction, all sold out, max profit
		// g[i][j] global indicates the maximum profit
		// l[i][j] = max(g[i-1][j-1] + max(diff, 0), local[i-1][j] + diff)

		vector<vector<int>> g(n, vector<int>(m + 1));
		vector<vector<int>> l(n, vector<int>(m + 1));

		for (int i = 1; i < n; ++i) {
			int diff = prices[i] - prices[i - 1];
			for (int j = 1; j <= m; ++j) {
				l[i][j] = max(g[i - 1][j - 1] + max(diff, 0), l[i - 1][j] + diff);
				g[i][j] = max(l[i][j], g[i - 1][j]);
			}
		}
		return g[n - 1][2];
	}

	int maxProfit_m_times_o1space(vector<int> &prices) {
		if (prices.empty()) return 0;
		const int m = 2;
		int g[m + 1] = { 0 };
		int l[m + 1] = { 0 };
		for (int i = 0; i < prices.size() - 1; ++i) {
			int diff = prices[i + 1] - prices[i];
			for (int j = 2; j >= 1; --j) {
				l[j] = max(g[j - 1] + max(diff, 0), l[j] + diff);
				g[j] = max(l[j], g[j]);
			}
		}
		return g[2];
	}


	// 188. Best Time to Buy and Sell Stock IV
	// condition: buy and sell m times
	int maxProfit(int k, vector<int> &prices) {
		if (prices.empty()) return 0;
		int n = (int)prices.size();
		if (k >= n) return maxProfit_infinite_times(prices);
		vector<int> g(k + 1), l(k + 1);
		for (int i = 0; i < n - 1; ++i) {
			int diff = prices[i + 1] - prices[i];
			for (int j = k; j >= 1; --j) {
				l[j] = max(g[j - 1] + max(diff, 0), l[j] + diff);
				g[j] = max(g[j], l[j]);
			}
		}
		return g[k];
	}

	/**
	 * 309. Best Time to Buy and Sell Stock with 1day Cooldown
	 * prices = [1, 2, 3, 0, 2]
	 * maxProfit = 3
	 * transactions = [buy, sell, cooldown, buy, sell]
 	 **/
	int maxProfit_1d_cd(vector<int>& prices) {
		/**
		* buy[i]  = max(rest[i-1] - price, buy[i-1])
		* sell[i] = max(buy[i-1] + price, sell[i-1])
		* rest[i] = max(sell[i-1], buy[i-1], rest[i-1])
		*/
		// rest[i] = sell[i-1]
		// buy[i]  = max(sell[i-2] - price, buy[i-1]) 
		// sell[i] = max(buy[i-1] + price, sell[i-1])
		int buy = INT_MIN, pre_buy = 0, sell = 0, pre_sell = 0;
		for (int price : prices) {
			pre_buy = buy;
			buy = max(pre_sell - price, pre_buy);
			pre_sell = sell;
			sell = max(pre_buy + price, pre_sell);
		}
		return sell;
	}

};