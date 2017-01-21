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
}led_t;

volatile led_t led[4] = { {.r=15, .g=0, .b=0}, {.r=6, .g=9, .b=0}, 
                          {.r=0, .g=9, .b=6}, {.r=2, .g=0, .b=13} };

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
  static uint8_t animation = 0;
  static uint8_t delay_counter = 0;
  static uint8_t animation_running_counter = 0;
  uint8_t led_number, color;
  
  
  if (new_frame) {
    new_frame = 0;

    switch (animation) {
      case 0:
        delay_counter++;
        if (delay_counter == 10) {
          delay_counter = 0;
          //Calculate animation
          if (animation_running_counter == 0) {
            //Init animation
            led[0].r = 15;
            led[0].g = 0;
            led[0].b = 0;
            led[1].r = 6;
            led[1].g = 9;
            led[1].b = 9;
            led[2].r = 0;
            led[2].g = 9;
            led[2].b = 6;
            led[3].r = 2;
            led[3].g = 0;
            led[3].b = 13;
          }
          //Circle some colors
          for (led_number = 0; led_number < 4; led_number++) {
            if (led[led_number].r && !led[led_number].b) {
              led[led_number].r -= 1;
              led[led_number].g += 1;
            }
            if (led[led_number].g && !led[led_number].r) {
              led[led_number].g -= 1;
              led[led_number].b += 1;
            }
            if (led[led_number].b && !led[led_number].g) {
              led[led_number].b -= 1;
              led[led_number].r += 1;
            }
          }
          animation_running_counter++;
          if (animation_running_counter == 50) {
            //Go to the next animation
            animation_running_counter = 0;
            animation++;
          }
        }
        break;

      case 4:
        delay_counter++;
        if (delay_counter == 20) {
          delay_counter = 0;
          //Calculate animation
          if (animation_running_counter == 0) {
            //Init animation
            led[0].r = 0;
            led[0].g = 0;
            led[0].b = 0;
            led[1].r = 0;
            led[1].g = 0;
            led[1].b = 0;
            led[2].r = 0;
            led[2].g = 0;
            led[2].b = 0;
            led[3].r = 0;
            led[3].g = 0;
            led[3].b = 0;
          }
          //Flash red
          if (led[0].r) {
            for (led_number = 0; led_number < 4; led_number++){
              led[led_number].r = 0;
            }
          } else {
            for (led_number = 0; led_number < 4; led_number++){
              led[led_number].r = 15;
            }
          }
          animation_running_counter++;
          if (animation_running_counter == 10) {
            //Go to the next animation
            animation_running_counter = 0;
            animation++;
          }
        }
        break;

      case 2:
        delay_counter++;
        if (delay_counter == 20) {
          delay_counter = 0;
          //Calculate animation
          if (animation_running_counter == 0) {
            //Init animation
            led[0].r = 0;
            led[0].g = 0;
            led[0].b = 0;
            led[1].r = 0;
            led[1].g = 0;
            led[1].b = 0;
            led[2].r = 0;
            led[2].g = 0;
            led[2].b = 0;
            led[3].r = 0;
            led[3].g = 0;
            led[3].b = 0;
          }
          //Flash Green
          if (led[0].g) {
            for (led_number = 0; led_number < 4; led_number++){
              led[led_number].g = 0;
            }
          } else {
            for (led_number = 0; led_number < 4; led_number++){
              led[led_number].g = 15;
            }
          }
          animation_running_counter++;
          if (animation_running_counter == 10) {
            //Go to the next animation
            animation_running_counter = 0;
            animation++;
          }
        }
        break;

      case 3:
        delay_counter++;
        if (delay_counter == 20) {
          delay_counter = 0;
          //Calculate animation
          if (animation_running_counter == 0) {
            //Init animation
            led[0].r = 0;
            led[0].g = 0;
            led[0].b = 0;
            led[1].r = 0;
            led[1].g = 0;
            led[1].b = 0;
            led[2].r = 0;
            led[2].g = 0;
            led[2].b = 0;
            led[3].r = 0;
            led[3].g = 0;
            led[3].b = 0;
          }
          //Flash Blue
          if (led[0].b) {
            for (led_number = 0; led_number < 4; led_number++){
              led[led_number].b = 0;
            }
          } else {
            for (led_number = 0; led_number < 4; led_number++){
              led[led_number].b = 15;
            }
          }
          animation_running_counter++;
          if (animation_running_counter == 10) {
            //Go to the next animation
            animation_running_counter = 0;
            animation++;
          }
        }
        break;

      case 1:
        delay_counter++;
        if (delay_counter == 10) {
          delay_counter = 0;
          //Calculate animation
          if (animation_running_counter == 0) {
            //Init animation
            led[0].r = 0;
            led[0].g = 0;
            led[0].b = 0;
            led[1].r = 0;
            led[1].g = 0;
            led[1].b = 0;
            led[2].r = 0;
            led[2].g = 0;
            led[2].b = 0;
            led[3].r = 0;
            led[3].g = 0;
            led[3].b = 0;
          }
          if (animation_running_counter % 6 == 0) {   //Red
            led[animation_running_counter % 4].r = 15;
            led[animation_running_counter % 4].g = 0;
            led[animation_running_counter % 4].b = 0;
          }
          if (animation_running_counter % 6 == 1) {   //Yellow
            led[animation_running_counter % 4].r = 15;
            led[animation_running_counter % 4].g = 15;
            led[animation_running_counter % 4].b = 0;
          }
          if (animation_running_counter % 6 == 2) {   //Green
            led[animation_running_counter % 4].r = 0;
            led[animation_running_counter % 4].g = 15;
            led[animation_running_counter % 4].b = 0;
          }
          if (animation_running_counter % 6 == 3) {   //Cyan
            led[animation_running_counter % 4].r = 0;
            led[animation_running_counter % 4].g = 15;
            led[animation_running_counter % 4].b = 15;
          }
          if (animation_running_counter % 6 == 4) {   //Blue
            led[animation_running_counter % 4].r = 0;
            led[animation_running_counter % 4].g = 0;
            led[animation_running_counter % 4].b = 15;
          }
          if (animation_running_counter % 6 == 5) {   //Purple
            led[animation_running_counter % 4].r = 15;
            led[animation_running_counter % 4].g = 0;
            led[animation_running_counter % 4].b = 15;
          }
          animation_running_counter++;
          if (animation_running_counter == 40) {
            //Go to the next animation
            animation_running_counter = 0;
            animation++;
          }
        }
        break;

      default:
        animation = 0;
        break;
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

