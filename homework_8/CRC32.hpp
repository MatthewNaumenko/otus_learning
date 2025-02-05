#pragma once
#include <cstddef>
#include <cstdint>

/**
 * @brief Вычисляет контрольную сумму блока данных CRC32
 * @details Вычисляет CRC-32-IEEE 802.3 (0xEDB88320).
 * Значение prev может быть использовано для эффективного "довычисления"
 * контрольной суммы (КС) при появлении новых данных Например, пусть v - КС
 * первых 100 байт данных: v = crc32(d, 100) Тогда q1 и q2 совпадают: q1 =
 * crc32(d, 104) и q2 = crc32(d + 100, 4, v), причем расчет q2 выполняется
 * гораздо быстрее
 * @param bytes указатель на начало буфера с данными
 * @param bytesCount размер буфера в байтах
 * @param prev начальное значение CRC32
 * @return контрольная сумма
 */
uint32_t crc32(const char *bytes, size_t bytesCount,
               uint32_t prev = 0xFFFFFFFF);
