<h3>
Hardware yang digunakan:
<h5>
  - Arduino Uno R3
</h5>
ByteWordOperation.ino berisi eksperimen operasi byte, word, dan pointer.
<br>
Serial Monitor yang dihasilkan oleh kode ini adalah:
</h3>

<h6>
Mulai


Operasi Byte
(((11110000 >> 4) & 1111) << 4) | 0 = 11110000

Operasi Word
((111100001111 | 1111111100000000) << 4) >> 4 = 111100001111

Operasi Array Byte dengan Pointer
{1111, 11110000, 11110000} menjadi {11110000, 11110000, 1111}

Operasi Array Word dengan Pointer
{111100001111, 1111111100000000, 111100001111} menjadi {111100001111, 1010101001010101, 1111111111111110}


Selesai
</h6>
