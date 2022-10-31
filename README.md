# midi-tee

For systems using USB MIDI and sndio. Simulates MIDI thru by piping the incoming MIDI signal to its output port, and then allows one additional input from the system itself to join the stream. A workaround to an OpenBSD limitation on one MIDI device per process.

## Build

```
cc main.c -lsndio -o midi-tee
```

## Usage

```
<your process here> | midi-tee <midi port> 
```

MIDI port will default to `rmidi/0` if omitted.

Listens for binary MIDI signal at stdin. Writes it to USB MIDI output. I use it alongside my [Kiwi-8P sysex shell](https://github.com/jimd1989/kiwi8p) like so:

```
rlwrap kiwi8p | midi-tee
```

Doing so, my synthesizer can be synced to something like a Polyend Tracker, which will send clock and note info to the USB MIDI in port, but then also accept parameter controls via `kiwi8p` on my laptop.
