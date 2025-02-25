// TEMPLATE -- Kelas Himpunan berisi anggota dengan type dan jumlah yang dapat disesuaikan
template<typename T, byte N>
class Himpunan
{
  private:
  T anggota[N];

  public:
  // constructor dgn argumen pointer type
  Himpunan(T* x)
  {
    for(byte i = 0; i <= N; i++)
    {
      this->anggota[i] = *(x + i);
    }
  }

  // getter
  void read()
  {
    for(byte i = 0; i < N; i++)
    {
      Serial.println(this->anggota[i]);
    }
    Serial.println();
  }
};

void setup()
{
  // Serial untuk ujicoba
  Serial.begin(600);
  Serial.write("TEMPLATE CLASS USING ARDUINO UNO\n\n\n");


  // kelas Himpunan dengan tipe int sebanyak 10
  Serial.write("Himpunan dengan tipe int sebanyak 10\n\n");
  int bilangan[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  Himpunan<int, 10> bilanganBulat(bilangan);
  bilanganBulat.read();


  // kelas Himpunan dengan tipe bool sebanyak 8
  Serial.write("Himpunan dengan tipe bool sebanyak 8\n\n");
  byte reg = 0b11001111;
  bool buff[8];
  // mengubah byte menjadi array of bool
  for(byte i = 0; i <= 7; i++)
  {
    buff[7 - i] = reg % 2 == 0 ? false : true;
    reg >>= 1;
  }
  Himpunan<bool, 8> regState(buff);
  regState.read();


  // kelas Himpunan dengan tipe char sebanyak 5
  Serial.write("Himpunan dengan tipe char sebanyak 5\n\n");
  char alpabet[5] = {'A', 'B', 'C', 'D', 'E'};
  Himpunan<char, 5> limaAlpabetPertama(alpabet);
  limaAlpabetPertama.read();


  // matikan Serial
  Serial.write("\nSELESAI");
  Serial.end();
}

void loop()
{
}
