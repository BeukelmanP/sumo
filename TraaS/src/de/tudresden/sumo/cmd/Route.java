/*   
    Copyright (C) 2013 Mario Krumnow, Dresden University of Technology

    This file is part of TraaS.

    TraaS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    TraaS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TraaS.  If not, see <http://www.gnu.org/licenses/>.
*/

package de.tudresden.sumo.cmd;
import de.tudresden.sumo.config.Constants;
import de.tudresden.sumo.util.SumoCommand;
import de.tudresden.ws.container.SumoStringList;

public class Route {

	//getter methods

	/**
	 * Returns the subscription results for the last time step and the given route.
	 */

	public static SumoCommand getEdges(String routeID){
		return new SumoCommand(Constants.CMD_GET_ROUTE_VARIABLE, Constants.VAR_EDGES, routeID, Constants.RESPONSE_GET_ROUTE_VARIABLE, Constants.TYPE_STRINGLIST);
	}

	/**
	 * Returns a list of all routes in the network.
	 */

	public static SumoCommand getIDList(){
		return new SumoCommand(Constants.CMD_GET_ROUTE_VARIABLE, Constants.ID_LIST, "", Constants.RESPONSE_GET_ROUTE_VARIABLE, Constants.TYPE_STRINGLIST);
	}

	//setter methods

	/**
	 * add
	 */

	public static SumoCommand add(String routeID, SumoStringList edges){

		return new SumoCommand(Constants.CMD_SET_ROUTE_VARIABLE, Constants.VAR_ROUTE, routeID, edges);
	}


}