from pydub import AudioSegment

notes = [
    "E",
    "F",
    "Gb",
    "G",
    "Ab",
    "A",
    "Bb",
    "B",
    "C",
    "Db",
    "D",
    "Eb"
]

#fnameSuffix = input("Filename suffix: ")
octave = 4

bpm = 120
quarterNoteDuration = (60000 / bpm) * 4 # gives duration in ms. 60,000ms / bpm = duration # not actual quarter notes its actually a whole bar but who gives a fuck
variantsPerNote = 2
totalDivisions = len(notes) * variantsPerNote

for i in range(totalDivisions):
    print(f"Trimming for note number {52+i}")
    
    if i % 12 == 0: octave += 1

    for j in range(variantsPerNote):
        print(f"    trimming for variant {j}")
        start = (i * variantsPerNote + j) * quarterNoteDuration
        end = (i * variantsPerNote + j + 1) * quarterNoteDuration

        audio = AudioSegment.from_wav("batch4.wav")
        
        audio = audio[start:end]
        audio.export(f'trbx174/slap/{notes[i]}{octave}{j}.wav', format="wav")
