#include "pico/malloc.h"
#include "pico/multicore.h"
#include "pico/mutex.h"
#include "pico/rand.h"
#include "pico/stdlib.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_LENGTH 30
#define N_ALIVE_MESSAGES 8
#define ECHO_SLEEP 500
#define ALIVE_SLEEP 8000

auto_init_mutex(mutex);
unsigned int cursor = 0;
char buffer[BUFFER_LENGTH];

const char ALIVE_MESSAGES[N_ALIVE_MESSAGES][200] = {
    "...",
    "so much silence...",
    "hello?",
    "anyone there?",
    "I'm waaiting...",
    "hi there, need some help?",
    "I'm the pico-echo demo program, welcome!",
    "you can write anything to <<read>> an ECHO!",
};

const char *random_alive_message() {
  uint32_t min = 0;
  uint32_t max = N_ALIVE_MESSAGES * 1.3;
  unsigned int n = min + (get_rand_32() % (max - min + 1));
  if (n >= N_ALIVE_MESSAGES) {
    n = N_ALIVE_MESSAGES - 1;
  }

  return ALIVE_MESSAGES[n];
}

void reduce_echo(char *str) {
  int length = strlen(str);
  if (length == 0)
    return; // Edge case: empty string

  printf("Yelled: %s\n", str);
  sleep_ms(ECHO_SLEEP); // Delay for effect

  // Step 1: Preserve only capital letters (if any exist)
  int has_caps = 0;
  for (int i = 0; i < length; i++) {
    if (isupper(str[i])) {
      has_caps = 1;
      break;
    }
  }

  if (has_caps) {
    char temp[length + 1];
    int j = 0;
    for (int i = 0; i < length; i++) {
      if (isupper(str[i]) || str[i] == '!') { // Keep capitals and punctuation
        temp[j++] = str[i];
      }
    }
    temp[j] = '\0';
    printf("%s\n", temp); // First step: uppercase only
    strcpy(str, temp);
    length = j;
    sleep_ms(ECHO_SLEEP);
  }

  // Step 2: Convert to lowercase while reducing
  while (length > 3) {
    int reduced_length = length - length / 4; // Reduce by ~25%
    for (int i = 0; i < reduced_length; i++) {
      str[i] = tolower(str[i]);
    }
    str[reduced_length] = '\0';
    length = reduced_length;
    printf("%s\n", str); // Print each step
    sleep_ms(ECHO_SLEEP);
  }

  // Step 3: Final fade with "..."
  if (length > 2) {
    str[length - 2] = '.';
    str[length - 1] = '.';
    str[length] = '\0';
    printf("%s\n", str);
    sleep_ms(ECHO_SLEEP);
  }
}

void blink_alive() {
  gpio_put(25, 1);
  sleep_ms(50);
  gpio_put(25, 0);
  sleep_ms(50);
}

void core1_main() {
  while (1) {
    mutex_enter_blocking(&mutex);
    if (cursor != 0) {
      printf("\r");
      for (int i = 0; i <= cursor; ++i) {
        printf(" ");
      }
      printf("\r");
    }
    printf("%s\n", random_alive_message());
    printf("%s", buffer);
    mutex_exit(&mutex);
    for (int i = 0; i < 3; ++i) {
      blink_alive();
    }
    sleep_ms(ALIVE_SLEEP);
  }
}

void clear_arr(char *arr) { memset(&arr[0], 0, sizeof(arr)); }

int main() {
  stdio_init_all();

  // initialise GPIO (Green LED connected to pin 25)
  gpio_init(25);
  gpio_set_dir(25, GPIO_OUT);
  clear_arr(buffer);

  sleep_ms(ECHO_SLEEP);
  printf("%s\n", ALIVE_MESSAGES[N_ALIVE_MESSAGES - 2]);
  printf("%s\n", ALIVE_MESSAGES[N_ALIVE_MESSAGES - 1]);

  // init core 1 task
  multicore_launch_core1(core1_main);

  while (1) {
    char ch;
    scanf("%c", &ch);
    printf("%c", ch);
    mutex_enter_blocking(&mutex);
    buffer[cursor] = ch;
    cursor++;
    if ((cursor >= BUFFER_LENGTH - 1) || (ch == '\r' || ch == '\n')) {
      printf("\n");
      reduce_echo(buffer);
      clear_arr(buffer);
      cursor = 0;
    }
    mutex_exit(&mutex);
  }
}
