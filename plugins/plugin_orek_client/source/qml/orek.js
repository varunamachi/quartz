.pragma library
var token = "";
var address = ""
//var serverAddress = "xhr://localhost:8000/v0/in"

function request(verb, endpoint, obj, callback, errCallback) {
    if( token === "") {
        return
    }
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if(xhr.readyState === XMLHttpRequest.DONE) {
            if(xhr.status === 200) {
                if(callback) callback(xhr.responseText);
            } else if (xhr.status === 401 ) {
                token = "";
                if(errCallback) errCallback(xhr.responseText)
            } else {
                if(errCallback) errCallback(xhr.responseText)
            }
        }
    }
    var url = address + "/v0/in" + (endpoint ? ('/' + endpoint) :'' )
    xhr.open(verb, url);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.setRequestHeader('Accept', 'application/json');
    var header = "Bearer " + token;
    xhr.setRequestHeader("Authorization", header);
    var data = obj ? JSON.stringify(obj) : '';
    xhr.send(data)
}

function login(userName, password, callback, errCallback) {
    var xhr = new XMLHttpRequest();
    var url = address + "/v0/login";
    var params = "username=" + userName + "&password=" + password;
    xhr.open("POST", url);
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhr.setRequestHeader("Content-length", params.length);
    xhr.setRequestHeader("Connection", "close");
    xhr.onreadystatechange = function() {
        if(xhr.readyState === XMLHttpRequest.DONE) {
            if(xhr.status === 200) {
                var obj = JSON.parse(xhr.responseText)
                token = obj["token"]
                if(callback) callback()
            } else {
                if(errCallback) errCallback(xhr.responseText)
            }
        }
    }
    xhr.send(params);
}


function getAllUsers(callback, errCallback) {
    request("GET", "users", null, callback, errCallback);
}

function getUser(userName, callback, errCallback) {
    request("GET", "users/" + userName, callback, errCallback );
}

function createUser(obj, callback, errCallback) {
    request("POST", "users", obj, callback, errCallback);
}

function updateUser(obj, callback, errCallback) {
    request("PUT", "users", obj, callback, errCallback);
}

function deleteUser(userName, callback, errCallback) {
    request("DELETE", "users/" + userName, callback, errCallback );
}

function getAllGroups(callback, errCallback) {
    request("GET", "groups", null, callback, errCallback);
}

function getGroup(groupName, callback, errCallback) {
    request("GET", "groups/" + groupName, callback, errCallback );
}

function deleteGroup(groupName, callback, errCallback) {
    request("DELETE", "groups/" + groupName, callback, errCallback );
}

function createGroup(obj, callback, errCallback) {
    request("POST", "groups", obj, callback, errCallback);
}

function updateGroup(obj, callback, errCallback) {
    request("PUT", "groups", obj, callback, errCallback);
}

function getAllEndpoints(callback, errCallback) {
    request("GET", "endpoints", null, callback, errCallback);
}

function getEndpoint(endpointName, callback, errCallback) {
    request("GET", "endpoints/" + endpointName, callback, errCallback );
}

function deleteEndpoint(endpointName, callback, errCallback) {
    request("DELETE", "endpoints/" + endpointName, callback, errCallback );
}

function createEndpoint(obj, callback, errCallback) {
    request("POST", "endpoints", obj, callback, errCallback);
}

function updateEndpoint(obj, callback, errCallback) {
    request("PUT", "endpoints", obj, callback, errCallback);
}

function getAllVariables(callback, errCallback) {
    request("GET", "variables", null, callback, errCallback);
}

function getVariable(variableName, callback, errCallback) {
    request("GET", "variables/" + variableName, callback, errCallback );
}

function deleteVariable(variableName, callback, errCallback) {
    request("DELETE", "variables/" + variableName, callback, errCallback );
}

function createVariable(obj, callback, errCallback) {
    request("POST", "variables", obj, callback, errCallback);
}

function updateVariable(obj, callback, errCallback) {
    request("PUT", "variables", obj, callback, errCallback);
}

function getAllParameters(callback, errCallback) {
    request("GET", "parameters", null, callback, errCallback);
}

function getParameter(parameterName, callback, errCallback) {
    request("GET", "parameters/" + variableName, callback, errCallback );
}

function deleteParameter(parameterName, callback, errCallback) {
    request("DELETE", "parameters/" + variableName, callback, errCallback );
}

function createParameter(obj, callback, errCallback) {
    request("POST", "parameters", obj, callback, errCallback);
}

function updateParameter(obj, callback, errCallback) {
    request("PUT", "parameters", obj, callback, errCallback);
}


