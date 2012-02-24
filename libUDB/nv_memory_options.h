#ifndef NV_MEMORY_OPTIONS_H
#define NV_MEMORY_OPTIONS_H

////////////////////////////////////////////////////////////////////////////////
// Use non volatile memory to store and recall settings
// Set to 1 to include non volatile memory service in compilation
// WARNING: THIS FEATURE IS UNDER DEVELOPMENT
// WARNING: Use on UDB4+ only
#define USE_NV_MEMORY					1


////////////////////////////////////////////////////////////////////////////////
// Manual erase / format of non volatile memory table
// If set to 1, does manual erase of memory table when it runs.
// Use to go back to all hard coded defaults.
// Reset to 0 after clearing to use the non volatile memory again.
#define MANUAL_ERASE_TABLE				0


////////////////////////////////////////////////////////////////////////////////
// Use flexifunctions for mixing instead of standard servomix
// Setting to 1 to enable, 0 to use standard servomix.
// WARNING: THIS FEATURE IS UNDER DEVELOPMENT
// WARNING: Must use MAVlink and NV memory on UDB4+ only
#define USE_FLEXIFUNCTION_MIXING		0


////////////////////////////////////////////////////////////////////////////////
// Use the I2C shared device driver on the second I2C port
#define USE_I2C_SECOND_PORT_DRIVER		1


#endif //NV_MEMORY_OPTIONS_H


