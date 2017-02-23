
.import qz.app 1.0 as Qz

function showResult(dialog, str) {
    var resultObj = JSON.parse(str)
    title: qsTr("Orek %s", resultObj.operation)
    dialog.text = resultObj.message
    dialog.icon = resultObj.error === "" ? StandardIcon.Information
                                         : StandardIcon.Critical
    dialog.visible = true
}


function logInfo(msg) {
    Qz.Service.info( "Orek", msg)
}

function logError(msg) {
    Qz.Service.error("Orek", msg)
}

function showResult(resultStr) {
    var resultObj = JSON.parse(resultStr)
    if(resultObj.error) {
        Qz.Service.error("Orek", resultObj.message)
        Qz.Service.statusFailure(resultObj.operation, resultObj.message)
    }
    else {
        Qz.Service.info("Orek", resultObj.message)
        Qz.Service.statusSuccess(resultObj.operation, resultObj.message)
    }
}


function confirm(operation, question, callback) {
    return Qz.Service.confirm(operation, question)
}


