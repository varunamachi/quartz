
var token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhZG1pbiI6dHJ1ZSwiZXhwIjoxNDg3MTQ5NzI2LCJuYW1lIjoidHdvIn0.zuUVA88fym8u3vwQ-0ZvgIs7CrxneTC9Qdi-EEm_Yo8";
var serverAddress = "http://localhost:8000/v0/in"

function request(verb, endpoint, obj, callback, errCallback) {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if(xhr.readyState === XMLHttpRequest.DONE) {
            if(xhr.status === 200) {
                if(callback) callback(xhr.responseText.toString());
            } else if (xhr.status === 401 ) {
//                token = "";
                if(errCallback) errCallback(xhr.responseText.toString())
            }else {
                if(errCallback) errCallback(xhr.responseText.toString())
            }
        }
    }
    var url = serverAddress + (endpoint ? ('/' + endpoint) :'' )
    xhr.open(verb, url);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.setRequestHeader('Accept', 'application/json');
    console.log(token)
    var header = "Bearer " + token;
    xhr.setRequestHeader("Authorization", header);
    var data = obj ? JSON.stringify(obj) : '';
    xhr.send(data)
}

function login(userName, password, callback, errCallback) {
    var http = new XMLHttpRequest();
    var url = serverAddress + "/login";
    var params = "username=" + userName + "&password=" + password;
    http.open("POST", url);

    //Send the proper header information along with the request
    http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    http.setRequestHeader("Content-length", params.length);
    http.setRequestHeader("Connection", "close");
    http.onreadystatechange = function() {
        if(xhr.readyState === XMLHttpRequest.DONE && http.status === 200) {
            if(callback) callback()
        } else {
            if(errCallback) errCallback(http.responseText.toString())
        }
    }
    http.send(params);
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


