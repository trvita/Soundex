#include <csv.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <soundex.hpp>
int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Usage: SoundexHash <inputFilename> <outputFilename>"
              << std::endl;
    return 1;
  }
  std::ifstream inFile(argv[1]);
  if (!inFile) {
    std::cerr << "Error: File " << argv[1] << " does not exist" << std::endl;
    return 2;
  }
  csv::CSVReader reader(inFile);
  std::ofstream outFile(argv[2]);

  nlohmann::json output;
  for (auto &row : reader) {
    std::string name = row[0].get<std::string>();

    uint32_t hash = soundex::soundex_hash(name);

    if (hash == 0) {
      continue;
    }

    output[soundex::hashToString(hash)].push_back(name);
  }

  std::map<std::string, std::vector<std::string>> sorted_output;
  for (auto &entry : output.items()) {
    sorted_output[entry.key()] =
        entry.value().get<std::vector<std::string>>();
  }

  nlohmann::json sorted_json(sorted_output);

  outFile << sorted_json.dump(4);
  return 0;
}



/*Обработка файла

Напишите утилиту, которая:

    Парсит csv-файл names2020.csv.

    Группирует имена из файла по их soundex-хешам.

    Выводит результат в машиночитаемом формате в соответствии со своим
вариантом. Вывод должен быть стабильным:

        Хеши должны быть отсортированы по возрастанию.

        Имена внутри каждого списка также должны быть отсортированы.

Способ ввода и вывода данных (stdin/stdout/файлы) остается на ваше усмотрение,
но выбор должен быть аргументирован. Считаем, что утилита для продакшена,
хардкод не допускается.

Формат входного файла:

<name>,<gender>,<count>

Можете воспользоваться любой библиотекой для парсинга csv или с помощью
стандартных алгоритмов отделить первое поле.*/
