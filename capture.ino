/*
  Arduino DSLR Shutter Controller
*/

// --- COPY AND PASTE PYTHON OUTPUT HERE ---
// Calculated for 240 frames.
const unsigned long shutterListMS[] = {100, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 400, 400, 400, 400, 400, 400, 400, 400, 400, 500, 500, 500, 500, 500, 500, 500, 600, 600, 600, 600, 600, 600, 700, 700, 700, 700, 700, 800, 800, 800, 800, 900, 900, 900, 900, 1000, 1000, 1000, 1100, 1100, 1100, 1200, 1200, 1200, 1300, 1300, 1400, 1400, 1400, 1500, 1500, 1600, 1600, 1700, 1700, 1800, 1800, 1900, 2000, 2000, 2100, 2100, 2200, 2300, 2400, 2400, 2500, 2600, 2700, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3900, 4000, 4100, 4200, 4400, 4500, 4600, 4800, 4900, 5100, 5300, 5400, 5600, 5800, 5900, 6100, 6300, 6500, 6700, 6900, 7200, 7400, 7600, 7900, 8100, 8400, 8600, 8900, 9200, 9500, 9800, 10100, 10400, 10800, 11100, 11400, 11800, 12200, 12600, 13000, 13400, 13800, 14200, 14700, 15200, 15600, 16100, 16600, 17200, 17700, 18300, 18900, 19500, 20100, 20700, 21400, 22100, 22800, 23500, 24200, 25000, 25800, 26600, 27500, 28300, 29200, 30200, 31100, 32100, 33100, 34200, 35300, 36400, 37600, 38800, 40000, 41300, 42600, 43900, 45300, 46800, 48300, 49800, 51400, 53000, 54700, 56500, 58300, 60100, 62000, 64000, 66000, 68100, 70300, 72500, 74800, 77200, 79700, 82200, 84800, 87500, 90300, 93200, 96200, 99200, 102400, 105700, 109000, 112500, 116100, 119800, 123600, 127500, 131600, 135800, 140100, 144600, 149200, 153900, 158800, 163900, 169100, 174500, 180000};
const unsigned long pauseListMS[] = {120000, 117700, 115300, 113000, 110800, 108600, 106400, 104300, 102200, 100200, 98200, 96200, 94300, 92400, 90600, 88800, 87000, 85300, 83600, 81900, 80300, 78700, 77100, 75600, 74100, 72600, 71200, 69800, 68400, 67000, 65700, 64400, 63100, 61800, 60600, 59400, 58200, 57100, 55900, 54800, 53700, 52700, 51600, 50600, 49600, 48600, 47600, 46700, 45700, 44800, 43900, 43100, 42200, 41400, 40500, 39700, 39000, 38200, 37400, 36700, 35900, 35200, 34500, 33800, 33200, 32500, 31900, 31200, 30600, 30000, 29400, 28800, 28200, 27700, 27100, 26600, 26100, 25500, 25000, 24500, 24100, 23600, 23100, 22600, 22200, 21800, 21300, 20900, 20500, 20100, 19700, 19300, 18900, 18500, 18200, 17800, 17400, 17100, 16800, 16400, 16100, 15800, 15500, 15200, 14900, 14600, 14300, 14000, 13700, 13400, 13200, 12900, 12700, 12400, 12200, 11900, 11700, 11500, 11200, 11000, 10800, 10600, 10400, 10200, 10000, 9800, 9600, 9400, 9200, 9000, 8800, 8700, 8500, 8300, 8200, 8000, 7800, 7700, 7500, 7400, 7200, 7100, 6900, 6800, 6700, 6500, 6400, 6300, 6200, 6000, 5900, 5800, 5700, 5600, 5500, 5400, 5300, 5100, 5000, 4900, 4900, 4800, 4700, 4600, 4500, 4400, 4300, 4200, 4100, 4100, 4000, 3900, 3800, 3700, 3700, 3600, 3500, 3500, 3400, 3300, 3300, 3200, 3100, 3100, 3000, 3000, 2900, 2800, 2800, 2700, 2700, 2600, 2600, 2500, 2500, 2400, 2400, 2300, 2300, 2200, 2200, 2200, 2100, 2100, 2000, 2000, 2000, 1900, 1900, 1800, 1800, 1800, 1700, 1700, 1700, 1600, 1600, 1600, 1500, 1500, 1500, 1500, 1400, 1400, 1400, 1300, 1300, 1300, 1300, 1200, 1200, 1200, 1200, 1200, 1100, 1100, 1100, 1100, 1000};
// --- END OF COPY/PASTE BLOCK ---

// This is the pause before the very first shot
const unsigned long initialPauseMS = 5000;

// Hardware and State Variables (Do Not Edit)
const int shutterPin = 7;
const int listLen = (sizeof(shutterListMS) / sizeof(shutterListMS[0]));

unsigned long lastMillis = 0;
unsigned long currentPauseDuration = 0;
unsigned int exposureCount = 0;


void setup() {
  pinMode(shutterPin, OUTPUT);
  digitalWrite(shutterPin, LOW);

  // Set the initial pause before the sequence begins
  currentPauseDuration = initialPauseMS;
  lastMillis = millis(); // Start the timer
}

void loop() {
  // Check if there are still exposures to take
  if (exposureCount < listLen) {
    
    // Check if the pause time has elapsed
    if (millis() - lastMillis >= currentPauseDuration) {
      
      // --- Take the Picture ---
      // (You could add a status update here for your 7-segment display)
      digitalWrite(shutterPin, HIGH);
      delay(shutterListMS[exposureCount]); // Hold shutter open for the calculated time
      digitalWrite(shutterPin, LOW);

      // --- Prepare for the Next Shot ---
      exposureCount++; // Increment the counter
      
      // If there are more shots to take, set the next pause duration
      if (exposureCount < listLen) {
        // The pauseListMS has one fewer element than shutterListMS,
        // so we use exposureCount-1 as the index.
        currentPauseDuration = pauseListMS[exposureCount - 1];
      }
      
      // Reset the timer for the beginning of the next pause
      lastMillis = millis();
    }
  }
  // If exposureCount >= listLen, the loop will do nothing. The program is finished.
}