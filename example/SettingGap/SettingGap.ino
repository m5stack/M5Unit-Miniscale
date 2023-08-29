#include <M5Stack.h>
#include <M5GFX.h>
#include "UNIT_SCALES.h"

M5GFX display;
M5Canvas canvas(&display);
UNIT_SCALES scales;

void setup() {
    M5.begin();
    display.begin();
    canvas.setColorDepth(8);  // mono color
    canvas.setFont(&fonts::efontCN_12);
    canvas.createSprite(display.width(), display.height());
    canvas.setTextSize(2);
    while (!scales.begin(&Wire, 21, 22, DEVICE_DEFAULT_ADDR)) {
        Serial.println("scales connect error");
        M5.Lcd.print("scales connect error");
        delay(1000);
    }
    scales.setLEDColor(0x001000);
}

void loop() {
    float weight = scales.getWeight();
    float gap    = scales.getGapValue();
    int adc      = scales.getRawADC();

    canvas.fillSprite(BLACK);
    canvas.setTextSize(2);
    canvas.drawString("Unit Scale Gap Setting", 10, 10);
    canvas.setTextColor(WHITE);
    canvas.setCursor(10, 50);
    canvas.setTextSize(2);
    canvas.printf("WEIGHT:");
    canvas.setTextColor(GREEN);
    canvas.setTextSize(3);
    canvas.printf("%.2fg", weight);
    canvas.setCursor(10, 100);
    canvas.setTextColor(WHITE);
    canvas.setTextSize(2);
    canvas.printf("ADC:");
    canvas.setTextColor(GREEN);
    canvas.setTextSize(3);
    canvas.printf("%d", adc);
    canvas.setTextColor(WHITE);
    canvas.setCursor(10, 150);
    canvas.setTextSize(2);
    canvas.printf("GAP:");
    canvas.setTextColor(GREEN);
    canvas.setTextSize(3);
    canvas.printf("%.2f", gap);
    canvas.setTextColor(ORANGE);
    canvas.setTextSize(2);
    canvas.drawString("[GapVal+]", 0, 210);
    canvas.drawString("[Offset]", 110, 210);
    canvas.drawString("[GapVal-]", 210, 210);
    canvas.pushSprite(0, 0);

    M5.update();
    if (M5.BtnA.wasPressed()) {
        gap += 0.1;
        scales.setGapValue(gap);
    } else if (M5.BtnC.wasPressed()) {
        gap -= 0.1;
        scales.setGapValue(gap);
    } else if (M5.BtnB.wasPressed()) {
        scales.setOffset();
    }
}