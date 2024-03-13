#ifndef PARSER_H
#define PARSER_H

#include "parallel_executor/EventQueue/EventQueue.h"
#include "parallel_executor/Device/Device.h"
#include "stdexcept"
class Parser
{
public:
  /*!
   * \brief Конструктор
   *
   * \param queue Умный указатель на очередь.
   * \param A Умный указатель на устройство A.
   * \param B Умный указатель на устройство B.
  */

    Parser(std::shared_ptr<EventQueue> queue, std::shared_ptr<Device> A, std::shared_ptr<Device> B);
  /*!
   * \brief Функция, запускающая чтение данных с устройств в параллельном режиме.
   *
   * \param loop_count_A Беззнаковое целое число, задающее кол-во итераций чтения с устройства А.
   * \param loop_count_B Беззнаковое целое число, задающее кол-во итераций чтения с устройства В.
   * \param crush_index_A Целое число, указывающая на какой итерации сломается устройство А.
   * \param crush_index_B Целое число, указывающая на какой итерации сломается устройство B.
  */

  void run(size_t loop_count_A = 1, size_t loop_count_B = 1, int crush_index_A = -1, int crush_index_B = -1);
private:
  /*!
   * \brief Читает данные с устройства.
   *
   * \param device Умный указатель на устройство
   * \param sleep_duration Секунды, задающие длительность прерывания для симулированной работы.
   * \param loop_count Беззнаковое целое число, задающее кол-во итераций чтения с устройства.
   * \param crush_index Целое число, указывающая на какой итерации сломается устройство.
  */
  void read(std::shared_ptr<Device> device, std::chrono::seconds sleep_duration, size_t loop_count, int crush_index);

private:
  std::shared_ptr<EventQueue> queue;
  std::shared_ptr<Device> A;
  std::shared_ptr<Device> B;
};
#endif
