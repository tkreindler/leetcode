// this is horrible practice but simulates leetcode well
#include "headers.cpp"

typedef std::vector<int>::const_iterator iter_t;

// simple xor based hasher for the type std::tuple<int, int, int>
struct triplet_hash
{
    std::size_t operator()(tuple<int, int, int> triplet) const
    {
        std::hash<int> hasher;

        int val1 = std::get<0>(triplet);
        int val2 = std::get<1>(triplet);
        int val3 = std::get<2>(triplet);

        return hasher(val1) ^ hasher(val2) ^ hasher(val3);
    }
};

tuple<int, int, int> getSortedTuple(int val1, int val2, int val3)
{
    int min = std::min(val1, std::min(val2, val3));

    if (val1 == min)
    {
        if (val2 < val3)
        {
            return {val1, val2, val3};
        }
        else
        {
            return {val1, val3, val2};
        }
    }
    else if (val2 == min)
    {
        if (val1 < val3)
        {
            return {val2, val1, val3};
        }
        else
        {
            return {val2, val3, val1};
        }
    }
    else
    {
        if (val2 < val1)
        {
            return {val3, val2, val1};
        }
        else
        {
            return {val3, val1, val2};
        }
    }
}

class Solution {
public:
    vector<vector<int>> threeSum(const vector<int>& nums)
    {
        unordered_map<int, vector<tuple<iter_t, iter_t>>> twoSums(nums.size() * nums.size());

        // populate the map with all pairs, O(n^2) time, O(n^2) space
        for (iter_t iter1 = nums.begin(); iter1 != nums.end(); ++iter1)
        {
            for (iter_t iter2 = nums.begin(); iter2 != nums.end(); ++iter2)
            {
                // skip using the same index twice
                if (iter1 == iter2)
                {
                    continue;
                }

                int sum = *iter1 + *iter2;

                vector<tuple<iter_t, iter_t>>& vec = twoSums[sum];

                // check order and check for duplicates to avoid edge cases with endless repetition
                // time complexity of this is quite bad, O(n^3) in the worse case but I think in the
                // general case it's still better than using a hashmap here which would be O(n^2 * logn)
                // but with much, much more overhead
                tuple<iter_t, iter_t> sortedTuple;
                if (*iter1 < *iter2)
                {
                    sortedTuple = {iter1, iter2};
                }
                else
                {
                    sortedTuple = {iter2, iter1};
                }

                auto found = std::find_if(vec.begin(), vec.end(), [&](tuple<iter_t, iter_t> tup)
                {
                    return *std::get<0>(tup) == *std::get<0>(sortedTuple) &&
                        *std::get<1>(tup) == *std::get<1>(sortedTuple);
                });

                // only if no duplicate was found with the same values push it in
                if (found == vec.end())
                {
                    twoSums[sum].push_back({iter1, iter2});
                }
            }
        }

        unordered_set<tuple<int, int, int>, triplet_hash> deduplicator;

        // final loop through, add all triplets to output result
        for (iter_t iter = nums.begin(); iter != nums.end(); ++iter)
        {
            int val = *iter;
            auto dictionaryIter = twoSums.find(-1 * val);

            // if no matches that sum up to this are found, move on
            if (dictionaryIter == twoSums.end())
            {
                continue;
            }

            const vector<tuple<iter_t, iter_t>>& foundPairs = dictionaryIter->second;

            for (tuple<iter_t, iter_t> pair : foundPairs)
            {
                iter_t iter2 = std::get<0>(pair);
                iter_t iter3 = std::get<1>(pair);

                // skip it if it's trying to repeat the same index twice
                if (iter == iter2 || iter == iter3)
                {
                    continue;
                }

                // make sure to sort output so the deduplicator can function
                tuple<int, int, int> triplet = getSortedTuple(val, *iter2, *iter3);
                deduplicator.insert(triplet);
            }
        }

        // turn the deduplicated tuples into the desired output type
        vector<vector<int>> result;
        for (tuple<int, int, int> triplet : deduplicator)
        {
            int val1 = std::get<0>(triplet);
            int val2 = std::get<1>(triplet);
            int val3 = std::get<2>(triplet);

            result.push_back({val1, val2, val3});
        }

        return result;
    }
};