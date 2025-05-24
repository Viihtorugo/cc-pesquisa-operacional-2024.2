#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

typedef struct item
{
    int id;
    double tam;
} item;

typedef struct bin_package
{
    double cap;
    vector<item> items;
} bin;

bool compara_tam(const item &a, const item &b)
{
    return a.tam > b.tam;
}

bool compara_cap(const bin &a, const bin &b)
{
    return a.cap > b.cap;
}

int rating(vector<bin> solution)
{
    return solution.size();
}

bin create_bin()
{
    bin b;
    b.cap = 0;
    b.items = vector<item>();

    return b;
}

vector<bin> greedy_randomized_construction(vector<item> items, int RCL_size)
{
    vector<bin> bins;
    random_device rd;
    mt19937 gen(rd());

    while (!items.empty())
    {
        item current;

        sort(items.begin(), items.end(), compara_tam);

        int limit = min(RCL_size, (int)items.size());
        uniform_int_distribution<> dist(0, limit - 1);
        int index = dist(gen);
        current = items[index];
        items.erase(items.begin() + index);

        bool placed = false;
        for (auto &b : bins)
        {
            if (b.cap + current.tam <= 1.0)
            {
                b.cap += current.tam;
                b.items.push_back(current);
                placed = true;
                break;
            }
        }
        if (!placed)
        {
            bin new_bin = create_bin();
            new_bin.cap += current.tam;
            new_bin.items.push_back(current);
            bins.push_back(new_bin);
        }
    }

    return bins;
}

vector<bin> first_improvement(vector<bin> bins)
{

    for (int i = 0; i < bins.size(); i++)
    {
        for (int j = 0; j < bins[i].items.size(); j++)
        {
            item current = bins[i].items[j];

            for (int k = 0; k < bins.size(); k++)
            {
                if (k == i)
                    continue;

                if (bins[k].cap + current.tam <= 1.0)
                {
                    vector<bin> new_bins = bins;

                    new_bins[k].cap += current.tam;
                    new_bins[k].items.push_back(current);

                    new_bins[i].cap -= current.tam;
                    new_bins[i].items.erase(new_bins[i].items.begin() + j);

                    if (new_bins[i].items.empty())
                    {
                        new_bins.erase(new_bins.begin() + i);
                    }

                    if (rating(new_bins) < rating(bins))
                    {
                        bins = new_bins;
                    }
                }
            }
        }
    }

    return bins;
}

vector<bin> grasp(vector<item> items, int n, int rcl, int seg)
{
    vector<bin> best_bin = greedy_randomized_construction(items, rcl);
    int best_rating = rating(best_bin);

    auto start = high_resolution_clock::now();

    while (duration_cast<seconds>(high_resolution_clock::now() - start).count() < seg)
    {
        vector<bin> aux_bin = greedy_randomized_construction(items, rcl);
        aux_bin = first_improvement(aux_bin);
        int aux_rating = rating(aux_bin);

        if (aux_rating < best_rating)
        {
            cout << "Atualizando o melhor bin: " << best_rating << " bins para " << aux_rating << " bins\n";
            best_rating = aux_rating;
            best_bin = aux_bin;
        }
    }

    return best_bin;
}

void print_bins(vector<bin> bins)
{
    cout << "\nSolução viável: \n\n";

    int size = bins.size();

    cout << fixed << setprecision(2);
    for (int i = 0; i < size; i++)
    {
        cout << "Bin " << i + 1 << ": cap = " << bins[i].cap << " - Items: ";

        for (auto item : bins[i].items)
            cout << item.id << " ";

        cout << endl;
    }

    cout << "\nA melhor solução que ele encontrou tem " << rating(bins) << " bins\n\n";
}

bool check_seg(char seg[])
{
    for (int i = 0; i < seg[i] != '\0'; i++)
        if (seg[i] < '0' || seg[i] > '9')
            return true;

    return false;
}

int count_items_bins(vector<bin> bins)
{
    int count = 0;

    for (auto b : bins)
        count += b.items.size();

    return count;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Uso: ./programa <tempo_em_segundos>" << endl;
        return 1;
    }
    else if (check_seg(argv[1]))
    {
        cout << "Uso: ./programa <tempo_em_segundos (inteiro)>" << endl;
        return 1;
    }

    int seg = atoi(argv[1]);

    int n, rcl;
    cin >> n >> rcl;

    vector<item> items;
    for (int i = 0; i < n; i++)
    {
        item new_item;
        cin >> new_item.tam;
        new_item.id = i;
        items.push_back(new_item);
    }

    // sort(items.begin(), items.end(), compara_tam);

    vector<bin> bins = grasp(items, n, rcl, seg);
    print_bins(bins);
    cout << "\nVerificando a quantidade de items nos bins\nTotal: " << count_items_bins(bins) << "\n";

    return 0;
}