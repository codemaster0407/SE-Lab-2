from dash import Dash, dcc
import dash_bootstrap_components as dbc

app = Dash(__name__, external_stylesheets=[dbc.themes.SOLAR])
mytext = dcc.Markdown(children = '')
myInput = dbc.Input(value = "Hello World")

app.layout = dbc.Container([mytext,myInput])

@app.callback(
    Output(mytext,component_property = 'children'),
    [Input(myInput, component_property = 'value')]
)

def update_title(user_input):
    return user_input

app.run_server(port = 8851)