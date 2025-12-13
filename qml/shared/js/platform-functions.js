.pragma library

// Fallback platform functions

function formatDate(timestamp, formatType) {
    return Qt.formatDate(new Date(timestamp * 1000), formatType)
}

function getDateTimeElapsed(timestamp) {
    // FIXME: this is wrong!!
    return formatDate(timestamp, Qt.DefaultLocaleShortDate)
}

function getDateTimeTimepoint(timestamp) {
    // FIXME: this is wrong!!
    return formatDate(timestamp, Qt.DefaultLocaleShortDate)
}

function getDateTimeTimepointRelative(timestamp) {
    // FIXME: this is wrong!!
    return formatDate(timestamp, Qt.DefaultLocaleShortDate)
}

function isWidescreen(appWindow) {
    return false
}