# vdc
Virtual Drum Circle

This project originated circa 2007 with the intent of creating a system by which individuals could participate in a virtual drum circle in an MRI scanner, tapping along bi-manually to various accompanying loops, with the scanner pinging sounds constituting one of the metric levels. Various Max/MSP patches were created in support of these efforts, including a Groove Sequencer, first written by Peter Keller during a research visit to the lab, and an Experiment Manager, largely written by Joe Saavedra, an undergraduate in the lab. The documentation below was pulled from the Janata Lab wiki pages. Running the experiments requires various external hardware, but the core capabilities of the Groove Sequencer and Experiment Manager are not dependent on it.

## Max/MSP
These components are part of a family of [[Max/MSP patches]] that have been developed in the lab. All patches were written and have been optimized for Max/MSP 4.6.2. Most current versions can be found at : < afs/petrlab/vdc/CURRENT_as_of_Joe/ >

### General Setup
Before running any of the patches:
1. Menu: Options->"DSP Status..." - make sure all audio is setup correctly.
2. Menu: Options->"File Preferences..." - make sure that the directory containing the patches and the directory containing the "conditions" file are listed in your Max Path. Currently, for the local copy, these are:
- "Groove HD:/Users/Shared/projects/VDC/Patches/"
- "Groove HD:/Users/Shared/projects/VDC/Lists/coll_object_lists/
3. Make sure the correct MIDI output device is selected for the Groove Sequencer.
- This can be changed by double-clicking on the "playpattern" subpatch, then double-clicking on the "noteout a" patches for each instrument. Currently, for playing through the Proteus 2000, we are selecting "Fastlane USB Port B".
4. Set up the drum pad
- **If you are using the Blue Box, make sure to turn it on after the Max patch.** Otherwise, the Max Patch will not register MIDI messages from it.
- **Set the first 8 hex numbers of the Blue Box to "E011E122".**
- If you are using the Roland Handsonic, change the MIDI note numbers for the left and right hands.
- Open the "subject tapping" subpatch in the vdc_exp_control patch and change the "sel" objects for left and right hands to the correct MIDI notes.
- For the Roland Handsonic, these are "sel 60" for the left hand and "sel 74" for the right hand. For the Whoopie Box, they are "sel 115" and "sel 127" for left and right respectively.
- The patch needs to be improved so that we could change MIDI notes without having to change the object text.

### Launching and Running
1. Launch Experiment Manager in the "Patches" folder.
2. In the "Save" dialog box that pops up, select the folder and enter the filename of the log file for this session. Click "Save"
3. Type in a Subject ID under "Subject ID Number". When this is changed and you click outside the box, you will get a dialog box to select a folder where MIDI files for subject tapping responses will be saved.
4. Select the MIDI Tapping input device. Currently we are using "Fastlabe USB Port B"
5. Double click on "vdc_exp_control_1_2". This will open the VDC Controller/Recorder.
6. Click "Load New Stim Lists" in vdc_exp_control. An "open document" dialog box will open. Select the file for the polyphonic instrument stim ID list and click "Choose". A second "open document" dialog box will open for the Simgle instrument stim ID list. Select the appropriate file and click "choose". The order is always poly instrument, then single instrument. Currently we are using "poly_inst_stims" for poly and "single_inst_stims" for single instrument stims. These are located in the Lists/coll_object_lists folder.
7. Double click the "groove_sequencer_2_3_exp" patch in the vdc_exp_control window. This will open the Groove Sequencer.

### Troubleshooting
- If patches aren't behaving correctly, or if you see a message in the Max window that indicates "no file conditions", check the File Preferences in Max (described in General Setup above).
- If the Groove Sequencer seems to start (Column value changes), but you hear no sound, check that the correct MIDI device is selected (General Setup above). Also see if the MIDI lights are flashing on all the devices through which you are sending MIDI (e.g. Fastlane-USB, Proteus 2000, etc.).
- If you can't record tapping and "detonate" window (timeline) does not show any MIDI messages, see that the correct MIDI notes are selected for your instrument (General Setup).

### Experiment Manager
- Current version: 1.3 [experiment_manager_1_3]
This is intended to be a modular abstraction, and can be used with any experiment that requires a parent controller. 
Patch includes 
- text fields for Experiment Name and Subject ID
- menu for selecting a MIDI input device
- duration of trial, current duration
- several fields for specific conditions per trial
- text file documentation of all changes made

