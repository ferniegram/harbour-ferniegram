.pragma library
.import Sailfish.Silica 1.0 as Silica

// Silica platform functions

function formatDate(timestamp, formatType) {
    return Silica.Format.formatDate(new Date(timestamp * 1000), formatType)
}

function getDateTimeElapsed(timestamp) {
    return formatDate(timestamp, Silica.Formatter.DurationElapsed)
}

function getDateTimeTimepoint(timestamp) {
    return formatDate(timestamp, Silica.Formatter.Timepoint)
}

function getDateTimeTimepointRelative(timestamp) {
    return formatDate(timestamp, Silica.Formatter.TimepointRelative)
}


function isWidescreen(appWindow) {
    return (appWindow.deviceOrientation & Silica.Orientation.LandscapeMask) || Silica.Screen.sizeCategory === Silica.Screen.Large || Silica.Screen.sizeCategory === Silica.Screen.ExtraLarge
}