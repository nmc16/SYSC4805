import pygame
import pygame.midi
from pygame.locals import *
import bluetooth
import serial

pygame.init()

pygame.fastevent.init()
post_event = pygame.fastevent.post

pygame.midi.init()
in_id = pygame.midi.get_default_input_id()
print("Got ID: %d\n" % in_id)
print("Have %d IDs\n" % pygame.midi.get_count())
print("Device info: %s" % str(pygame.midi.get_device_info(in_id)))
inp = pygame.midi.Input(in_id)

while True:
    events = pygame.fastevent.get()

    if inp.poll():
        midi_events = inp.read(10)
        if int(midi_events[0][0][0]) in [224, 225, 226]:  # Pitch Bender
            print str(midi_events[0][0][2])  # right(0)  center(64)  left(124)

        print "full midi_events " + str(midi_events)
        print "my midi note is " + str(midi_events[0][0][1])
        # convert them into pygame events.
        midi_evs = pygame.midi.midis2events(midi_events, inp.device_id)
        print("Note Events: %s" % str(midi_evs))
        for m_e in midi_evs:
            pygame.fastevent.post(m_e)

print "exit button clicked."
i.close()
pygame.midi.quit()
pygame.quit()
exit()
