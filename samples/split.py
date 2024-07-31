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

fnameSuffix = input("Filename suffix: ")

bpm = 120
quarterNoteDuration = (60000 / bpm) * 4 # gives duration in ms. 60,000ms / bpm = duration # not actual quarter notes its actually a whole bar but who gives a fuck
variantsPerNote = 1
totalDivisions = len(notes) * variantsPerNote

for i in range(totalDivisions):
    print(f"Trimming for note number {52+i}")
    for j in range(variantsPerNote):
        print(f"    trimming for variant {j}")
        start = (i * variantsPerNote + j) * quarterNoteDuration
        end = (i * variantsPerNote + j + 1) * quarterNoteDuration

        audio = AudioSegment.from_wav("batch3.wav")
        
        audio = audio[start:end]
        audio.export(f'trbx174/{notes[i]}{fnameSuffix}.wav', format="wav")
