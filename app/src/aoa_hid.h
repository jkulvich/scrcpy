#ifndef SC_AOA_HID_H
#define SC_AOA_HID_H

#include <stdint.h>
#include <stdbool.h>

#include <libusb-1.0/libusb.h>

#include "util/cbuf.h"
#include "util/thread.h"
#include "util/tick.h"

struct sc_hid_event {
    uint16_t accessory_id;
    unsigned char *buffer;
    uint16_t size;
    sc_tick delay;
};

// Takes ownership of buffer
void
sc_hid_event_init(struct sc_hid_event *hid_event, uint16_t accessory_id,
                  unsigned char *buffer, uint16_t buffer_size);

void
sc_hid_event_destroy(struct sc_hid_event *hid_event);

struct sc_hid_event_queue CBUF(struct sc_hid_event, 64);

struct sc_aoa {
    libusb_context *usb_context;
    libusb_device *usb_device;
    libusb_device_handle *usb_handle;
    sc_thread thread;
    sc_mutex mutex;
    sc_cond event_cond;
    bool stopped;
    struct sc_hid_event_queue queue;
};

bool
sc_aoa_init(struct sc_aoa *aoa, const char *serial);

void
sc_aoa_destroy(struct sc_aoa *aoa);

bool
sc_aoa_start(struct sc_aoa *aoa);

void
sc_aoa_stop(struct sc_aoa *aoa);

void
sc_aoa_join(struct sc_aoa *aoa);

bool
sc_aoa_setup_hid(struct sc_aoa *aoa, uint16_t accessory_id,
              const unsigned char *report_desc, uint16_t report_desc_size);

bool
sc_aoa_unregister_hid(struct sc_aoa *aoa, uint16_t accessory_id);

bool
sc_aoa_push_hid_event(struct sc_aoa *aoa, const struct sc_hid_event *event);

#endif
