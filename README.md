# Deneyap-Kart-Uyku-Apnesi-Tespit
Bu projenin amacı, kullanıcının uyku sırasında aldığı pozisyonu ve uzun süreli hareketsizlik durumlarını algılayarak, riskli pozisyonlar (özellikle yüz üstü yatış) ve olası uyku apnesi durumlarını tespit etmek ve kullanıcıyı sesli uyarı ile bilgilendirmektir.
Sistem aynı zamanda tüm verileri OLED ekran üzerinden anlık olarak kullanıcıya sunar.

Sistemin Çalışma Prensibi:

Projede LSM6DSM 6 eksenli ataletsel ölçüm birimi (IMU) kullanılmıştır. Bu sensör, üç eksende ivme (X, Y, Z) ölçümü yaparak cihazın uzaydaki yönelimini belirler.

Z ekseni kullanılarak kullanıcının sırt üstü veya yüz üstü yatıp yatmadığı tespit edilir.
Y ekseni üzerinden kullanıcının sağ yan veya sol yan pozisyonları algılanır.
Belirlenen eşik değerlerine göre pozisyonlar sınıflandırılır.
Riskli Pozisyon Algılama

Sistem, özellikle yüz üstü yatış pozisyonunu riskli olarak kabul eder.
Bu pozisyon algılandığında:
OLED ekranda uyarı mesajı gösterilir
Buzzer üzerinden sesli alarm verilir
Bu sayede kullanıcı pozisyon değiştirmeye teşvik edilir.

Apne (Hareketsizlik) Tespiti:

Apne tespiti için ivme verilerinin toplam değişimi izlenmiştir:
X, Y ve Z eksenlerindeki ivme değerlerinin mutlak toplamı hesaplanır
Belirli bir süre (örneğin 10 saniye) boyunca anlamlı bir hareket algılanmazsa bu durum olası apne olarak kabul edilir
Her apne olayı sayaçta kaydedilir
Kullanıcı kısa bir sesli uyarı ile bilgilendirilir

  OLED Ekran Gösterimi:
    
Sistem tüm bilgileri harici bir bilgisayar bağlantısına ihtiyaç duymadan OLED ekran üzerinden gösterir:
Anlık sistem durumu (Normal / Apne)
X, Y, Z eksenlerindeki ivme değerleri
Algılanan uyku pozisyonu
Toplam apne sayısı
Ekran güncellemesi satır bazlı yapıldığı için titreme oluşmaz ve görüntü stabildir.

   Uyarı Mekanizması:

Yüz üstü pozisyon algılandığında sürekli sesli uyarı
Apne tespitinde kısa süreli yüksek frekanslı bip sesi
Diğer durumlarda sistem sessiz çalışır

Kullanılan Donanımlar:
Deneyap Kart 1a v1
Deneyap 6 Eksenli Ataletsel Ölçüm Birimi
Deneyap OLED ekran
Buzzer

  Kullanılan Yazılım:
Deneyapkart IDE

  Kullanılan kütüphaneler:
Deneyap_6EksenAtaletselOlcumBirimi
Deneyap_OLED
Arduino Core Libraries
