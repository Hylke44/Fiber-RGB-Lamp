//##############################################################################                   
//#     ______      # PROJECT:
//#    -      -     #   Fiber RGB Lamp
//#   /  |  |\ \    # DESCRIPTION:
//#  |  _|__|_\ |   #   A hacked blue fiber lamp to support rgb lights.
//#  | \ |  |   |   #   The big 10mm blue led inside the lamp has been 
//#   \ \|  |  /    #   replaced with an arduino nano and four smd rgb leds.
//#    -______-     #
//#                 #
//##############################################################################

const uint8_t interrupt_time[] = {104, 43, 32, 28, 24, 21, 20};

volatile uint8_t new_frame = 1;
uint8_t counter = 0;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t animation;
  uint8_t delay_counter;
  uint8_t animation_running_counter;
}led_t;

volatile led_t led[4] = {0};

void setup() {
  // put your setup code here, to run once:

  //Set led pins as output
  DDRB |= 0b00000011;   //D8, D9
  DDRC |= 0b00111111;   //A0, A1, A2, A3, A4, A5
  DDRD |= 0b11110000;   //D4, D5, D6, D7

  //Set default output to 1
  PORTB |= 0b00000011;   //D8, D9
  PORTC |= 0b00111111;   //A0, A1, A2, A3, A4, A5
  PORTD |= 0b11110000;   //D4, D5, D6, D7
  
  cli();//stop interrupts

  //set timer0 interrupt
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register
  OCR0A = 68;
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS02 bits for 256 prescaler
  TCCR0B |= (1 << CS02);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  sei();//allow interrupts
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t led_number;
  
  
  if (new_frame) {
    new_frame = 0;

    // Calculate the color of each led
    for (led_number = 0; led_number < 4; led_number++) {
      led[led_number].delay_counter++;
      
      // Each led has its own delay so the colors shift
      if (led_number == 0 && led[led_number].delay_counter == 3 ||
          led_number == 1 && led[led_number].delay_counter == 4 ||
          led_number == 2 && led[led_number].delay_counter == 5 ||
          led_number == 3 && led[led_number].delay_counter == 6    ) {
        // Reset the delay counter
        led[led_number].delay_counter = 0;

        // Calculate the animation
        switch (led[led_number].animation) {
          case 0:   // Black
            // No changes in color
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 1:   // Black -> Blue
            // Turn blue on to max
            led[led_number].b = led[led_number].animation_running_counter;
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 2:   // Blue
            // No changes in color
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 3:   // Blue -> Purple
            // Set both blue and red to 10/15
            led[led_number].b = 15 - led[led_number].animation_running_counter/3;
            led[led_number].r = led[led_number].animation_running_counter*2/3;
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 4:   // Purple
            // No changes in color
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 5:   // Purple -> Red
            // Set red to 15/15
            led[led_number].b = 10 - led[led_number].animation_running_counter*2/3;
            led[led_number].r = 10 + led[led_number].animation_running_counter/3;
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 6:   // Red
            // No changes in color
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 7:   // Red -> Yellow
            // Set red and green to 10/10
            led[led_number].r = 15 - led[led_number].animation_running_counter/3;
            led[led_number].g = led[led_number].animation_running_counter*2/3;
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 8:   // Yellow
            // No changes in color
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 9:   // Yellow -> Green
            // Set green to 15/15
            led[led_number].r = 10 - led[led_number].animation_running_counter*2/3;
            led[led_number].g = 10 + led[led_number].animation_running_counter/3;
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 10:  // Green
            // No changes in color
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 11:  // Green -> Cyan
            // Set green and blue to 10/15
            led[led_number].g = 15 - led[led_number].animation_running_counter/3;
            led[led_number].b = led[led_number].animation_running_counter*2/3;
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 12:  // Cyan
            // No changes in color
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 13:  // Cyan -> White
            // Set red, green and blue to 7/15
            led[led_number].g = 10 - led[led_number].animation_running_counter/5;
            led[led_number].b = 10 - led[led_number].animation_running_counter/5;
            led[led_number].r = led[led_number].animation_running_counter/2;
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 14:  // White
            // No changes in color
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
  
          case 15:  // White -> black
            // Set red, green and blue to 0/15
            led[led_number].g = 7 - led[led_number].animation_running_counter/2;
            led[led_number].b = 7 - led[led_number].animation_running_counter/2;
            led[led_number].r = 7 - led[led_number].animation_running_counter/2;
            led[led_number].animation_running_counter++;
            if (led[led_number].animation_running_counter == 16) {
              led[led_number].animation_running_counter = 0;
              led[led_number].animation++;  // Goto next animation part
            }
            break;
              
          default:
            led[led_number].animation = 0;
            break;
        }
      }
    }
  }
}

ISR(TIMER0_COMPA_vect) {
  static uint8_t frame_counter = 0;
  uint8_t out_b = 0, out_c = 0, out_d = 0;
  
  frame_counter++;
  if (frame_counter == 15) {
    new_frame = 1;
    frame_counter = 0;
  }

  if (led[0].r <= frame_counter) out_d |= 0x40;  //D6
  if (led[0].g <= frame_counter) out_d |= 0x20;  //D5
  if (led[0].b <= frame_counter) out_d |= 0x10;  //D4
  
  if (led[1].r <= frame_counter) out_c |= 0x20;  //A5
  if (led[1].g <= frame_counter) out_c |= 0x10;  //A4
  if (led[1].b <= frame_counter) out_c |= 0x08;  //A3
  
  if (led[2].r <= frame_counter) out_c |= 0x04;  //A2
  if (led[2].g <= frame_counter) out_c |= 0x02;  //A1
  if (led[2].b <= frame_counter) out_c |= 0x01;  //A0
  
  if (led[3].r <= frame_counter) out_b |= 0x02;  //D9
  if (led[3].g <= frame_counter) out_b |= 0x01;  //D8
  if (led[3].b <= frame_counter) out_d |= 0x80;  //D7
  
  PORTB = (PORTB & ~0b00000011) | out_b;
  PORTC = (PORTC & ~0b00111111 ) | out_c;
  PORTD = (PORTD & ~0b11110000 ) | out_d;

}