The most important feature of the Experiment Manager is the text file it produces.  The moment any parameter is changed or button pressed, a save dialog box will appear asking for a file name.  This is for a text file that will save a log of every event or change that occurs, as well as what time it occurred. [time is kept by cpuclock object - logical time from max's scheduler, relative to when max started].
This version contains an abstraction of the more specific VDC Experiment Controller patch, brilliantly named "vdc_exp_control_1_2".

#### Subpatch Descriptions
- write_events_to_text_with_clock - Handles writing to Experiment Manager's event log

### VDC Experiment Controller

- Current version: 1.2 [vdc_exp_control_1_2]

This abstraction is specific to the VDC project, and serves the following purposes:
- holds lists of the stims to be used in a given run
Clicking "check stim lists" will open the lists automatically stored in the 'coll' objects located within the sub-patch [preset_list_interp].  These are lists, created beforehand of stim ID numbers to be used in a run.  Clicking "Load New Stim Lists" will bring up two dialog boxes for choosing a new stim list. As noted in the patch, the first dialog box is for the poly instrument stim list, and the second is for the single instrument stim list.
- performs a randomized stim selection
This occurs within the [preset_list_interp] sub-patch
- controls volume levels for the subject tapping and stim presentation
- plays back stims directly from the sequencer
Stims are recalled and then performed from the Groove Sequencer abstraction
- records all data (stim, tapping, other information) into MIDI files.
The 'detonate' object is used for all MIDI file writing. Sub-patch [write_MIDI_file_by_subjectID] has a somewhat misleading name, as it is used to create an initial MIDI file, and then all subsequent MIDI files.  Specifically, each time a single trial is executed, a new MIDI is saved (in a folder which is chosen when the Subject ID field of the Manager is filled) using the unique current trial number. The Stim ID is also written into each MIDI file using the 4-digit format.
##### 4-digit stim ID format
- Stim ID format used to recall stims within these here max/msp patches. Once stims (specifically those from the Groove Sequencer) are selected for use in an experiment, they need to be located within the Groove Sequencer's preset objects. 
- Stims in preset bank A are assigned to 1XXX
- Stims in preset bank B are assigned to 2XXX
- Stims in preset bank C are assigned to 3XXX

An example of this is if a stim is preset 101 in preset bank B, it's Stim ID is 2101.  Preset number 5 in bank C would be 3005.  Preset number 51 in bank A would be 1051. I think the pattern is pretty clear at this point.


### Groove Sequencer
Current Version: 2.3 [groove_sequencer_2_3_exp] -written by Peter Keller and Joe Saavedra-

Features:
- Stores all stims in three preset banks (A, B, and C)
Each preset bank can be saved in it's entirety by clicking 'write'. 'read' allows you to load a different preset bank file (files of current banks are located in the vdc_exp_run folder).  Saving a preset is simple - just compose the sequence, set the tempo and instrument levels, then hold shift while clicking in a preset slot within a bank.  To delete a single preset, click it, then hit 'clear' message above the appropriate bank.
- Controls tempo and playback of each stim
Tempo is controlled by the uslider labeled tempo, and literally changes the milliseconds spent on each column (beat) of the sequencer.  A BPM calculation is made below it for information purposes.  The Cycle Length uslider controls how many beats are in each repetition of a phrase or measure (max 64).
- Sends MIDI noteouts for each instrument
Currently, the instruments listed in the menus on the left are specifically set for the [[Proteus 2000 setup]].
- Currently has sample playback capabilities
Within the sub-patch [playpattern] you can see the makenotes for each instrument's MIDI notes.  At the bottom, another sub-p, [sample_playback] contains a series of buffers representing each instrument for recall and playback without the need of the Proteus, but still allows us to record MIDI and hear the given instruments.  Currently, the samples loaded are recorded directly from the Proteus.
- Instrument 6 devoted to mimicking ping sound of MRI scanner
This is just a constant 16th note, triggering a sample of the pinging sound.
- Process for composing new stims
Objects directly below the sequencer matrix are methods for composing objective stims. A,B,C,and D are the four possibilities for organizing beats within a 4/4 time signature. All stims were created using permutations of these basic roots.

