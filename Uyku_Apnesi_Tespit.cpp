#include <Deneyap_6EksenAtaletselOlcumBirimi.h>
#include <Deneyap_OLED.h>

#define BUZZER_PIN D12

LSM6DSM AccGyro;
OLED OLED;

float accX, accY, accZ;
const float POZISYON_ESIK = 0.30;

unsigned long sonHareketZamani = 0;
unsigned long ekranGuncellemeZamani = 0;
bool apneDurumu = false;
int toplamApneSayisi = 0;
String pozisyonMetni = "BASLIYOR";

void setup() {
  // IMU baslat (geri donus degeri ONEMSIZ)
  AccGyro.begin(0x6A);
  AccGyro.begin(0x6B);   // biri mutlaka tutar

  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);

  OLED.begin(0x7A);

  OLED.setTextXY(2, 2);
  OLED.putString("Kalibrasyon");
  delay(1000);

  // Sabit basliklar (bir kere yazilir)
  OLED.setTextXY(0, 0); OLED.putString("Durum:");
  OLED.setTextXY(1, 0); OLED.putString("X:");
  OLED.setTextXY(2, 0); OLED.putString("Y:");
  OLED.setTextXY(3, 0); OLED.putString("Z:");
  OLED.setTextXY(4, 0); OLED.putString("Poz:");
  OLED.setTextXY(6, 0); OLED.putString("Apne:");

  sonHareketZamani = millis();
}

void loop() {
  // --- SENSOR OKUMA ---
  accX = AccGyro.readFloatAccelX();
  accY = AccGyro.readFloatAccelY();
  accZ = AccGyro.readFloatAccelZ();

  // --- POZISYON TESPITI ---
  if (accZ < -POZISYON_ESIK) {
    pozisyonMetni = "YUZ USTU";
    tone(BUZZER_PIN, 1000);
  } else {
    noTone(BUZZER_PIN);

    if (accZ > POZISYON_ESIK)        pozisyonMetni = "SIRT USTU";
    else if (accY > POZISYON_ESIK)   pozisyonMetni = "SOL YAN";
    else if (accY < -POZISYON_ESIK)  pozisyonMetni = "SAG YAN";
    else                            pozisyonMetni = "ARA POZ";
  }

  // --- APNE KONTROL ---
  static float oncekiAcc = 0;
  float toplamAcc = abs(accX) + abs(accY) + abs(accZ);
  float fark = abs(toplamAcc - oncekiAcc);
  oncekiAcc = toplamAcc;

  if (fark > 0.05) {
    sonHareketZamani = millis();
    apneDurumu = false;
  }

  if (millis() - sonHareketZamani > 10000) {
    if (!apneDurumu) {
      apneDurumu = true;
      toplamApneSayisi++;
    }
    tone(BUZZER_PIN, 2000, 150);
  }

  // --- OLED GUNCELLEME (TITREME YOK) ---
  if (millis() - ekranGuncellemeZamani > 400) {

    OLED.setTextXY(0, 7);
    OLED.putString(apneDurumu ? "!APNE! " : "NORMAL");

    OLED.setTextXY(1, 3); OLED.putString("       ");
    OLED.setTextXY(1, 3); OLED.putString(String(accX, 2).c_str());

    OLED.setTextXY(2, 3); OLED.putString("       ");
    OLED.setTextXY(2, 3); OLED.putString(String(accY, 2).c_str());

    OLED.setTextXY(3, 3); OLED.putString("       ");
    OLED.setTextXY(3, 3); OLED.putString(String(accZ, 2).c_str());

    OLED.setTextXY(4, 5); OLED.putString("         ");
    OLED.setTextXY(4, 5); OLED.putString(pozisyonMetni.c_str());

    OLED.setTextXY(6, 6); OLED.putString("   ");
    OLED.setTextXY(6, 6); OLED.putString(String(toplamApneSayisi).c_str());

    ekranGuncellemeZamani = millis();
  }

  delay(20); // I2C stabilitesi (50 Hz)
}
